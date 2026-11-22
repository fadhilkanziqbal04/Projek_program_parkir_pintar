#include <stdio.h>
#include <string.h>
#include "../include/searching.h"

void Carikendaraan (Slotparkir parkir[3][50]){
    int jenis;
    int idx = -1;
    char platnomor[10];
    printf("1. Mobil/truk pengangkut barang");
    printf("\n2. Mobil penumpang");
    printf("\n3. Sepeda motor");
    printf("\nMasukkan tipe kendaraan : ");
    while (scanf("%d", &jenis) != 1 || jenis < 1 || jenis > 3){
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Pilihan tidak valid, masukkan lagi : ");
    }
    printf("Masukkan plat nomor(contoh : BM1234HH)\n");
    do{
        
        while((scanf(" %9s", platnomor)) != 1 || cekplat(platnomor) != 1){
            printf("Plat tidak valid, masukkan lagi: ");
        }
        for(int i = 0; i < 50; i++){
            if(strcmp(platnomor, parkir[jenis - 1][i].plat) == 0){
                idx = i;
                break;
            }
        }
        if (idx == -1){
            printf("Plat nomor tidak di temukan, masukkan lagi: \n");
        }
    } while(idx == -1);
    printf("Kendaraan anda dengan plat %s berada di lantai %d dengan nomor parkir %d", parkir[jenis - 1][idx].plat, jenis, parkir[jenis - 1][idx].nomor);
}