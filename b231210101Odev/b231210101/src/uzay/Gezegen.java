/**
*
* Eyüp Mutlu Erol mutlu.erol@ogr.sakarya.edu.tr
* 26.04.2025
* Gezegen sınıfı,bir gezegenin temel özellikleri ve zamanını (Zaman nesnesi aracılığıyla) yönetir.
*/

package uzay;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.Objects;

public class Gezegen {
    private String ad;
    private final int gunlukSaat;
    private Zaman gezegenZamani; // Şu anki zamanı tutar
    private final Zaman baslangicZamani; // Dosyadan okunan ilk zamanı saklar (mini simülasyon için)
    private int nufus;

    private static final DateTimeFormatter DATE_FORMATTER = DateTimeFormatter.ofPattern("dd.MM.yyyy");

    public Gezegen(String ad, int gunlukSaat, LocalDate baslangicTarihi) {
        this.ad = Objects.requireNonNull(ad, "Gezegen adı null olamaz.");
        this.gunlukSaat = gunlukSaat;
        this.baslangicZamani = new Zaman(baslangicTarihi, gunlukSaat);
        this.gezegenZamani = new Zaman(baslangicTarihi, gunlukSaat);
        this.nufus = 0;
    }

    /** Gezegenin saatini 1 saat ilerletir */
    public void saatIlerle() {
        this.gezegenZamani.saatIlerle();
    }


    public LocalDate getTarih() { return this.gezegenZamani.getTarih(); }
    public String getTarihFormatted() { return this.gezegenZamani.getTarihFormatted(DATE_FORMATTER); }
    public int getSaat() { return this.gezegenZamani.getSaat(); }

    /** Mini simülasyon için gezegenin ilk zaman durumunun bir kopyasını döndürür */
    public Zaman getBaslangicZamaniKopyasi() {
        return new Zaman(this.baslangicZamani); // Zaman'ın copy constructor'ını kullanır
    }

    // --- Diğer Getters & Setters ---
    public String getAd() { return ad; }
    public int getGunlukSaat() { return gunlukSaat; }
    public int getNufus() { return nufus; }
    public void setNufus(int nufus) { this.nufus = Math.max(0, nufus); }


    @Override
    public String toString() { return this.ad; }
}


