#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 500         // Dizinin boyutunu 500 olarak belirliyoruz
#define MAX_VALUE 1000   // Dizideki rastgele say�lar�n 0 ile 1000 aras�nda olaca��n� belirliyoruz

// Insertion Sort algoritmas�
// Bu fonksiyon, diziyi Insertion Sort algoritmas� ile s�ralar
void insertionSort(int arr[], int size) {
    int i, j, key;
    for (i = 1; i < size; i++) {  // 1. elemandan ba�layarak s�ralama yap�lacak
        key = arr[i];             // S�ralanacak eleman� "key" olarak belirle
        j = i - 1;                // "key" ile kar��la�t�r�lacak eleman
        while (j >= 0 && arr[j] > key) {  // E�er "key" de�erinden b�y�k elemanlar varsa, onlar� sa�a kayd�r
            arr[j + 1] = arr[j];   // Elemanlar� sa�a kayd�r
            j = j - 1;             // Bir sonraki elemanla kar��la�t�rmak i�in j'yi bir azalt
        }
        arr[j + 1] = key;          // "key" de�erini do�ru pozisyona yerle�tir
    }
}

// Selection Sort algoritmas�
// Bu fonksiyon, diziyi Selection Sort algoritmas� ile s�ralar
void selectionSort(int arr[], int size) {
    int i, j, temp, minIdx;
    for (i = 0; i < size - 1; i++) {   // Dizinin her eleman� i�in en k���k eleman bulunacak
        minIdx = i;                     // �lk olarak, �u anki eleman en k���k kabul edilir

        for (j = i + 1; j < size; j++) {  // Dizinin geri kalan�n� kontrol et
            if (arr[j] < arr[minIdx]) {  // E�er bir eleman daha k���kse
                minIdx = j;             // En k���k eleman�n indeksini g�ncelle
            }
        }

        temp = arr[minIdx];             // En k���k eleman� ge�ici bir de�i�kende tut
        arr[minIdx] = arr[i];           // En k���k eleman� do�ru pozisyona yerle�tir
        arr[i] = temp;                  // Eski eleman� en k���k eleman�n yerine koy
    }
}

// Diziyi rastgele say�larla dolduran fonksiyon
// Bu fonksiyon diziyi 0 ile 1000 aras�nda rastgele say�larla doldurur
void fillArrayWithRandomNumbers(int arr[], int size) {
    for (int i = 0; i < size; i++) {        // Dizinin her eleman� i�in
        arr[i] = rand() % (MAX_VALUE + 1);   // 0 ile 1000 aras�nda rastgele bir say� ata
    }
}

int main() {
    int arr1[SIZE], arr2[SIZE];  // arr1 dizisi rastgele say�larla doldurulacak, arr2 s�ralanacak

    srand(time(NULL));  // Rastgele say� �retici ba�lat�l�yor (zaman fonksiyonu ile)

    // Diziyi rastgele say�larla doldur
    fillArrayWithRandomNumbers(arr1, SIZE);

    // Insertion Sort i�in zaman �l��m� ba�lat�l�yor
    for (int i = 0; i < SIZE; i++) {
        arr2[i] = arr1[i];  // arr1 dizisinin bir kopyas�n� arr2'ye al�yoruz
    }
    clock_t start = clock();  // Zaman �l��m�n� ba�lat�yoruz
    insertionSort(arr2, SIZE); // Insertion Sort s�ralama i�lemi
    clock_t end = clock();    // Zaman �l��m�n� bitiriyoruz
    double insertionTime = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden zaman hesaplan�yor

    // Selection Sort i�in zaman �l��m� ba�lat�l�yor
    for (int i = 0; i < SIZE; i++) {
        arr2[i] = arr1[i];  // arr1 dizisinin bir kopyas�n� arr2'ye al�yoruz
    }
    start = clock();  // Zaman �l��m�n� ba�lat�yoruz
    selectionSort(arr2, SIZE); // Selection Sort s�ralama i�lemi
    end = clock();    // Zaman �l��m�n� bitiriyoruz
    double selectionTime = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden zaman hesaplan�yor

    // Sonu�lar� ekrana yazd�r�yoruz
    printf("Insertion Sort Suresi: %.3f ms\n", insertionTime); // Insertion Sort s�ralama s�resi
    printf("Selection Sort Suresi: %.3f ms\n", selectionTime); // Selection Sort s�ralama s�resi

    return 0;
}