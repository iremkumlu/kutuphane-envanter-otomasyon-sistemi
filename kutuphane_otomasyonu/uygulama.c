#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Kütüphane Otomasyonu

typedef struct Kitap{
	int barkod;         // birincil anahtar
	char kitapAdi[30];
	char yazarAdi[30];
	char yayinEvi[30];
	char kitapTuru[30];
	char teminTuru[30];
	char teminTarihi[30];
	int stokSayisi[30];
}kitap ;

typedef struct Uye {
	
	char tc[30];               //birincil anahtar
	char adSoyad[30];
	char cinsiyet;
	char dogumTarihi[30];
	char telefon[30];
	char eposta[30];
	char uyelikTarihi[30];
	char adres[30];
	int durum;
	
} uye ;

typedef struct Emanet {
	char uyeTC[20];                // yabancýl anahtar
	int kitapBarkod;               // yabancýl anahtar
	int durum;
} emanet ;

void kitapEkle()
{
	system("cls");
	printf("Kitap ekleme ekrani.... \n \n");
	
	kitap k1;
	
	printf("Barkod       :");          scanf("%d",&k1.barkod);
	printf("Kitap adi    :");          scanf(" %[^\n]s",k1.kitapAdi);
	printf("Yazar adi    :");          scanf(" %[^\n]s",k1.yazarAdi);
	printf("Yayin evi    :");          scanf(" %[^\n]s",k1.yayinEvi);
	printf("Kitap turu   :");          scanf(" %[^\n]s",k1.kitapTuru);
	printf("Temin turu   :");          scanf(" %[^\n]s",k1.teminTuru);
	printf("Temin tarihi :");          scanf(" %[^\n]s",k1.teminTarihi);
	printf("Stok sayisi  :");          scanf(" %d",&k1.stokSayisi);
	
	FILE * ptr= fopen("kitaplar.dat","a+b"); 
	fwrite(&k1, sizeof(kitap), 1, ptr);
	fclose(ptr);
	printf("Kitap kaydi tamamlandi \n");
	
}
void kitapSil()
{
	system("cls");
	printf("Kitap silme ekrani.... \n \n");
	
	kitap k1;
	int barkod, sonuc=0 ;
	
	printf("Barkod       :");          scanf("%d",&barkod);
	
	
	FILE * ptr= fopen("kitaplar.dat","r+b"); 
	FILE * yptr= fopen("yedek.dat","w+b");           
	

	while ( fread(&k1, sizeof(kitap) , 1, ptr) != NULL)
	{
		if( barkod != k1.barkod)
		 fwrite (&k1, sizeof(kitap) , 1, yptr);
		else
		sonuc=1;
	}
	
	
	fclose(ptr);
	fclose(yptr);

    if(sonuc==0)
    {
    	
    	printf("%d barkod numarali kitap bulunamadi. \n",barkod);
	}
	
	else
	{
		remove("kitaplar.dat");
		rename("yedek.dat","kitaplar.dat");
		printf("%d barkod numarali kitap silindi...",barkod);
	}

}
void kitapListele()
{
	system("cls");
	printf("Kitap listeleme ekrani.... \n \n");
	
	kitap k1;
	int kitapSayisi=0;

	
	FILE * ptr= fopen("kitaplar.dat","r+b"); 
	
	printf("%-20s%-30s%-30s%-30s%-20s%-20s%-20s%-20s\n","BARKOD","KITAP-ADI","YAZAR-ADI","YAYIN-EVI","KITAP-TURU","TEMIN-TURU","TEMIN-TARIHI","STOK-SAYISI");


	

	while ( fread(&k1, sizeof(kitap) , 1, ptr) != NULL)
	{
		printf("%-20d%-30s%-30s%-30s%-20s%-20s%-20s%-20d\n", k1.barkod, k1.kitapAdi, k1.yazarAdi, k1.yayinEvi, k1.kitapTuru, k1.teminTuru, k1.teminTarihi, k1.stokSayisi);
		kitapSayisi += k1.stokSayisi;
	}
	
	
	fclose(ptr);
	printf(" \n Toplam kitap sayisi : %d \n", kitapSayisi);

   }

void kitapIslemleri()
{
	
	system("cls"); 
	printf("Kitap islemleri ekranina hosgeldiniz\n\n");
	
	int secim;
	printf("1- Kitap Ekle \n");
	printf("2- Kitap Sil \n");
	printf("3- Kitap Listele \n");
	printf("4- Ana menuye don \n");
	printf("Seciminiz : ");  scanf("%d",&secim);
	
	switch(secim)
	{
		case 1: kitapEkle(); break;
		case 2: kitapSil(); break;
		case 3: kitapListele(); break;
		case 0:  break;
		default : printf("Hatali secim yaptiniz, ana menuye yonlendiriliyorsunuz...\n"); break;
		
	}
	
	}
	
	void uyeEkle()
	{
	system("cls");
	printf("Uye ekleme ekrani.... \n \n");
	
	uye u1;
	
    printf("TC                :");   scanf(" %[^\n]s", u1.tc);
    printf("Ad-Soyad          :");   scanf(" %[^\n]s", u1.adSoyad);
    printf("Cinsiyet          :");   scanf(" %[^\n]s", &u1.cinsiyet);
    printf("Dogum tarihi      :");   scanf(" %[^\n]s", u1.dogumTarihi);
    printf("Telefon           :");   scanf(" %[^\n]s", u1.telefon);
    printf("E-Posta           :");   scanf(" %[^\n]s", u1.eposta);
    printf("Adres             :");   scanf(" %[^\n]s", u1.adres);
    
    u1.durum=0;
	
	FILE * ptr= fopen("uyeler.dat","a+b"); 
	fwrite(&u1, sizeof(uye), 1, ptr);
	fclose(ptr);
	printf("Uye kaydi tamamlandi \n");
	}
	
	void uyeSil()
	{
	system("cls");
    printf("Uye silme ekrani.... \n \n");
	
	uye u1;
	int sonuc=0 ;
	char tc[20];
	
	printf("TC       :");          scanf(" %[^\n]s", tc );
	
	
	FILE * ptr= fopen("uyeler.dat","r+b"); 
	FILE * yptr= fopen("yedek.dat","w+b");           //y yedek pointer demek
	

	while ( fread(&u1, sizeof(uye) , 1, ptr) != NULL)
	{
		if(  strcmp(tc, u1.tc) !=0 )
		 fwrite (&u1, sizeof(uye) , 1, yptr);
		else
		sonuc=1;
	}
	
	
	fclose(ptr);
	fclose(yptr);

    if(sonuc==0)
    {
    	
    	printf("%s TC numarali kisi kaydi bulunamadi. \n", tc);
	}
	
	else
	{
		remove("uyeler.dat");
		rename("yedek.dat","uyeler.dat");
		printf("%s TC numarali uye kaydi silindi...", tc);
	}

	}
	
	void uyeListele()
	{
	system("cls");
	printf("Uye listeleme ekrani.... \n \n");
	
	uye u1;
	int kisiSayisi=0;

	
	FILE * ptr= fopen("uyeler.dat","r+b"); 
	
	printf("%-20s%-30s%-20s%-20s%-20s%-30s%-20s%-30s%-20s\n", "TC", "AD-SOYAD", "CINSIYET","DOGUM-TARIH","TELEFON","E-POSTA","UYELIK-TARIH","ADRES","DURUM" );
    
  

	while ( fread(&u1, sizeof(uye) , 1, ptr) != NULL)
	{
		printf("%-20s%-30s%-20c%-20s%-20s%-30s%-20s%-30s%-20d\n", u1.tc, u1.adSoyad , u1.cinsiyet, u1.dogumTarihi, u1.telefon, u1.eposta, u1.uyelikTarihi, u1.adres ,u1.durum);
		kisiSayisi++ ;
	}
	
	
	fclose(ptr);
	printf(" \n Toplam uye sayisi : %d \n", kisiSayisi);

   
	}
	
	
void uyeIslemleri()
{
	system("cls"); 
	printf("Uye islemleri ekranina hosgeldiniz\n\n");
	
	int secim;
	printf("1- Uye Ekle \n");
	printf("2- Uye Sil \n");
	printf("3- Uye Listele \n");
	printf("4- Ana menuye don \n");
	printf("Seciminiz : ");  scanf("%d",&secim); 
	
	switch(secim)
	{
		case 1: uyeEkle(); break;
		case 2: uyeSil(); break;
		case 3: uyeListele(); break;
		case 0:  break;
		default : printf("Hatali secim yaptiniz, ana menuye yonlendiriliyorsunuz...\n"); break;
		
	}
	
	
}

void stokGuncelle( int barkod , int sayi)
{
	kitap k1;
	int sonuc=0 , sayac=0 ;
	
	
	FILE * ptr = fopen("kitaplar.dat","r+b");
	
	while(fread( &k1 ,sizeof(kitap), 1, ptr) != NULL)
	{
		if (barkod == k1.barkod)
		{
		
		sonuc=1;
		break;	
		sayac++ ;
	    }
	    
	}
	if(sonuc==0)
	{
		printf("Stokta bu kitabýn kaydý mevcut degildir.\n");
	}
	
	if(sonuc==1)
	{
	rewind(ptr);
	
	fseek( ptr, (sayac) * sizeof(kitap), 0);
	
   	//k1.stokSayisi += sayi ;
	fwrite( &k1, sizeof(kitap) , 1 , ptr);
	fclose(ptr);
	printf("stok guncellendi \n");
     }
     fclose(ptr);
	
}

void emanetKitapVer()
{
	system("cls");
	printf("Emanet Kitap Verme Ekrani..... \n\n");
	emanet e1;
	uye u1;
	kitap k1;
	int usonuc=0 , ksonuc=0;
	
	printf("TC  : \n ");      
	scanf("%[^\n]s", e1.uyeTC);
	printf("Barkod : \n");  
	scanf("%d", &e1.kitapBarkod);
	
	FILE *uptr=fopen("uyeler.dat","r+b");
	while(fread(&u1,sizeof(uye),1,uptr) != NULL)
	{
		if( strcmp(e1.uyeTC, u1.tc) == 0)
		{
			usonuc=1;
			break;
		} 
	}
	fclose(uptr);
	if(usonuc==0)
	{
		printf("%s TC  numrali uye yok. \n",e1.uyeTC);
		return ;
	}
	
    FILE * kptr = fopen("kitaplar.dat","r+b");
	while(fread ( &k1 , sizeof(kitap) , 1 , kptr) != NULL)
	{
		if( e1.kitapBarkod== k1.barkod)
		{
			ksonuc=1;
			break;
		} 
	}
	fclose(kptr);
	if(ksonuc==0)
	{
		printf("%d barkod numarali kitap kaydi yok. \n",e1.kitapBarkod);
		return ;
	}
	
	if(k1.stokSayisi<1)
	{
		printf("%d barkod numarali kitaptan stokta yok. \n",e1.kitapBarkod);
		return ;
	}
	
	FILE * eptr = fopen("emanetler.dat","a+b");
	fwrite(&e1 , sizeof(emanet), 1, eptr);
	fclose(eptr);
	printf("Emanet kaydi tamamlandi \n");
	
    stokGuncelle(e1.kitapBarkod , -1);
   
	
}

void emanetKitabiIadeAl()
{
	system("cls");
	printf("Emanet Kitap Iade Alma Ekrani..... \n\n");
	emanet e1;
	uye u1;
	kitap k1;
	int sonuc=0 , sayac=0;
	char uyeTC[20];
	int kitapBarkod;
	
	printf("TC \n :  ");      
	scanf("%[^\n]s", e1.uyeTC);
	printf("Barkod \n :  ");  
	scanf("%d", &e1.kitapBarkod);
	
	FILE *ptr=fopen("emanetler.dat","r+b");
	while(fread(&e1,sizeof(emanet),1,ptr) != NULL)
	{
		if( strcmp(e1.uyeTC, uyeTC) == 0 && kitapBarkod == e1.kitapBarkod)
		{
			sonuc=1;
			break;
		} 
		sayac++ ;
	}
	
	
	if(sonuc==0)
	{
	    fclose(ptr);
		printf("%s TC veya %d Barkod numarali emanet kaydi yoktur. \n",uyeTC,kitapBarkod);
		return ;
	}
	
	fseek (ptr , (sayac)*sizeof(emanet),0);
	fwrite (&e1 , sizeof(emanet), 1 ,ptr);
	fclose(ptr);
	printf("Emanet Iade Kaydi Tamamlandi \n");
	
    stokGuncelle(e1.kitapBarkod , 1);

	
}

void emanettekiKitaplariListele()
{
	
	system("cls");
	printf("Emanet Kitap Listeleme Ekrani ...  \n \n");
	emanet e1;
	int sayac=0;
	FILE * ptr = fopen("emanetler.dat","r+b");
	printf("%-20s%-20s%-20%s\n","TC","BARKOD","DURUM");
	while (fread(&e1, sizeof(emanet),1,ptr) != NULL)
	{
		
			printf("%-20s%-20d-20%d\n", e1.uyeTC, e1.kitapBarkod,e1.durum);
			sayac++;
		
	   
	}
	fclose(ptr);
	printf("Emanet kayit sayisi : %d \n",sayac);
	
}


void emanetKitapIslemleri()
{
		system("cls"); 
	printf("Emanet Kitap islemleri ekranina hosgeldiniz\n\n");
	
	int secim;
	printf("1- Emanet Kitap Ver \n");
	printf("2- Emanet Kitabi Iade Al \n");
	printf("3- Emanetteki Kitaplari Listele \n");
	printf("4- Ana menuye don \n");
	printf("Seciminiz : ");  scanf("%d",&secim); 
	
	switch(secim)
	{
		case 1: emanetKitapVer(); break;
		case 2: emanetKitabiIadeAl(); break;
		case 3: emanettekiKitaplariListele(); break;
		case 0:  break;
		default : printf("Hatali secim yaptiniz, ana menuye yonlendiriliyorsunuz...\n"); break;
		
	}
}

int menu()
{
	int secim;
	printf("\n \t KUTUPHANE OTOMASYONU \n \n");
	printf("\t 1- KITAP ISLEMLERI \n");
	printf("\t 2- UYE ISLEMLERI \n");
	printf("\t 3- EMANET KITAP ISLEMLERI \n");
	printf("\t 0- PROGRAMI KAPAT \n \n");
	printf("\t Seciminiz :"); 
	scanf("%d",&secim);
	return secim;
}

int main()
{
	int secim=menu();
	
	while (secim != 0)
	{
		switch(secim)
		{
			case 1: kitapIslemleri(); break;
			case 2: uyeIslemleri(); break;
			case 3: emanetKitapIslemleri(); break;
			case 0: break;
			default : printf("Hatali secim yaptiniz ! \n");
		}
		secim=menu();
	}
	
	printf("Programi kapattiniz...");
	

	return 0;
}
