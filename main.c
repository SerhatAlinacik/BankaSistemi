#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

struct Musteri // Müþteri bilgilerini tuttuðumuz struct.
{
    int MusteriNo;
    char tc[12];
    char isim[30];
    char soyisim[30];
    char sehir[30];
    int telefon;
    int sifre;
    double para;
    
}musteri;

struct Gecici //Müþteriden onay almak için kullandýðýmýz verileri tuttuðumuz struct.
{
	char tc2[12];
    int sifre2;
    
}gecici;

void Bakiye() //Müþterinin bakiyesini görüntülediði fonksiyon.
{
    system("cls");

    FILE *dosya = fopen("musteriler.txt", "r"); //Dosyayý okuma modunda açýyoruz.
    
    if (dosya == NULL) {	
        printf("Dosya Bulunamadi!");	//Dosyayý bulamazsa hata veriyor.
        return;
    }

    while (fscanf(dosya, "Musteri No: %d\n", &musteri.MusteriNo) == 1) //MusteriNo deðerini onaylayýnca verileri okuyor daha sonra if koþuluna giriyor.
	{
        fscanf(dosya, "TC        : %[^\n]\n", musteri.tc);
        fscanf(dosya, "Isim      : %[^\n]\n", musteri.isim);
        fscanf(dosya, "Soyisim   : %[^\n]\n", musteri.soyisim);
        fscanf(dosya, "Sehir     : %[^\n]\n", musteri.sehir);
        fscanf(dosya, "Telefon   : %d\n", &musteri.telefon);
        fscanf(dosya, "Sifre     : %d\n", &musteri.sifre);
        fscanf(dosya, "Para      : %lf\n", &musteri.para);
        fscanf(dosya, "\n");

        if (strcmp(musteri.tc, gecici.tc2) == 0 && musteri.sifre == gecici.sifre2) //Strcmp kullanaracak TC ve Þifre kontrolü yapýyoruz.
		{
            printf("Hesabýnýzdaki Bakiye: %.2lf\n", musteri.para);
            break;
        }
    }

    fclose(dosya);
}


void MusteriSil()	//Müþteri Silme Fonksiyonu.
 {
    system("cls");

    int SilMusteriNo;
    
    printf("Silinecek Musteri No: ");	//Silinecek müþterinin MusteriNo bilgisi alýnýyor.
    scanf("%d", &SilMusteriNo);

    FILE *dosya = fopen("musteriler.txt", "r");		//Silme iþlemi için iki dosyaya ihtiyacýmýz var ana dosyayý okuma, ikinci dosyayý yazma modunda açýyoruz.
    FILE *dosya2 = fopen("musteriler2.txt", "w");

    if (dosya == NULL || dosya2 == NULL) 
	{
        printf("Dosya Acilamadi!");		//Dosyayý bulamazsa hata veriyor.
        return;
    }

    int bulundu = 0;

    while (fscanf(dosya, "Musteri No	: %d\n", &musteri.MusteriNo) == 1) //Dosyadaki deðerleri okuyor.
	{
        fscanf(dosya, "TC				: %[^\n]\n", musteri.tc);
        fscanf(dosya, "Isim				: %[^\n]\n", musteri.isim);
        fscanf(dosya, "Soyisim			: %[^\n]\n", musteri.soyisim);
        fscanf(dosya, "Sehir			: %[^\n]\n", musteri.sehir);
        fscanf(dosya, "Telefon			: %d\n", &musteri.telefon);
        fscanf(dosya, "Sifre			: %d\n", &musteri.sifre);
        fscanf(dosya, "Para				: %lf\n", &musteri.para);

        if (musteri.MusteriNo != SilMusteriNo) 		//Eðer müþteri numarasý ile silinmek istenen numara uyuþmuyorsa verileri yeni dosyaya yazýyor, uyuþan numara ise yazýlmýyor. Böylece uyuþan numara silinmiþ oluyor.
		{
            fprintf(dosya2, "Musteri No		: %d\n", musteri.MusteriNo);
            fprintf(dosya2, "TC				: %s\n", musteri.tc);
            fprintf(dosya2, "Isim 			: %s\n", musteri.isim);
            fprintf(dosya2, "Soyisim 		: %s\n", musteri.soyisim);
            fprintf(dosya2, "Sehir			: %s\n", musteri.sehir);
            fprintf(dosya2, "Telefon		: %d\n", musteri.telefon);
            fprintf(dosya2, "Sifre			: %d\n", musteri.sifre);
            fprintf(dosya2, "Para			: %.2lf\n", musteri.para);
            	
        } 
		else 
		{
            bulundu = 1;	//Baþarýlý ise,
        }
    }

    fclose(dosya);
    fclose(dosya2);
							//Baþarýsýz ise aþaðýdaki if koþullarýna giriyor.
    if (bulundu == 0) {
        printf("Musteri Bulunamadi!\n");
        remove("musteriler2.txt");
        return;
    }

    if (remove("musteriler.txt") != 0) {
        printf("Dosya Silinemedi/Bulunamadi!!");
        return;
    }

    if (rename("musteriler2.txt", "musteriler.txt") != 0) {
        printf("Dosya Degistirilemedi!!");
        return;
    }

    printf("Musteri Silindi.\n");
}




void MusteriEkle() 		//Müþteri Ekleme Fonksiyonu.
{
    system("cls");

    printf("TC             : ");	//Eklenecek müþteri için veri alýnýyor.
    scanf("%s", musteri.tc);
    printf("Isim           : ");
    scanf("%s", musteri.isim);
    printf("Soyisim        : ");
    scanf("%s", musteri.soyisim);
    printf("Sehir          : ");
    scanf("%s", musteri.sehir);
    printf("Telefon        : ");
    scanf("%d", &musteri.telefon);

    srand(time(0));		//Rastgele sayý üretmek için kullanýlan fonksiyon.
    
    musteri.MusteriNo = rand() % 9000000 + 1000000;		//Rastgele müþteri numarasý ve þifre üretiliyor, otomatik olarak para deðeri 0 belirleniyor.
    musteri.sifre = rand() % 1000 + 1000;
    musteri.para = 0.00;

    FILE *dosya = fopen("musteriler.txt", "a");		//Dosyayý ekleme modunda açýyoruz.

    if (dosya == NULL) 
	{
        printf("Dosya Bulunamadi!");
        return;
    }

    fprintf(dosya, "Musteri No: %d\n", musteri.MusteriNo);		//Dosyaya ekleme iþlemi.
    fprintf(dosya, "TC        : %s\n", musteri.tc);
    fprintf(dosya, "Isim      : %s\n", musteri.isim);
    fprintf(dosya, "Soyisim   : %s\n", musteri.soyisim);
    fprintf(dosya, "Sehir     : %s\n", musteri.sehir);
    fprintf(dosya, "Telefon   : %d\n", musteri.telefon);
    fprintf(dosya, "Sifre     : %d\n", musteri.sifre);
    fprintf(dosya, "Para      : %.2lf\n", musteri.para);
    fprintf(dosya, "\n");
    
    fclose(dosya);
    
    printf("Sistem Tarafýndan Otomatik Olusturulan Sifreniz... : %d\n", musteri.sifre);		//Kullanýcý ekleniyor ve otomatik þifresi kullanýcýya bildiriliyor.
    printf("Musteri Bilgileri Kaydedildi!\n");
    
}



void MusteriListele() 	//Müþteri Listeleme Fonksiyonu.
{
    system("cls");
    
    FILE *dosya = fopen("musteriler.txt", "r");		//Dosyayý okuma modunda açýyoruz.

    if (dosya == NULL) 
	{
        printf("Dosya bulunamadi!\n");
        return;
    }

    printf("Sistemde Kayitli Musterilerin Listesi... \n\n\n");

    while (fscanf(dosya, "Musteri No: %d\n", &musteri.MusteriNo) == 1)		//Doyadan verileri okuyoruz ve konsola yazdýrýyoruz. 
	{
        fscanf(dosya, "TC        : %[^\n]\n", musteri.tc);
        fscanf(dosya, "Isim      : %[^\n]\n", musteri.isim);
        fscanf(dosya, "Soyisim   : %[^\n]\n", musteri.soyisim);
        fscanf(dosya, "Sehir     : %[^\n]\n", musteri.sehir);
        fscanf(dosya, "Telefon   : %d\n", &musteri.telefon);
        fscanf(dosya, "Sifre     : %d\n", &musteri.sifre);
        fscanf(dosya, "Para      : %lf\n", &musteri.para);			
															
																
        printf("Musteri No         : %d\n", musteri.MusteriNo);
        printf("TC                 : %s\n", musteri.tc);
        printf("Isim               : %s\n", musteri.isim);
        printf("Soyisim            : %s\n", musteri.soyisim);
        printf("Sehir              : %s\n", musteri.sehir);
        printf("Telefon            : %d\n", musteri.telefon);
        printf("Sifre              : %d\n", musteri.sifre);
        printf("Para               : %.2lf\n", musteri.para);
        printf("\n");
    }

    fclose(dosya);
    
}



int CalisanMenusu()		//Çalýþanýn gördüðü menü. 
{		
    int sec3;
    
    printf("\n 1 - - - MUSTERI EKLE \n");
    printf("\n 2 - - - MUSTERI SIL \n");
    printf("\n 3 - - - MUSTERI LISTELE \n");
    printf("\n 4 - - - KAPAT... :");
    scanf("%d", &sec3);
    
    return sec3;
    
}



void CalisanIslem() 	//Çalýsanlarýn iþlemrinin yapýldýðý switch-case yapýsý fonksiyonu.
{
	system("cls");
	
	printf("\n\n Degerli Calisanimiz, Hos Geldiniz...\n\n");
	
    int sec3 = CalisanMenusu();
    
    while (sec3 != 4) {
    		
        switch (sec3) {
            case 1:
                MusteriEkle();
                break;
            case 2:
                MusteriSil();
                break;
            case 3:
                MusteriListele();
                break;
            default:
                printf("Yanlis Secim...\n");
                break;
        }
        sec3 = CalisanMenusu();
    }
	
	
    printf("Ana Menuye Donuluyor...\n");
    
}



void ParaYatir() 	//Para Yatýrma Fonksiyonu.
{
    system("cls");
    
    
    double YatirilacakMiktar;		

    printf("Yatirmak Istediginiz Miktari Giriniz... : ");	//Müþteriden yatýracaðý miktarý alýyoruz.
    scanf("%lf", &YatirilacakMiktar);

    FILE *dosya = fopen("musteriler.txt", "r+");  //Dosyayý okuma ve kaydetme modunda açýyoruz.
    
    if (dosya == NULL) 
	{
        printf("Dosya Bulunamadi!");
        return;
    }

    int bulunduyatir = 0;
    long int dosyaBaslangic = ftell(dosya);		//ftell fonksiyonu oluþturuyoruz. 

    while (fscanf(dosya, "Musteri No: %d\n", &musteri.MusteriNo) == 1) //Müþteri bulunup okunuyor.
	{
        fscanf(dosya, "TC        : %[^\n]\n", musteri.tc);
        fscanf(dosya, "Isim      : %[^\n]\n", musteri.isim);
        fscanf(dosya, "Soyisim   : %[^\n]\n", musteri.soyisim);
        fscanf(dosya, "Sehir     : %[^\n]\n", musteri.sehir);
        fscanf(dosya, "Telefon   : %d\n", &musteri.telefon);
        fscanf(dosya, "Sifre     : %d\n", &musteri.sifre);
        fscanf(dosya, "Para      : %lf\n", &musteri.para);
        fscanf(dosya, "\n");

        if (strcmp(musteri.tc, gecici.tc2) == 0 && musteri.sifre == gecici.sifre2) 	//Giriþ kontrolü yapýlýyor, eðer doðru ise iþlem yapýlýyor ve para hesaba ekleniyor.
		{
            musteri.para += YatirilacakMiktar;
            bulunduyatir = 1;
            
            fseek(dosya, dosyaBaslangic, SEEK_SET);		//fseek ile dosyaBaslangic önceki konumuna gönderilir ve karýþýklýk engellenir.
            fprintf(dosya, "Musteri No: %d\n", musteri.MusteriNo);
            fprintf(dosya, "TC        : %s\n", musteri.tc);
            fprintf(dosya, "Isim      : %s\n", musteri.isim);
            fprintf(dosya, "Soyisim   : %s\n", musteri.soyisim);
            fprintf(dosya, "Sehir     : %s\n", musteri.sehir);
            fprintf(dosya, "Telefon   : %d\n", musteri.telefon);
            fprintf(dosya, "Sifre     : %d\n", musteri.sifre);
            fprintf(dosya, "Para      : %.2lf\n", musteri.para);
            fprintf(dosya, "\n");
            break;
        }
        
        dosyaBaslangic = ftell(dosya);		//ftell fonksiyonu ile dosya konumunu kaydediyoruz ve karýþmasýný önlüyoruz. 
    }

    fclose(dosya);

    if (bulunduyatir) 
	{
        printf("Para Yatirildi...\n");
    } else 
	{
        printf("Musteri Bulunamadi...!\n");
    }
}






void ParaCek() 	//Para Çekme Fonksiyonu, Matematik iþlemi dýþýnda ayný fonkisyon.
{
    system("cls");
    
    double CekilecekMiktar;

    printf("Cekilecek Miktar: ");
    scanf("%lf", &CekilecekMiktar);

    FILE *dosya = fopen("musteriler.txt", "r+");
    if (dosya == NULL) 
	{
        printf("Dosya Bulunamadi...!");
        return;
    }

    int bulunducek = 0;
    long int dosyaBaslangic = ftell(dosya);

    while (fscanf(dosya, "Musteri No: %d\n", &musteri.MusteriNo) == 1) 
	{
        fscanf(dosya, "TC        : %[^\n]\n", musteri.tc);
        fscanf(dosya, "Isim      : %[^\n]\n", musteri.isim);
        fscanf(dosya, "Soyisim   : %[^\n]\n", musteri.soyisim);
        fscanf(dosya, "Sehir     : %[^\n]\n", musteri.sehir);
        fscanf(dosya, "Telefon   : %d\n", &musteri.telefon);
        fscanf(dosya, "Sifre     : %d\n", &musteri.sifre);
        fscanf(dosya, "Para      : %lf\n", &musteri.para);
        fscanf(dosya, "\n");

        if (strcmp(musteri.tc, gecici.tc2) == 0 && musteri.sifre == gecici.sifre2) 
		{
            musteri.para -= CekilecekMiktar;
            bulunducek = 1;
            
            fseek(dosya, dosyaBaslangic, SEEK_SET);
            fprintf(dosya, "Musteri No: %d\n", musteri.MusteriNo);
            fprintf(dosya, "TC        : %s\n", musteri.tc);
            fprintf(dosya, "Isim      : %s\n", musteri.isim);
            fprintf(dosya, "Soyisim   : %s\n", musteri.soyisim);
            fprintf(dosya, "Sehir     : %s\n", musteri.sehir);
            fprintf(dosya, "Telefon   : %d\n", musteri.telefon);
            fprintf(dosya, "Sifre     : %d\n", musteri.sifre);
            fprintf(dosya, "Para      : %.2lf\n", musteri.para);
            fprintf(dosya, "\n");
            break;
        }
        dosyaBaslangic = ftell(dosya);
    }

    fclose(dosya);

    if (bulunducek) 
	{
        printf("Para Cekildi.\n");
    } else 
	{
        printf("Musteri Bulunamadi!\n");
    }
}




void ParaTransfer()	//Para Transferi Fonksiyonu.
 {
    system("cls");
    
    struct Musteri gonderen;	//Alan ve Gönderen olarak iki struct belirtiyoruz.
    struct Musteri alan;
    
    double transferMiktar;
    int transferMusteriNo;

    printf("Para Gondermek Istediginiz MusteriNo...: ");
    scanf("%d", &transferMusteriNo);

    printf("Transfer Etmek Istediginiz Miktar...: ");
    scanf("%lf", &transferMiktar);

    FILE *dosya = fopen("musteriler.txt", "r+");	//Kullanýcýdan deðerleri alýyoruz ve dosyayý açýyoruz.
    if (dosya == NULL)
	 {
        printf("Dosya Bulunamadi...!");
        return;
    }
    
    long int dosyaBaslangic = ftell(dosya);
    
    int gonderenBulundu = 0;	//Doðrulamak için iki deðer oluþturduk.
    int alanBulundu = 0;

    while (fscanf(dosya, "Musteri No: %d\n", &gonderen.MusteriNo) == 1)	//Gönderici bilgilerini okuyoruz.
	 {
        fscanf(dosya, "TC        : %[^\n]\n", gonderen.tc);
        fscanf(dosya, "Isim      : %[^\n]\n", gonderen.isim);
        fscanf(dosya, "Soyisim   : %[^\n]\n", gonderen.soyisim);
        fscanf(dosya, "Sehir     : %[^\n]\n", gonderen.sehir);
        fscanf(dosya, "Telefon   : %d\n", &gonderen.telefon);
        fscanf(dosya, "Sifre     : %d\n", &gonderen.sifre);
        fscanf(dosya, "Para      : %lf\n", &gonderen.para);
        fscanf(dosya, "\n");

        if (strcmp(gonderen.tc, gecici.tc2) == 0 && gonderen.sifre == gecici.sifre2)	
		 {
            if (gonderen.para >= transferMiktar) 	//Eðer hesapta yeterli para varsa,
			{
                gonderen.para -= transferMiktar;	//Para hesaptan düþüyor.
                gonderenBulundu = 1;
                
                fseek(dosya, dosyaBaslangic, SEEK_SET);		//fseek ile dosyaBaslangic önceki konumuna gönderilir ve karýþýklýk engellenir.
                fprintf(dosya, "Musteri No: %d\n", gonderen.MusteriNo);		//Gönderici bilgilerini yazýyoruz.
                fprintf(dosya, "TC        : %s\n", gonderen.tc);
                fprintf(dosya, "Isim      : %s\n", gonderen.isim);
                fprintf(dosya, "Soyisim   : %s\n", gonderen.soyisim);
                fprintf(dosya, "Sehir     : %s\n", gonderen.sehir);
                fprintf(dosya, "Telefon   : %d\n", gonderen.telefon);
                fprintf(dosya, "Sifre     : %d\n", gonderen.sifre);
                fprintf(dosya, "Para      : %.2lf\n", gonderen.para);
                fprintf(dosya, "\n");
                break;
            } else {
                printf("Yetersiz bakiye...!\n");
                fclose(dosya);
                return;
            }
        }
        dosyaBaslangic = ftell(dosya);	//ftell fonksiyonu ile dosyanýn baþlangýç konumunu kaydediyoruz ve karýþmasýný önlüyoruz. 
    }

    dosyaBaslangic = ftell(dosya);
    rewind(dosya);	//Gönderen verisini yazdýktan sonra dosya okumayý baþa sarýyoruz.

    while (fscanf(dosya, "Musteri No: %d\n", &alan.MusteriNo) == 1) //Alýcý verileri okuyoruz.
	{
        fscanf(dosya, "TC        : %[^\n]\n", alan.tc);
        fscanf(dosya, "Isim      : %[^\n]\n", alan.isim);
        fscanf(dosya, "Soyisim   : %[^\n]\n", alan.soyisim);
        fscanf(dosya, "Sehir     : %[^\n]\n", alan.sehir);
        fscanf(dosya, "Telefon   : %d\n", &alan.telefon);
        fscanf(dosya, "Sifre     : %d\n", &alan.sifre);
        fscanf(dosya, "Para      : %lf\n", &alan.para);
        fscanf(dosya, "\n");

        if (alan.MusteriNo == transferMusteriNo) 	//Eðer alýcý müþteri numarasý transfer edilecek numara ile uyuþuyor ise iþlemi ve kayýtlarý yapýyoruz.
		{
            alan.para += transferMiktar;
            alanBulundu = 1;

            fseek(dosya, dosyaBaslangic, SEEK_SET);
            fprintf(dosya, "Musteri No: %d\n", alan.MusteriNo);
            fprintf(dosya, "TC        : %s\n", alan.tc);
            fprintf(dosya, "Isim      : %s\n", alan.isim);
            fprintf(dosya, "Soyisim   : %s\n", alan.soyisim);
            fprintf(dosya, "Sehir     : %s\n", alan.sehir);
            fprintf(dosya, "Telefon   : %d\n", alan.telefon);
            fprintf(dosya, "Sifre     : %d\n", alan.sifre);
            fprintf(dosya, "Para      : %.2lf\n", alan.para);
            fprintf(dosya, "\n");
            break;
        }
        dosyaBaslangic = ftell(dosya);
    }

    fclose(dosya);

    if (gonderenBulundu && alanBulundu) // Ýki kullanýcý da kayýtlý ise transfer baþarýlý tamamlanýyor.
	{
        printf("Para transferi tamamlandý.\n");
    } else
	 {
        printf("Müþteri bulunamadý!\n");
    }
}




int MusteriMenusu()		//Müþterinin gördüðü seçim menüsü.
{
    int sec2;
    printf("\n 1 - - - PARA CEK \n");
    printf("\n 2 - - - PARA YATIR \n");
    printf("\n 3 - - - BAKIYE GORUNTULE \n");
    printf("\n 4 - - - PARA TRANSFERI \n");
    printf("\n 5 - - - KAPAT... :");
    
    scanf("%d", &sec2);
    return sec2;
    
}




void MusteriIslem() // Müþteri seçim iþlemlerinin switch-case yapýsý.
{
	system("cls");
	
    int sec2;
    printf("\n Degerli Musterimiz Hos Geldiniz...\n");

    sec2 = MusteriMenusu(); 

    while (sec2 != 5)
	 {
        switch (sec2) {
            case 1:
                ParaCek();
                break;
            case 2:
                ParaYatir();
                break;
            case 3:
                Bakiye();
                break;
            case 4:
                ParaTransfer();
                break;
			case 5:
				break;    
            default:
                printf("Yanlis Secim...\n");
                break;
        }
        sec2 = MusteriMenusu();
    }
	
    printf("Ana Menuye Donuluyor...\n");
}



void MusteriGiris() //Müþteri Giriþ Menüsü.
{
    system("cls");
    
    printf("Musteri Girisi, Lutfen Sisteme Kayitli TC ve Sifrenizi Giriniz\n\n"); //Müþteri giriþ için þifre ve tc verisi alýyoruz, kayýtlarda bulunursa giriþ onaylanýyor.

    printf("TC: ");
    scanf("%s", gecici.tc2);
    printf("Sifre: ");
    scanf("%d", &gecici.sifre2);

    FILE *dosya = fopen("musteriler.txt", "r");
    

    int bulundumusteri = 0;

    while (
	fscanf(dosya, "Musteri No: %d\n", &musteri.MusteriNo) == 1) 	//MüþteriNo onayý aldýktan sonra dosyadan müþteri bilgilerini okuyoruz.
	{
    fscanf(dosya, "TC        : %s\n", musteri.tc);
    fscanf(dosya, "Isim      : %s\n", musteri.isim);
    fscanf(dosya, "Soyisim   : %s\n", musteri.soyisim);
    fscanf(dosya, "Sehir     : %s\n", musteri.sehir);
    fscanf(dosya, "Telefon   : %d\n", &musteri.telefon);
    fscanf(dosya, "Sifre     : %d\n", &musteri.sifre);
    fscanf(dosya, "Para      : %lf\n", &musteri.para);
    fscanf(dosya, "\n");
    

        if (strcmp(musteri.tc, gecici.tc2) == 0 && musteri.sifre == gecici.sifre2) 	//Dosyada kayýtlý TC ve Þifre verilerini müþterinin ekrana girdiði veriler ile karþýlaþtýrýyoruz.
		{
          	bulundumusteri = 1;		// Sýfýr olarak belirlediðimiz deðeri doðruluyoruz.
            break;
        }
    }

    fclose(dosya);

    if (bulundumusteri) {
        printf("Giris Basarili, Hos Geldiniz Sayin  %s %s!\n", musteri.isim, musteri.soyisim);	//Baþarýlý giriþ durumunda MusteriIslem fonksiyonu çalýþýyor.
        MusteriIslem();
    } else {
        printf("Hatali Giris Denemesi, Lütfen TC ve/veya Sifrenizi Kontrol Ediniz...!\n");
    }
}



void CalisanGiris() // Çalýþan Giriþ Menüsü.
{
    system("cls");
    
    printf("Calisan Giris Menusu, Lutfen Giris Icýn Gecerli Admin-Sifre Degerlerini Giriniz (Admin-123456)\n\n");
    char stradmin[20];
    int sifre;
    
    printf("Isim: ");
    scanf("%s", stradmin);
    printf("Sifre: ");
    scanf("%d", &sifre);

    if (strcmp(stradmin, "admin") == 0 && sifre == 123456) {	//Önceden belirlediðimiz çalýþan giriþi için onay alýyoruz, doðru ise CalisanIslem çalýþýyor.
        CalisanIslem();
    } else 
	{
        printf("Hatali Giris Denemesi...\n");
    }
}

int GirisMenu() 
{
	system("cls");
	
    int sec;
    printf("\n - - - - - - - Banka Otomasyon Sistemi - - - - - - - \n");	//Giriþte karþýlaþtýðýmýz menü.
    printf("\n 1 - - - MUSTERI GIRIS \n");
    printf("\n 2 - - - CALISAN GIRIS \n");
    printf("\n 3 - - - PROGRAMI SONLANDIR \n");
    printf("\n\n Lutfen Secim Yapiniz... ");
    scanf("%d", &sec);
    return sec;
}

int main() {	//Main Fonksiyonu.			
    int sec = GirisMenu();

    while (sec != 3) {
        switch (sec) {
            case 1:
                MusteriGiris();
                break;
            case 2:
                CalisanGiris();
                break;
            default:
                printf("Yanlýs Secim...\n");
                break;
        }
        sec = GirisMenu();
    }

    printf("Program Kapatiliyor...\n");

    return 0;
}





