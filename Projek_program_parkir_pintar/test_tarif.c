#include <stdio.h>
#include "include/tarif.h"

int main(void) {
    RincianTarif rincian;
    Slotparkir slot = {0};

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

    printf("\n=== UJI PEMBACAAN SLOT PARKIR ===\n");

slot.terisi = 1;
slot.kendaraan = JENIS_MOBIL;
slot.isMember = 1;
slot.booking = 0;
slot.karcishilang = 0;

slot.waktumasuk_hour = 10;
slot.waktumasuk_mnt = 0;
slot.waktukeluar_hour = 12;
slot.waktukeluar_mnt = 0;

if (prosesTarifSlot(&slot, HARI_WEEKDAY, &rincian)) {
    cetakStruk(&rincian);
    printf("Tarif tersimpan di slot: Rp%.0f\n", slot.tarif);
} else {
    printf("Pengujian slot gagal.\n");
    return 1;
}

return 0;
}
