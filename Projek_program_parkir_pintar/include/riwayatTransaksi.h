#ifndef RIWAYATTRANSAKSI_H
#define RIWAYATTRANSAKSI_H

#include <stdio.h>

#define MAX_RIWAYAT     1000
#define JUMLAH_TERBARU  5      /* menu menampilkan 5 riwayat terbaru */

/* jenis kejadian */
#define EVENT_MASUK      1
#define EVENT_KELUAR     2
#define EVENT_RESERVASI  3

/* Satu baris riwayat. Waktu disimpan sebagai hari (1=Senin ... 7=Minggu), jam, dan menit. */
typedef struct {
    int    kejadian;     /* EVENT_MASUK / EVENT_KELUAR / EVENT_RESERVASI */
    char   plat[15];
    int    jenis;        /* 1 motor, 2 mobil, 3 truk */
    int    member;       /* 1 = member, 0 = bukan */
    int    hari;
    int    jam;
    int    menit;
    double biaya;        /* total biaya (hanya terisi untuk EVENT_KELUAR, selain itu 0) */
} Riwayat;

extern Riwayat riwayat[MAX_RIWAYAT];
extern int jumlahRiwayat;

/* Dipanggil setiap kendaraan masuk, keluar, atau reservasi. Return 1 jika berhasil, 0 jika ditolak. */
int  catatRiwayat(int kejadian, const char *plat, int jenis, int member,
                  int hari, int jam, int menit, double biaya);

void tampilRiwayatTerbaru(void);                 /* tampilkan 5 riwayat terbaru */
const Riwayat *riwayatTerbaru(int urutan);       /* 0 = terbaru, 1 = sebelumnya, ... ; NULL jika tidak ada */
double totalPendapatan(void);                    /* jumlah biaya semua kejadian keluar */

/* fungsi bantu tampilan (dipakai juga oleh laporan.c) */
const char *namaKejadian(int kejadian);
const char *namaJenisKendaraan(int jenis);
const char *namaHari(int hari);
void cetakRiwayatGaris(FILE *f);
void cetakRiwayatHeader(FILE *f);
void cetakRiwayatBaris(FILE *f, int no, const Riwayat *r);

#endif
