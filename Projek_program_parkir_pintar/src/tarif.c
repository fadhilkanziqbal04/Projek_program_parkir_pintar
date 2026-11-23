#include <stdio.h>
#include "tarif.h"
#include "../include/parkir.h"

#define MENIT_PER_JAM 60
#define MENIT_PER_HARI 1440

/* Mengambil tarif per jam sesuai jenis kendaraan. */
static int ambilTarifPerJam(int jenis) {
    switch (jenis) {
        case JENIS_TRUK:  return TARIF_TRUK_PER_JAM;
        case JENIS_MOBIL: return TARIF_MOBIL_PER_JAM;
        case JENIS_MOTOR: return TARIF_MOTOR_PER_JAM;
        default:          return -1;
    }
}

/* Mengambil batas maksimum biaya untuk satu periode 24 jam. */
static int ambilMaksimum24Jam(int jenis) {
    switch (jenis) {
        case JENIS_TRUK:  return MAKS_TRUK_24_JAM;
        case JENIS_MOBIL: return MAKS_MOBIL_24_JAM;
        case JENIS_MOTOR: return MAKS_MOTOR_24_JAM;
        default:          return -1;
    }
}

/* Tarif untuk satu potongan waktu yang panjangnya maksimal 24 jam. */
static int hitungTarifSatuPeriode(int tarifPerJam, int durasiMenit) {
    int biaya;
    int sisaMenit;
    int jamPenuh;

    if (durasiMenit <= 0) {
        return 0;
    }

    /* Ketentuan biaya singkat sebelum satu jam. */
    if (durasiMenit <= 30) {
        return (tarifPerJam * PERSEN_BIAYA_SINGKAT + 50) / 100;
    }

    if (durasiMenit < 60) {
        return (tarifPerJam * PERSEN_BIAYA_SINGKAT_TAMBAHAN + 50) / 100;
    }

    /* Jam pertama selalu dikenakan tarif satu jam. */
    biaya = tarifPerJam;
    sisaMenit = durasiMenit - MENIT_PER_JAM;

    /* Setiap jam penuh setelah jam pertama dikenakan tarif penuh. */
    jamPenuh = sisaMenit / MENIT_PER_JAM;
    biaya += jamPenuh * tarifPerJam;
    sisaMenit %= MENIT_PER_JAM;

    /* Setelah jam pertama, sisa sampai 30 menit tidak menambah biaya.
       Jika lebih dari 30 menit, tambahkan setengah tarif per jam. */
    if (sisaMenit > 30) {
        biaya += (tarifPerJam + 1) / 2;
    }

    return biaya;
}

int hitungDurasi(time_t waktuMasuk, time_t waktuKeluar) {
    double selisihDetik;
    long totalDetik;

    if (waktuKeluar < waktuMasuk) {
        return -1;
    }

    selisihDetik = difftime(waktuKeluar, waktuMasuk);
    totalDetik = (long)selisihDetik;

    /* Pembulatan ke atas: 1 detik tetap dihitung 1 menit. */
    return (int)((totalDetik + 59) / 60);
}

int hitungTarif(int jenis, int durasiMenit) {
    int tarifPerJam = ambilTarifPerJam(jenis);
    int maksimum = ambilMaksimum24Jam(jenis);
    int total = 0;
    int sisaDurasi = durasiMenit;

    if (tarifPerJam < 0 || maksimum < 0 || durasiMenit < 0) {
        return -1;
    }

    if (durasiMenit == 0) {
        return 0;
    }

    /* Setiap blok 24 jam memiliki batas maksimum masing-masing. */
    while (sisaDurasi > 0) {
        int durasiPeriode;
        int biayaPeriode;

        if (sisaDurasi >= MENIT_PER_HARI) {
            durasiPeriode = MENIT_PER_HARI;
        } else {
            durasiPeriode = sisaDurasi;
        }

        biayaPeriode = hitungTarifSatuPeriode(tarifPerJam, durasiPeriode);
        if (biayaPeriode > maksimum) {
            biayaPeriode = maksimum;
        }

        total += biayaPeriode;
        sisaDurasi -= durasiPeriode;
    }

    return total;
}

int hitungDenda(int jenis, int tiketHilang) {
    if (tiketHilang != 1) {
        return 0;
    }

    switch (jenis) {
        case JENIS_TRUK:  return DENDA_TRUK;
        case JENIS_MOBIL: return DENDA_MOBIL;
        case JENIS_MOTOR: return DENDA_MOTOR;
        default:          return -1;
    }
}

int hitungDiskonMember(int subtotal, int isMember, int jenisHari) {
    int persenDiskon;

    if (subtotal < 0) {
        return -1;
    }

    if (isMember != 1) {
        return 0;
    }

    if (jenisHari == HARI_WEEKDAY) {
        persenDiskon = DISKON_WEEKDAY;
    } else if (jenisHari == HARI_WEEKEND) {
        persenDiskon = DISKON_WEEKEND;
    } else {
        return -1;
    }

    /* Pembulatan ke rupiah terdekat tanpa memerlukan math.h. */
    return (subtotal * persenDiskon + 50) / 100;
}

int hitungBiayaBooking(int jenisHari) {
    if (jenisHari == HARI_WEEKDAY) {
        return BOOKING_WEEKDAY;
    }
    if (jenisHari == HARI_WEEKEND) {
        return BOOKING_WEEKEND;
    }
    return -1;
}

int prosesPerhitunganTarif(int jenis, int durasiMenit,
                           int isMember, int jenisHari,
                           int isBooking, int tiketHilang,
                           RincianTarif *rincian) {
    int biayaParkir;
    int biayaBooking = 0;
    int denda;

    if (rincian == NULL || (isMember != 0 && isMember != 1) ||
        (isBooking != 0 && isBooking != 1) ||
        (tiketHilang != 0 && tiketHilang != 1) ||
        (jenisHari != HARI_WEEKDAY && jenisHari != HARI_WEEKEND)) {
        return 0;
    }

    biayaParkir = hitungTarif(jenis, durasiMenit);
    denda = hitungDenda(jenis, tiketHilang);

    if (biayaParkir < 0 || denda < 0) {
        return 0;
    }

    if (isBooking == 1) {
        biayaBooking = hitungBiayaBooking(jenisHari);
        if (biayaBooking < 0 || isMember != 1) {
            return 0; /* Booking hanya boleh dilakukan member. */
        }
    }

    rincian->durasiMenit = durasiMenit;
    rincian->tarifParkir = biayaParkir;
    rincian->diskonParkir = hitungDiskonMember(biayaParkir, isMember, jenisHari);
    rincian->biayaBooking = biayaBooking;
    rincian->denda = denda;

    if (rincian->diskonParkir < 0) {
        return 0;
    }

    rincian->totalBayar = (biayaParkir - rincian->diskonParkir) +
                          biayaBooking + denda;
    return 1;
}

void cetakStruk(const RincianTarif *rincian) {
    if (rincian == NULL) {
        printf("Data struk tidak tersedia.\n");
        return;
    }

    printf("\n========== STRUK SMARTPARK ==========\n");
    printf("Durasi parkir       : %d menit\n", rincian->durasiMenit);
    printf("Tarif parkir        : Rp%d\n", rincian->tarifParkir);
    printf("Diskon parkir       : Rp%d\n", rincian->diskonParkir);
    printf("Biaya booking       : Rp%d\n", rincian->biayaBooking);
    printf("Denda tiket hilang  : Rp%d\n", rincian->denda);
    printf("-------------------------------------\n");
    printf("TOTAL PEMBAYARAN    : Rp%d\n", rincian->totalBayar);
    printf("=====================================\n");
}

int prosesTarifSlot(
    Slotparkir *slot,
    int jenisHari,
    RincianTarif *rincian
) {
    int waktuMasuk;
    int waktuKeluar;
    int durasiMenit;
    int berhasil;

    if (slot == NULL || rincian == NULL) {
        return 0;
    }

    /* Memastikan slot berisi kendaraan. */
    if (slot->terisi != 1) {
        return 0;
    }

    /* Memastikan data waktu valid. */
    if (slot->waktumasuk_hour < 0 ||
        slot->waktumasuk_hour > 23 ||
        slot->waktukeluar_hour < 0 ||
        slot->waktukeluar_hour > 23 ||
        slot->waktumasuk_mnt < 0 ||
        slot->waktumasuk_mnt > 59 ||
        slot->waktukeluar_mnt < 0 ||
        slot->waktukeluar_mnt > 59) {
        return 0;
    }

    /* Mengubah jam dan menit menjadi total menit. */
    waktuMasuk =
        (slot->waktumasuk_hour * 60) + slot->waktumasuk_mnt;

    waktuKeluar =
        (slot->waktukeluar_hour * 60) + slot->waktukeluar_mnt;

    /* Menghitung durasi, termasuk jika melewati tengah malam. */
    durasiMenit = waktuKeluar - waktuMasuk;

    if (durasiMenit < 0) {
        durasiMenit += 24 * 60;
    }

    /* Menghitung tarif berdasarkan data dari Slotparkir. */
    berhasil = prosesPerhitunganTarif(
        slot->kendaraan,
        durasiMenit,
        slot->isMember,
        jenisHari,
        slot->booking,
        slot->karcishilang,
        rincian
    );

    if (!berhasil) {
        return 0;
    }

    /* Menyimpan total pembayaran ke array parkir. */
    slot->tarif = (float)rincian->totalBayar;

    return 1;
}
