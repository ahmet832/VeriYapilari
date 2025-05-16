#include <stdio.h>
#include <stdlib.h> // malloc ve free kullanmak için dahil edilir

// Bu fonksiyon diziyi büyükten küçüğe sıralar (Selection Sort yöntemiyle)
void siralaBuyuktenKucuge(int dizi[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (dizi[i] < dizi[j]) {
                // Yer değiştirme işlemi
                int temp = dizi[i];
                dizi[i] = dizi[j];
                dizi[j] = temp;
            }
        }
    }
}

// Bu fonksiyon özel zikzak sıralamayı yapar:
// En büyük → En küçük → Sonraki büyük → Sonraki küçük... şeklinde
void ozelSiralama(int dizi[], int n) {
    // Geçici diziler oluşturuluyor
    int* sirali = (int*)malloc(n * sizeof(int));  // Sıralı versiyon için
    int* sonuc = (int*)malloc(n * sizeof(int));   // Nihai sonucu tutacak dizi

    // Orijinal dizi sirali dizisine kopyalanıyor
    for (int i = 0; i < n; i++) {
        sirali[i] = dizi[i];
    }

    // sirali[] dizisi büyükten küçüğe sıralanıyor
    siralaBuyuktenKucuge(sirali, n);

    int sol = 0;         // Büyükleri almak için baştan başlayacak
    int sag = n - 1;     // Küçükleri almak için sondan başlayacak
    int i = 0;           // sonuc dizisinin indeksi

    // Zikzak sıraya göre elemanlar yerleştiriliyor
    while (sol <= sag) {
        if (i % 2 == 0) {
            // Çift indekslerde en büyükten al
            sonuc[i] = sirali[sol++];
        }
        else {
            // Tek indekslerde en küçükten al
            sonuc[i] = sirali[sag--];
        }
        i++;
    }

    // sonuc[] dizisindeki elemanları orijinal diziye kopyalıyoruz
    for (int j = 0; j < n; j++) {
        dizi[j] = sonuc[j];
    }

    // Bellekten ayrılan alanlar temizleniyor
    free(sirali);
    free(sonuc);
}

int main() {
    // Örnek giriş dizisi
    int dizi[] = { 60, 80, 3, 9, 57, 11 };
    int n = sizeof(dizi) / sizeof(dizi[0]); // Dizi boyutu hesaplanıyor

    // Zikzak sıralama fonksiyonu çağrılıyor
    ozelSiralama(dizi, n);

    // Sıralanmış dizi ekrana yazdırılıyor
    printf("Siralanmis dizi: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", dizi[i]);
    }

    return 0;
}
