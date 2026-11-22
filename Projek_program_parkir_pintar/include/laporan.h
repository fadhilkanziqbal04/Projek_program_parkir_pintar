#ifndef LAPORAN_H
#define LAPORAN_H

#define FOLDER_LAPORAN "laporan"     /* folder harus sudah ada (ada .gitkeep di repo) */
#define FOLDER_BACKUP  "backup"      /* folder harus sudah ada (ada .gitkeep di repo) */

/* Salin SEMUA riwayat ke file txt yang bisa dibaca: laporan/laporan_YYYYMMDD.txt,
   lalu otomatis membuat salinannya di backup/laporan_YYYYMMDD_HHMMSS.txt.
   Return 1 jika keduanya berhasil. */
int simpanLaporan(void);

/* Submenu untuk menu utama nomor "Laporan & Riwayat Transaksi" (dipanggil dari menu.c) */
const char *pathLaporanTerakhir(void);   /* path file laporan yang terakhir disimpan */

void menuLaporanRiwayat(void);

#endif
