#include <stdio.h>
#include <string.h>
#include "../include/fileio.h"
#include "../include/riwayatTransaksi.h"

int simpanBinary(const char *namaFile, const void *data, size_t ukuran, size_t jumlah) {
    FILE *f = fopen(namaFile, "wb");
    if (f == NULL) {
        printf("Gagal menyimpan %s (pastikan folder data/ ada)\n", namaFile);
        return 0;
    }
    if (fwrite(data, ukuran, jumlah, f) != jumlah) {
        printf("Gagal menulis %s\n", namaFile);
        fclose(f);
        return 0;
    }
    fclose(f);
    return 1;
}

int muatBinary(const char *namaFile, void *data, size_t ukuran, size_t jumlah) {
    FILE *f = fopen(namaFile, "rb");
    if (f == NULL) return 0;                 /* belum ada: run pertama */
    if (fread(data, ukuran, jumlah, f) != jumlah) {
        printf("File %s rusak atau tidak lengkap.\n", namaFile);
        fclose(f);
        return 0;
    }
    fclose(f);
    return 1;
}

int simpanParkir(Slotparkir parkir[JUMLAH_LANTAI][SLOT_PER_LANTAI]) {
    return simpanBinary(FILE_PARKIR, parkir, sizeof(Slotparkir),
                        (size_t)JUMLAH_LANTAI * SLOT_PER_LANTAI);
}

int muatParkir(Slotparkir parkir[JUMLAH_LANTAI][SLOT_PER_LANTAI]) {
    return muatBinary(FILE_PARKIR, parkir, sizeof(Slotparkir),
                      (size_t)JUMLAH_LANTAI * SLOT_PER_LANTAI);
}

typedef struct {
    int lantai;          /* 0..2 */
    int indeks;          /* 0..49 */
    Slotparkir slot;
} CatatanReservasi;

int simpanReservasi(Slotparkir parkir[JUMLAH_LANTAI][SLOT_PER_LANTAI]) {
    FILE *f = fopen(FILE_RESERVASI, "wb");
    int l, i, n = 0;
    CatatanReservasi c;

    if (f == NULL) {
        printf("Gagal menyimpan %s (pastikan folder data/ ada)\n", FILE_RESERVASI);
        return 0;
    }
    if (fwrite(&n, sizeof(int), 1, f) != 1) { fclose(f); return 0; }     /* jumlah diisi di akhir */
    for (l = 0; l < JUMLAH_LANTAI; l++) {
        for (i = 0; i < SLOT_PER_LANTAI; i++) {
            if (parkir[l][i].booking == 1 && parkir[l][i].status_booking == 1) {
                c.lantai = l;
                c.indeks = i;
                c.slot = parkir[l][i];
                if (fwrite(&c, sizeof(c), 1, f) != 1) { fclose(f); return 0; }
                n++;
            }
        }
    }
    if (fseek(f, 0, SEEK_SET) != 0 || fwrite(&n, sizeof(int), 1, f) != 1) { fclose(f); return 0; }
    fclose(f);
    return 1;
}

int muatReservasi(Slotparkir parkir[JUMLAH_LANTAI][SLOT_PER_LANTAI]) {
    FILE *f = fopen(FILE_RESERVASI, "rb");
    int n, k;
    CatatanReservasi c;
    Slotparkir *s;

    if (f == NULL) return 0;                 /* belum ada: run pertama */
    if (fread(&n, sizeof(int), 1, f) != 1 || n < 0 || n > JUMLAH_LANTAI * SLOT_PER_LANTAI) {
        printf("File %s rusak.\n", FILE_RESERVASI);
        fclose(f);
        return 0;
    }
    for (k = 0; k < n; k++) {
        if (fread(&c, sizeof(c), 1, f) != 1) {
            printf("File %s tidak lengkap.\n", FILE_RESERVASI);
            fclose(f);
            return 0;
        }
        if (c.lantai < 0 || c.lantai >= JUMLAH_LANTAI || c.indeks < 0 || c.indeks >= SLOT_PER_LANTAI) continue;
        s = &parkir[c.lantai][c.indeks];
        if (s->terisi == 0 || strcmp(s->plat, c.slot.plat) == 0) *s = c.slot;   /* jangan timpa kendaraan lain */
    }
    fclose(f);
    return 1;
}

int simpanRiwayat(void) {
    FILE *f = fopen(FILE_RIWAYAT, "wb");
    if (f == NULL) {
        printf("Gagal menyimpan %s (pastikan folder data/ ada)\n", FILE_RIWAYAT);
        return 0;
    }
    if (fwrite(&jumlahRiwayat, sizeof(int), 1, f) != 1 ||
        fwrite(riwayat, sizeof(Riwayat), (size_t)jumlahRiwayat, f) != (size_t)jumlahRiwayat) {
        printf("Gagal menulis riwayat.\n");
        fclose(f);
        return 0;
    }
    fclose(f);
    return 1;
}

int muatRiwayat(void) {
    FILE *f = fopen(FILE_RIWAYAT, "rb");
    int n;

    if (f == NULL) return 0;                 /* belum ada: run pertama */
    if (fread(&n, sizeof(int), 1, f) != 1 || n < 0 || n > MAX_RIWAYAT ||
        fread(riwayat, sizeof(Riwayat), (size_t)n, f) != (size_t)n) {
        printf("File %s rusak.\n", FILE_RIWAYAT);
        fclose(f);
        return 0;
    }
    fclose(f);
    jumlahRiwayat = n;
    return 1;
}

int salinFile(const char *asal, const char *tujuan) {
    FILE *in = fopen(asal, "rb");
    FILE *out;
    char buf[1024];
    size_t n;

    if (in == NULL) return 0;
    out = fopen(tujuan, "wb");
    if (out == NULL) { fclose(in); return 0; }
    while ((n = fread(buf, 1, sizeof(buf), in)) > 0) {
        if (fwrite(buf, 1, n, out) != n) { fclose(in); fclose(out); return 0; }
    }
    fclose(in);
    fclose(out);
    return 1;
}
