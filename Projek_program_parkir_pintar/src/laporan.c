#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "laporan.h"
#include "riwayattransaksi.h"
#include "fileio.h"

static void tulisLaporan(FILE *f) {
    int i, masuk = 0, keluar = 0, reservasi = 0;
    char waktu[32] = "-";
    time_t sekarang = time(NULL);
    struct tm *p = localtime(&sekarang);

    if (p != NULL) strftime(waktu, sizeof(waktu), "%d-%m-%Y %H:%M", p);

    fprintf(f, "LAPORAN RIWAYAT TRANSAKSI - SMARTPARK\n");
    fprintf(f, "Dicetak: %s\n", waktu);
    cetakRiwayatHeader(f);
    for (i = 0; i < jumlahRiwayat; i++) {
        cetakRiwayatBaris(f, i + 1, &riwayat[i]);
        if (riwayat[i].kejadian == EVENT_MASUK) masuk++;
        else if (riwayat[i].kejadian == EVENT_KELUAR) keluar++;
        else if (riwayat[i].kejadian == EVENT_RESERVASI) reservasi++;
    }
    cetakRiwayatGaris(f);
    fprintf(f, "Jumlah riwayat    : %d\n", jumlahRiwayat);
    fprintf(f, "Kendaraan masuk   : %d\n", masuk);
    fprintf(f, "Kendaraan keluar  : %d\n", keluar);
    fprintf(f, "Reservasi         : %d\n", reservasi);
    fprintf(f, "Total pendapatan  : Rp%.0f\n", totalPendapatan());
}

int simpanLaporan(void) {
    FILE *f;
    char stempel[24], backup[80];
    time_t sekarang = time(NULL);
    struct tm *p = localtime(&sekarang);

    f = fopen(FILE_LAPORAN, "w");
    if (f == NULL) {
        printf("Gagal membuat %s\n", FILE_LAPORAN);
        return 0;
    }
    tulisLaporan(f);
    fclose(f);
    printf("Laporan disimpan ke %s\n", FILE_LAPORAN);

    if (p == NULL) return 0;
    strftime(stempel, sizeof(stempel), "%Y%m%d_%H%M%S", p);
    snprintf(backup, sizeof(backup), "%s/laporan_%s.txt", FOLDER_BACKUP, stempel);
    if (!salinFile(FILE_LAPORAN, backup)) {
        printf("Salinan backup gagal (pastikan folder %s/ ada)\n", FOLDER_BACKUP);
        return 0;
    }
    printf("Salinan backup: %s\n", backup);
    return 1;
}

void menuLaporanRiwayat(void) {
    char buf[32];
    int pilih;

    do {
        printf("\n== LAPORAN & RIWAYAT TRANSAKSI ==\n");
        printf(" 1. Tampilkan 5 riwayat terbaru\n");
        printf(" 2. Simpan laporan ke file txt (+ backup)\n");
        printf(" 0. Kembali\n");
        printf(" Pilih: ");
        if (fgets(buf, sizeof(buf), stdin) == NULL) return;
        pilih = atoi(buf);

        if (pilih == 1) tampilRiwayatTerbaru();
        else if (pilih == 2) simpanLaporan();
        else if (pilih != 0) printf("Pilihan tidak valid.\n");
    } while (pilih != 0);
}
