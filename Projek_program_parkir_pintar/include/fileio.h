#ifndef FILEIO_H
#define FILEIO_H

#include <stddef.h>

#define FILE_RIWAYAT "data/riwayat.dat"

/* ---- fungsi umum: bisa dipakai modul lain untuk menyimpan data apa saja ----
   Contoh (denah milik modul parkir):
     simpanBinary("data/parkir.dat", denah, sizeof(Slot), LANTAI * BARIS * KOLOM);
     muatBinary("data/parkir.dat", denah, sizeof(Slot), LANTAI * BARIS * KOLOM);
   Return 1 jika berhasil, 0 jika gagal (muatBinary: 0 juga jika file belum ada). */
int simpanBinary(const char *namaFile, const void *data, size_t ukuran, size_t jumlah);
int muatBinary(const char *namaFile, void *data, size_t ukuran, size_t jumlah);

/* ---- riwayat transaksi ---- */
int simpanRiwayat(void);
int muatRiwayat(void);

/* salin satu file apa adanya (dipakai untuk backup laporan). Return 1 jika berhasil. */
int salinFile(const char *asal, const char *tujuan);

#endif
