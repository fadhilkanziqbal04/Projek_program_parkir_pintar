#ifndef RIWAYATTRANSAKSI_H
#define RIWAYATTRANSAKSI_H

#include <stdio.h>
#include "parkir.h"      /* milik teman: struct Slotparkir */

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

/* Dipanggil setiap kendaraan masuk, keluar, atau reservasi. Return 1 jika berhasil, 0 jika ditolak.
   Hari diambil otomatis dari jam sistem (struct teman tidak menyimpan hari).
   Contoh: catatRiwayat(EVENT_MASUK, p->plat, p->kendaraan, p->isMember, p->waktumasuk_hour, p->waktumasuk_mnt, 0); */
int  catatRiwayat(int kejadian, const char *plat, int jenis, int member,
                  int jam, int menit, double biaya);

/* Sama seperti catatRiwayat, tetapi hari diisi sendiri (1=Senin ... 7=Minggu). Dipakai untuk uji. */
int  catatRiwayatDenganHari(int kejadian, const char *plat, int jenis, int member,
                            int hari, int jam, int menit, double biaya);

/* Pemanggilan singkat: data diambil langsung dari slot (plat, jenis, member, jam, menit).
   catatMasuk      -> waktumasuk_hour/mnt        (kendaraan masuk atau reservasi tiba)
   catatReservasi  -> waktureservasi_hour/mnt    (reservasi dibuat)
   catatKeluar     -> waktukeluar_hour/mnt + biaya (panggil SEBELUM kosongkan_array) */
int  catatMasuk(const Slotparkir *s);
int  catatReservasi(const Slotparkir *s);
int  catatKeluar(const Slotparkir *s, double biaya);

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
