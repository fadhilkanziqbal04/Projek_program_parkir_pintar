#include <stdio.h>
#include "include/tarif.h"

int main(void) {
    RincianTarif rincian;

    printf("UJI MODUL TARIF SMARTPARK\n");

    printf("Mobil 60 menit : Rp%d\n",
           hitungTarif(JENIS_MOBIL, 60));

    printf("Mobil 91 menit : Rp%d\n",
           hitungTarif(JENIS_MOBIL, 91));

    printf("Mobil 24 jam   : Rp%d\n",
           hitungTarif(JENIS_MOBIL, 1440));

    printf("Mobil 30 jam   : Rp%d\n",
           hitungTarif(JENIS_MOBIL, 1800));

    printf("Motor 24 jam   : Rp%d\n",
           hitungTarif(JENIS_MOTOR, 1440));

    if (prosesPerhitunganTarif(
        JENIS_MOBIL, 120, 1,
        HARI_WEEKDAY, 1, 0, &rincian)) {

        cetakStruk(&rincian);

    } else {
        printf("Pengujian transaksi gagal.\n");
        return 1;
    }

    return 0;
}