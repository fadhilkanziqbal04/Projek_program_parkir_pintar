#include <stdio.h>
#include <string.h>
#include <ctype.h>

void inputkendaraan(int *jenis){
    printf("1. Mobil/truk pengangkut barang");
    printf("\n2. Mobil penumpang");
    printf("\n3. Sepeda motor");
    printf("\nMasukkan tipe kendaraan : ");
    while (scanf("%d", &jenis) != 1 || jenis < 1 || jenis > 3){
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Pilihan tidak valid, masukkan lagi : ");
    }
}
void InputYaatauTidak(const char *pesan, int *pilihan){
    printf("%s", pesan);
    while((scanf(" %d", &pilihan)) != 1 || pilihan > 1 || pilihan < 0){
    int M;
    while((M = getchar()) != '\n');
        printf("Input tidak valid, masukkan lagi : ");
    }
}
int cekplat(const char *platKendaraan){
    int len = strlen(platKendaraan);
    int hurufawal = 0;
    int idx = 0;
    while (idx < len && isalpha((unsigned char)platKendaraan[idx])){
        hurufawal++;
        idx++;
    }
    if (hurufawal < 1|| hurufawal > 2){
        return 0;
    }
    int angkatengah = 0;
    while (idx < len && isdigit((unsigned char)platKendaraan[idx])){
        angkatengah++;
        idx++;
    }
    if (angkatengah < 1 || angkatengah > 4){
        return 0;
    }
    int hurufakhir = 0;
    while(idx < len && isalpha((unsigned char)platKendaraan[idx])){
        hurufakhir++;
        idx++;
    }
    if(hurufakhir < 1 || hurufakhir > 3){
        return 0;
    }
    if(idx != len) return 0;
    return 1;
}
