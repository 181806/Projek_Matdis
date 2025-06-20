#include <stdio.h>
#include <string.h>

#define MAX 100

// fungsi untuk menghitung sesi (PBB)
int hitungSesi (int a, int b){
    while (b!=0) {
        int sisa = a % b;
        a = b;
        b = sisa;
    }
    return a;
}

// Fungsi untuk menghitung konversi jam - menit
void konversiWaktu (int totalWaktu, int *jam, int *menit) {
    *jam = totalWaktu / 60;
    *menit = totalWaktu % 60;
}

int main(){
    int jumlahMapel;
    int waktu[MAX];
    char mapel[MAX][50];
    int jedaIstirahat = 0;

    printf("\n===========================\n");
    printf("*******SMART SCHEDULER*******\n");
    printf("=============================\n\n");

    printf("Masukkan jumlah mata pelajaran: ");
    scanf("%d", &jumlahMapel);
    printf("\n");

    for (int i = 0; i < jumlahMapel; i++) {
        printf("Mata Pelajaran ke-%d\n", i + 1);
        printf("Nama mata pelajaran: ");
        scanf(" %99[^\n]", mapel[i]);
        printf("Waktu (menit): ");
        scanf("%d", &waktu[i]);
        while (waktu[i] <= 0) {
            printf("Waktu tidak valid! Masukkan ulang waktu (menit): ");
            scanf("%d", &waktu[i]);
        }
    }

        printf("Masukkan waktu jeda istirahat yang kamu inginkan (menit): ");
        scanf("%d", &jedaIstirahat);

    // Menghitung waktu sesi dengan PBB
    int sesi = waktu[0];
    for (int i = 1; i < jumlahMapel; i++) {
        sesi = hitungSesi(sesi, waktu[i]);
    }
    int minimalSesi = 10;
    if (sesi < minimalSesi) {
        // menggunakan minimal sesi secara otomatis, karena hasil PBB < 10
        for (int i = minimalSesi; i <= 60; i++) {
            int valid = 1;
            for (int j = 0; j < jumlahMapel; j++) {
                if (waktu[j] % i != 0) {
                    valid = 0;
                    break;
                }
            }
            if (valid) {
                sesi = i;
                printf("Sesi diubah menjadi %d menit.\n", sesi);
                break;
            }
        }

        if (sesi < minimalSesi) {
            printf("Hasil sesi dibawah %d", minimalSesi);
            printf("Menggunakan jumlah sesi default: %d menit.\n", minimalSesi, sesi);
            sesi = minimalSesi;
        }
    }

        int jumlahSesi = 0, totalWaktu = 0;
        for (int i = 0; i < jumlahMapel; i++){
            jumlahSesi += waktu[i] / sesi;
            totalWaktu += waktu[i];
        }

        // Menghitung jeda istirahat per sesi
        if (jedaIstirahat < 0) {
            printf("Jeda istirahat tidak boleh negatif. Menggunakan jeda istirahat default 5 menit.\n");
            jedaIstirahat = 5;
        }else if (sesi < jedaIstirahat) {
            printf("Jeda istirahat tidak boleh lebih besar dari durasi sesi.\n");
            printf("Menggunakan jeda istirahat default 5 menit.\n");
            jedaIstirahat = 5;
        }
        // jika lebih dari satu sesi
        if (jumlahSesi > 1) {
        int jumlahJeda = (jumlahSesi - 1);
        totalWaktu += jumlahJeda * jedaIstirahat; }
   
        
        // Konversi waktu dalam menit
        int jam, menit;
        konversiWaktu(totalWaktu, &jam, &menit);

        printf("\n=================================\n");
        printf("Durasi waktu kamu belajar tiap mata pelajaran per sesi: %d menit \n", sesi);
        printf("Jumlah sesi belajar: %d\n", jumlahSesi);
        printf("Waktu jeda istirahat per sesi: %d menit\n", jedaIstirahat);
        printf("Total waktu belajar: %d jam %d menit\n", jam, menit); 
        printf("\n=================================\n");

}