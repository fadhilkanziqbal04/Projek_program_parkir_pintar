#ifndef PARKIR_H
#define PARKIR_H

typedef struct{
    int terisi ;
    int nomor;
    int isMember ;
    int kendaraan ;
    char plat[10] ;
    int karcishilang ;
    int waktumasuk_hour ;
    int waktumasuk_mnt ;
    int waktukeluar_hour ; 
    int waktukeluar_mnt ;
    int waktureservasi_hour;
    int waktureservasi_mnt;
    int booking;
    int status_booking;
} Slotparkir ;

typedef struct{
    int lantai;
    int indeks;
    char plat[10];
    int jam_booking;
    int mnt_booking;
    int selisih_menit;
} kandidatbookinghangus;

void Inputdatakendaraan (Slotparkir parkir[3][50]);
void Inputdatareservasi (Slotparkir parkir[3][50]);
void reservasitiba (Slotparkir parkir[3][50]);
void kendaraankeluar(Slotparkir parkir[3][50], int *lantai, int *indeks);
void pengingatWaktuReservasi (Slotparkir parkir[3][50]);
void batalkanreservasi(Slotparkir parkir[3][50]);;
int Cekkapasitas (Slotparkir parkir[3][50]);
void kosongkan_array(Slotparkir parkir[3][50], int *lantai, int *indeks);
#endif