========================================

Kendaraan Masuk
Kendaraan Keluar
Lihat Denah Parkir
Booking slot
Laporan & Riwayat
Simpan & Keluar
Kapasitas: 38/60 terisi (63%) Pilih menu:

fitur tambahan:

slot parkir khusus untuk customer yang membeli layanan VIP, dan ada diskon khusus
mencari dan merekomendasikan slot terdekat yang masih tersedia
booking slot parkir, slot yang di booking akan di tandai oleh admin agar tidak di anggap kosong, jika slot parkir terlambat di isi, booking di anggap batal dan slot kembali dianggap kosong
laporan riwayat transaksi


List pembagian tugas dan detail alur kerja

Bagian Rica:

Bagian menu.c
========================================
        SMARTPARK - SISTEM PARKIR
========================================
 1. Kendaraan Masuk
 2. Kendaraan Keluar
 3. Lihat Denah Parkir
 4. Booking Slot            
 5. Laporan & Riwayat Transaksi
 0. Keluar
----------------------------------------
 Kapasitas: 38/150 terisi (25%) | Booking aktif: 3
 Pilih menu:

1. Kendaran masuk
> Reservasi
	>Input jenis kendaraan(1,2,3)
		>Input plat nomor
		>Program mengambil jam dan menit serta hari waktu sistem
		>Program menampilkan jam berapa booking akan hangus
		>fitur mencari dan menentukan lahan parkir(memprioritaskan slot member)
		>menyimpan data booking
		>kembali ke menu utama
> Parkir langsung
>Input plat nomor dkembali
>Input jam dan menit kendaraan masuk 
>Input apakah member atau tidak(1=iya, 0=tidak) 
>mencari dan menentukan lahan parkir(jika member, memprioritaskan slot member) 
>menyimpan data 
>kembali ke menu utama
2. Kendaraan keluar
	>Input jenis kendaraan
	>Input plat nomor
	>Input jam keluar
	>Input apakah member atau tidak(1=iya, 0=tidak)
	>Input apakah karcis parkir hilang(1=iya, 0=tidak)
	>Tampilkan data customer dan total biaya
	>simpan data
	>kosongkan slot parkir
	>kembali ke menu utama



3. Denah parkir
	>Tampilkan denah
	>Cari kendaraan
		>input plat nomor
4.Booking slot
	>Tampilkan semua booking
		>pilih booking
			>customer tiba
			>batalkan booking
			>kembali ke menu utama

5.Laporan dan riwayat transaksi

Contoh gambaran outputnya (Bagian Rafif)

 

File yg akan dikerjakan rica:
main.c (program utama untuk memanggil semua fungsi dan file yg akan di gunakan)
menu.c dan menu.h(pembuatan tampilan menu)
utils.c dan utils(bagian berisi fungsi fungsi seperti input plat nomor, dll,  agar tidak perlu mengulangi program yg sama terus menerus)
untuk input waktu kendaraan masuk, keluar dan booking, buat input nya dalam bentuk jam dan waktu

Bagian fitur fitur penghitung tarif adalah bagian alfian, yaitu:
tarif.h(tempat deklarasi semua struct dan fungsi yang akan dipakai)
tarif.c(tempat berisi perintah perintah untuk fungsi fungsi itu)
untuk menentukan waktu nya,  konversi jam menjadi menit dulu lalu gabungkan dengan menit sebelumnya, jadi yg dihitung adalah total menit nya



Fitur yang dikerjakan Rafif:
fileio.c dan fileio.h (untuk menyimpan data kedalam file dan membacanya)
riwayattransaksi.c dan riwayattransaksii.h (untuk menampilkan 5 riwayat kendaraan masuk, keluar atau reservasi terbaru)
laporan.c dan laporan.h(untuk menyalin semua history kedalam  file txt yg bisa dibaca manusia)
folder backup, setiap laporan di simpan, otomatis membuat salinannya di folder backup


kegunaan file file:
file di src itu semua file program/source code, sementara di include itu isinya file header
file utils isi nya fungsi yg bisa di pakai untuk program seperti input waktu, input plat, dll




