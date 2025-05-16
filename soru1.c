#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 500         // Dizinin boyutunu 500 olarak belirliyoruz
#define MAX_VALUE 1000   // Dizideki rastgele sayýlarýn 0 ile 1000 arasýnda olacaðýný belirliyoruz

// Insertion Sort algoritmasý
// Bu fonksiyon, diziyi Insertion Sort algoritmasý ile sýralar
void insertionSort(int arr[], int size) {
    int i, j, key;
    for (i = 1; i < size; i++) {  // 1. elemandan baþlayarak sýralama yapýlacak
        key = arr[i];             // Sýralanacak elemaný "key" olarak belirle
        j = i - 1;                // "key" ile karþýlaþtýrýlacak eleman
        while (j >= 0 && arr[j] > key) {  // Eðer "key" deðerinden büyük elemanlar varsa, onlarý saða kaydýr
            arr[j + 1] = arr[j];   // Elemanlarý saða kaydýr
            j = j - 1;             // Bir sonraki elemanla karþýlaþtýrmak için j'yi bir azalt
        }
        arr[j + 1] = key;          // "key" deðerini doðru pozisyona yerleþtir
    }
}

// Selection Sort algoritmasý
// Bu fonksiyon, diziyi Selection Sort algoritmasý ile sýralar
void selectionSort(int arr[], int size) {
    int i, j, temp, minIdx;
    for (i = 0; i < size - 1; i++) {   // Dizinin her elemaný için en küçük eleman bulunacak
        minIdx = i;                     // Ýlk olarak, þu anki eleman en küçük kabul edilir

        for (j = i + 1; j < size; j++) {  // Dizinin geri kalanýný kontrol et
            if (arr[j] < arr[minIdx]) {  // Eðer bir eleman daha küçükse
                minIdx = j;             // En küçük elemanýn indeksini güncelle
            }
        }

        temp = arr[minIdx];             // En küçük elemaný geçici bir deðiþkende tut
        arr[minIdx] = arr[i];           // En küçük elemaný doðru pozisyona yerleþtir
        arr[i] = temp;                  // Eski elemaný en küçük elemanýn yerine koy
    }
}

// Diziyi rastgele sayýlarla dolduran fonksiyon
// Bu fonksiyon diziyi 0 ile 1000 arasýnda rastgele sayýlarla doldurur
void fillArrayWithRandomNumbers(int arr[], int size) {
    for (int i = 0; i < size; i++) {        // Dizinin her elemaný için
        arr[i] = rand() % (MAX_VALUE + 1);   // 0 ile 1000 arasýnda rastgele bir sayý ata
    }
}

int main() {
    int arr1[SIZE], arr2[SIZE];  // arr1 dizisi rastgele sayýlarla doldurulacak, arr2 sýralanacak

    srand(time(NULL));  // Rastgele sayý üretici baþlatýlýyor (zaman fonksiyonu ile)

    // Diziyi rastgele sayýlarla doldur
    fillArrayWithRandomNumbers(arr1, SIZE);

    // Insertion Sort için zaman ölçümü baþlatýlýyor
    for (int i = 0; i < SIZE; i++) {
        arr2[i] = arr1[i];  // arr1 dizisinin bir kopyasýný arr2'ye alýyoruz
    }
    clock_t start = clock();  // Zaman ölçümünü baþlatýyoruz
    insertionSort(arr2, SIZE); // Insertion Sort sýralama iþlemi
    clock_t end = clock();    // Zaman ölçümünü bitiriyoruz
    double insertionTime = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden zaman hesaplanýyor

    // Selection Sort için zaman ölçümü baþlatýlýyor
    for (int i = 0; i < SIZE; i++) {
        arr2[i] = arr1[i];  // arr1 dizisinin bir kopyasýný arr2'ye alýyoruz
    }
    start = clock();  // Zaman ölçümünü baþlatýyoruz
    selectionSort(arr2, SIZE); // Selection Sort sýralama iþlemi
    end = clock();    // Zaman ölçümünü bitiriyoruz
    double selectionTime = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden zaman hesaplanýyor

    // Sonuçlarý ekrana yazdýrýyoruz
    printf("Insertion Sort Suresi: %.3f ms\n", insertionTime); // Insertion Sort sýralama süresi
    printf("Selection Sort Suresi: %.3f ms\n", selectionTime); // Selection Sort sýralama süresi

    return 0;
}