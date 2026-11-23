#ifndef FILEIO_H
#define FILEIO_H

#include <stddef.h>
#include "parkir.h"      /* milik teman: struct Slotparkir */

#define FILE_RIWAYAT "data/riwayat.dat"
#define FILE_PARKIR  "data/parkir.dat"
#define FILE_RESERVASI "data/reservasi.dat"

/* ukuran array parkir di parkir.h: Slotparkir parkir[3][50] */
#ifndef JUMLAH_LANTAI
#define JUMLAH_LANTAI   3
#endif
#ifndef SLOT_PER_LANTAI
#define SLOT_PER_LANTAI 50
#endif

/* ---- fungsi umum: bisa dipakai modul lain untuk menyimpan data apa saja ----
   Return 1 jika berhasil, 0 jika gagal (muatBinary: 0 juga jika file belum ada). */
int simpanBinary(const char *namaFile, const void *data, size_t ukuran, size_t jumlah);
int muatBinary(const char *namaFile, void *data, size_t ukuran, size_t jumlah);

/* ---- data parkir milik teman (array Slotparkir parkir[3][50]) ---- */
int simpanParkir(Slotparkir parkir[JUMLAH_LANTAI][SLOT_PER_LANTAI]);
int muatParkir(Slotparkir parkir[JUMLAH_LANTAI][SLOT_PER_LANTAI]);

/* ---- reservasi aktif (slot dengan booking == 1 dan status_booking == 1) ----
   simpanReservasi: hanya menyimpan reservasi yang masih menunggu kedatangan.
   muatReservasi: mengembalikan reservasi itu ke slotnya; kendaraan lain yang sudah menempati
   slot tersebut TIDAK ditimpa. Return 0 jika file belum ada (run pertama). */
int simpanReservasi(Slotparkir parkir[JUMLAH_LANTAI][SLOT_PER_LANTAI]);
int muatReservasi(Slotparkir parkir[JUMLAH_LANTAI][SLOT_PER_LANTAI]);

/* ---- riwayat transaksi ---- */
int simpanRiwayat(void);
int muatRiwayat(void);

/* salin satu file apa adanya (dipakai untuk backup laporan). Return 1 jika berhasil. */
int salinFile(const char *asal, const char *tujuan);

#endif
