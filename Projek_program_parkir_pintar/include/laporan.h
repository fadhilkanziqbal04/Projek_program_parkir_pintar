#ifndef LAPORAN_H
#define LAPORAN_H
#include <time.h>

#define MAX_TRANSAKSI 1000

typedef struct {
    char   plat[15];
    int    jenis;         /* 1 motor, 2 mobil, 3 truk */
    int    vip;           /* 1 = layanan VIP */
    time_t waktuMasuk;
    time_t waktuKeluar;
    double diskon;        /* potongan (rupiah) */
    double biaya;         /* biaya akhir */
} Transaksi;

extern Transaksi riwayat[MAX_TRANSAKSI];
extern int jumlahRiwayat;

int    tambahRiwayat(const char *plat, int jenis, int vip,
                     time_t masuk, time_t keluar, double diskon, double biaya);
void   tampilRiwayat(void);
double totalPendapatan(void);
int    cariRiwayatPlat(const char *plat);
void   menuLaporan(void);

#endif