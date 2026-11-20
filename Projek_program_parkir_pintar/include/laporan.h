#ifndef LAPORAN_H
#define LAPORAN_H

#define FILE_LAPORAN   "laporan_riwayat.txt"
#define FOLDER_BACKUP  "backup"      /* folder harus sudah ada */

/* Salin SEMUA riwayat ke file txt yang bisa dibaca, lalu otomatis membuat salinannya
   di folder backup (backup/laporan_YYYYMMDD_HHMMSS.txt). Return 1 jika keduanya berhasil. */
int simpanLaporan(void);

/* Submenu untuk menu utama nomor "Laporan & Riwayat Transaksi" (dipanggil dari menu.c) */
void menuLaporanRiwayat(void);

#endif
