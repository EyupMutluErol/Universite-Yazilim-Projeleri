#ifndef DNAVERILERIOKU_HPP
#define DNAVERILERIOKU_HPP


#include <list>
#include <string>
#include "Kromozom.hpp"

// DNAİşlemci sınıfı, DNA ile ilgili işlemleri yönetir.
class DnaVerileriOku {
public:
    std::list<Kromozom> kromozomlar; // Kromozomları tutan liste

    void dnaDosyasiniYukle(const std::string& dosyaAdi); // DNA dosyasını yükle
    void caprazlamaYap(int birinciIndeks, int ikinciIndeks); // Çaprazlama işlemi
    void mutasyonUygula(int kromozomIndeksi, int genIndeksi); // Mutasyon işlemi
    void otomatikIslemler(const std::string& dosyaAdi); // Otomatik işlemler
    void kromozomlariEkranaYaz() const; // Kromozomları ekrana yazdır
};

#endif // DNAVERILERIOKU_HPP
