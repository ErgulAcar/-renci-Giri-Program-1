#include <stdio.h>
#include <string.h>
#include <unistd.h>//sleep fonk ve system fonk var
#include <stdlib.h>
#include<math.h>
#include<locale.h>
#define CLASSSIZE 35 // SINIFKAPASITE
#define STUDENTNUMBERLENGTH 10 // OGRENCINUMARAUZUNLUGU
#define NAMELENGTH 25 // ADIUZUNLUGU
#define COURSENAMELENGTH 50 // DERSADIUZUNLUGU
#define COURSECODELENGTH 10 // DERSKODUZUNLUGU
#define COURSESREGISTERED 5 // KAYITLIDERSLER
#define MIDTERMWEIGHT 30 // VIZEAGIRLIK
#define FINALWEIGHT 30 // FINALAGIRLIK
#define QUIZWEIGHT 20 // QUIZAGIRLIK
#define HOMEWORKWEIGHT 20 // ODEVAGIRLIK
typedef struct fullName//tam adi
{ 
	char *name; //adi
	char *surname; //soyadi
}name_t;
typedef struct examGrades//sinav not
{ 
	double midterm; //vize
	double final; //final
	double quiz; //quiz
	double homework; //odev
	double but; //but
}grades_t;
typedef struct courseRegistered//kayitliDersler
{ 
	char courseName[COURSENAMELENGTH]; //ders adi
	char courseCode[COURSECODELENGTH]; //ders kodu
	grades_t grades; //notler
	char letterGrade[2]; //herf notu
	double numericGrade; //numerik notu
	double courseAverage; //ders ortalama
}courseReg_t;
typedef struct studentInfo//ogrenci bilgi
{ 
	name_t studentName; //ogrenci adi
	char *stNo; //ogrenci numara
	courseReg_t *courses[COURSESREGISTERED]; //dersler
	double gpa; //ortalama
}student_t;
typedef struct courseInfo//ders bilgi
{ 
	char courseName[COURSENAMELENGTH]; //ders adi
	char courseCode[COURSECODELENGTH]; //ders kodu
	student_t students[CLASSSIZE]; //ogrenciler
}courses_t;
void menu1(int secim);//i�lem men�s�
void menu1SwitchCase(int secim);//secim icin switch case 
void ogrenciEkle();
void dersEkle();
void OgrencininDersNotuHesapla();
void OgrenciOrtalamHesapla();
void OgrenciBilgiGoster();
void DersBilgiGoster();
void SinifGoster();
double numerikNotu(double ortalama);
void harflendirme(double ortalama, char *harf);
void Karsilama();


int main(int argc, char** argv) 
{
	int secim=0;//tabloda secicegi i�lemi tutacak
	setlocale(LC_ALL,"Turkish");//t�rkce karakter kullanmam�z� sa�l�yor
	//Karsilama();
	menu1(secim);
	return 0;
}

void menu1(int secim)
{
	int i;//for icin
	int sayac=0,sayac2;
	while(1)
	{
		printf("\n\t\t\tHO�GELD�N�Z->>\n");
		for(i=0; i<25; i++)
		{
			printf("* ");
		}
		printf("\n1->> ��RENC� EKLE\n");
		printf("2->> DERS EKLE\n");
		printf("3->> ��RENC� DERS NOTU HESAPLAMA\n");
		printf("4->> ��RENC� ORTALAMAS� HESAPLAMA\n");
		printf("5->> ��RENC� B�LG�S� G�STER\n");
		printf("6->> DERS B�LG�S� G�STER\n");
		printf("7->> SINIFI G�STER\n");
		printf("8->> EKRAN TEM�ZLE\n");
		printf("9->> ��K��\n");
		for(i=0; i<25; i++)
		{
			printf("* ");
		}
		printf("\n");
		printf("L�TLEN B�R�S�N� SEC�N�Z->>");
		scanf("%d", &secim);
		menu1SwitchCase(secim);
	}
}

void menu1SwitchCase(int secim)
{
	switch(secim)
	{
		printf("\n\tTekrardan Ho�geldiniz->>\n\n");
		case 1:
			ogrenciEkle();
			break;
		case 2:
			dersEkle();
			break;
		case 3:
			OgrencininDersNotuHesapla();
			break;
		case 4:
			OgrenciOrtalamHesapla();
			break;
		case 5:
			OgrenciBilgiGoster();
			break;
		case 6:
			DersBilgiGoster();
			break;
		case 7:
			SinifGoster();
			break;
		case 8:
			system("CLS");//Ekrandaki her �eyin silinmesi sa�lanmaktad�r.
			break;
		case 9:
			exit(1);
			break;
		default:
			printf("yanli� bir bilgi girdiniz->>");
	}
}

void ogrenciEkle()
{
	FILE *fp,*fp2;
	courseReg_t kDersler1, kDersler2;
	student_t ogr1,ogr2;
	char *adres = (char *)malloc(sizeof(char)*30);//sistemden bir kelime * 30  alanl�k yer istiyorum ge�i�i
	adres = "��renci Ekle.txt";
	ogr1.studentName.name = (char *)malloc(sizeof(NAMELENGTH));//sistemden NAMELENGTH  alanl�k yer istiyorum ge�i�i
	ogr1.studentName.surname = (char *)malloc(sizeof(NAMELENGTH));//sistemden NAMELENGTH  alanl�k yer istiyorum ge�i�i
	ogr1.stNo = (char *)malloc(sizeof(STUDENTNUMBERLENGTH));//sistemden STUDENTNUMBERLENGTH  alanl�k yer istiyorum ge�i�i
	ogr2.studentName.name = (char *)malloc(sizeof(NAMELENGTH));//sistemden NAMELENGTH  alanl�k yer istiyorum ge�i�i
	ogr2.studentName.surname = (char *)malloc(sizeof(NAMELENGTH));//sistemden NAMELENGTH  alanl�k yer istiyorum ge�i�i
	ogr2.stNo = (char *)malloc(sizeof(STUDENTNUMBERLENGTH));//sistemden STUDENTNUMBERLENGTH  alanl�k yer istiyorum ge�i�i
	printf("Kayit Edilecek ��rencinin Adi->> ");
	scanf("%s",ogr1.studentName.name);
	printf("Kayit Edilecek ��rencinin Soyadi->> ");
	scanf("%s",ogr1.studentName.surname);
	int denetim=0;//e�er kay�tl� ��renci varsa hata vbermesi icin gecici bir data;
	while(denetim!=1)
	{
		printf("Kayit Edilecek ��rencinin Okul Numarasi(10 basamakli)->>");
		scanf("%s",ogr1.stNo);
		//while icinde acma nedim e�er ikninci hata olursa sat�rabakmaz son sat�r oldugu icin hata vermez devam eder
		if ((fp = fopen(adres, "r+")) == NULL)
		{
     		fp = fopen(adres, "a+");
  		}
		if( (atoi(ogr1.stNo)>999999999 ) && (atoi(ogr1.stNo)<10000000000))
		{//strcmp eper 0 dan k�c�k ise ilk yazilan ikinci yazilandan k�c�kt�r demek 0 dan b�y�k ise tam tersi 0 ise e�it demek
			while(!feof(fp))
			{
				fscanf(fp,"%s %s %s %s %s %lf %lf %lf %lf %lf\n", ogr2.studentName.name, ogr2.studentName.surname, ogr2.stNo, kDersler2.courseName, kDersler2.courseCode, &kDersler2.grades.midterm, &kDersler2.grades.homework, &kDersler2.grades.quiz, &kDersler2.grades.final, &kDersler2.grades.but);
				if(strcmp(ogr1.stNo,ogr2.stNo)==0)
				{
					printf("Okul Numarasi Bulunmaktadir...\n");
					denetim=4;
					break;
				}
			}
			if(denetim!=4)
				denetim=1;
			
			else
				denetim=0;
		}
		else
			printf("��renci Numarasi rakam ve 10 haneli olmalidir!!!\n");
		fclose(fp); // islem bittiginde dosyayi kapatir
	}
	
  	if ((fp2 = fopen("DersBilgileri.txt", "r")) == NULL)
	{
     	printf("Dosya A�ma Hatasi");
     	exit(1);
  	}
  	while(!feof(fp2))
	{
		fscanf(fp2,"%s %s\n", kDersler1.courseName, kDersler1.courseCode);
		while(1)
		{
			printf("%s->>%s Dersinden Aldi�i Vize Notu->> ",kDersler1.courseCode ,kDersler1.courseName);
			scanf("%lf", &kDersler1.grades.midterm);
			if(kDersler1.grades.midterm<=100 && kDersler1.grades.midterm>=0)
				break;
			else
				printf("0 ve 100 Aras� Not Giriniz!!!\n");
		}
		while(1)
		{
			printf("%s->>%s Dersinden Aldi�i Quiz Notu->> ",kDersler1.courseCode ,kDersler1.courseName);
			scanf("%lf", &kDersler1.grades.quiz);
			if(kDersler1.grades.quiz<=100 && kDersler1.grades.quiz>=0)
				break;
			else
				printf("0 ve 100 Aras� Not Giriniz!!!\n");
		}
		while(1)
		{
			printf("%s->>%s Dersinden Aldi�i �dev Notu->> ",kDersler1.courseCode ,kDersler1.courseName);
			scanf("%lf", &kDersler1.grades.homework);
			if(kDersler1.grades.homework<=100 && kDersler1.grades.homework>=0)
				break;
			else
				printf("0 ve 100 Aras� Not Giriniz!!!\n");
		}
		while(1)
		{
			printf("%s->>%s Dersinden Aldi�i Final Notu->> ",kDersler1.courseCode ,kDersler1.courseName);
			scanf("%lf", &kDersler1.grades.final);
			if(kDersler1.grades.final<=100 && kDersler1.grades.final>=0)
				break;
			else
				printf("0 ve 100 Aras� Not Giriniz!!!\n");
		}
		while(1)
		{
			printf("��reenci B�te Girdimi?? Evet ise 1 Hayir ise 2 ye Basin->> ");
			scanf("%d", &denetim);
			if(denetim==1 || denetim==2)
				break;
			else
				printf("1 veya 2 ye basiniz!!!\n");
		}
		if(denetim==1)
		{
			kDersler1.grades.final=0;
			while(1)
			{
				printf("%s->>%s Dersinden Aldi�i B�t Notu->> ",kDersler1.courseCode ,kDersler1.courseName);
				scanf("%lf", &kDersler1.grades.but);
				if(kDersler1.grades.but<=100 && kDersler1.grades.but>=0)
					break;
				else
					printf("0 ve 100 Aras� Not Giriniz!!!\n");
			}
		}
		fp = fopen(adres, "a");
  		fprintf(fp,"%s %s %s %s %s %lf %lf %lf %lf %lf\n", ogr1.studentName.name, ogr1.studentName.surname, ogr1.stNo, kDersler1.courseName, kDersler1.courseCode, kDersler1.grades.midterm, kDersler1.grades.homework, kDersler1.grades.quiz, kDersler1.grades.final, kDersler1.grades.but);
  		fclose(fp);
	}
}

void dersEkle()
{
	FILE *fp;
	int sayac=0;//sayac bize e�er 5 ders varsa ekleme yaptirmicak
	char *adres = (char *)malloc(sizeof(char)*30);//sistemden bir kelime * 30  alanl�k yer istiyorum ge�i�i
	adres = "DersBilgileri.txt";
	courses_t ders1,ders2;
	printf("Kayit Edilecek Dersin Adi->>");
	scanf("%s",ders1.courseName);
	int denetim=0;//e�er kay�tl� ��renci varsa hata vbermesi icin gecici bir data;
	while(denetim!=1)
	{
		printf("Kayit Edilecek Dersin Kodu(10 basamakli)->>");
		scanf("%s",ders1.courseCode);
		//while icinde acma nedim e�er ikninci hata olursa sat�rabakmaz son sat�r oldugu icin hata vermez devam eder
		if ((fp = fopen(adres, "r+")) == NULL)
		{
			fp = fopen(adres, "a+");
  		}
		if( (atoi(ders1.courseCode)>999999999 ) && (atoi(ders1.courseCode)<10000000000))
		{//strcmp eper 0 dan k�c�k ise ilk yazilan ikinci yazilandan k�c�kt�r demek 0 dan b�y�k ise tam tersi 0 ise e�it demek
			while(!feof(fp))
			{
				fscanf(fp,"%s %s\n", ders2.courseName, ders2.courseCode);
				if(strcmp(ders1.courseCode,ders2.courseCode)==0)
				{
					printf("Ders Kodu Bulunmaktadir...\n");
					denetim=4;
					break;
				}
				sayac++;
			}
			if(sayac==5)
			{
				printf("5 Ders Mevcut!!!");
				break;
			}
			if(denetim!=4 && sayac!=5)
			{
				fprintf(fp,"%s %s\n", ders1.courseName, ders1.courseCode);
				denetim=1;
			}
			else
				denetim=0;
		}
		else
			printf("Ders Kodu rakam ve 10 haneli olmalidir!!!\n");
		fclose(fp); // islem bittiginde dosyayi kapatir
	}
	
}


void OgrencininDersNotuHesapla()
{
	int secim;//numaraya g�re secim veya herkesin notunu hesapla
	int sayac=0;// bu sayac bize eger numara bulamad�ysa ekrana hata mesaj� yazmak iicin var..
	int sayac2=0;//e�er notu hesaplanm�ssa uyar� verilecek bir sistem icin lazim
	FILE *fp,*fp2,*fp3;
	courseReg_t kDersler1, kDersler2;
	student_t ogr1, ogr2;
	char gecicino[10];
	char *adres = (char *)malloc(sizeof(char)*30);//sistemden bir kelime * 30  alanl�k yer istiyorum ge�i�i
	adres = "��renci Ekle.txt";
	ogr1.studentName.name = (char *)malloc(sizeof(NAMELENGTH));//sistemden NAMELENGTH  alanl�k yer istiyorum ge�i�i
	ogr1.studentName.surname = (char *)malloc(sizeof(NAMELENGTH));//sistemden NAMELENGTH  alanl�k yer istiyorum ge�i�i
	ogr1.stNo = (char *)malloc(sizeof(STUDENTNUMBERLENGTH));//sistemden STUDENTNUMBERLENGTH  alanl�k yer istiyorum ge�i�i
	ogr2.studentName.name = (char *)malloc(sizeof(NAMELENGTH));//sistemden NAMELENGTH  alanl�k yer istiyorum ge�i�i
	ogr2.studentName.surname = (char *)malloc(sizeof(NAMELENGTH));//sistemden NAMELENGTH  alanl�k yer istiyorum ge�i�i
	ogr2.stNo = (char *)malloc(sizeof(STUDENTNUMBERLENGTH));//sistemden STUDENTNUMBERLENGTH  alanl�k yer istiyorum ge�i�i
	while(1)
	{
		printf("\n* * * * * *  * * * * * * * * * *\n");
		printf("1->> T�m ��rencilerin Notunu Hesapla->>\n");
		printf("2->> Numarasi Girilen ��rencinin Notlarini Hesaplayin->>\n");
		printf("3->> Ekrani Temizle\n");
		printf("4->> Geri\n");
		printf("5->> �iki�\n");
		printf("* * * * * *  * * * * * * * * * *\n");
		printf("Seciniz->> ");
		scanf("%d",&secim);
		if(secim==4)
			break;
		switch(secim)
		{
			case 1:
				fp2 = fopen("Ders Ortalama.txt", "w");
				fclose(fp2);
				fp = fopen(adres, "r");
				while(!feof(fp))
				{
					fscanf(fp,"%s %s %s %s %s %lf %lf %lf %lf %lf\n", ogr1.studentName.name, ogr1.studentName.surname, ogr1.stNo, kDersler1.courseName, kDersler1.courseCode, &kDersler1.grades.midterm, &kDersler1.grades.homework, &kDersler1.grades.quiz, &kDersler1.grades.final, &kDersler1.grades.but);
					if(kDersler1.grades.final==0)
					{
						kDersler1.courseAverage = (kDersler1.grades.midterm*30/100)+(kDersler1.grades.quiz*20/100)+(kDersler1.grades.homework*20/100)+(kDersler1.grades.but*30/100);
						harflendirme(kDersler1.courseAverage, kDersler1.letterGrade);
						kDersler1.numericGrade=numerikNotu(kDersler1.courseAverage);
						fp2 = fopen("Ders Ortalama.txt", "a");
  						fprintf(fp2,"%s %s %s %s %s %lf %lf %lf %lf %lf %lf %lf %s\n", ogr1.studentName.name, ogr1.studentName.surname, ogr1.stNo, kDersler1.courseName, kDersler1.courseCode, kDersler1.grades.midterm, kDersler1.grades.homework, kDersler1.grades.quiz, kDersler1.grades.final, kDersler1.grades.but, kDersler1.courseAverage, kDersler1.numericGrade, kDersler1.letterGrade);
  						fclose(fp2);
					}
					else
					{
						kDersler1.courseAverage = (kDersler1.grades.midterm*30/100)+(kDersler1.grades.quiz*20/100)+(kDersler1.grades.homework*20/100)+(kDersler1.grades.final*30/100);
						harflendirme(kDersler1.courseAverage, kDersler1.letterGrade);
						kDersler1.numericGrade=numerikNotu(kDersler1.courseAverage);
						fp2 = fopen("Ders Ortalama.txt", "a");
  						fprintf(fp2,"%s %s %s %s %s %lf %lf %lf %lf %lf %lf %lf %s\n", ogr1.studentName.name, ogr1.studentName.surname, ogr1.stNo, kDersler1.courseName, kDersler1.courseCode, kDersler1.grades.midterm, kDersler1.grades.homework, kDersler1.grades.quiz, kDersler1.grades.final, kDersler1.grades.but, kDersler1.courseAverage, kDersler1.numericGrade, kDersler1.letterGrade);
  						fclose(fp2);
					}
				}
				break;
			case 2:
				while(sayac==0)
				{
					printf("Ders Ortalamalari Girilecek ��rencinin Numarsini Giriniz->> ");
					scanf("%s", gecicino);
					fp = fopen(adres, "r");
					while(!feof(fp))
					{
						fscanf(fp,"%s %s %s %s %s %lf %lf %lf %lf %lf\n", ogr1.studentName.name, ogr1.studentName.surname, ogr1.stNo, kDersler1.courseName, kDersler1.courseCode, &kDersler1.grades.midterm, &kDersler1.grades.homework, &kDersler1.grades.quiz, &kDersler1.grades.final, &kDersler1.grades.but);
						if(strcmp(gecicino,ogr1.stNo)==0)
						{
							fp3 = fopen("Ders Ortalama.txt", "r");
							while(!feof(fp3))
							{
								fscanf(fp3,"%s %s %s %s %s %lf %lf %lf %lf %lf %lf %lf %s\n", ogr2.studentName.name, ogr2.studentName.surname, ogr2.stNo, kDersler2.courseName, kDersler2.courseCode, &kDersler2.grades.midterm, &kDersler2.grades.homework, &kDersler2.grades.quiz, &kDersler2.grades.final, &kDersler2.grades.but, &kDersler2.courseAverage, &kDersler2.numericGrade, kDersler2.letterGrade);
								if(strcmp(gecicino,ogr2.stNo)==0)
								{
									sayac2++;
								}
							}
							fclose(fp3);
							if(sayac2==0)
							{
								if(kDersler1.grades.final==0)
								{	
									kDersler1.courseAverage = (kDersler1.grades.midterm*30/100)+(kDersler1.grades.quiz*20/100)+(kDersler1.grades.homework*20/100)+(kDersler1.grades.but*30/100);
									harflendirme(kDersler1.courseAverage, kDersler1.letterGrade);
									kDersler1.numericGrade=numerikNotu(kDersler1.courseAverage);
									fp2 = fopen("Ders Ortalama.txt", "a");
  									fprintf(fp2,"%s %s %s %s %s %lf %lf %lf %lf %lf %lf %lf %s\n", ogr1.studentName.name, ogr1.studentName.surname, ogr1.stNo, kDersler1.courseName, kDersler1.courseCode, kDersler1.grades.midterm, kDersler1.grades.homework, kDersler1.grades.quiz, kDersler1.grades.final, kDersler1.grades.but, kDersler1.courseAverage, kDersler1.numericGrade, kDersler1.letterGrade);
  									fclose(fp2);
  									sayac++;
								}
									else
								{	
									kDersler1.courseAverage = (kDersler1.grades.midterm*30/100)+(kDersler1.grades.quiz*20/100)+(kDersler1.grades.homework*20/100)+(kDersler1.grades.final*30/100);
									harflendirme(kDersler1.courseAverage, kDersler1.letterGrade);
									kDersler1.numericGrade=numerikNotu(kDersler1.courseAverage);
									fp2 = fopen("Ders Ortalama.txt", "a");
  									fprintf(fp2,"%s %s %s %s %s %lf %lf %lf %lf %lf %lf %lf %s\n", ogr1.studentName.name, ogr1.studentName.surname, ogr1.stNo, kDersler1.courseName, kDersler1.courseCode, kDersler1.grades.midterm, kDersler1.grades.homework, kDersler1.grades.quiz, kDersler1.grades.final, kDersler1.grades.but, kDersler1.courseAverage, kDersler1.numericGrade, kDersler1.letterGrade);
  									fclose(fp2);
  									sayac++;
								}
							}
						}
					}
					if(sayac2!=0)
					{
						printf("��rencinin Ortalama Zaten Hesaplanmi�!!!!");
						break;
					}
					if(sayac==0)
						printf("Girdi�iniz Numaraya Aid Bir ��renci Bulunmadi!!! \n");
				}
				sayac2=0;
				sayac=0;
				break;
			case 3:
				system("CLS");//Ekrandaki her �eyin silinmesi sa�lanmaktad�r.
				break;
			case 4:
				break;
			case 5:
				exit(1);
				break;
		}
	}	
	
}

void OgrenciOrtalamHesapla()
{
	int secim;//secim bize secti�imiz i�lemin rakam�n� tutacak
	courseReg_t kDersler1;
	student_t ogr1;
	FILE *fp,*fp2;
	char *adres = (char *)malloc(sizeof(char)*30);//sistemden bir kelime * 30  alanl�k yer istiyorum ge�i�i
	adres = "Ders Ortalama.txt";
	ogr1.studentName.name = (char *)malloc(sizeof(NAMELENGTH));//sistemden NAMELENGTH  alanl�k yer istiyorum ge�i�i
	ogr1.studentName.surname = (char *)malloc(sizeof(NAMELENGTH));//sistemden NAMELENGTH  alanl�k yer istiyorum ge�i�i
	ogr1.stNo = (char *)malloc(sizeof(STUDENTNUMBERLENGTH));//sistemden STUDENTNUMBERLENGTH  alanl�k yer istiyorum ge�i�i
	int sayac=0;//5 ders oldu�u icin her5 oldugunda 0 lan�r
	while(1)
	{
		printf("\n* * * * * *  * * * * * * * * * *\n");
		printf("1->> T�m ��rencilerin Ortalamalarini Hesapla->>\n");
		printf("2->> Ekrani Temizle\n");
		printf("3->> Geri\n");
		printf("4->> �iki�\n");
		printf("* * * * * *  * * * * * * * * * *\n");
		printf("Seciniz->> ");
		scanf("%d",&secim);
		if(secim==3)
			break;
		switch(secim)
		{
			case 1:
				fp2 = fopen("��renci Ortalamalari.txt","w");
				fclose(fp2);
				fp = fopen(adres, "r");
				while(!feof(fp))
				{
					fscanf(fp,"%s %s %s %s %s %lf %lf %lf %lf %lf %lf %lf %s\n", ogr1.studentName.name, ogr1.studentName.surname, ogr1.stNo, kDersler1.courseName, kDersler1.courseCode, &kDersler1.grades.midterm, &kDersler1.grades.homework, &kDersler1.grades.quiz, &kDersler1.grades.final, &kDersler1.grades.but, &kDersler1.courseAverage, &kDersler1.numericGrade, kDersler1.letterGrade);
					if(sayac<5)
					{
						ogr1.gpa+=kDersler1.courseAverage;
						sayac++;
					}
					if(sayac==5)
					{
						ogr1.gpa=(ogr1.gpa/5);
						fp2 = fopen("��renci Ortalamalari.txt","a");
						fprintf(fp2,"%s %s %s %lf\n", ogr1.studentName.name, ogr1.studentName.surname, ogr1.stNo, ogr1.gpa);
						fclose(fp2);
						sayac=0;
						ogr1.gpa=0;
					}
				}
				printf("islem Gercekle�mi�tir...\n");
				fclose(fp);
				break;
			case 2:
				system("CLS");//Ekrandaki her �eyin silinmesi sa�lanmaktad�r.
				break;
			case 3:
				break;
			case 4:
				exit(1);
				break;
		}
	}
}
void OgrenciBilgiGoster()
{
	FILE *fp;
	student_t ogr1;
	char *adres = (char *)malloc(sizeof(char)*30);//sistemden bir kelime * 30  alanl�k yer istiyorum ge�i�i
	adres = "��renci Ortalamalari.txt";
	ogr1.studentName.name = (char *)malloc(sizeof(NAMELENGTH));//sistemden NAMELENGTH  alanl�k yer istiyorum ge�i�i
	ogr1.studentName.surname = (char *)malloc(sizeof(NAMELENGTH));//sistemden NAMELENGTH  alanl�k yer istiyorum ge�i�i
	ogr1.stNo = (char *)malloc(sizeof(STUDENTNUMBERLENGTH));//sistemden STUDENTNUMBERLENGTH  alanl�k yer istiyorum ge�i�i
	if ((fp = fopen(adres, "r")) == NULL)
	{
     	printf("Dosya a�ma hatas�!\n");
    	exit(1);
  	}
  	printf("|��renci Ad| |��renci Soyadi| |��renci No| |��renci Genel Ort|\n");
  	while(!feof(fp))
	{
		fscanf(fp,"%s %s %s %lf\n", ogr1.studentName.name, ogr1.studentName.surname, ogr1.stNo, &ogr1.gpa);
		printf("%s %s %s %lf\n", ogr1.studentName.name, ogr1.studentName.surname, ogr1.stNo, ogr1.gpa);
	}
  	fclose(fp); // islem bittiginde dosyayi kapatir
	printf("\n\t\t--i�lem Basari Ile Gerceklestirilmistir--\n");
}

void DersBilgiGoster()
{
	FILE *fp;
	char *adres = (char *)malloc(sizeof(char)*30);//sistemden bir kelime * 30  alanl�k yer istiyorum ge�i�i
	adres = "DersBilgileri.txt";
	courses_t ders1;
	if ((fp = fopen(adres, "r")) == NULL)
	{
     	printf("Dosya a�ma hatas�!\n");
    	exit(1);
  	}
  	printf("|Ders Ad| |Ders Kodu|\n");
  	while(!feof(fp))
	{
		fscanf(fp,"%s %s\n", ders1.courseName, ders1.courseCode);
		printf("%s %s\n", ders1.courseName, ders1.courseCode);
	}
  	fclose(fp); // islem bittiginde dosyayi kapatir
	printf("\n\t\t--i�lem Basari Ile Gerceklestirilmistir--\n");
}

void SinifGoster()
{
	FILE *fp;
	student_t ogr1,ogr2;
	courseReg_t kDersler1;
	char *adres = (char *)malloc(sizeof(char)*30);//sistemden bir kelime * 30  alanl�k yer istiyorum ge�i�i
	adres = "��renci Ekle.txt";
	ogr1.studentName.name = (char *)malloc(sizeof(NAMELENGTH));//sistemden NAMELENGTH  alanl�k yer istiyorum ge�i�i
	ogr1.studentName.surname = (char *)malloc(sizeof(NAMELENGTH));//sistemden NAMELENGTH  alanl�k yer istiyorum ge�i�i
	ogr1.stNo = (char *)malloc(sizeof(STUDENTNUMBERLENGTH));//sistemden STUDENTNUMBERLENGTH  alanl�k yer istiyorum ge�i�i
	int tekhak=0;//her 5 te 0 olacak
	int i=0;//ki�i sayisi
	if ((fp = fopen(adres, "r")) == NULL)
	{
     	printf("Dosya a�ma hatas�!\n");
    	exit(1);
  	}
  	printf("|��renci Ad| |��renci Soyadi| |��renci No|\n");
  	while(!feof(fp))
	{
		fscanf(fp,"%s %s %s %s %s %lf %lf %lf %lf %lf\n", ogr1.studentName.name, ogr1.studentName.surname, ogr1.stNo, kDersler1.courseName, kDersler1.courseCode, &kDersler1.grades.midterm, &kDersler1.grades.homework, &kDersler1.grades.quiz, &kDersler1.grades.final, &kDersler1.grades.but);
		if(tekhak==0)
		{
			ogr2.studentName.name=ogr1.studentName.name;
			ogr2.studentName.surname=ogr1.studentName.surname;
			ogr2.stNo=ogr1.stNo;
			printf("%d->>%s %s %s\n", i+1, ogr2.studentName.name, ogr2.studentName.surname, ogr2.stNo);
			i++;
		}
		tekhak++;
		if(tekhak==5)
			tekhak=0;
	}
  	fclose(fp); // islem bittiginde dosyayi kapatir
	printf("\n\t\t--i�lem Basari Ile Gerceklestirilmistir--\n");
}

double numerikNotu(double ortalama)
{
	if ( ortalama < 50 )
		return 0.00;
	else if ( ortalama < 60 )
		return 1.00;
	else if ( ortalama < 70 )
		return 1.50;
	else if ( ortalama < 75 )
		return 2.00;
	else if ( ortalama < 80 )
		return 2.50;
	else if ( ortalama < 85 )
		return 3.00;
	else if ( ortalama < 90 )
		return 3.50;
	else
		return 4.00;
}
void harflendirme(double ortalama, char *harf)
{
	if ( ortalama < 50 )
		strcpy(harf,"FF");//0-49
	else if ( ortalama < 60 )
		strcpy(harf,"DD");//-50-59
	else if ( ortalama < 70 )
		strcpy(harf,"DC");//60-69
	else if ( ortalama < 75 )
		strcpy(harf,"CC");//70-74
	else if ( ortalama < 80 )
		strcpy(harf,"CB");//75-79
	else if ( ortalama < 85 )
		strcpy(harf,"BB");//80-84
	else if ( ortalama < 90 )
		strcpy(harf,"BA");//85-90
	else
		strcpy(harf,"AA");
}

void Karsilama( void )//giri�
{
	printf("\n\n\n\t\t\tHO�GELD�N�Z->>\n\n");
	sleep(1);//burda bekletmek i�in bir fonksiyon
  	printf("\n\n\t\tSistem Y�kleniyor!!!\n\n\t\t");
    sleep(1);//burda bekletmek i�in bir fonksiyon
    printf("Y�kleme Tamamland�...\n");
    sleep(1);//burda bekletmek i�in bir fonksiyon
    system("CLS");//Ekrandaki her �eyin silinmesi sa�lanmaktad�r.
}//fonksiyonun sonu

