#ifndef GEN_HPP
#define GEN_HPP

#include <string>

// Gen sınıfı, genin adını ve bir sonraki geni tutar.
class Gen {
public:
    std::string ad; // Genin adı
    Gen* sonraki;   // Bir sonraki genin göstericisi

    // Yapıcı fonksiyon
    Gen(const std::string& genAdi) : ad(genAdi), sonraki(nullptr) {}
};

#endif //  GEN_HPP
