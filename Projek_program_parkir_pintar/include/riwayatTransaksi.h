#ifndef RIWAYATTRANSAKSI_H
#define RIWAYATTRANSAKSI_H

#include <stdio.h>
#include "parkir.h"

#define MAX_RIWAYAT     1000
#define JUMLAH_TERBARU  5 

#define EVENT_MASUK      1
#define EVENT_KELUAR     2
#define EVENT_RESERVASI  3

typedef struct {
    int    kejadian;
    char   plat[15];
    int    jenis;
    int    member;
    int    hari;
    int    jam;
    int    menit;
    double biaya;
} Riwayat;

extern Riwayat riwayat[MAX_RIWAYAT];
extern int jumlahRiwayat;

int  catatRiwayat(int kejadian, const char *plat, int jenis, int member,
                  int jam, int menit, double biaya);

int  catatRiwayatDenganHari(int kejadian, const char *plat, int jenis, int member,
                            int hari, int jam, int menit, double biaya);

int  catatMasuk(const Slotparkir *s);
int  catatReservasi(const Slotparkir *s);
int  catatKeluar(const Slotparkir *s, double biaya);

void tampilRiwayatTerbaru(void); 
const Riwayat *riwayatTerbaru(int urutan);
double totalPendapatan(void);

const char *namaKejadian(int kejadian);
const char *namaJenisKendaraan(int jenis);
const char *namaHari(int hari);
void cetakRiwayatGaris(FILE *f);
void cetakRiwayatHeader(FILE *f);
void cetakRiwayatBaris(FILE *f, int no, const Riwayat *r);

#endif
