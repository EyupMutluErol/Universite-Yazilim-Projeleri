/**
*
* Eyüp Mutlu Erol mutlu.erol@ogr.sakarya.edu.tr
* 26.04.2025
* Kisi sınıfı bir bireyin bilgilerini ve ömür yönetimini içerir.
*/

package uzay;

public class Kisi {
    private String isim;
    private int yas;
    private int kalanOmur; // saat cinsinden
    private String uzayAraciAdi; // Hangi araca ait olduğunu belirtir
    private boolean hayattaMi;

    public Kisi(String isim, int yas, int kalanOmur, String uzayAraciAdi) {
        this.isim = isim;
        this.yas = yas;
        this.kalanOmur = kalanOmur;
        this.uzayAraciAdi = uzayAraciAdi;
        this.hayattaMi = kalanOmur > 0; // Başlangıçta ömrü varsa hayatta
    }

    /**
     * Simülasyonun her saatlik adımı için çağrılır.
     * Kişinin kalan ömrünü bir saat azaltır ve ömrü biterse durumunu günceller.
     */
    public void saatIlerle() {
        if (hayattaMi) {
            kalanOmur--;
            if (kalanOmur <= 0) {
                hayattaMi = false;
                kalanOmur = 0; // Negatif olmasın
            }
        }
    }

    public boolean isHayatta() {
        return hayattaMi;
    }

    public String getUzayAraciAdi() {
        return uzayAraciAdi;
    }

    public String getIsim() {
        return isim;
    }

    public int getYas() {
        return yas;
    }

    public int getKalanOmur() {
        return kalanOmur;
    }


    @Override
    public String toString() {
        return isim + " (" + yas + ", Ömür: " + kalanOmur + " saat, Durum: " + (hayattaMi ? "Hayatta" : "Öldü") + ")";
    }
}

