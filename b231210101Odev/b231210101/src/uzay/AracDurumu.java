/**
*
* Eyüp Mutlu Erol mutlu.erol@ogr.sakarya.edu.tr
* 26.04.2025
* Uzay aracının olası durumlarını tanımlar.
*/

package uzay;

public enum AracDurumu {
    BEKLIYOR("Bekliyor"), // Kalkış için gezegende bekliyor
    YOLDA("Yolda"),      // Gezegenler arası seyahat ediyor
    VARDI("Vardı"),      // Hedef gezegene ulaştı
    IMHA("İMHA");        // Tüm yolcular öldüğü için imha oldu

    private final String label;

    AracDurumu(String label) {
        this.label = label;
    }

    @Override
    public String toString() {
        return label;
    }
}