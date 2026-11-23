#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../include/riwayatTransaksi.h"

Riwayat riwayat[MAX_RIWAYAT];
int jumlahRiwayat = 0;

const char *namaKejadian(int kejadian) {
    switch (kejadian) {
        case EVENT_MASUK:     return "Masuk";
        case EVENT_KELUAR:    return "Keluar";
        case EVENT_RESERVASI: return "Reservasi";
        default:              return "?";
    }
}

const char *namaJenisKendaraan(int jenis) {
    switch (jenis) {
        case 1:  return "Truk";      /* mobil/truk pengangkut barang */
        case 2:  return "Mobil";     /* mobil penumpang */
        case 3:  return "Motor";
        default: return "?";
    }
}

const char *namaHari(int hari) {
    static const char *nama[8] = {"?", "Sen", "Sel", "Rab", "Kam", "Jum", "Sab", "Min"};
    if (hari < 1 || hari > 7) return nama[0];
    return nama[hari];
}

void cetakRiwayatGaris(FILE *f) {
    fprintf(f, "------------------------------------------------------------------\n");
}

void cetakRiwayatHeader(FILE *f) {
    cetakRiwayatGaris(f);
    fprintf(f, "%-3s %-10s %-12s %-6s %-6s %-9s %10s\n",
            "No", "Kejadian", "Plat", "Jenis", "Member", "Waktu", "Biaya");
    cetakRiwayatGaris(f);
}

void cetakRiwayatBaris(FILE *f, int no, const Riwayat *r) {
    char waktu[16], biaya[16];
    snprintf(waktu, sizeof(waktu), "%s %02d:%02d", namaHari(r->hari), r->jam, r->menit);
    if (r->kejadian == EVENT_KELUAR) snprintf(biaya, sizeof(biaya), "Rp%.0f", r->biaya);
    else snprintf(biaya, sizeof(biaya), "-");
    fprintf(f, "%-3d %-10s %-12s %-6s %-6s %-9s %10s\n",
            no, namaKejadian(r->kejadian), r->plat, namaJenisKendaraan(r->jenis),
            r->member ? "Ya" : "-", waktu, biaya);
}

int catatRiwayatDenganHari(int kejadian, const char *plat, int jenis, int member,
                           int hari, int jam, int menit, double biaya) {
    Riwayat *r;
    if (jumlahRiwayat >= MAX_RIWAYAT || plat == NULL) return 0;
    if (kejadian < EVENT_MASUK || kejadian > EVENT_RESERVASI) return 0;
    if (jenis < 1 || jenis > 3) return 0;
    if (member != 0 && member != 1) return 0;
    if (hari < 1 || hari > 7 || jam < 0 || jam > 23 || menit < 0 || menit > 59) return 0;
    if (biaya < 0) return 0;

    r = &riwayat[jumlahRiwayat++];
    strncpy(r->plat, plat, sizeof(r->plat) - 1);
    r->plat[sizeof(r->plat) - 1] = '\0';
    r->kejadian = kejadian;
    r->jenis = jenis;
    r->member = member;
    r->hari = hari;
    r->jam = jam;
    r->menit = menit;
    r->biaya = biaya;
    return 1;
}

int catatRiwayat(int kejadian, const char *plat, int jenis, int member,
                 int jam, int menit, double biaya) {
    time_t sekarang = time(NULL);
    struct tm *p = localtime(&sekarang);
    int hari = 1;

    if (p != NULL) hari = (p->tm_wday == 0) ? 7 : p->tm_wday;   /* 0=Minggu -> 7 */
    return catatRiwayatDenganHari(kejadian, plat, jenis, member, hari, jam, menit, biaya);
}

int catatMasuk(const Slotparkir *s) {
    if (s == NULL) return 0;
    return catatRiwayat(EVENT_MASUK, s->plat, s->kendaraan, s->isMember,
                        s->waktumasuk_hour, s->waktumasuk_mnt, 0);
}

int catatReservasi(const Slotparkir *s) {
    if (s == NULL) return 0;
    return catatRiwayat(EVENT_RESERVASI, s->plat, s->kendaraan, s->isMember,
                        s->waktureservasi_hour, s->waktureservasi_mnt, 0);
}

int catatKeluar(const Slotparkir *s, double biaya) {
    if (s == NULL) return 0;
    return catatRiwayat(EVENT_KELUAR, s->plat, s->kendaraan, s->isMember,
                        s->waktukeluar_hour, s->waktukeluar_mnt, biaya);
}

const Riwayat *riwayatTerbaru(int urutan) {
    if (urutan < 0 || urutan >= jumlahRiwayat) return NULL;
    return &riwayat[jumlahRiwayat - 1 - urutan];
}

void tampilRiwayatTerbaru(void) {
    int i;
    const Riwayat *r;

    if (jumlahRiwayat == 0) {
        printf("Belum ada riwayat.\n");
        return;
    }
    printf("%d RIWAYAT TERBARU\n", jumlahRiwayat < JUMLAH_TERBARU ? jumlahRiwayat : JUMLAH_TERBARU);
    cetakRiwayatHeader(stdout);
    for (i = 0; i < JUMLAH_TERBARU; i++) {
        r = riwayatTerbaru(i);
        if (r == NULL) break;
        cetakRiwayatBaris(stdout, i + 1, r);
    }
    cetakRiwayatGaris(stdout);
}

double totalPendapatan(void) {
    double total = 0;
    int i;
    for (i = 0; i < jumlahRiwayat; i++)
        if (riwayat[i].kejadian == EVENT_KELUAR) total += riwayat[i].biaya;
    return total;
}
