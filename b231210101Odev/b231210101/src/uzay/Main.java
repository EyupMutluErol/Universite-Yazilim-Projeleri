/**
*
* Eyüp Mutlu Erol mutlu.erol@ogr.sakarya.edu.tr
* 26.04.2025
* Programı çalıştıran ana sınıftır.
*/

package uzay;

import java.util.List;

public class Main {

    public static void main(String[] args) {

        // Veri Dosyalarını Oku
        String kisilerDosya = "veriler/Kisiler.txt";
        String gezegenlerDosya = "veriler/Gezegenler.txt";
        String araclarDosya = "veriler/Araclar.txt";

        List<Kisi> kisiler = DosyaOkuma.kisileriOku(kisilerDosya);
        List<Gezegen> gezegenler = DosyaOkuma.gezegenleriOku(gezegenlerDosya);
        List<UzayAraci> uzayAraclari = DosyaOkuma.uzayAraclariOku(araclarDosya, gezegenler);

        // Dosya okuma sonrası temel kontroller 
        if (gezegenler.isEmpty()) {
             System.err.println("HATA: Hiç gezegen verisi okunamadı. Lütfen " + gezegenlerDosya + " dosyasını kontrol edin.");
             return; // Gezegen yoksa simülasyon anlamsız
        }
        if (uzayAraclari.isEmpty() && !gezegenler.isEmpty()) {
             System.out.println("UYARI: Hiç uzay aracı verisi okunamadı veya gezegenlerle eşleştirilemedi. Gezegenler gösterilecek ancak araç olmayacak.");
             // Araçsız da gezegenler gösterilebilir, devam edilebilir.
        }
         if (kisiler.isEmpty() && !uzayAraclari.isEmpty()){
              System.out.println("UYARI: Hiç kişi verisi okunamadı. Araçlar boş olarak yolculuk yapacak veya imha olacak.");
         }


        // Simülasyonu Başlat
        Simulasyon.baslatSimulasyon(gezegenler, uzayAraclari, kisiler);

        System.out.println("\nProgram sonlandı.");
    }
}










