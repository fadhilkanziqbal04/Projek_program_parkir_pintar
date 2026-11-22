#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../include/parkir.h"
#include <ctype.h>
#include <stdlib.h>

void Inputdatakendaraan (Slotparkir parkir[3][50]){
    int jenis;

    printf("1. Mobil/truk pengangkut barang");
    printf("\n2. Mobil penumpang");
    printf("\n3. Sepeda motor");
    printf("\nMasukkan tipe kendaraan : ");
    while (scanf("%d", &jenis) != 1 || jenis < 1 || jenis > 3){
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Pilihan tidak valid, masukkan lagi : ");
    }

    int i = 0;
    int member;
    int idx ;
    printf("Apakah member?(1=Iya, 0=tidak)\n");
    while((scanf(" %d", &member)) != 1 || member > 1 || member < 0){
    int M;
    while((M = getchar()) != '\n');
        printf("Input tidak valid, masukkan lagi : ");
    }
    if(member == 1){
       idx = i;
    } else {
        idx = i + 20;
    }
    for(i = idx; i < 50; i++){
        if (parkir[jenis - 1][i].terisi == 0){
            parkir[jenis - 1][i].isMember = member;
            parkir[jenis -  1][i].kendaraan = jenis;
            printf("Masukkan plat nomor(contoh : BM1234HH)\n");
            while((scanf(" %9s", parkir[jenis - 1][i].plat)) != 1 || cekplat(parkir[jenis - 1][i].plat) != 1){
                printf("Plat tidak valid, masukkan lagi: ");
            }
            time_t waktu_mentah = time(NULL);
            struct tm *waktu_lokal = localtime(&waktu_mentah);
            parkir[jenis - 1][i].waktumasuk_hour = waktu_lokal->tm_hour;
            parkir[jenis - 1][i].waktumasuk_mnt = waktu_lokal->tm_min;
            parkir[jenis - 1][i].nomor = jenis * 100 + i + 1;
            parkir[jenis - 1][i].terisi = 1;
            break;
        }
    }
    if (i == 50){
        printf("parkiran penuh");
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


void kendaraankeluar(Slotparkir parkir[3][50], int *lantai, int *indeks){
    *indeks = -1;
    printf("Masukkan lantai parkir : ");
    while (scanf("%d", lantai) != 1 || *lantai < 1 || *lantai > 3){
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Lantai tidak valid, masukkan lagi : ");
    }
    int karcis;
    printf("Apakah karcis hilang?(1=Iya, 0=tidak)\n");
    while((scanf(" %d", &karcis)) != 1 || karcis > 1 || karcis < 0){
        int M;
        while((M = getchar()) != '\n');
        printf("Input tidak valid, masukkan lagi : ");
    }
    if(karcis == 1){
        printf("Masukkan plat nomor(contoh : BM1234HH)\n");
        char platnomor[10];
        do{
            while((scanf(" %9s", platnomor)) != 1 || cekplat(platnomor) != 1){
                printf("Plat tidak valid, masukkan lagi: ");
            }
            for(int i = 0; i < 50; i++){
                if(strcmp(platnomor, parkir[*lantai - 1][i].plat) == 0){
                    *indeks = i;
                    break;
            }
        }
        if (*indeks == -1){
            printf("Plat nomor tidak di temukan, masukkan lagi: \n");
        }
        } while(*indeks == -1);
    } else if (karcis == 0){
        int nomor;
        do{
            printf("Masukkan nomor parkir (0 jika ingin kembali) : ");
            if(scanf(" %d", &nomor) != 1 ){
              while(getchar() != '\n');
              printf("input harus berupa angka : ");
              continue; 
            }
            if (nomor == 0){
                return;
            }
            if (nomor < *lantai * 100 || nomor > *lantai * 100 + 50){
                printf("Nomor parkir tidak valid, masukkan lagi : ");
                continue;
            }
        
            for(int i = 0; i < 50; i++){
                if(nomor == parkir[*lantai - 1][i].nomor){
                    *indeks = i;
                    break;
                }
            }
            if (*indeks == -1){
                printf("Nomor parkir tidak valid, masukkan lagi : ");
            }
        }while (*indeks == -1);
    }
    
    time_t raw_time = time(NULL);
    struct tm *keluar = localtime(&raw_time);
    parkir[*lantai - 1][*indeks].waktukeluar_hour = keluar->tm_hour;
    parkir[*lantai - 1][*indeks].waktukeluar_mnt = keluar->tm_min;
}
void kosongkan_array(Slotparkir parkir[3][50], int *lantai, int *indeks){
    if(*indeks < 0 || *indeks >= 50 || *lantai < 1 || *lantai > 3){
        return;
    }
    int c;
    while((c = getchar()) != '\n' && c != EOF);
    printf("Tekan enter untuk menghapus data parkir yang baru keluar...");
    getchar();
    parkir[*lantai - 1][*indeks] = (Slotparkir){0};

}

int Cekkapasitas (Slotparkir parkir[3][50]){
    int adaisi = 0;
    for(int j = 0; j < 3;j++){
        for(int i = 0;i < 50;i++){
            if(parkir[j][i].terisi == 1){
                adaisi += 1;
            }
        }
    }
    return adaisi;
}

void Inputdatareservasi (Slotparkir parkir[3][50]){
    int jenis;
    printf("1. Mobil/truk pengangkut barang");
    printf("\n2. Mobil penumpang");
    printf("\n3. Sepeda motor");
    printf("\nMasukkan tipe kendaraan : ");
    while (scanf("%d", &jenis) != 1 || jenis < 1 || jenis > 3){
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Pilihan tidak valid, masukkan lagi : ");
    }
    int i;
    for(i = 0; i < 50; i++){
        if (parkir[jenis - 1][i].terisi == 0){
            parkir[jenis - 1][i].kendaraan = jenis;
            parkir[jenis - 1][i].isMember = 1;
            printf("Masukkan plat nomor(contoh : BM1234HH)\n");
            while((scanf(" %9s", parkir[jenis - 1][i].plat)) != 1 || cekplat(parkir[jenis - 1][i].plat) != 1){
                printf("Plat tidak valid, masukkan lagi: ");
            }
            time_t waktu_mentah = time(NULL);
            struct tm *waktu_lokal = localtime(&waktu_mentah);
            parkir[jenis - 1][i].waktureservasi_hour = waktu_lokal->tm_hour;
            parkir[jenis - 1][i].waktureservasi_mnt = waktu_lokal->tm_min;
            parkir[jenis - 1][i].nomor = jenis * 100 + i + 1;
            parkir[jenis - 1][i].terisi = 1;
            parkir[jenis - 1][i].booking = 1;
            parkir[jenis - 1][i].status_booking = 1;
            break;
        }
    }
    if (i == 50){
        printf("parkiran penuh");
    }


}

void reservasitiba (Slotparkir parkir[3][50]){
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
    time_t waktu_mentah = time(NULL);
    struct tm *waktu_lokal = localtime(&waktu_mentah);
    parkir[jenis - 1][idx].waktumasuk_hour = waktu_lokal->tm_hour;
    parkir[jenis - 1][idx].waktumasuk_mnt = waktu_lokal->tm_min;
    parkir[jenis - 1][idx].status_booking = 0;
}
void batalkanreservasi(Slotparkir parkir[3][50]){
    int lantaiParkir;
    printf("Masukkan lantai parkir : ");
    while (scanf("%d", &lantaiParkir) != 1 || lantaiParkir < 1 || lantaiParkir > 3){
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Lantai tidak valid, masukkan lagi : ");
    }
    int nomor;
    int indeks = -1;
        do{
            printf("Masukkan nomor parkir (0 jika ingin kembali) : ");
            if(scanf(" %d", &nomor) != 1 ){
              while(getchar() != '\n');
              printf("input harus berupa angka : ");
              continue; 
            }
            if (nomor == 0){
                return;
            }
            if (nomor < lantaiParkir * 100 || nomor > lantaiParkir * 100 + 50){
                printf("Nomor parkir tidak valid, masukkan lagi : ");
                continue;
            }
            for(int i = 0; i < 50; i++){
                if(nomor == parkir[lantaiParkir - 1][i].nomor){
                    indeks = i;
                    break;
                }
            }
            if (indeks == -1){
                printf("Nomor parkir tidak valid, masukkan lagi : ");
            }
        }while (indeks == -1);
        parkir[lantaiParkir -1][indeks] = (Slotparkir){0};
}

void pengingatWaktuReservasi (Slotparkir parkir[3][50]){
    time_t waktusekarang = time(NULL);
    struct tm *waktu = localtime(&waktusekarang);
    int jam_sekarang = waktu->tm_hour;
    int mnt_sekarang = waktu->tm_min;
    int totalMNT = (jam_sekarang * 60) + mnt_sekarang;

    kandidatbookinghangus pengingat[150];
    int jumlahkandidat = 0;
    for(int j = 0;j < 3;j++){
        for(int i = 0; i < 50;i++){
            if(parkir[j][i].status_booking == 1){
                int totalmntboking = (parkir[j][i].waktureservasi_hour *60) + parkir[j][i].waktureservasi_mnt;
                int selisih = totalMNT - totalmntboking;
                if (selisih < 0){
                    selisih += 24 *60;
                }
                if (selisih >= 60){
                    parkir[j][i] = (Slotparkir){0};
                } else if (selisih > 30){
                    pengingat[jumlahkandidat].lantai = j + 1;
                    pengingat[jumlahkandidat].indeks = i;
                    snprintf(pengingat[jumlahkandidat].plat, sizeof(pengingat[jumlahkandidat].plat), "%s", parkir[j][i].plat);
                    pengingat[jumlahkandidat].jam_booking = parkir[j][i].waktureservasi_hour;
                    pengingat[jumlahkandidat].mnt_booking = parkir[j][i].waktureservasi_mnt;
                    pengingat[jumlahkandidat].selisih_menit = selisih;
                    jumlahkandidat++;                  
                }
            }
        }
    }
    if (jumlahkandidat > 0) {
        for (int a = 0; a < jumlahkandidat - 1; a++) {
            for (int b = 0; b < jumlahkandidat - a - 1; b++) {
                if (pengingat[b].selisih_menit < pengingat[b + 1].selisih_menit) {
                    kandidatbookinghangus temp = pengingat[b];
                    pengingat[b] = pengingat[b + 1];
                    pengingat[b + 1] = temp;
                }
            }
        }
    

    int batastampil ;
    if (jumlahkandidat < 3){
        batastampil = jumlahkandidat;
    } else {
        batastampil = 3;
    }

    printf("\n--- Pengingat booking yang melewati 30 menit ---\n");
        for (int k = 0; k < batastampil; k++) {
            printf("%d. Plat %-9s | Lantai %d Slot %d | Booking %02d:%02d (%d menit lalu)\n",
                   k + 1,
                   pengingat[k].plat,
                   pengingat[k].lantai,
                   pengingat[k].indeks + 1,
                   pengingat[k].jam_booking,
                   pengingat[k].mnt_booking,
                   pengingat[k].selisih_menit);
        }
    }
}

