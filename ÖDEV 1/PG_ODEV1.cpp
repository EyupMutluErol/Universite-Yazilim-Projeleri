/****************************************************************************
**					       SAKARYA ÜNİVERSİTESİ
**		          BİLGİSAYAR VE BİLİŞİM BİLİMLERİ FAKÜLTESİ
**				      BİLGİSAYAR MÜHENDİSLİĞİ BÖLÜMÜ
**				        PROGRAMLAMAYA GİRİŞİ DERSİ
**
**				ÖDEV NUMARASI : 1
**				ÖĞRENCİ ADI : Eyüp Mutlu Erol
**				ÖĞRENCİ NUMARASI : b231210101
**				DERS GRUBU : A Grubu
****************************************************************************/


#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<cmath>

using namespace std;

struct Ogrenci {    //Öğrenci isimli yapı veri tipi oluşturulur.
	string isim;
	string soyisim;
	double kısa_sınav1;
	double kısa_sınav2;
	double odev1;
	double odev2;
	double vize;
	double final;
	double ortalama;
	string harf_notu;
};

int rastgeleNotUret(int i, int ogrenci_sayisi) { //Rastgele not üretmek için bir fonksiyon tanımlanır.
	if (i + 1 <= double(ogrenci_sayisi) / 5) //Öğrenci sayısının yüzde 20'si 80 ile 100 arası bir not alır.
		return 80 + (rand() % 21);
	else if (i + 1 <= double(ogrenci_sayisi) / 10 * 5) //Öğrenci sayısının yüzde 50'si  50 ile 80 arası bir not alır.
		return 50 + (rand() % 31);
	else
		return 0 + (rand() % 51); //Öğrenci sayısının yüzde 30'u  0 ile 50 arası bir not alır.
}

int main()
{

	setlocale(LC_ALL, "Turkish");//Türkçe karakterleri kullanabilmek için setlocale fonksiyonu kullanılır.

	double ödev1_ağırlığı, ödev2_ağırlığı, kısa_sınav1_ağırlığı, kısa_sınav2_ağırlığı, vizenin_ağırlığı, gecme_notuna_etki;
	int sayi;
	cout << "Öğrenci Sayısını Giriniz: ";
	cin >> sayi;
	cout << "Yıl İçi Notunun Geçme Notuna Etkisinin Yüzdesini Giriniz : ";
	cin >> gecme_notuna_etki;
	cout << "Toplamı 100 olacak şekilde aşağıdaki yüzde değerlerini giriniz!" << endl;
	cout << "1.Ödevin Ortalamaya Etkisinin Yüzdesini Giriniz : ";
	cin >> ödev1_ağırlığı;
	cout << "2.Ödevin Ortalamaya Etkisinin Yüzdesini Giriniz : ";
	cin >> ödev2_ağırlığı;
	cout << "1.Kısa Sınavın Ortalamaya Etkisinin Yüzdesini Giriniz : ";
	cin >> kısa_sınav1_ağırlığı;
	cout << "2.Kısa Sınavın Ortalamaya Etkisinin Yüzdesini Giriniz : ";
	cin >> kısa_sınav2_ağırlığı;
	cout << "Vizenin Ortalamaya Etkisinin Yüzdesini Giriniz : ";
	cin >> vizenin_ağırlığı;
	cout << endl;


	Ogrenci ogrenciler[1000];//Muhtemel sınıf mevcudunun çok üstünde bir değer parametrenin içine değer olarak verilir.O yüzden 1000 gibi yüksek bir değer girilir.Ancak döngü sınıf mevcudu kadar döndürülür.
	srand(time(0));//Rastgele veriler üretmek için srand fonksiyonu kullanılır.
	string öğrencilerin_isimleri[] = { "Berk","Mert","Efe","Sinan","Melih","Cem","Kaan","Rıfat","Selim","Yavuz","Feyzullah","Görkem","Mustafa","Kemal","Enver","Serdar","Aytunç","Tolga","Deniz","Hikmet","Refik","Hayati","İrfan Can","Ferdi","İsmail","Yusuf","Kerem","Akın",
	"Defne","Yağmur","Ahsen","İrem","Zeynep","Ayşegül","Asrın","Banu","Bengü","Yıldız","Ebru","Ceren","Eda","Işıl","Irmak","Pelin","Sevinç","Beyza","Büşra","Esma","Nisanur","Hazal","Sena","Elif","Azra","Ece","Ravza","Zümra","Açelya","Almila","Aybüke","Ayşe" };
	string öğrencilerin_soyisimleri[] = { "Yılmaz","Çelik","Demir","Aslan","Rüzgar","Şener","Ilgaz","Öztürk","Şahin","Yiğit","Poyraz","Mutlu","Kaya","Çetin","Akın","Yıldız","Bulut","Kahveci","Demirel","Özdemir","Kural","Ergün","Akdemir","Karademir","Yıldırım","Şimşek","Yalçın",
	"Erdem","Karakurt","Alemdar","Özgür","Eren","Özçelik","Ayhan","Karayel","Çetin","Özkan","Uğur","Korkmaz","Çakır","Işık","Aydoğdu","Yüksek","Akaydın","Aydın","Gök","Zor","Albayrak","Ertekin","Karataş","Ulusoy","Canatan","Dinç","Serbes","Toprak","Ak","Al","Kara","Kılıç","Yağcı" };
	string harf_notları[] = { "AA","BA","BB","CB","CC","DC","DD","FD","FF" };

	int toplamNot = 0;
	double standartSapma = 0.0;
	double enYuksekNot = 0;
	double enDusukNot = 100;
	int sınıfHarfNotlari[9] = { 0 };

	//İki alt satırda tanımlanan ve for döngüsüne sokulan i sayısı dizilerin içinde döndürülecek olan sayıdır.
	//Dizilerin içinde döndürülecek olan i sayısı sıfırdan başlar ve sınıf mevcudu olarak kullanıcıdan alınan sayi değişkeninden küçük olduğu sürece 1 arttırılarak döngüyü döndürmeye devam eder ve sıradaki öğrencinin bilgilerini atar.
	for (int i = 0; i < sayi; i++) {

		ogrenciler[i].isim = öğrencilerin_isimleri[rand() % 60];  //87-99 satırları arasında sıradaki öğrencinin isim-soyisim ve not bilgileri atanıp ortalaması hesaplanır.
		ogrenciler[i].soyisim = öğrencilerin_soyisimleri[rand() % 60];
		ogrenciler[i].vize = rastgeleNotUret(i, sayi);
		ogrenciler[i].odev1 = rastgeleNotUret(i, sayi);
		ogrenciler[i].odev2 = rastgeleNotUret(i, sayi);
		ogrenciler[i].kısa_sınav1 = rastgeleNotUret(i, sayi);
		ogrenciler[i].kısa_sınav2 = rastgeleNotUret(i, sayi);
		ogrenciler[i].final = rastgeleNotUret(i, sayi);
		ogrenciler[i].ortalama = ((ogrenciler[i].vize * vizenin_ağırlığı / 100) +
			(ogrenciler[i].odev1 * ödev1_ağırlığı / 100) +
			(ogrenciler[i].odev2 * ödev2_ağırlığı / 100) +
			(ogrenciler[i].kısa_sınav1 * kısa_sınav1_ağırlığı / 100) +
			(ogrenciler[i].kısa_sınav2 * kısa_sınav2_ağırlığı / 100)) * (gecme_notuna_etki) / 100 + (ogrenciler[i].final * (100 - gecme_notuna_etki) / 100);
		//Aşağıdaki if - else if - else koşullarında öğrencilerin ortalamalarına göre aldıkları harf notu hesaplanır.Ayrıca o harf notunu alan öğrenci sayısı da bir bir arttırılarak o harf notunu alan öğrenci sayısı hesaplanır.
		if (ogrenciler[i].ortalama >= 90 && ogrenciler[i].ortalama <= 100) {
			ogrenciler[i].harf_notu = harf_notları[0];
			sınıfHarfNotlari[0]++;
		}
		else if (ogrenciler[i].ortalama >= 85 && ogrenciler[i].ortalama < 90) {
			ogrenciler[i].harf_notu = harf_notları[1];
			sınıfHarfNotlari[1]++;
		}
		else if (ogrenciler[i].ortalama >= 80 && ogrenciler[i].ortalama < 85) {
			ogrenciler[i].harf_notu = harf_notları[2];
			sınıfHarfNotlari[2]++;
		}
		else if (ogrenciler[i].ortalama >= 75 && ogrenciler[i].ortalama < 80) {
			ogrenciler[i].harf_notu = harf_notları[3];
			sınıfHarfNotlari[3]++;
		}
		else if (ogrenciler[i].ortalama >= 65 && ogrenciler[i].ortalama < 75) {
			ogrenciler[i].harf_notu = harf_notları[4];
			sınıfHarfNotlari[4]++;
		}
		else if (ogrenciler[i].ortalama >= 58 && ogrenciler[i].ortalama < 65) {
			ogrenciler[i].harf_notu = harf_notları[5];
			sınıfHarfNotlari[5]++;
		}
		else if (ogrenciler[i].ortalama >= 50 && ogrenciler[i].ortalama < 58) {
			ogrenciler[i].harf_notu = harf_notları[6];
			sınıfHarfNotlari[6]++;
		}
		else if (ogrenciler[i].ortalama >= 40 && ogrenciler[i].ortalama < 50) {
			ogrenciler[i].harf_notu = harf_notları[7];
			sınıfHarfNotlari[7]++;
		}
		else {
			ogrenciler[i].harf_notu = harf_notları[8];
			sınıfHarfNotlari[8]++;
		}
		//Aşağıdaki 10 satır boyunca sıradaki öğrencinin bilgileri ekrana yazdırılır.
		cout << "Öğrencinin İsmi : " << ogrenciler[i].isim << endl;
		cout << "Öğrencinin Soyismi : " << ogrenciler[i].soyisim << endl;
		cout << "1.Kısa Sınav Notu : " << ogrenciler[i].kısa_sınav1 << endl;
		cout << "2.Kısa Sınav Notu : " << ogrenciler[i].kısa_sınav2 << endl;
		cout << "1.Ödev Notu : " << ogrenciler[i].odev1 << endl;
		cout << "2.Ödev Notu : " << ogrenciler[i].odev2 << endl;
		cout << "Vize Notu : " << ogrenciler[i].vize << endl;
		cout << "Final Notu : " << ogrenciler[i].final << endl;
		cout << "Ortalaması : " << ogrenciler[i].ortalama << endl;
		cout << "Harf Notu : " << ogrenciler[i].harf_notu << endl;
		cout << endl;

		toplamNot += ogrenciler[i].ortalama;//Bütün öğrencilerin ortalamaları toplanır ve toplamNot değişkeninde saklanır.

		//Alt satırdaki if koşulunda sınıfın en yüksek ortalaması hesaplanır.
		if (ogrenciler[i].ortalama > enYuksekNot)
			enYuksekNot = ogrenciler[i].ortalama;
		//Alt satırdaki if koşulunda sınıfın en düşük ortalaması hesaplanır.
		if (ogrenciler[i].ortalama < enDusukNot)
			enDusukNot = ogrenciler[i].ortalama;
	}

	double sınıfOrtalama = double(toplamNot) / sayi;//Sınıfın ortalaması hesaplanır.

	//Aşağıdaki for döngüsünde sınıfın standart sapması hesaplanır.
	for (int i = 0; i < sayi; i++) {
		standartSapma += (ogrenciler[i].ortalama - sınıfOrtalama) * (ogrenciler[i].ortalama - sınıfOrtalama);
	}
	standartSapma = sqrt(standartSapma / sayi);
	//Aşağıdaki 4 satır boyunca sınıfın notları ile ilgili bilgiler ekrana yazdırılır.
	cout << "Sınıfın Not İstatistikleri" << endl;
	cout << "Sınıf Ortalaması : " << sınıfOrtalama << endl;
	cout << "Standart Sapma : " << standartSapma << endl;
	cout << "En Yüksek Ortalama : " << enYuksekNot << endl;
	cout << "En Düşük Ortalama : " << enDusukNot << endl;
	cout << endl;

	//Aşağıdaki 10 satır boyunca sınıftaki öğrencilerin kaçının hangi harf notunu aldığı ve bu öğrencilerin yüzdesi ekrana yazdırılır.
	cout << "Harf Notu İstatistikleri" << endl;
	cout << "AA Alan Öğrenci Sayısı : " << sınıfHarfNotlari[0] << " Öğrenci /" << " Sınıftaki Yüzdesi : % " << (double(sınıfHarfNotlari[0]) / sayi * 100) << endl;
	cout << "BA Alan Öğrenci Sayısı : " << sınıfHarfNotlari[1] << " Öğrenci /" << " Sınıftaki Yüzdesi : % " << (double(sınıfHarfNotlari[1]) / sayi * 100) << endl;
	cout << "BB Alan Öğrenci Sayısı : " << sınıfHarfNotlari[2] << " Öğrenci /" << " Sınıftaki Yüzdesi : % " << (double(sınıfHarfNotlari[2]) / sayi * 100) << endl;
	cout << "CB Alan Öğrenci Sayısı : " << sınıfHarfNotlari[3] << " Öğrenci /" << " Sınıftaki Yüzdesi : % " << (double(sınıfHarfNotlari[3]) / sayi * 100) << endl;
	cout << "CC Alan Öğrenci Sayısı : " << sınıfHarfNotlari[4] << " Öğrenci /" << " Sınıftaki Yüzdesi : % " << (double(sınıfHarfNotlari[4]) / sayi * 100) << endl;
	cout << "DC Alan Öğrenci Sayısı : " << sınıfHarfNotlari[5] << " Öğrenci /" << " Sınıftaki Yüzdesi : % " << (double(sınıfHarfNotlari[5]) / sayi * 100) << endl;
	cout << "DD Alan Öğrenci Sayısı : " << sınıfHarfNotlari[6] << " Öğrenci /" << " Sınıftaki Yüzdesi : % " << (double(sınıfHarfNotlari[6]) / sayi * 100) << endl;
	cout << "FD Alan Öğrenci Sayısı : " << sınıfHarfNotlari[7] << " Öğrenci /" << " Sınıftaki Yüzdesi : % " << (double(sınıfHarfNotlari[7]) / sayi * 100) << endl;
	cout << "FF Alan Öğrenci Sayısı : " << sınıfHarfNotlari[8] << " Öğrenci /" << " Sınıftaki Yüzdesi : % " << (double(sınıfHarfNotlari[8]) / sayi * 100) << endl;

}



