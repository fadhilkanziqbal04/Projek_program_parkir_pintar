#ifndef MENU_H
#define MENU_H

// Fungsi input dan validasi
int inputPilihan(const char *prompt);
int validasiPilihan(int pilihan, const int pilihanValid[], int jumlah);
int inputValid(const char *prompt, const int pilihanValid[], int jumlah);

// Menu utama
int tampilkanMenu(void);

// Submenu
int tampilkanSubmenuKendaraanMasuk(void);
int tampilkanSubmenuReservasi(void);
int tampilkanSubmenuDenah(void);
int tampilkanSubmenuBooking(void);
int tampilkanSubmenuKendaraanKeluar(void);
int tampilkanSubmenuRiwayat(void);

#endif