#include <stdio.h>
#include <string.h>

struct SlotParkir {
    int nomorSlot;
    char platNomor[15];
    int status;
    int jamMasuk;
    int jenisKendaraan;
};

// Fungsi void untuk mengisi data pada indeks tertentu
void isiData(struct SlotParkir arr[], int indeks) {
    arr[indeks].nomorSlot = 2;
    strcpy(arr[indeks].platNomor, "BM3245HA");
    arr[indeks].status = 1;
    arr[indeks].jamMasuk = 3;
    arr[indeks].jenisKendaraan = 4;
}

int main() {
    // Deklarasi array ukuran 2, diinisialisasi 0 semua di awal
    struct SlotParkir data[2] = {0};

    // Mengisi hanya indeks 0 menggunakan fungsi void
    isiData(data, 0);

    // Menampilkan isi seluruh array (indeks 0 dan indeks 1)
    for (int i = 0; i < 2; i++) {
        printf("=== Indeks [%d] ===\n", i);
        printf("Nomor Slot : %d\n", data[i].nomorSlot);
        printf("Plat Nomor : '%s'\n", data[i].platNomor);
        printf("Status     : %d\n", data[i].status);
        printf("Jam Masuk  : %d\n", data[i].jamMasuk);
        printf("Jenis      : %d\n\n", data[i].jenisKendaraan);
    }

    return 0;
}
