#ifndef TARIF_H
#define TARIF_H

#include "parkir.h"
#include <time.h>

/* Kode jenis kendaraan mengikuti dokumen rancangan sistem parkir kelompok:
   1 = truk/pengangkut barang, 2 = mobil, 3 = motor.
   Pastikan nilainya sama dengan yang digunakan di parkir.h. */
#define JENIS_TRUK  1
#define JENIS_MOBIL 2
#define JENIS_MOTOR 3

#define HARI_WEEKDAY 0
#define HARI_WEEKEND 1

#define TARIF_TRUK_PER_JAM  8000
#define TARIF_MOBIL_PER_JAM 4000
#define TARIF_MOTOR_PER_JAM 2000

#define MAKS_TRUK_24_JAM  40000
#define MAKS_MOBIL_24_JAM 20000
#define MAKS_MOTOR_24_JAM 10000

/* Nominal biaya singkat adalah usulan awal kelompok. */
#define PERSEN_BIAYA_SINGKAT 25
#define PERSEN_BIAYA_SINGKAT_TAMBAHAN 75

/* Nominal booking masih perlu persetujuan ketua kelompok. */
#define BOOKING_WEEKDAY 3000
#define BOOKING_WEEKEND 5000

#define DENDA_TRUK  25000
#define DENDA_MOBIL 25000
#define DENDA_MOTOR 10000

#define DISKON_WEEKDAY 10
#define DISKON_WEEKEND 15

/* Menyimpan rincian hasil perhitungan untuk struk/laporan. */
typedef struct {
    int durasiMenit;
    int tarifParkir;
    int diskonParkir;
    int biayaBooking;
    int denda;
    int totalBayar;
} RincianTarif;

/* Menghitung durasi. Hasil dibulatkan ke atas ke menit berikutnya.
   Mengembalikan -1 jika waktu tidak valid atau waktu keluar lebih awal. */
int hitungDurasi(time_t waktuMasuk, time_t waktuKeluar);

/* Menghitung tarif parkir berdasarkan jenis dan durasi dalam menit.
   Maksimum diterapkan untuk setiap blok/periode 24 jam.
   Mengembalikan -1 jika jenis kendaraan atau durasi tidak valid. */
int hitungTarif(int jenis, int durasiMenit);

/* Menghitung denda. tiketHilang bernilai 1 jika tiket hilang, selain itu 0. */
int hitungDenda(int jenis, int tiketHilang);

/* Mengembalikan nominal diskon, bukan total setelah diskon.
   jenisHari gunakan HARI_WEEKDAY atau HARI_WEEKEND. */
int hitungDiskonMember(int subtotal, int isMember, int jenisHari);

/* Mengembalikan biaya booking tetap berdasarkan hari.
   Booking hanya untuk member; diskon member tidak diterapkan pada booking. */
int hitungBiayaBooking(int jenisHari);

/* Mengisi seluruh rincian pembayaran. isBooking dan tiketHilang bernilai 0/1.
   Biaya booking tidak mendapatkan diskon member.
   jenisHari adalah hari kendaraan keluar untuk diskon parkir.
   Mengembalikan 1 jika berhasil, 0 jika input tidak valid. */
int prosesPerhitunganTarif(int jenis, int durasiMenit,
                           int isMember, int jenisHari,
                           int isBooking, int tiketHilang,
                           RincianTarif *rincian);

/* Menampilkan struk dari hasil prosesPerhitunganTarif(). */
void cetakStruk(const RincianTarif *rincian);

/* Membaca data kendaraan langsung dari satu slot array parkir. */
int prosesTarifSlot(
    Slotparkir *slot,
    int jenisHari,
    RincianTarif *rincian
);

#endif

