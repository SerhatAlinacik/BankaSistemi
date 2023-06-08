#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

struct Musteri // M��teri bilgilerini tuttu�umuz struct.
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

struct Gecici //M��teriden onay almak i�in kulland���m�z verileri tuttu�umuz struct.
{
	char tc2[12];
    int sifre2;
    
}gecici;

void Bakiye() //M��terinin bakiyesini g�r�nt�ledi�i fonksiyon.
{
    system("cls");

    FILE *dosya = fopen("musteriler.txt", "r"); //Dosyay� okuma modunda a��yoruz.
    
    if (dosya == NULL) {	
        printf("Dosya Bulunamadi!");	//Dosyay� bulamazsa hata veriyor.
        return;
    }

    while (fscanf(dosya, "Musteri No: %d\n", &musteri.MusteriNo) == 1) //MusteriNo de�erini onaylay�nca verileri okuyor daha sonra if ko�uluna giriyor.
	{
        fscanf(dosya, "TC        : %[^\n]\n", musteri.tc);
        fscanf(dosya, "Isim      : %[^\n]\n", musteri.isim);
        fscanf(dosya, "Soyisim   : %[^\n]\n", musteri.soyisim);
        fscanf(dosya, "Sehir     : %[^\n]\n", musteri.sehir);
        fscanf(dosya, "Telefon   : %d\n", &musteri.telefon);
        fscanf(dosya, "Sifre     : %d\n", &musteri.sifre);
        fscanf(dosya, "Para      : %lf\n", &musteri.para);
        fscanf(dosya, "\n");

        if (strcmp(musteri.tc, gecici.tc2) == 0 && musteri.sifre == gecici.sifre2) //Strcmp kullanaracak TC ve �ifre kontrol� yap�yoruz.
		{
            printf("Hesab�n�zdaki Bakiye: %.2lf\n", musteri.para);
            break;
        }
    }

    fclose(dosya);
}


void MusteriSil()	//M��teri Silme Fonksiyonu.
 {
    system("cls");

    int SilMusteriNo;
    
    printf("Silinecek Musteri No: ");	//Silinecek m��terinin MusteriNo bilgisi al�n�yor.
    scanf("%d", &SilMusteriNo);

    FILE *dosya = fopen("musteriler.txt", "r");		//Silme i�lemi i�in iki dosyaya ihtiyac�m�z var ana dosyay� okuma, ikinci dosyay� yazma modunda a��yoruz.
    FILE *dosya2 = fopen("musteriler2.txt", "w");

    if (dosya == NULL || dosya2 == NULL) 
	{
        printf("Dosya Acilamadi!");		//Dosyay� bulamazsa hata veriyor.
        return;
    }

    int bulundu = 0;

    while (fscanf(dosya, "Musteri No	: %d\n", &musteri.MusteriNo) == 1) //Dosyadaki de�erleri okuyor.
	{
        fscanf(dosya, "TC				: %[^\n]\n", musteri.tc);
        fscanf(dosya, "Isim				: %[^\n]\n", musteri.isim);
        fscanf(dosya, "Soyisim			: %[^\n]\n", musteri.soyisim);
        fscanf(dosya, "Sehir			: %[^\n]\n", musteri.sehir);
        fscanf(dosya, "Telefon			: %d\n", &musteri.telefon);
        fscanf(dosya, "Sifre			: %d\n", &musteri.sifre);
        fscanf(dosya, "Para				: %lf\n", &musteri.para);

        if (musteri.MusteriNo != SilMusteriNo) 		//E�er m��teri numaras� ile silinmek istenen numara uyu�muyorsa verileri yeni dosyaya yaz�yor, uyu�an numara ise yaz�lm�yor. B�ylece uyu�an numara silinmi� oluyor.
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
            bulundu = 1;	//Ba�ar�l� ise,
        }
    }

    fclose(dosya);
    fclose(dosya2);
							//Ba�ar�s�z ise a�a��daki if ko�ullar�na giriyor.
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




void MusteriEkle() 		//M��teri Ekleme Fonksiyonu.
{
    system("cls");

    printf("TC             : ");	//Eklenecek m��teri i�in veri al�n�yor.
    scanf("%s", musteri.tc);
    printf("Isim           : ");
    scanf("%s", musteri.isim);
    printf("Soyisim        : ");
    scanf("%s", musteri.soyisim);
    printf("Sehir          : ");
    scanf("%s", musteri.sehir);
    printf("Telefon        : ");
    scanf("%d", &musteri.telefon);

    srand(time(0));		//Rastgele say� �retmek i�in kullan�lan fonksiyon.
    
    musteri.MusteriNo = rand() % 9000000 + 1000000;		//Rastgele m��teri numaras� ve �ifre �retiliyor, otomatik olarak para de�eri 0 belirleniyor.
    musteri.sifre = rand() % 1000 + 1000;
    musteri.para = 0.00;

    FILE *dosya = fopen("musteriler.txt", "a");		//Dosyay� ekleme modunda a��yoruz.

    if (dosya == NULL) 
	{
        printf("Dosya Bulunamadi!");
        return;
    }

    fprintf(dosya, "Musteri No: %d\n", musteri.MusteriNo);		//Dosyaya ekleme i�lemi.
    fprintf(dosya, "TC        : %s\n", musteri.tc);
    fprintf(dosya, "Isim      : %s\n", musteri.isim);
    fprintf(dosya, "Soyisim   : %s\n", musteri.soyisim);
    fprintf(dosya, "Sehir     : %s\n", musteri.sehir);
    fprintf(dosya, "Telefon   : %d\n", musteri.telefon);
    fprintf(dosya, "Sifre     : %d\n", musteri.sifre);
    fprintf(dosya, "Para      : %.2lf\n", musteri.para);
    fprintf(dosya, "\n");
    
    fclose(dosya);
    
    printf("Sistem Taraf�ndan Otomatik Olusturulan Sifreniz... : %d\n", musteri.sifre);		//Kullan�c� ekleniyor ve otomatik �ifresi kullan�c�ya bildiriliyor.
    printf("Musteri Bilgileri Kaydedildi!\n");
    
}



void MusteriListele() 	//M��teri Listeleme Fonksiyonu.
{
    system("cls");
    
    FILE *dosya = fopen("musteriler.txt", "r");		//Dosyay� okuma modunda a��yoruz.

    if (dosya == NULL) 
	{
        printf("Dosya bulunamadi!\n");
        return;
    }

    printf("Sistemde Kayitli Musterilerin Listesi... \n\n\n");

    while (fscanf(dosya, "Musteri No: %d\n", &musteri.MusteriNo) == 1)		//Doyadan verileri okuyoruz ve konsola yazd�r�yoruz. 
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



int CalisanMenusu()		//�al��an�n g�rd��� men�. 
{		
    int sec3;
    
    printf("\n 1 - - - MUSTERI EKLE \n");
    printf("\n 2 - - - MUSTERI SIL \n");
    printf("\n 3 - - - MUSTERI LISTELE \n");
    printf("\n 4 - - - KAPAT... :");
    scanf("%d", &sec3);
    
    return sec3;
    
}



void CalisanIslem() 	//�al�sanlar�n i�lemrinin yap�ld��� switch-case yap�s� fonksiyonu.
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



void ParaYatir() 	//Para Yat�rma Fonksiyonu.
{
    system("cls");
    
    
    double YatirilacakMiktar;		

    printf("Yatirmak Istediginiz Miktari Giriniz... : ");	//M��teriden yat�raca�� miktar� al�yoruz.
    scanf("%lf", &YatirilacakMiktar);

    FILE *dosya = fopen("musteriler.txt", "r+");  //Dosyay� okuma ve kaydetme modunda a��yoruz.
    
    if (dosya == NULL) 
	{
        printf("Dosya Bulunamadi!");
        return;
    }

    int bulunduyatir = 0;
    long int dosyaBaslangic = ftell(dosya);		//ftell fonksiyonu olu�turuyoruz. 

    while (fscanf(dosya, "Musteri No: %d\n", &musteri.MusteriNo) == 1) //M��teri bulunup okunuyor.
	{
        fscanf(dosya, "TC        : %[^\n]\n", musteri.tc);
        fscanf(dosya, "Isim      : %[^\n]\n", musteri.isim);
        fscanf(dosya, "Soyisim   : %[^\n]\n", musteri.soyisim);
        fscanf(dosya, "Sehir     : %[^\n]\n", musteri.sehir);
        fscanf(dosya, "Telefon   : %d\n", &musteri.telefon);
        fscanf(dosya, "Sifre     : %d\n", &musteri.sifre);
        fscanf(dosya, "Para      : %lf\n", &musteri.para);
        fscanf(dosya, "\n");

        if (strcmp(musteri.tc, gecici.tc2) == 0 && musteri.sifre == gecici.sifre2) 	//Giri� kontrol� yap�l�yor, e�er do�ru ise i�lem yap�l�yor ve para hesaba ekleniyor.
		{
            musteri.para += YatirilacakMiktar;
            bulunduyatir = 1;
            
            fseek(dosya, dosyaBaslangic, SEEK_SET);		//fseek ile dosyaBaslangic �nceki konumuna g�nderilir ve kar���kl�k engellenir.
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
        
        dosyaBaslangic = ftell(dosya);		//ftell fonksiyonu ile dosya konumunu kaydediyoruz ve kar��mas�n� �nl�yoruz. 
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






void ParaCek() 	//Para �ekme Fonksiyonu, Matematik i�lemi d���nda ayn� fonkisyon.
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
    
    struct Musteri gonderen;	//Alan ve G�nderen olarak iki struct belirtiyoruz.
    struct Musteri alan;
    
    double transferMiktar;
    int transferMusteriNo;

    printf("Para Gondermek Istediginiz MusteriNo...: ");
    scanf("%d", &transferMusteriNo);

    printf("Transfer Etmek Istediginiz Miktar...: ");
    scanf("%lf", &transferMiktar);

    FILE *dosya = fopen("musteriler.txt", "r+");	//Kullan�c�dan de�erleri al�yoruz ve dosyay� a��yoruz.
    if (dosya == NULL)
	 {
        printf("Dosya Bulunamadi...!");
        return;
    }
    
    long int dosyaBaslangic = ftell(dosya);
    
    int gonderenBulundu = 0;	//Do�rulamak i�in iki de�er olu�turduk.
    int alanBulundu = 0;

    while (fscanf(dosya, "Musteri No: %d\n", &gonderen.MusteriNo) == 1)	//G�nderici bilgilerini okuyoruz.
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
            if (gonderen.para >= transferMiktar) 	//E�er hesapta yeterli para varsa,
			{
                gonderen.para -= transferMiktar;	//Para hesaptan d���yor.
                gonderenBulundu = 1;
                
                fseek(dosya, dosyaBaslangic, SEEK_SET);		//fseek ile dosyaBaslangic �nceki konumuna g�nderilir ve kar���kl�k engellenir.
                fprintf(dosya, "Musteri No: %d\n", gonderen.MusteriNo);		//G�nderici bilgilerini yaz�yoruz.
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
        dosyaBaslangic = ftell(dosya);	//ftell fonksiyonu ile dosyan�n ba�lang�� konumunu kaydediyoruz ve kar��mas�n� �nl�yoruz. 
    }

    dosyaBaslangic = ftell(dosya);
    rewind(dosya);	//G�nderen verisini yazd�ktan sonra dosya okumay� ba�a sar�yoruz.

    while (fscanf(dosya, "Musteri No: %d\n", &alan.MusteriNo) == 1) //Al�c� verileri okuyoruz.
	{
        fscanf(dosya, "TC        : %[^\n]\n", alan.tc);
        fscanf(dosya, "Isim      : %[^\n]\n", alan.isim);
        fscanf(dosya, "Soyisim   : %[^\n]\n", alan.soyisim);
        fscanf(dosya, "Sehir     : %[^\n]\n", alan.sehir);
        fscanf(dosya, "Telefon   : %d\n", &alan.telefon);
        fscanf(dosya, "Sifre     : %d\n", &alan.sifre);
        fscanf(dosya, "Para      : %lf\n", &alan.para);
        fscanf(dosya, "\n");

        if (alan.MusteriNo == transferMusteriNo) 	//E�er al�c� m��teri numaras� transfer edilecek numara ile uyu�uyor ise i�lemi ve kay�tlar� yap�yoruz.
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

    if (gonderenBulundu && alanBulundu) // �ki kullan�c� da kay�tl� ise transfer ba�ar�l� tamamlan�yor.
	{
        printf("Para transferi tamamland�.\n");
    } else
	 {
        printf("M��teri bulunamad�!\n");
    }
}




int MusteriMenusu()		//M��terinin g�rd��� se�im men�s�.
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




void MusteriIslem() // M��teri se�im i�lemlerinin switch-case yap�s�.
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



void MusteriGiris() //M��teri Giri� Men�s�.
{
    system("cls");
    
    printf("Musteri Girisi, Lutfen Sisteme Kayitli TC ve Sifrenizi Giriniz\n\n"); //M��teri giri� i�in �ifre ve tc verisi al�yoruz, kay�tlarda bulunursa giri� onaylan�yor.

    printf("TC: ");
    scanf("%s", gecici.tc2);
    printf("Sifre: ");
    scanf("%d", &gecici.sifre2);

    FILE *dosya = fopen("musteriler.txt", "r");
    

    int bulundumusteri = 0;

    while (
	fscanf(dosya, "Musteri No: %d\n", &musteri.MusteriNo) == 1) 	//M��teriNo onay� ald�ktan sonra dosyadan m��teri bilgilerini okuyoruz.
	{
    fscanf(dosya, "TC        : %s\n", musteri.tc);
    fscanf(dosya, "Isim      : %s\n", musteri.isim);
    fscanf(dosya, "Soyisim   : %s\n", musteri.soyisim);
    fscanf(dosya, "Sehir     : %s\n", musteri.sehir);
    fscanf(dosya, "Telefon   : %d\n", &musteri.telefon);
    fscanf(dosya, "Sifre     : %d\n", &musteri.sifre);
    fscanf(dosya, "Para      : %lf\n", &musteri.para);
    fscanf(dosya, "\n");
    

        if (strcmp(musteri.tc, gecici.tc2) == 0 && musteri.sifre == gecici.sifre2) 	//Dosyada kay�tl� TC ve �ifre verilerini m��terinin ekrana girdi�i veriler ile kar��la�t�r�yoruz.
		{
          	bulundumusteri = 1;		// S�f�r olarak belirledi�imiz de�eri do�ruluyoruz.
            break;
        }
    }

    fclose(dosya);

    if (bulundumusteri) {
        printf("Giris Basarili, Hos Geldiniz Sayin  %s %s!\n", musteri.isim, musteri.soyisim);	//Ba�ar�l� giri� durumunda MusteriIslem fonksiyonu �al���yor.
        MusteriIslem();
    } else {
        printf("Hatali Giris Denemesi, L�tfen TC ve/veya Sifrenizi Kontrol Ediniz...!\n");
    }
}



void CalisanGiris() // �al��an Giri� Men�s�.
{
    system("cls");
    
    printf("Calisan Giris Menusu, Lutfen Giris Ic�n Gecerli Admin-Sifre Degerlerini Giriniz (Admin-123456)\n\n");
    char stradmin[20];
    int sifre;
    
    printf("Isim: ");
    scanf("%s", stradmin);
    printf("Sifre: ");
    scanf("%d", &sifre);

    if (strcmp(stradmin, "admin") == 0 && sifre == 123456) {	//�nceden belirledi�imiz �al��an giri�i i�in onay al�yoruz, do�ru ise CalisanIslem �al���yor.
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
    printf("\n - - - - - - - Banka Otomasyon Sistemi - - - - - - - \n");	//Giri�te kar��la�t���m�z men�.
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
                printf("Yanl�s Secim...\n");
                break;
        }
        sec = GirisMenu();
    }

    printf("Program Kapatiliyor...\n");

    return 0;
}





