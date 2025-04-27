/**
*
* Eyüp Mutlu Erol mutlu.erol@ogr.sakarya.edu.tr
* 26.04.2025
* Uzay aracı bilgilerini, durumunu ve yolculuk detaylarını yönetir.Varış tarihi başlangıçta hesaplanır.
*/

package uzay;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;


public class UzayAraci {
    private String isim;
    private Gezegen cikisGezegeni;
    private Gezegen varisGezegeni;
    private LocalDate cikisTarihi; // Planlanan
    private int mesafeSaat;

    private AracDurumu durum;
    private int hedefeKalanSaat;
    private LocalDate hedefeVarisTarihi; // Başlangıçta hesaplanan gerçek tarih
    private boolean hareketEttiMi;
    private boolean nufusEklendiMi; // Nüfusun varışta eklendiğini takip eden boolean degisken

    private static final DateTimeFormatter DATE_FORMATTER = DateTimeFormatter.ofPattern("dd.MM.yyyy");

    public UzayAraci(String isim, Gezegen cikisGezegeni, Gezegen varisGezegeni, LocalDate cikisTarihi, int mesafeSaat) {
        this.isim = Objects.requireNonNull(isim);
        this.cikisGezegeni = Objects.requireNonNull(cikisGezegeni);
        this.varisGezegeni = Objects.requireNonNull(varisGezegeni);
        this.cikisTarihi = Objects.requireNonNull(cikisTarihi);
        this.mesafeSaat = mesafeSaat;

        this.durum = AracDurumu.BEKLIYOR;
        this.hedefeKalanSaat = this.mesafeSaat;
        this.hedefeVarisTarihi = null; // Hesaplama Simulasyon'da yapılacak
        this.hareketEttiMi = false;
        this.nufusEklendiMi = false;
    }

    /** Varış tarihini ayarlamak için Simulasyon sınıfı tarafından kullanılır. */
    public void setHesaplanmisVarisTarihi(LocalDate varisTarihi) {
         this.hedefeVarisTarihi = varisTarihi;
    }

    /** Nüfusun varışta eklendiğini işaretler. */
    public void setIsNufusEklendi() {
        this.nufusEklendiMi = true;
    }

    /** Nüfusun daha önce eklenip eklenmediğini döndürür. */
    public boolean isNufusEklendi() {
        return nufusEklendiMi;
    }


    public void saatIlerleYolda() {
        if (this.durum == AracDurumu.YOLDA) {
            if (this.hedefeKalanSaat > 0) { this.hedefeKalanSaat--; }
            if (this.hedefeKalanSaat <= 0) {
                this.durum = AracDurumu.VARDI;
                this.hedefeKalanSaat = 0;
            }
        }
    }

    public void kalkisYap() {
         if (this.durum == AracDurumu.BEKLIYOR && !this.hareketEttiMi) {
             this.durum = AracDurumu.YOLDA;
             this.hareketEttiMi = true;
         }
     }

    public void imhaEt() {
        if (this.durum != AracDurumu.IMHA) {
            this.durum = AracDurumu.IMHA;
            this.hedefeKalanSaat = 0;
            this.hedefeVarisTarihi = null;
        }
    }

    public List<Kisi> getHayattakiYolcular(List<Kisi> tumKisiler) {
        List<Kisi> yolcular = new ArrayList<>();
        if (tumKisiler == null) return yolcular;
        for (Kisi kisi : tumKisiler) {
            if (this.isim.equals(kisi.getUzayAraciAdi()) && kisi.isHayatta()) {
                yolcular.add(kisi);
            }
        }
        return yolcular;
    }

    // --- GETTERLAR ---
    public String getIsim() { return isim; }
    public Gezegen getCikisGezegeni() { return cikisGezegeni; }
    public Gezegen getVarisGezegeni() { return varisGezegeni; }
    public LocalDate getCikisTarihi() { return cikisTarihi; }
    public int getMesafeSaat() { return mesafeSaat; }
    public AracDurumu getDurum() { return durum; }
    public int getHedefeKalanSaat() { return hedefeKalanSaat; }
    public LocalDate getHedefeVarisTarihi() { return hedefeVarisTarihi; }
    public boolean isHareketEttiMi() { return hareketEttiMi; }

    /**
     * Hedefe varış tarihini formatlanmış String olarak döndürür veya uygun mesajı verir.
     */
     public String getHedefeVarisTarihiFormatted() {
         if (durum == AracDurumu.IMHA) {
             return "--";
         }
         if (hedefeVarisTarihi == null) {
              if (durum == AracDurumu.BEKLIYOR || !hareketEttiMi) {
                  return "Hesaplanıyor...";
              } else {
                  return "Hesaplanamadı";
              }
         }
         return hedefeVarisTarihi.format(DATE_FORMATTER);
     }

    /**
     * Hedefe kalan saati String olarak döndürür veya "--" döndürür.
     */
     public String getHedefeKalanSaatFormatted() {
          if (durum == AracDurumu.IMHA) {
              return "--";
          }
          return String.valueOf(hedefeKalanSaat);
     }

    @Override
    public String toString() {
        return "UzayAraci{" + "isim='" + isim + '\'' + ", durum=" + durum + '}';
    }
}