#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../include/laporan.h"
#include "../include/riwayatTransaksi.h"
#include "../include/fileio.h"

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

static char laporanTerakhir[96] = "";

const char *pathLaporanTerakhir(void) {
    return laporanTerakhir;
}

int simpanLaporan(void) {
    FILE *f;
    char tanggal[16], stempel[24], backup[96];
    time_t sekarang = time(NULL);
    struct tm *p = localtime(&sekarang);

    if (p == NULL) return 0;
    strftime(tanggal, sizeof(tanggal), "%Y%m%d", p);
    strftime(stempel, sizeof(stempel), "%Y%m%d_%H%M%S", p);
    snprintf(laporanTerakhir, sizeof(laporanTerakhir), "%s/laporan_%s.txt", FOLDER_LAPORAN, tanggal);

    f = fopen(laporanTerakhir, "w");
    if (f == NULL) {
        printf("Gagal membuat %s (pastikan folder %s/ ada)\n", laporanTerakhir, FOLDER_LAPORAN);
        return 0;
    }
    tulisLaporan(f);
    fclose(f);
    printf("Laporan disimpan ke %s\n", laporanTerakhir);

    snprintf(backup, sizeof(backup), "%s/laporan_%s.txt", FOLDER_BACKUP, stempel);
    if (!salinFile(laporanTerakhir, backup)) {
        printf("Salinan backup gagal (pastikan folder %s/ ada)\n", FOLDER_BACKUP);
        return 0;
    }
    printf("Salinan backup: %s\n", backup);
    return 1;
}

void menuLaporanRiwayat(void) {
    int pilih, c;

    do {
        printf("\n== LAPORAN & RIWAYAT TRANSAKSI ==\n");
        printf(" 1. Tampilkan 5 riwayat terbaru\n");
        printf(" 2. Simpan laporan ke file txt (+ backup)\n");
        printf(" 0. Kembali\n");
        printf(" Pilih: ");
        if (scanf(" %d", &pilih) != 1) {
            if (feof(stdin)) return;
            while ((c = getchar()) != '\n' && c != EOF);
            pilih = -1;
        }

        if (pilih == 1) tampilRiwayatTerbaru();
        else if (pilih == 2) simpanLaporan();
        else if (pilih != 0) printf("Pilihan tidak valid.\n");
    } while (pilih != 0);
}
