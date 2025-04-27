/**
*
* Eyüp Mutlu Erol mutlu.erol@ogr.sakarya.edu.tr
* 26.04.2025
* Belirli bir bağlamdaki zamanı (tarih ve saat) ve ilerlemesini yönetir.Kopyalanabilir yapıdadır.
*/

package uzay;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.Objects;


public class Zaman {
    private LocalDate tarih;
    private int saat;
    private final int gunlukSaat;

    /** Ana Constructor */
    public Zaman(LocalDate baslangicTarihi, int gunlukSaat) {
        if (gunlukSaat <= 0) {
            throw new IllegalArgumentException("Günlük saat pozitif olmalıdır.");
        }
        this.tarih = Objects.requireNonNull(baslangicTarihi, "Başlangıç tarihi null olamaz.");
        this.gunlukSaat = gunlukSaat;
        this.saat = 0;
    }

    /** Copy Constructor */
    public Zaman(Zaman other) {
        Objects.requireNonNull(other, "Kopyalanacak Zaman nesnesi null olamaz.");
        this.tarih = other.tarih; // LocalDate immutable olduğu için direkt atanabilir
        this.saat = other.saat;
        this.gunlukSaat = other.gunlukSaat;
    }

    public void saatIlerle() {
        this.saat++;
        if (this.saat >= this.gunlukSaat) {
            this.saat = 0;
            this.tarih = this.tarih.plusDays(1);
        }
    }

    // --- Getters ---
    public LocalDate getTarih() { return tarih; }
    public int getSaat() { return saat; }
    public int getGunlukSaat() { return gunlukSaat; }

    public String getTarihFormatted(DateTimeFormatter formatter) {
        Objects.requireNonNull(formatter, "Formatlayıcı null olamaz.");
        return this.tarih.format(formatter);
    }


     public void setSaat(int saat) {
         if (saat >= 0 && saat < this.gunlukSaat) { this.saat = saat; }
     }
     public void setTarih(LocalDate tarih) {
          this.tarih = Objects.requireNonNull(tarih, "Tarih null olamaz.");
     }

    @Override
    public String toString() {
        return tarih.toString() + " " + String.format("%02d:00", saat);
    }

    // Mini simülasyon için eşitlik kontrolü
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Zaman zaman = (Zaman) o;
        return saat == zaman.saat && gunlukSaat == zaman.gunlukSaat && Objects.equals(tarih, zaman.tarih);
    }

    @Override
    public int hashCode() {
        return Objects.hash(tarih, saat, gunlukSaat);
    }
}