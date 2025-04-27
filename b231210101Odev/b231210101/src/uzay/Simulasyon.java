/**
*
* Eyüp Mutlu Erol mutlu.erol@ogr.sakarya.edu.tr
* 26.04.2025
* Uzay simülasyonunu yöneten ana sınıftır.
*/

package uzay;

import java.time.LocalDate;
import java.util.*;


public class Simulasyon {

    // Simülasyonu başlatan ana metot
    public static void baslatSimulasyon(List<Gezegen> gezegenler, List<UzayAraci> uzayAraclari, List<Kisi> tumKisiler) {

        // Başlangıç Nüfusunu Hesapla
        hesaplaBaslangicNufus(gezegenler, uzayAraclari, tumKisiler);

        // Başlangıçta tüm varış tarihlerini hesapla

        hesaplaTumVarisTarihleriOnceden(gezegenler, uzayAraclari);



        //Başlangıç Durumunu Yazdır
        ekranTemizle();
        System.out.println("--- BAŞLANGIÇ DURUMU ---");
        yazdirDurum(gezegenler, uzayAraclari);
        bekle(2000);

        // Ana Simülasyon Döngüsü
        int adim = 0;
        while (true) {
            adim++;

            //Tüm Gezegenlerin Saatini İlerlet
            for (Gezegen gezegen : gezegenler) {
                gezegen.saatIlerle();
            }

            //Tüm Kişilerin ömrünü azalt ve Varış Sonrası Ölümde Nüfusu Düzelt
            for (Kisi kisi : tumKisiler) {
                boolean yasiyorMuydu = kisi.isHayatta(); // Önceki durumu al
                kisi.saatIlerle(); // Ömrü azalt

                // Eğer kişi bu adımda öldüyse ve gemisi VARDI durumundaysa, nüfusu azalt
                if (yasiyorMuydu && !kisi.isHayatta()) {
                    // Ölen kişinin gemisini bul
                    UzayAraci olduguArac = null;
                    for(UzayAraci arac : uzayAraclari) {
                        if (arac.getIsim().equals(kisi.getUzayAraciAdi())) {
                            olduguArac = arac;
                            break;
                        }
                    }
                    // Eğer gemisi bulunduysa ve durumu VARDI ise
                    if (olduguArac != null && olduguArac.getDurum() == AracDurumu.VARDI) {
                         // Varış gezegeninin nüfusunu 1 azalt
                         azaltNufus(olduguArac.getVarisGezegeni(), 1);
                    }
                }
            } // Kişi döngüsü sonu

            // Uzay Araçlarının Durumunu Güncelle (Kalkış, Yolda İlerleme, Nüfus Ekleme)
            for (UzayAraci arac : uzayAraclari) {
                // c.1. Kalkış Kontrolü
                if (!arac.isHareketEttiMi() && arac.getDurum() == AracDurumu.BEKLIYOR) {
                    Gezegen cikisGezegeni = arac.getCikisGezegeni();
                    LocalDate gezegenTarihi = cikisGezegeni.getTarih();
                    LocalDate aracKalkisTarihi = arac.getCikisTarihi();
                    if (gezegenTarihi.isEqual(aracKalkisTarihi) || gezegenTarihi.isAfter(aracKalkisTarihi)) {
                        azaltNufus(cikisGezegeni, arac.getHayattakiYolcular(tumKisiler).size());
                        arac.kalkisYap();
                    }
                }

                //  Yoldaki Araçları İlerlet
                if (arac.getDurum() == AracDurumu.YOLDA) {
                     arac.saatIlerleYolda(); // Saati azaltır, vardıysa durumu VARDI yapar
                }

                // Varışta Nüfus Artırma Kontrolü (SADECE bir kez yapılır)
                if (arac.getDurum() == AracDurumu.VARDI && !arac.isNufusEklendi()) {
                    // O anda hayatta olanları ekle
                    List<Kisi> hayattakiYolcularVarisAninda = arac.getHayattakiYolcular(tumKisiler);
                    if (!hayattakiYolcularVarisAninda.isEmpty()) {
                         arttirNufus(arac.getVarisGezegeni(), hayattakiYolcularVarisAninda.size());
                    }
                    arac.setIsNufusEklendi(); // Nüfusun eklendiğini/kontrol edildiğini işaretle
                }

            } // İlk araç güncelleme döngüsü sonu


            // Genel İmha Kontrolü
            for (UzayAraci arac : uzayAraclari) {
                if (arac.getDurum() != AracDurumu.IMHA) {
                    if (arac.getHayattakiYolcular(tumKisiler).isEmpty()) {
                         arac.imhaEt();
                    }
                }
            } 


            // Bitiş kontrolü
            boolean tumAraclarHedefte = true;
            for (UzayAraci arac : uzayAraclari) {
                if (arac.getDurum() != AracDurumu.VARDI && arac.getDurum() != AracDurumu.IMHA) {
                    tumAraclarHedefte = false;
                    break;
                }
            }


            // Ekranı Güncelle
            ekranTemizle();
            System.out.println("--- Simülasyon Saati: " + adim + " ---");
            yazdirDurum(gezegenler, uzayAraclari);
            bekle(10);


            // Bitiş Koşulunu Kontrol Et
            if (tumAraclarHedefte) {
                System.out.println("\n===============================");
                System.out.println("=== SİMÜLASYON TAMAMLANDI ===");
                System.out.println("Toplam Geçen Süre: " + adim + " saat");
                System.out.println("===============================");
                ekranTemizle();
                System.out.println("--- SON DURUM (Saat: " + adim + ") ---");

                yazdirDurum(gezegenler, uzayAraclari);
                break;
            }
        } // Ana while döngüsü sonu
    }


     /** Başlangıçta varış tarihlerini hesaplar */
     private static void hesaplaTumVarisTarihleriOnceden(List<Gezegen> gezegenler, List<UzayAraci> uzayAraclari) {
         if (uzayAraclari == null || gezegenler == null || gezegenler.isEmpty()) { return; }
         Map<String, Zaman> baslangicZamanlari = new HashMap<>();
         for(Gezegen g : gezegenler) { baslangicZamanlari.put(g.getAd(), g.getBaslangicZamaniKopyasi()); }
         for (UzayAraci arac : uzayAraclari) {
             Gezegen cikisGezegeni = arac.getCikisGezegeni(); Gezegen varisGezegeni = arac.getVarisGezegeni();
             LocalDate planlananKalkisTarihi = arac.getCikisTarihi(); int mesafe = arac.getMesafeSaat();
             if (cikisGezegeni == null || varisGezegeni == null || planlananKalkisTarihi == null || mesafe <= 0) { arac.setHesaplanmisVarisTarihi(null); continue; }
             Zaman kalkisZamanSim = baslangicZamanlari.get(cikisGezegeni.getAd());
             if (kalkisZamanSim == null) { arac.setHesaplanmisVarisTarihi(null); continue; }
             kalkisZamanSim = new Zaman(kalkisZamanSim); int kalkisAdim = 0;
             while (kalkisZamanSim.getTarih().isBefore(planlananKalkisTarihi)) {
                 kalkisZamanSim.saatIlerle(); kalkisAdim++;
                 if (kalkisAdim > 2000000) { System.err.println("UYARI: " + arac.getIsim() + " kalkış adımı limiti!"); kalkisAdim = -1; break; }
             }
             if (kalkisAdim < 0) { arac.setHesaplanmisVarisTarihi(null); continue; }
             Zaman varisZamanSim = baslangicZamanlari.get(varisGezegeni.getAd());
             if (varisZamanSim == null) { arac.setHesaplanmisVarisTarihi(null); continue; }
             varisZamanSim = new Zaman(varisZamanSim);
             for (int i = 0; i < kalkisAdim; i++) { varisZamanSim.saatIlerle(); }
             for (int i = 0; i < mesafe; i++) { varisZamanSim.saatIlerle(); }
             arac.setHesaplanmisVarisTarihi(varisZamanSim.getTarih());
         }
     }

    /** Başlangıç nüfusunu hesaplar */
    private static void hesaplaBaslangicNufus(List<Gezegen> gezegenler, List<UzayAraci> uzayAraclari, List<Kisi> tumKisiler) {
        Map<String, Integer> gezegenNufusMap = new HashMap<>();
        for (Gezegen g : gezegenler) { gezegenNufusMap.put(g.getAd(), 0); }
        for (UzayAraci arac : uzayAraclari) {
            if (arac.getDurum() == AracDurumu.BEKLIYOR) {
                String cikisGezegenAdi = arac.getCikisGezegeni().getAd();
                int aracYolcuSayisi = arac.getHayattakiYolcular(tumKisiler).size();
                gezegenNufusMap.put(cikisGezegenAdi, gezegenNufusMap.getOrDefault(cikisGezegenAdi, 0) + aracYolcuSayisi);
            }
        }
        for (Gezegen g : gezegenler) { g.setNufus(gezegenNufusMap.getOrDefault(g.getAd(), 0)); }
    }

    /** Nüfusu azaltır */
    private static void azaltNufus(Gezegen gezegen, int miktar) {
        if (gezegen != null && miktar > 0) { gezegen.setNufus(Math.max(0, gezegen.getNufus() - miktar)); }
    }

    /** Nüfusu artırır */
    private static void arttirNufus(Gezegen gezegen, int miktar) {
         if (gezegen != null && miktar > 0) { gezegen.setNufus(gezegen.getNufus() + miktar); }
    }

    /** Mevcut durumu formatlı yazdırır */
     public static void yazdirDurum(List<Gezegen> gezegenler, List<UzayAraci> araclar) {
         int gezegenSutunGenisligi = 22; int labelSutunGenisligi = 10; int planetsPerRow = 5;
         System.out.println("GEZEGENLER");
         if (gezegenler.isEmpty()) { System.out.println("Gösterilecek gezegen yok."); }
         else {
             for (int i = 0; i < gezegenler.size(); i += planetsPerRow) {
                 List<Gezegen> currentRowPlanets = gezegenler.subList(i, Math.min(i + planetsPerRow, gezegenler.size()));
                 System.out.printf("%-" + labelSutunGenisligi + "s", "");
                 for (Gezegen g : currentRowPlanets) { System.out.print(centerString("--- " + g.getAd() + " ---", gezegenSutunGenisligi)); }
                 for (int k = currentRowPlanets.size(); k < planetsPerRow; k++) { System.out.printf("%-" + gezegenSutunGenisligi + "s", ""); } System.out.println();
                 System.out.printf("%-" + labelSutunGenisligi + "s", "Tarih");
                 for (Gezegen g : currentRowPlanets) { System.out.print(centerString(g.getTarihFormatted(), gezegenSutunGenisligi)); }
                 for (int k = currentRowPlanets.size(); k < planetsPerRow; k++) { System.out.printf("%-" + gezegenSutunGenisligi + "s", ""); } System.out.println();
                 System.out.printf("%-" + labelSutunGenisligi + "s", "Nüfus");
                 for (Gezegen g : currentRowPlanets) { System.out.print(centerString(String.valueOf(g.getNufus()), gezegenSutunGenisligi)); }
                 for (int k = currentRowPlanets.size(); k < planetsPerRow; k++) { System.out.printf("%-" + gezegenSutunGenisligi + "s", ""); } System.out.println();
                 if (i + planetsPerRow < gezegenler.size()) { System.out.println(); }
             }
         } System.out.println();
         System.out.println("Uzay Araçları:");
         if (araclar.isEmpty()) { System.out.println("Gösterilecek uzay aracı yok."); }
         else {
             System.out.printf("%-20s %-15s %-20s %-20s %-30s %-30s\n", "Araç Adı", "Durum", "Çıkış", "Varış", "Hedefe Kalan Saat", "Hedefe Varacağı Tarih");
             araclar.sort(Comparator.comparing(UzayAraci::getIsim));
             for (UzayAraci a : araclar) {
                 System.out.printf("%-20s %-15s %-20s %-20s %-30s %-30s\n", a.getIsim(), a.getDurum(), a.getCikisGezegeni().getAd(), a.getVarisGezegeni().getAd(), a.getHedefeKalanSaatFormatted(), a.getHedefeVarisTarihiFormatted());
             }
         }
     }

    /** String'i ortalar */
    private static String centerString(String text, int width) {
        if (text == null) text = ""; if (text.length() >= width) { return String.format("%-" + width + "s", text); }
        int padding = width - text.length(); int leftPadding = padding / 2; int rightPadding = padding - leftPadding;
        return " ".repeat(leftPadding) + text + " ".repeat(rightPadding);
    }

    /** Ekranı temizler */
    public static void ekranTemizle() {
        try { String os = System.getProperty("os.name"); if (os.contains("Windows")) { new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor(); } else { System.out.print("\033[H\033[2J"); System.out.flush(); }
        } catch (Exception e) { /* Sessiz kal */ }
    }

    /** Bekletir */
    private static void bekle(int ms) {
        if (ms <= 0) return; try { Thread.sleep(ms); } catch (InterruptedException e) { Thread.currentThread().interrupt(); }
    }
} // Class Sonu