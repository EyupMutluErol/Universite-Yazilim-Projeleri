#include <iostream>
#include "DnaVerileriOku.hpp"

int main() {
    DnaVerileriOku veri; // DNA işlemcisi nesnesi oluştur
    veri.dnaDosyasiniYukle("Dna.txt"); // DNA dosyasını yükle

    int secim; // Kullanıcının seçimi
    do {
        std::cout << "1- Caprazlama\n2- Mutasyon\n3- Otomatik Islemler\n4- Ekrana Yaz\n5- Cikis\n";
        std::cout << "Seciminizi yapin: ";
        std::cin >> secim; // Kullanıcıdan seçim al
        

        switch (secim) {
            case 1: {
                int birinci, ikinci;
                std::cout << "Caprazlama icin birinci kromozom satir numarasini girin: ";
                std::cin >> birinci; // Kullanıcıdan birinci kromozom indeksini al
                std::cout << "Caprazlama icin ikinci kromozom satir numarasini girin: ";
                std::cin >> ikinci;
                veri.caprazlamaYap(birinci, ikinci); // Çaprazlama işlemi uygula
                break;
            }
            case 2: {
                int kromozomIndeksi, genIndeksi;
                std::cout << "Mutasyon icin kromozom satir numarasini girin: ";
                std::cin >> kromozomIndeksi; // Kullanıcıdan kromozom ve gen indekslerini al
                std::cout << "Mutasyon icin gen sutun numarasini girin: ";
                std::cin >> genIndeksi;
                veri.mutasyonUygula(kromozomIndeksi, genIndeksi); // Mutasyonu uygula
                break;
            }
            case 3: {
                veri.otomatikIslemler("Islemler.txt"); // Otomatik işlemleri uygula
                break;
            }
            case 4: {
                veri.kromozomlariEkranaYaz(); // Kromozomları ekrana yazdır
                break;
            }
            case 5:
                std::cout << "Cikis yapiliyor...\n"; // Çıkış mesajı
                break;
            default:
                std::cout << "Gecersiz secim.\n"; // Hatalı seçim mesajı
        }
    } while (secim != 5); // 5'e kadar devam et

    return 0; // Programı sonlandır
}
