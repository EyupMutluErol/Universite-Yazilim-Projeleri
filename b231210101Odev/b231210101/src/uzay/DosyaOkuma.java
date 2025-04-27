/**
*
* Eyüp Mutlu Erol mutlu.erol@ogr.sakarya.edu.tr
* 26.04.2025
* Dosya okuma işlemlerini yapan sınıftır. d.M.yyyy ve dd.MM.yyyy formatlarını okuyabilir.
*/

package uzay;

import java.io.*;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.util.*;


public class DosyaOkuma {

	/*tek ve iki basamaklı girilecek gün ve aylar için okuma işlemi*/
    private static final DateTimeFormatter DATE_FORMATTER = DateTimeFormatter.ofPattern("d.M.yyyy");

    /**
     * Belirtilen dosyayı satır satır okur ve satırları liste olarak döndürür.
     */
    private static List<String> dosyayiOku(String dosyaYolu) {
        List<String> satirlar = new ArrayList<>();
        File dosya = new File(dosyaYolu);
        if (!dosya.exists()) {
             System.err.println("HATA: Dosya bulunamadı -> " + dosyaYolu);
             return satirlar;
        }

        try (BufferedReader reader = new BufferedReader(new FileReader(dosya))) {
            String satir;
            while ((satir = reader.readLine()) != null) {
                if (!satir.trim().isEmpty() && !satir.startsWith("#") && !satir.startsWith("//")) {
                    satirlar.add(satir.trim());
                }
            }
        } catch (IOException e) {
            System.err.println("Dosya okunurken hata oluştu: " + dosyaYolu);
            e.printStackTrace();
        }
        return satirlar;
    }

    /*
     * Kisiler dosyasını okur ve Kisi nesneleri listesi oluşturur.
     */
    public static List<Kisi> kisileriOku(String dosyaYolu) {
        List<Kisi> kisiler = new ArrayList<>();
        List<String> satirlar = dosyayiOku(dosyaYolu);

        for (String satir : satirlar) {
            String[] parcalar = satir.split("#");
            if (parcalar.length == 4) {
                try {
                    String isim = parcalar[0].trim();
                    int yas = Integer.parseInt(parcalar[1].trim());
                    int kalanOmur = Integer.parseInt(parcalar[2].trim());
                    String uzayAraciAdi = parcalar[3].trim();

                    if (yas < 0 || kalanOmur < 0) {
                         System.err.println("Uyarı: Geçersiz yaş veya kalan ömür değeri olan kişi satırı atlandı -> " + satir);
                         continue;
                    }
                    Kisi kisi = new Kisi(isim, yas, kalanOmur, uzayAraciAdi);
                    kisiler.add(kisi);
                } catch (NumberFormatException e) {
                    System.err.println("Hatalı sayı formatı olan kişi satırı atlandı: " + satir + " - Hata: " + e.getMessage());
                }
            } else {
                System.err.println("Hatalı kişi satırı atlandı (eksik/fazla alan): " + satir);
            }
        }
        return kisiler;
    }

    /*
     * Gezegenler dosyasını okur ve Gezegen nesneleri listesi oluşturur.
     */
    public static List<Gezegen> gezegenleriOku(String dosyaYolu) {
        List<Gezegen> gezegenler = new ArrayList<>();
        List<String> satirlar = dosyayiOku(dosyaYolu);

        for (String satir : satirlar) {
            String[] parcalar = satir.split("#");
            if (parcalar.length == 3) {
                try {
                    String isim = parcalar[0].trim();
                    int gunlukSaat = Integer.parseInt(parcalar[1].trim());
                    String tarihStr = parcalar[2].trim();
                    // Güncellenmiş formatlayıcı ile parse et
                    LocalDate tarih = LocalDate.parse(tarihStr, DATE_FORMATTER);

                    if (gunlukSaat <= 0) {
                         System.err.println("Uyarı: Geçersiz günlük saat değeri olan gezegen satırı atlandı -> " + satir);
                         continue;
                    }
                    Gezegen gezegen = new Gezegen(isim, gunlukSaat, tarih);
                    gezegenler.add(gezegen);
                } catch (NumberFormatException e) {
                    System.err.println("Hatalı sayı formatı olan gezegen satırı atlandı: " + satir + " - Hata: " + e.getMessage());
                } catch (DateTimeParseException e) {
                    System.err.println("Hatalı tarih formatı veya geçersiz tarih, gezegen satırı atlandı: " + satir + " - Hata: " + e.getMessage());
                }
            } else {
                System.err.println("Hatalı gezegen satırı atlandı (eksik/fazla alan): " + satir);
            }
        }
        return gezegenler;
    }

    /*
     * Uzay araçları dosyasını okur, mevcut gezegen listesiyle eşleştirir ve UzayAraci nesneleri oluşturur.
     */
    public static List<UzayAraci> uzayAraclariOku(String dosyaYolu, List<Gezegen> gezegenler) {
        List<UzayAraci> uzayAraclari = new ArrayList<>();
        List<String> satirlar = dosyayiOku(dosyaYolu);
        Map<String, Gezegen> gezegenMap = new HashMap<>();
        for (Gezegen g : gezegenler) { gezegenMap.put(g.getAd(), g); }

        for (String satir : satirlar) {
            String[] parcalar = satir.split("#");
            if (parcalar.length == 5) {
                try {
                    String uzayAraciAdi = parcalar[0].trim();
                    String cikisGezegeniAdi = parcalar[1].trim();
                    String varisGezegeniAdi = parcalar[2].trim();
                    String cikisTarihiStr = parcalar[3].trim();
                    int mesafeSaat = Integer.parseInt(parcalar[4].trim());

                    // Güncellenmiş formatlayıcı ile parse edilir
                    LocalDate cikisTarihi = LocalDate.parse(cikisTarihiStr, DATE_FORMATTER);

                    Gezegen cikisGezegeni = gezegenMap.get(cikisGezegeniAdi);
                    Gezegen varisGezegeni = gezegenMap.get(varisGezegeniAdi);

                    if (cikisGezegeni == null || varisGezegeni == null || cikisGezegeniAdi.equals(varisGezegeniAdi) || mesafeSaat <= 0 || cikisTarihi.isBefore(cikisGezegeni.getTarih())) {
                         System.err.println("Geçersiz uzay aracı verisi, satır atlandı -> " + satir); continue;
                    }
                    UzayAraci uzayAraci = new UzayAraci(uzayAraciAdi, cikisGezegeni, varisGezegeni, cikisTarihi, mesafeSaat);
                    uzayAraclari.add(uzayAraci);
                } catch (NumberFormatException e) { System.err.println("Sayı format hatası, araç atlandı: " + satir);
                } catch (DateTimeParseException e) { System.err.println("Hatalı tarih formatı veya geçersiz tarih, araç atlandı: " + satir + " - Hata: " + e.getMessage());
                } catch (Exception e) { System.err.println("Araç satırı işlenirken hata: " + satir); e.printStackTrace(); }
            } else { System.err.println("Hatalı araç satırı (alan sayısı): " + satir); }
        }
        return uzayAraclari;
    }
}
