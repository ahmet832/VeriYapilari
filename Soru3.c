#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26  // Ýngilizce alfabesindeki harf sayýsý (26 harf)

// Trie düðüm yapýsýnýn tanýmý
typedef struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];  // 26 harf için çocuk düðümler
    int isEndOfWord;  // Bu düðüm bir kelimenin sonu mu? (Evetse 1, hayýrsa 0)
} TrieNode;

// Yeni bir TrieNode (düðüm) oluþturma fonksiyonu
TrieNode* createNode() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));  // Yeni düðüm için hafýza ayýr
    node->isEndOfWord = 0;  // Baþlangýçta bu düðüm kelimenin sonu deðil
    // Tüm çocuklarý NULL olarak baþlat
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
    return node;  // Yeni düðümü geri döndür
}

// Bir karakteri alfabedeki indekse dönüþtüren fonksiyon
int charToIndex(char c) {
    return tolower(c) - 'a';  // Karakteri küçük harfe dönüþtürüp, a'ya göre index hesapla
}

// Trie'ye kelime eklemek için kullanýlan fonksiyon
void insert(TrieNode* root, const char* word) {
    TrieNode* temp = root;  // Baþlangýçta root'tan baþlayarak ilerle
    for (int i = 0; word[i]; i++) {  // Kelimenin her karakterini tek tek iþle
        if (!isalpha(word[i])) continue;  // Eðer karakter bir harf deðilse, geç
        int index = charToIndex(word[i]);  // Karakteri index'e çevir
        // Eðer bu karakter için bir düðüm yoksa, yeni düðüm oluþtur
        if (!temp->children[index]) {
            temp->children[index] = createNode();
        }
        temp = temp->children[index];  // Sonraki düðüme geç
    }
    temp->isEndOfWord = 1;  // Kelimenin sonuna geldik, bu düðümü kelimenin sonu olarak iþaretle
}

// Trie'de kelime aramak için kullanýlan fonksiyon
int search(TrieNode* root, const char* word) {
    TrieNode* temp = root;  // Baþlangýçta root'tan baþlayarak ilerle
    for (int i = 0; word[i]; i++) {  // Kelimenin her karakterini tek tek iþle
        if (!isalpha(word[i])) continue;  // Eðer karakter bir harf deðilse, geç
        int index = charToIndex(word[i]);  // Karakteri index'e çevir
        if (!temp->children[index]) {  // Eðer bu karakter için düðüm yoksa, kelime bulunamaz
            return 0;
        }
        temp = temp->children[index];  // Sonraki düðüme geç
    }
    return temp->isEndOfWord;  // Eðer kelimenin sonu ise, 1 döndür (bulundu)
}

// Otomatik tamamlama için yardýmcý fonksiyon (tüm prefix'lere sahip kelimeleri yazdýrýr)
void autoCompleteUtil(TrieNode* root, char* buffer, int depth) {
    // Eðer bu düðüm bir kelimenin sonuysa, kelimeyi yazdýr
    if (root->isEndOfWord) {
        buffer[depth] = '\0';  // Buffer'ý sonlandýr
        printf("- %s\n", buffer);  // Kelimeyi ekrana yazdýr
    }

    // Alfabedeki her harf için rekürsif olarak alt düðümlere git
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {  // Eðer alt düðüm varsa
            buffer[depth] = i + 'a';  // Harfi buffer'a ekle
            autoCompleteUtil(root->children[i], buffer, depth + 1);  // Alt düðüme geç
        }
    }
}

// Prefix'e sahip kelimeleri yazdýrmak için fonksiyon
void autoComplete(TrieNode* root, const char* prefix) {
    TrieNode* temp = root;  // Baþlangýçta root'tan baþla
    int length = strlen(prefix);  // Prefix'in uzunluðunu al
    char buffer[100];  // Geçici bir buffer oluþtur

    // Prefix'i buffer'a kopyala
    memcpy(buffer, prefix, length);
    buffer[length] = '\0';  // Null sonlandýr

    // Prefix'in her karakteri için Trie'de ilerle
    for (int i = 0; i < length; i++) {
        if (!isalpha(prefix[i])) continue;  // Eðer karakter bir harf deðilse, geç
        int index = charToIndex(prefix[i]);  // Karakteri index'e dönüþtür
        if (!temp->children[index]) {  // Eðer bu karakter için bir düðüm yoksa, kelime bulunamaz
            printf("Hiçbir takým '%s' ile baþlamýyor.\n", prefix);
            return;
        }
        temp = temp->children[index];  // Sonraki düðüme geç
    }

    // Prefix'e sahip tüm kelimeleri yazdýr
    autoCompleteUtil(temp, buffer, length);
}

// Ana fonksiyon
int main() {
    TrieNode* root = createNode();  // Baþlangýçta boþ bir Trie oluþtur

    // Süper Lig takýmlarýný Trie'ye ekle
    insert(root, "fenerbahce");
    insert(root, "galatasaray");
    insert(root, "besiktas");
    insert(root, "trabzonspor");
    insert(root, "Basaksehir");
    insert(root, "Kasimpasa");
    insert(root, "sivasspor");
    insert(root, "alanyaspor");
    insert(root, "adanademirspor");
    insert(root, "Kayserispor");

    // Arama örnekleri
    printf("Arama Sonuclari:\n");
    printf("besiktas: %s\n", search(root, "besiktas") ? "Var" : "Yok");  // Besiktas'ý arama
    printf("bursaspor: %s\n", search(root, "bursaspor") ? "Var" : "Yok");  // Bursaspor'u arama

    // Prefix'e göre otomatik tamamlama örnekleri
    printf("\n--- 'b' ile baþlayan takýmlar ---\n");
    autoComplete(root, "b");  // 'b' ile baþlayan takýmlarý listele

    printf("\n--- 'ka' ile baþlayan takýmlar ---\n");
    autoComplete(root, "ka");  // 'ka' ile baþlayan takýmlarý listele

    printf("\n--- 'a' ile baþlayan takýmlar ---\n");
    autoComplete(root, "a");  // 'a' ile baþlayan takýmlarý listele

    return 0;  // Programý sonlandýr
}
