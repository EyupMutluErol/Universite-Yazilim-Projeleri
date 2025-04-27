/****************************************************************************
**					        SAKARYA ÜNİVERSİTESİ
**			        BİLGİSAYAR VE BİLİŞİM BİLİMLERİ FAKÜLTESİ
**				    BİLGİSAYAR MÜHENDİSLİĞİ BÖLÜMÜ
**				    PROGRAMLAMAYA GİRİŞİ DERSİ
**
**				ÖDEV NUMARASI : 2
**				ÖĞRENCİ ADI : Eyüp Mutlu Erol
**				ÖĞRENCİ NUMARASI : B231210101
**				DERS GRUBU : A Grubu
****************************************************************************/
#include<vector>
#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
using namespace std;



class GenelHesap {
public:
	float Bakiye;//Kripto paranın değerini tutacak değişken
	string HesapNo;//Hesap numarasının değerini tutacak değişken
	GenelHesap(string hesapno, float bakiye);//Genel Hesap sınıfından nesne üretilince çalışacak olan constructor
	~GenelHesap();////Genel Hesap sınıfından nesne üretilince çalışacak olan destructor
	bool KontrolHesapNo(string hesapno);//11 haneli hesap numarasını kontrol etmek için
	void setHesapNoAl(string hesapno);//hesap numarasını kullanıcıdan almak için
	void setBakiyeAl(float miktar);//başlangıç bakiyesini kullanıcıdan almak için
	string getHesapNoDöndür()const { return HesapNo; };//hesap numarasını programa return etmek için
	float getBakiyeDöndür()const { return Bakiye; };//bakiyeyi programa return etmek için
	void BilgileriGöster();//hesabın bilgilerini göstermek için
	void Al(float miktar);//hesaba para yüklemek için
	void Çek(float miktar);//hesaptan para çekmek için
	void BakiyeArttır();//Genel hesap bakiyesinin günlük % 1 artışını sağlamak için
	void BakiyeAzalt();//Genel hesap bakiyesinin 15 günde bir % 5 düşüşünü sağlamak için
};
void GenelHesap::BakiyeArttır() {
	Bakiye = (Bakiye)+(Bakiye * 1 / 100);
}
void GenelHesap::BakiyeAzalt() {
	Bakiye = (Bakiye)-(Bakiye * 5 / 100);
}
GenelHesap::GenelHesap(string hesapno, float bakiye) {
	setHesapNoAl(hesapno);
	setBakiyeAl(bakiye);
}
GenelHesap::~GenelHesap() {
}
bool GenelHesap::KontrolHesapNo(string hesapno) {  //Bu fonksiyon hesap numarasının 11 haneli olup olmadığını ve karakterlerin hepsinin rakam olup olmadığını kontrol eder ve buna göre true ya da false bir değer döndürür
	if (hesapno.length() != 11) {
		return false;
	}
	for (unsigned i = 0; i < hesapno.length(); i++) {
		if (!((hesapno.at(i) >= '0' && hesapno.at(i) <= '9'))) {
			return false;
		}
	}
	return true;
}
void GenelHesap::setHesapNoAl(string hesapno) { //Hesap numarası alma fonksiyonuna önce hesap numarası kontrol fonksiyonu gönderilir . Uygun hesap numarası girilene kadar kullanıcıdan hesap numarası istenir
	while (!(KontrolHesapNo(hesapno))) {
		cout << "Hatalı Hesap No Girişi , Lütfen 11 Haneli Bir Hesap Numarası Giriniz: ";
		cin >> hesapno;
	}
	HesapNo = hesapno;
}
void GenelHesap::setBakiyeAl(float bakiye) {  //Kullanıcıdan hesabın başlangıç bakiyesi istenir eğer kullanıcı 0 veya negatif bir sayı girerse hesaba 0 tl bakiye olarak atanır
	if (bakiye <= 0) {
		Bakiye = 0;
	}
	else {
		Bakiye = bakiye;
	}
}
void GenelHesap::BilgileriGöster() { //Hesabın Bilgileri Gösterilir
	cout << "Hesap Numarası: " << HesapNo << endl;
	cout << "Bakiye: " << Bakiye << endl;
}
void GenelHesap::Al(float miktar) {  //Kripto hesabına para yüklemeye yarar . 0 veya negatif bir sayı girilirse pozitif sayı girene kadar kullanıcıdan sayı tekrar istenir
	while (miktar <= 0) {
		cout << "Hatalı Giriş , Lütfen Uygun Bir Miktar Giriniz: ";
		cin >> miktar;
	}
	Bakiye += miktar;
}
void GenelHesap::Çek(float miktar) {  //Kripto hesabından para çekilmeye yarar . Negatif bir sayı girilirse pozitif sayı girilene kadar kullanıcıdan sayı tekrar istenir 
	while (miktar < 0 || miktar > Bakiye) {
		cout << "Hatalı Giriş , Lütfen Uygun Bir Miktar Giriniz: ";
		cin >> miktar;
	}
	Bakiye -= miktar;
}




class ÖzelHesap {
public:
	float Bakiye;
	string HesapNo;
	ÖzelHesap(string hesapno, float bakiye);
	~ÖzelHesap();
	bool KontrolHesapNo(string hesapno);
	void setHesapNoAl(string hesapno);
	void setBakiyeAl(float miktar);
	string getHesapNoDöndür()const { return HesapNo; };
	float getBakiyeDöndür()const { return Bakiye; };
	void BilgileriGöster();
	void Al(float miktar);
	void Çek(float miktar);
	void BakiyeArttır();//Özel hesap bakiyesini günlük %5 arttırmak için
	void BakiyeAzalt();//Özel hesap bakiyesini ayda rastgele 3 kez % 10 düşürmek için
};
void ÖzelHesap::BakiyeArttır() {
	Bakiye = (Bakiye)+(Bakiye * 5 / 100);
}
void ÖzelHesap::BakiyeAzalt() {
	Bakiye = (Bakiye)-(Bakiye * 10 / 100);
}
ÖzelHesap::ÖzelHesap(string hesapno, float bakiye) {
	setHesapNoAl(hesapno);
	setBakiyeAl(bakiye);
}
ÖzelHesap::~ÖzelHesap() {
}
bool ÖzelHesap::KontrolHesapNo(string hesapno) {
	if (hesapno.length() != 11) {
		return false;
	}
	for (unsigned i = 0; i < hesapno.length(); i++) {
		if (!((hesapno.at(i) >= '0' && hesapno.at(i) <= '9'))) {
			return false;
		}
	}
	return true;
}
void ÖzelHesap::setHesapNoAl(string hesapno) {
	while (!(KontrolHesapNo(hesapno))) {
		cout << "Hatalı Hesap No Girişi , Lütfen 11 Haneli Bir Hesap Numarası Giriniz: ";
		cin >> hesapno;
	}
	HesapNo = hesapno;
}
void ÖzelHesap::setBakiyeAl(float bakiye) {
	if (bakiye <= 0) {
		Bakiye = 0;
	}
	else {
		Bakiye = bakiye;
	}
}
void ÖzelHesap::BilgileriGöster() {
	cout << "Hesap Numarası: " << HesapNo << endl;
	cout << "Bakiye: " << Bakiye << endl;
}
void ÖzelHesap::Al(float miktar) {
	while (miktar <= 0) {
		cout << "Hatalı Giriş , Lütfen Uygun Bir Miktar Giriniz: ";
		cin >> miktar;
	}
	Bakiye += miktar;
}
void ÖzelHesap::Çek(float miktar) {
	while (miktar < 0 || miktar > Bakiye) {
		cout << "Hatalı Giriş , Lütfen Uygun Bir Miktar Giriniz: ";
		cin >> miktar;
	}
	Bakiye -= miktar;
}

#include<iostream>
#include<string>
using namespace std;

class Tarih {  //Tarih sınıfı gün bilgisini güncelleyerek kripto paranın değerini arttırmak veya azaltmak için tanımlanmıştır
private:
	int Gun, Ay, Yil;
	const int GunlerDizisi[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 }; //Sırasıyla aylardaki gün sayıları bir diziye atanmıştır
	const string AylarDizisi[12] = { "Ocak","Subat","Mart","Nisan","Mayis","Haziran","Temmuz","Agustos","Eylül","Ekim","Kasim","Aralik" };//Ayların isimleri bir diziye atanmıştır
public:
	Tarih(int gun = 15, int ay = 12, int yil = 2023);//Başlangıç tarihi default 15 Aralık 2023 olarak atanmıştır
	~Tarih();
	void setTarih(int gun, int ay, int yil);//Gün Ay Yıl bilgisini atamak için
	void setGun(int gun);//Gün bilgisini atamak için
	void setAy(int ay);//Ay bilgisini atamak için
	void setYil(int yil);//Yıl bilgisini atamak için
	void BilgileriGoster();//Tarih bilgisini göstermek için 
	void TarihiGuncelle();//Tarihi ilerletmek için
	int getGun() const { return Gun; };//Gün bilgisini return etmek için
	int getAy() const { return Ay; };//Ay bilgisini return etmek için
	int getYil() const { return Yil; };//Yıl bilgisini return etmek için
};
Tarih::Tarih(int gun, int ay, int yil) {
	setTarih(gun, ay, yil);
}
Tarih::~Tarih() {
}
void Tarih::setGun(int gun) { //Gün bilgisi uygun aralıktaysa gün değerine atanır aksi halde gün değeri 1'den başlatılır 
	if (gun >= 1 && gun <= GunlerDizisi[Ay - 1]) {
		Gun = gun;
	}
	else {
		Gun = 1;
	}
}
void Tarih::setAy(int ay) { //Ay bilgisi 1 ile 12 arasındaysa kaçıncı aya denk geliyorsa o ay değeri atanır
	if (ay >= 1 && ay <= 12) {
		Ay = ay;
	}
	else {
		Ay = 1;
	}
}
void Tarih::setYil(int yil) { //Yıl değeri 2023'ten büyük veya eşitse yıl değerine atanır aksi halde 2023 atanır
	if (yil >= 2023) {
		Yil = yil;
	}
	Yil = 2023;
}
void Tarih::setTarih(int gun, int ay, int yil) { //Gün atama , Ay atama ve Yıl atama fonksiyonları çağrılarak tarih değeri atanır
	setAy(ay);
	setGun(gun);
	setYil(yil);
}
void Tarih::BilgileriGoster() { //Tarih gösterilir
	cout << Gun << " " << AylarDizisi[Ay - 1] << " " << Yil << endl;
}
void Tarih::TarihiGuncelle() { // Günü , Ayı ve Yılı arttırmak için
	if (Gun < GunlerDizisi[Ay - 1]) { //Ayın günleri bitene kadar arttırılır bitince yeni aya geçilir ve gün değeri 1 olur . Aralığın sonunda ay değeri de 1 olur yıl değeri 1 artar
		Gun++;
	}
	else {
		Gun = 1;
		if (Ay < 12) {
			Ay++;
		}
		else {
			Ay = 1;
			Yil++;
		}
	}
}





int main() {
	setlocale(LC_ALL, "Turkish");
	Tarih tarih;
	vector<GenelHesap>GenelHesaplar;//açılan genel hesapları tutmak için
	vector<ÖzelHesap>ÖzelHesaplar;//açılan özel hesapları tutmak için
	while (true) {
		int seçim;
		cout << "Yapmak İstediğiniz İşlemi Seçin" << endl;
		cout << "Genel Hesap Açmak İçin (1)" << endl;
		cout << "Özel Hesap Açmak İçin (2)" << endl;
		cout << "Hesaba Para Eklemek İçin (3)" << endl;
		cout << "Hesaptan Para Çekmek İçin (4)" << endl;
		cout << "Açılan Hesapları Listelemek İçin (5)" << endl;
		cout << "Açılan Hesapların Bilgilerini Güncellemek İçin (6)" << endl;
		cout << "Seçiminizi Yapınız: ";
		cin >> seçim;
		cout << "-------------" << endl;
		switch (seçim) {
		case 1: {
			string hesapno;
			float bakiye;
			cout << "11 Haneli Hesap Numaranızı Girin: ";
			cin >> hesapno;
			cout << "Bakiye Giriniz: ";
			cin >> bakiye;
			cout << endl;
			GenelHesaplar.push_back(GenelHesap(hesapno, bakiye));//Girilen genel hesap bilgilerinden yeni bir genel hesap açar ve bilgilerini tutar
			GenelHesaplar.back().BilgileriGöster();//Son açılan genel hesabın bilgilerini gösterir
			cout << "----------------" << endl;
			break;
		}
		case 2: {
			string hesapno;
			float bakiye;
			cout << "11 Haneli Hesap Numaranızı Girin: ";
			cin >> hesapno;
			cout << "Bakiye Giriniz: ";
			cin >> bakiye;
			cout << endl;
			ÖzelHesaplar.push_back(ÖzelHesap(hesapno, bakiye));//Girilen özel hesap bilgilerinden yeni bir özel hesap açar ve bilgilerini tutar
			ÖzelHesaplar.back().BilgileriGöster();//Son açılan özel hesabın bilgilerini gösterir
			cout << "----------------" << endl;
			break;
		}
		case 3: {
			int seçim, hesapsayisi;
			float miktar;
			cout << "Genel Hesaba Para Eklemek İçin (1)" << endl;
			cout << "Özel Hesaba Para Eklemek İçin(2)" << endl;
			cout << "Seçiminizi Yapın: ";
			cin >> seçim;
			if (seçim == 1) {
				cout << "Kaçıncı Genel Hesaba Para Yüklemek İstiyorsunuz:";//Açılan kaçıncı genel hesaba para yükleneceği seçilir
				cin >> hesapsayisi;
				cout << "Eklemek İstediğiniz Miktarı Giriniz: ";
				cin >> miktar;
				cout << endl;
				GenelHesaplar[hesapsayisi - 1].Al(miktar);//Para yükleme işlemi gerçekleşir
				GenelHesaplar[hesapsayisi - 1].BilgileriGöster();//Para yüklendikten sonra hesabın bilgileri gösterilir
				cout << "------------------" << endl;
			}
			else if (seçim == 2) {
				cout << "Kaçıncı Özel Hesaba Para Yüklemek İstiyorsunuz:";//Açılan kaçıncı özel hesaba para yükleneceği seçilir
				cin >> hesapsayisi;
				cout << "Eklemek İstediğiniz Miktarı Giriniz: ";
				cin >> miktar;
				cout << endl;
				ÖzelHesaplar[hesapsayisi - 1].Al(miktar);//Para yükleme işlemi gerçekleşir
				ÖzelHesaplar[hesapsayisi - 1].BilgileriGöster();//Para yüklendikten sonra hesabın bilgileri gösterilir
				cout << "------------------" << endl;
			}
			break;
		}
		case 4: {
			int seçim, hesapsayisi;
			float miktar;
			cout << "Genel Hesaptan Para Çekmek İçin (1)" << endl;
			cout << "Özel Hesaptan Para Çekmek İçin (2)" << endl;
			cout << "Seçiminizi Yapın: ";
			cin >> seçim;
			if (seçim == 1) {
				cout << "Kaçıncı Genel Hesaptan Para Çekmek İstiyorsunuz: ";//Açılan kaçıncı genel hesaptan para çekileceği seçilir
				cin >> hesapsayisi;
				cout << "Çekmek İstediğiniz Miktarı Giriniz: ";
				cin >> miktar;
				cout << endl;
				GenelHesaplar[hesapsayisi - 1].Çek(miktar);//Para çekme işlemi gerçekleşir
				GenelHesaplar[hesapsayisi - 1].BilgileriGöster();//Para çekildikten sonra hesabın bilgileri gösterilir
				cout << "------------------" << endl;
			}
			else if (seçim == 2) {
				cout << "Kaçıncı Özel Hesaptan Para Çekmek İstiyorsunuz:";//Açılan kaçıncı özel hesaptan para çekileceği seçilir
				cin >> hesapsayisi;
				cout << "Çekmek İstediğiniz Miktarı Giriniz: ";
				cin >> miktar;
				cout << endl;
				ÖzelHesaplar[hesapsayisi - 1].Çek(miktar);//Para çekme işlemi gerçekleşir
				ÖzelHesaplar[hesapsayisi - 1].BilgileriGöster();//Para çekildikten sonra hesabın bilgileri gösterilir
				cout << "------------------" << endl;
			}
			break;
		}
		case 5: {
			for (int j = 0; j < GenelHesaplar.size(); j++) {
				GenelHesaplar[j].BilgileriGöster();//Açılan genel hesaplar listelenir
				cout << "Hesap Türü : Genel Hesap" << endl;//Hesabın türü yazdırılır
				cout << endl;
			}
			for (int k = 0; k < ÖzelHesaplar.size(); k++) {
				ÖzelHesaplar[k].BilgileriGöster();//Açılan özel hesaplar listelenir
				cout << "Hesap Türü : Özel Hesap" << endl;//Hesabın türü yazdırılır
				cout << endl;
			}
			break;
		}
		case 6: {
			int GünSayisi;
			cout << "Hesapların Bilgilerini Kaç Günlük Güncellemek İstiyorsunuz: ";//Hesapların kaç gün sonraki halinin listeleneceği kullanıcıdan istenir
			cin >> GünSayisi;
			for (int i = 1; i < GünSayisi + 1; i++) {
				tarih.BilgileriGoster();//her günün tarihi ve altında hesapların güncel bilgileri listelenir
				cout << endl;
				for (int j = 0; j < GenelHesaplar.size(); j++) {//Döngü , açılan tüm genel hesaplar için yapılacağından genel hesapların boyutu kadar tekrarlanır
					GenelHesaplar[j].BilgileriGöster();
					cout << "Hesap Türü : Genel Hesap" << endl;
					cout << endl;
					if (i % 15 == 0) {
						GenelHesaplar[j].BakiyeAzalt();//Genel hesapların bakiyesi her 15 günde bir istenilen oranda azaltılır
					}
					else {
						GenelHesaplar[j].BakiyeArttır();//Genel hesapların bakiyesi her gün geçtikçe istenilen oranda arttırılır
					}
				}
				for (int k = 0; k < ÖzelHesaplar.size(); k++) {//Döngü , açılan tüm özel hesaplar için de yapılacağından özel hesapların boyutu kadar da ayrıca tekrarlanır
					srand(time(NULL));//372 ile 380. satırlar arasında özel hesabın düşüş yaşayacağı rastgele 3 gün random olarak belirlenir
					int RastgeleGünler[3];
					for (int m = 0; m < 3; m++) {
						int RastgeleGün;
						do {
							RastgeleGün = rand() % 30 + 1;
						} while (RastgeleGün == RastgeleGünler[0] || RastgeleGün == RastgeleGünler[1]);
						RastgeleGünler[m] = RastgeleGün;
					}
					ÖzelHesaplar[k].BilgileriGöster();
					cout << "Hesap Türü : Özel Hesap" << endl;
					cout << endl;
					if (i == RastgeleGünler[0] || i == RastgeleGünler[1] || i == RastgeleGünler[2]) {//Rastgele belirlenen 3 günde özel hesap istenilen oranda düşüş sağlar
						ÖzelHesaplar[k].BakiyeAzalt();
					}
					else {
						ÖzelHesaplar[k].BakiyeArttır();//Rastgele 3 gün dışındaki günlerde özel hesap istenilen oranda artış sağlar
					}
				}
				cout << "-----------" << endl;
				tarih.TarihiGuncelle();//Kullanıcının istediği güne kadar tarih güncellenir ve ertesi gün genel ve özel hesaplar güncel halleriyle tekrar listelenir
			}

		}
		}
	}
}

