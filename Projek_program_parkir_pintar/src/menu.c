#include <stdio.h>
#include <limits.h>
#include "menu.h"

// =================================
// FUNGSI MENERIMA INPUT
// =================================

int inputPilihan(const char *prompt) {
    char input[100];
    int angka = 0;
    int i = 0;

    printf("%s", prompt);

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return -1;
    }

    // Input kosong
    if (input[0] == '\n') {
        return -1;
    }

    // Mengecek setiap karakter input
    while (input[i] != '\n' && input[i] != '\0') {

        // Input harus berupa angka
        if (input[i] < '0' || input[i] > '9') {
            return -1;
        }

        // Mencegah angka terlalu besar
        if (angka > (INT_MAX - (input[i] - '0')) / 10) {
            return -1;
        }

        angka = angka * 10 + (input[i] - '0');
        i++;
    }

    return angka;
}

// =================================
// FUNGSI VALIDASI PILIHAN
// =================================

int validasiPilihan(int pilihan, const int pilihanValid[], int jumlah) {
    int i;

    for (i = 0; i < jumlah; i++) {
        if (pilihan == pilihanValid[i]) {
            return 1;
        }
    }

    return 0;
}

// =================================
// FUNGSI INPUT DAN VALIDASI
// =================================

int inputValid(const char *prompt, const int pilihanValid[], int jumlah) {
    int pilihan;

    do {
        pilihan = inputPilihan(prompt);

        if (!validasiPilihan(pilihan, pilihanValid, jumlah)) {
            printf("Input tidak valid! Silakan coba lagi.\n");
        }

    } while (!validasiPilihan(pilihan, pilihanValid, jumlah));

    return pilihan;
}

// =================================
// MENU UTAMA
// =================================

int tampilkanMenu(void) {
    int pilihan;
    int opsi[] = {0, 1, 2, 3, 4, 5};

    printf("\n");
    printf("========================================\n");
    printf("        SMARTPARK - SISTEM PARKIR\n");
    printf("========================================\n");
    printf(" 1. Kendaraan Masuk\n");
    printf(" 2. Kendaraan Keluar\n");
    printf(" 3. Lihat Denah Parkir\n");
    printf(" 4. Booking Slot\n");
    printf(" 5. Laporan & Riwayat Transaksi\n");
    printf(" 0. Keluar\n");
    printf("========================================\n");

    pilihan = inputValid("Pilih menu: ", opsi, 6);

    return pilihan;
}

// =================================
// SUBMENU KENDARAAN MASUK
// =================================

int tampilkanSubmenuKendaraanMasuk(void) {
    int pilihan;
    int opsi[] = {0, 1, 2};

    printf("\n===== KENDARAAN MASUK =====\n");
    printf("1. Reservasi\n");
    printf("2. Parkir Langsung\n");
    printf("0. Kembali\n");

    pilihan = inputValid("Pilih menu: ", opsi, 3);

    return pilihan;
}

// =================================
// SUBMENU RESERVASI
// =================================

int tampilkanSubmenuReservasi(void) {
    int pilihan;
    int opsi[] = {0, 1, 2, 10};

    printf("\n===== RESERVASI =====\n");
    printf("1. Buat Reservasi\n");
    printf("2. Reservasi Tiba\n");
    printf("0. Kembali\n");
    printf("10. Kembali ke Menu Utama\n");

    pilihan = inputValid("Pilih menu: ", opsi, 4);

    return pilihan;
}

// =================================
// SUBMENU KENDARAAN KELUAR
// =================================

int tampilkanSubmenuKendaraanKeluar(void) {
    int pilihan;
    int opsi[] = {0};

    printf("\n===== KENDARAAN KELUAR =====\n");
    printf("0. Kembali\n");

    pilihan = inputValid("Pilih menu: ", opsi, 1);

    return pilihan;
}

// =================================
// SUBMENU DENAH PARKIR
// =================================

int tampilkanSubmenuDenah(void) {
    int pilihan;
    int opsi[] = {0, 1, 2};

    printf("\n===== DENAH PARKIR =====\n");
    printf("1. Tampilkan Denah\n");
    printf("2. Cari Kendaraan\n");
    printf("0. Kembali\n");

    pilihan = inputValid("Pilih menu: ", opsi, 3);

    return pilihan;
}

// =================================
// SUBMENU BOOKING SLOT
// =================================

int tampilkanSubmenuBooking(void) {
    int pilihan;
    int opsi[] = {0, 1};

    printf("\n===== BOOKING SLOT =====\n");
    printf("1. Hapus Booking\n");
    printf("0. Kembali\n");

    pilihan = inputValid("Pilih menu: ", opsi, 2);

    return pilihan;
}

// =================================
// SUBMENU LAPORAN & RIWAYAT
// =================================

int tampilkanSubmenuRiwayat(void) {
    int pilihan;
    int opsi[] = {0};

    printf("\n===== LAPORAN & RIWAYAT TRANSAKSI =====\n");
    printf("0. Kembali\n");

    pilihan = inputValid("Pilih menu: ", opsi, 1);

    return pilihan;
}