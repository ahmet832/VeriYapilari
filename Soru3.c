#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26  // �ngilizce alfabesindeki harf say�s� (26 harf)

// Trie d���m yap�s�n�n tan�m�
typedef struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];  // 26 harf i�in �ocuk d���mler
    int isEndOfWord;  // Bu d���m bir kelimenin sonu mu? (Evetse 1, hay�rsa 0)
} TrieNode;

// Yeni bir TrieNode (d���m) olu�turma fonksiyonu
TrieNode* createNode() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));  // Yeni d���m i�in haf�za ay�r
    node->isEndOfWord = 0;  // Ba�lang��ta bu d���m kelimenin sonu de�il
    // T�m �ocuklar� NULL olarak ba�lat
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
    return node;  // Yeni d���m� geri d�nd�r
}

// Bir karakteri alfabedeki indekse d�n��t�ren fonksiyon
int charToIndex(char c) {
    return tolower(c) - 'a';  // Karakteri k���k harfe d�n��t�r�p, a'ya g�re index hesapla
}

// Trie'ye kelime eklemek i�in kullan�lan fonksiyon
void insert(TrieNode* root, const char* word) {
    TrieNode* temp = root;  // Ba�lang��ta root'tan ba�layarak ilerle
    for (int i = 0; word[i]; i++) {  // Kelimenin her karakterini tek tek i�le
        if (!isalpha(word[i])) continue;  // E�er karakter bir harf de�ilse, ge�
        int index = charToIndex(word[i]);  // Karakteri index'e �evir
        // E�er bu karakter i�in bir d���m yoksa, yeni d���m olu�tur
        if (!temp->children[index]) {
            temp->children[index] = createNode();
        }
        temp = temp->children[index];  // Sonraki d���me ge�
    }
    temp->isEndOfWord = 1;  // Kelimenin sonuna geldik, bu d���m� kelimenin sonu olarak i�aretle
}

// Trie'de kelime aramak i�in kullan�lan fonksiyon
int search(TrieNode* root, const char* word) {
    TrieNode* temp = root;  // Ba�lang��ta root'tan ba�layarak ilerle
    for (int i = 0; word[i]; i++) {  // Kelimenin her karakterini tek tek i�le
        if (!isalpha(word[i])) continue;  // E�er karakter bir harf de�ilse, ge�
        int index = charToIndex(word[i]);  // Karakteri index'e �evir
        if (!temp->children[index]) {  // E�er bu karakter i�in d���m yoksa, kelime bulunamaz
            return 0;
        }
        temp = temp->children[index];  // Sonraki d���me ge�
    }
    return temp->isEndOfWord;  // E�er kelimenin sonu ise, 1 d�nd�r (bulundu)
}

// Otomatik tamamlama i�in yard�mc� fonksiyon (t�m prefix'lere sahip kelimeleri yazd�r�r)
void autoCompleteUtil(TrieNode* root, char* buffer, int depth) {
    // E�er bu d���m bir kelimenin sonuysa, kelimeyi yazd�r
    if (root->isEndOfWord) {
        buffer[depth] = '\0';  // Buffer'� sonland�r
        printf("- %s\n", buffer);  // Kelimeyi ekrana yazd�r
    }

    // Alfabedeki her harf i�in rek�rsif olarak alt d���mlere git
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {  // E�er alt d���m varsa
            buffer[depth] = i + 'a';  // Harfi buffer'a ekle
            autoCompleteUtil(root->children[i], buffer, depth + 1);  // Alt d���me ge�
        }
    }
}

// Prefix'e sahip kelimeleri yazd�rmak i�in fonksiyon
void autoComplete(TrieNode* root, const char* prefix) {
    TrieNode* temp = root;  // Ba�lang��ta root'tan ba�la
    int length = strlen(prefix);  // Prefix'in uzunlu�unu al
    char buffer[100];  // Ge�ici bir buffer olu�tur

    // Prefix'i buffer'a kopyala
    memcpy(buffer, prefix, length);
    buffer[length] = '\0';  // Null sonland�r

    // Prefix'in her karakteri i�in Trie'de ilerle
    for (int i = 0; i < length; i++) {
        if (!isalpha(prefix[i])) continue;  // E�er karakter bir harf de�ilse, ge�
        int index = charToIndex(prefix[i]);  // Karakteri index'e d�n��t�r
        if (!temp->children[index]) {  // E�er bu karakter i�in bir d���m yoksa, kelime bulunamaz
            printf("Hi�bir tak�m '%s' ile ba�lam�yor.\n", prefix);
            return;
        }
        temp = temp->children[index];  // Sonraki d���me ge�
    }

    // Prefix'e sahip t�m kelimeleri yazd�r
    autoCompleteUtil(temp, buffer, length);
}

// Ana fonksiyon
int main() {
    TrieNode* root = createNode();  // Ba�lang��ta bo� bir Trie olu�tur

    // S�per Lig tak�mlar�n� Trie'ye ekle
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

    // Arama �rnekleri
    printf("Arama Sonuclari:\n");
    printf("besiktas: %s\n", search(root, "besiktas") ? "Var" : "Yok");  // Besiktas'� arama
    printf("bursaspor: %s\n", search(root, "bursaspor") ? "Var" : "Yok");  // Bursaspor'u arama

    // Prefix'e g�re otomatik tamamlama �rnekleri
    printf("\n--- 'b' ile ba�layan tak�mlar ---\n");
    autoComplete(root, "b");  // 'b' ile ba�layan tak�mlar� listele

    printf("\n--- 'ka' ile ba�layan tak�mlar ---\n");
    autoComplete(root, "ka");  // 'ka' ile ba�layan tak�mlar� listele

    printf("\n--- 'a' ile ba�layan tak�mlar ---\n");
    autoComplete(root, "a");  // 'a' ile ba�layan tak�mlar� listele

    return 0;  // Program� sonland�r
}
