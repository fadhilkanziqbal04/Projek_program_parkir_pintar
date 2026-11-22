#ifndef FILEIO_H
#define FILEIO_H

#include <stddef.h>
#include "parkir.h"

#define FILE_RIWAYAT "data/riwayat.dat"
#define FILE_PARKIR  "data/parkir.dat"

#ifndef JUMLAH_LANTAI
#define JUMLAH_LANTAI   3
#endif
#ifndef SLOT_PER_LANTAI
#define SLOT_PER_LANTAI 50
#endif

int simpanBinary(const char *namaFile, const void *data, size_t ukuran, size_t jumlah);
int muatBinary(const char *namaFile, void *data, size_t ukuran, size_t jumlah);

int simpanParkir(Slotparkir parkir[JUMLAH_LANTAI][SLOT_PER_LANTAI]);
int muatParkir(Slotparkir parkir[JUMLAH_LANTAI][SLOT_PER_LANTAI]);

int simpanRiwayat(void);
int muatRiwayat(void);

int salinFile(const char *asal, const char *tujuan);

#endif
