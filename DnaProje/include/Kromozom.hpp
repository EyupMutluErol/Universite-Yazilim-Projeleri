#ifndef KROMOZOM_HPP
#define KROMOZOM_HPP

#include "Gen.hpp"
#include <iostream>
#include <list>

// Kromozom sınıfı, genleri yönetir.
class Kromozom {
public:
    Gen* bas; // Kromozomun ilk geni

    Kromozom(); // Yapıcı
    ~Kromozom(); // Yıkıcı
    void genEkle(const std::string& genAdi); // Gene ekle
    void ekranaYaz() const; // Kromozomu ekrana yazdır
    void caprazlama(const Kromozom& diger, std::list<Kromozom>& populasyon); // Çaprazlama işlemi
    void mutasyon(int genIndeksi); // Mutasyon işlemi
    int genSayisiniGetir() const; // Gen sayısını döndür
    std::string genGetir(int indeks) const; // Belirli bir indeksteki geni döndür
};

#endif // KROMOZOM_HPP
