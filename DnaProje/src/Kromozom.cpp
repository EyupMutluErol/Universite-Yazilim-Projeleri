#include "Kromozom.hpp"

// Kromozomun yapıcı fonksiyonu
Kromozom::Kromozom() : bas(nullptr) {}

// Kromozomun yıkıcı fonksiyonu
Kromozom::~Kromozom() {
    Gen* mevcut = bas; // Mevcut gen göstericisi
    while (mevcut != nullptr) { // Tüm genleri sil
        Gen* silinecek = mevcut; // Silinecek gen
        mevcut = mevcut->sonraki; // Sonraki gene geç
        delete silinecek; // Bellekten sil
    }
}

// Kromozoma gen ekleme fonksiyonu
void Kromozom::genEkle(const std::string& genAdi) {
    Gen* yeniGen = new Gen(genAdi); // Yeni gen oluştur
    yeniGen->sonraki = bas; // Yeni geni listenin başına ekle
    bas = yeniGen; // Baş göstericiyi güncelle
}

// Kromozomu ekrana yazdırma fonksiyonu
void Kromozom::ekranaYaz() const {
    Gen* mevcut = bas; // Mevcut gen göstericisi
    while (mevcut != nullptr) { // Liste sonuna kadar git
        std::cout << mevcut->ad << " "; // Geni ekrana yaz
        mevcut = mevcut->sonraki; // Sonraki gene geç
    }
    std::cout << std::endl; // Satır sonu
}

// Çaprazlama işlemi
void Kromozom::caprazlama(const Kromozom& diger, std::list<Kromozom>& populasyon) {
    int orta1 = genSayisiniGetir() / 2; // İlk kromozomun orta noktası
    int orta2 = diger.genSayisiniGetir() / 2; // İkinci kromozomun orta noktası

    Kromozom yeniKromozom1; // Yeni kromozom 1
    Kromozom yeniKromozom2; // Yeni kromozom 2

    // İlk kromozomun sol tarafı ve ikinci kromozomun sağ tarafı birleştiriliyor
    for (int i = 0; i < orta1; ++i) {
        yeniKromozom1.genEkle(genGetir(i));
    }
    for (int i = orta2; i < diger.genSayisiniGetir(); ++i) {
        yeniKromozom1.genEkle(diger.genGetir(i));
    }
    populasyon.push_back(yeniKromozom1); // Yeni kromozomu popülasyona ekle

    // İlk kromozomun sağ tarafı ve ikinci kromozomun sol tarafı birleştiriliyor
    for (int i = orta1; i < genSayisiniGetir(); ++i) {
        yeniKromozom2.genEkle(genGetir(i));
    }
    for (int i = 0; i < orta2; ++i) {
        yeniKromozom2.genEkle(diger.genGetir(i));
    }
    populasyon.push_back(yeniKromozom2); // Yeni kromozomu popülasyona ekle
}

// Mutasyon işlemi
void Kromozom::mutasyon(int genIndeksi) {
    if (genIndeksi < 0 || genIndeksi >= genSayisiniGetir()) { // Geçersiz indeks kontrolü
        std::cerr << "Gecersiz gen indeksi!" << std::endl;
        return;
    }

    Gen* mevcut = bas; // Mevcut gen göstericisi
    for (int i = 0; mevcut != nullptr && i < genIndeksi; ++i) {
        mevcut = mevcut->sonraki; // İstenilen gene git
    }

    if (mevcut != nullptr) {
        mevcut->ad = "X"; // Mutasyon işlemi
    }
}

// Gen sayısını döndürme fonksiyonu
int Kromozom::genSayisiniGetir() const {
    int sayac = 0; // Gen sayısı
    Gen* mevcut = bas; // Mevcut gen göstericisi
    while (mevcut != nullptr) {
        sayac++; // Sayacı artır
        mevcut = mevcut->sonraki; // Sonraki gene geç
    }
    return sayac; // Toplam gen sayısını döndür
}

// Belirli bir indeksteki geni döndürme fonksiyonu
std::string Kromozom::genGetir(int indeks) const {
    Gen* mevcut = bas; // Mevcut gen göstericisi
    for (int i = 0; mevcut != nullptr && i < indeks; ++i) {
        mevcut = mevcut->sonraki; // İstenilen gene git
    }
    return mevcut ? mevcut->ad : ""; // Geni döndür, yoksa boş döndür
}
