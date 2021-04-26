
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>

void menu();
void menuseneryo();
void ledyak(HANDLE hComm ,int lednum );
void ledsondur(HANDLE hComm ,int lednum);
void sureliyak(HANDLE hComm,int lednum,int sure );
void seneryo(HANDLE hComm);
int yakledal();
int sureal();
int ledal();
int sonledal();
void erornum();
void erorsure();
void erorsec();
void log1(int lednum1);
void log2(int lednum);
void log3(int lednum2,int sure);
void log4(char seneryo[3]);


int main() {
	
//---------------------------------------------------------------------PORT B�LG�LER�--------------------------------------------------------------------------------------------------	


	HANDLE hComm = CreateFile("COM3", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0); // COM3 portunu okuma ve yazma i�lemleri i�in a�
 
	if (hComm == INVALID_HANDLE_VALUE) { // porta eri�im sa�lanamad�ysa
		
		if (GetLastError() == ERROR_FILE_NOT_FOUND) { // olu�an hata "bulunamad�" ise
			
			printf("port erisimi yok\n") ; // ekrana "port erisimi yok" yaz
			
		}
	
	}

	DCB dcbSerialParams = {0};

	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

	if (!GetCommState(hComm, &dcbSerialParams)) { // seri ileti�im ayarlar� uygulanamad�ysa
		
		printf("baglanti hatasi\n"); // ekrana "baglanti hatasi" yaz
		
		return EXIT_FAILURE; // program� sonland�r
		
	}
	
	// seri ileti�im ayarlar�
	dcbSerialParams.BaudRate = CBR_9600; // 9600 h�z�nda
	dcbSerialParams.ByteSize = 8; // 8 bitlik paketler halinde
	dcbSerialParams.Parity = NOPARITY; // e�lik biti yok
	dcbSerialParams.StopBits = ONESTOPBIT; // 1 tane stop biti var
	
	if (!SetCommState(hComm, &dcbSerialParams)) { // seri ileti�im ayarlar� uygulanamad�ysa
		
		printf("baglanti hatasi\n"); // ekrana "baglanti hatasi" yaz
		
		return EXIT_FAILURE; // program� sonland�r

}	
	
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------	

	int s;
	//while d�g�s� kullan�c� 5 e basana kadar devam eder.kullan�c� 5 e bast���nda s=6 olur ve d�g�den ��karak program� sonland�r�r.
	while(s!=6){
	//menuyu yazd�ran fonksiyon	
	menu();
	printf("\nYapmak istediginiz secenegi giriniz:");
	//kullan�c�dan s de�i�keni al�narak program�n istenilen case'e girmesi sa�lan�r.
	scanf("%d",&s);
	
	switch(s){
		
	system("CLS");
//---------------------------------led yakma-----------------------------------------		

	case 1: 
	int lednum1;
	//yakledal fonksiyonu ile led numaras� al�r ve de�eri lednum1'e atar. 
	lednum1=yakledal();	
	
	//e�er al�nan led numaras� 1 ile 8 aras�nda ise if e girer ve ledyak fonksiyonunu �al��t�r ve bunu log1 fonksiyonu ile txt dosyas�na yazd�r�r. 
	if(lednum1>0 && lednum1<9){
	//led numaras�n� ve port bilgisini alarak ledyak fonksiyonuna g�nderir		
	ledyak(hComm ,lednum1);
	//led numaras��n� al�r ve log1 fonksiyonu ile txt dosyas�na yazd�r�r.
	log1(lednum1);	
 	system("CLS");
}
	//e�er al�nan led numaras� 1 ile 8 aras�nda de�ilse else ye girer ve erornum fonksiyonunu �al��t�r�r.
	else {
	
	system("CLS");
	erornum();
}
	break;
//---------------------------------led s�nd�rme----------------------------------------	
	case 2: 
	int lednum2;
	//sonledal fonksiyonu ile led numaras� al�r ve de�eri lednum2'ye atar. 
	lednum2=sonledal();	
	//e�er al�nan led numaras� 1 ile 8 aras�nda ise if e girer ve ledyak fonksiyonunu �al��t�r ve bunu log2 fonksiyonu ile txt dosyas�na yazd�r�r. 
	if(lednum2>0 && lednum2<9){
	//led numaras�n� ve port bilgisini alarak ledyak fonksiyonuna g�nderir	
	ledsondur(hComm ,lednum2);
	//led numaras��n� al�r ve log1 fonksiyonu ile txt dosyas�na yazd�r�r.
	log2(lednum2);
	system("CLS");
		
}
	//e�er al�nan led numaras� 1 ile 8 aras�nda de�ilse else ye girer ve erornum fonksiyonunu �al��t�r�r.
	else {
	system("CLS");
	erornum();
}
	
	break;
//----------------------------------istenen s�rede istenen ledi yakma--------------------------------------
	case 3:
	
	int lednum3,sure;
	//ledal fonksiyonu ile led numaras� al�r ve de�eri lednum3'e atar. 
	lednum3=ledal();	
	//sureal fonksiyonu ile s�re bilgisi al�n�r ve de�eri sure de�i�kenine atan�r.
	sure=sureal();
	
	//e�er al�nan led numaras� 1 ile 8 aras�nda ise if e girer.
	if(lednum3>0 && lednum3<9){
	//e�er girilen s�re 10 ile 1000 aras�nda de�ilse hata mesaj�n� yazd�r�r.
	if(sure<10 || sure>1000){	
	system("CLS");
	erorsure();
}
	//e�er al�nan de�er 10-1000 aras�nda ise else'girer.
	else{
	//port bilgisini led numaras�n� ledin yanma	s�resini alarak s�reliyak fonksiyonuna g�nderir.
	sureliyak(hComm,lednum3,sure);
	//led numaras� ve ledin yanma s�resini alarak log 3 fonksiyonuna g�nderir ve orada al�nan bilgiler txt dosyas�na yazd�r�l�r.	
	log3(lednum3,sure);
	system("CLS");
}
}	
	//e�er girilen led numaras� 1 ile 8 aras�nda de�ilse hata mesaj�n� yazd�r�r.
	else{
	system("CLS");	
	erornum();
	
}
	break;
//------------------------------------------seneryo-------------------------------------------------	
	case 4:
	system("CLS");
	//seneryo menusunu ekrena yazd�racak olan fonksiyon
	menuseneryo();	
	//port bilgisini alarak seneryo fonksiyonuna g�nderir.
	seneryo(hComm);
	system("CLS");	
	break;
//--------------------------------------------��k��-------------------------------------------------	
	case 5:
	 s=6;
	 printf("\n\ncikmak icin herhangi bir tusa basininz");
	break;
	
	default: printf("yanlis bir secenek tusladiniz lutfen tekrar deneyiniz!");
		
	}
	
}

}

//---------------------------------------------------------------------TANIMLANAN FONKS�YONLAR-------------------------------------------------------------------------------


//men�y� ekrana yazd�r�r.
	void menu(){
		
	printf("Kontrol Menusu \n1- Istenen Ledi yakma\n2- Istenen Ledi sondurme  \n3- Istenen Ledi istenen surede yakma \n4- Senaryo  \n5- Cikis\n");
		
	}
//seneryo men�s�n� ekrana yazd�r�r.	
	void menuseneryo(){
	
	printf("1-karasimsek\n2-sirali yakma\n3-polis cakari ");
}


//-----------------al�nan bilgileri kullanarak istenilen ledi yakan fonksiyon---------------- 	
	
	void ledyak(HANDLE hComm,int lednum1){
			
			//bir char dizisi tan�mlar al�nan de�erleri tutar.burada char dizisi �eklinde tan�malamam�n sebebi al�nan de�erleri string format�nda arduinoya g�ndermek. 
			char ledyak[10];
			//fonkgir de�i�keni ile 1 de�erini al�r.burada 1 yazmam�n sebebi arduinoya g�nderdi�imiz zaman ledyak k�sm�na girmesini sa�lamak. 
			int fonkgir=1;
			
	//bu fonksiyon ile ilk olarak fonkgir de�i�kenini stringe,sonrada lednum2 de�i�kenini stringe d�n��t�rerek s�ras�yla ledyak dizisine aktar�r.
	sprintf(ledyak,"%d%d",fonkgir,lednum1);
	
	
DWORD dNoOFBytestoWrite;         
DWORD dNoOfBytesWritten = 0;     
dNoOFBytestoWrite = sizeof(ledyak);

//burada char de�i�kenini string format�nda arduinoya g�nderir orada da 1 ve girilen led numaras� na ayr�larak ilgili yerlere g�nderilir.
WriteFile( hComm,ledyak,dNoOFBytestoWrite,&dNoOfBytesWritten,NULL);
		
		
	}
	
//yak�lacak ledin numaras�n� alan fonksiyon	
	int yakledal(){
		
	int lednum1;
	printf("1 ile 8 arasinda yakmak istediginiz led numarasini girin:");
	scanf("%d",&lednum1);

	return lednum1;	
		
	}

//--------------------al�nan bilgileri kullanarak istenilen ledi s�nd�ren fonksiyon-----------------------	

	void ledsondur(HANDLE hComm ,int lednum2){
			
			//bir char dizisi tan�mlar al�nan de�erleri tutar.burada char dizisi �eklinde tan�malamam�n sebebi al�nan de�erleri string format�nda arduinoya g�ndermek. 
			char ledson[10];
			//fonkgir de�i�keni ile 2 de�erini al�r.burada 2 yazmam�n sebebi arduinoya g�nderdi�imiz zaman leds�nd�r k�sm�na girmesini sa�lamak. 
			int fonkgir=2;
					
	//bu fonksiyon ile ilk olarak fonkgir de�i�kenini stringe,sonrada lednum2 de�i�kenini stringe d�n��t�rerek s�ras�yla ledson dizisine aktar�r.
	sprintf(ledson,"%d%d",fonkgir,lednum2);
	
DWORD dNoOFBytestoWrite;         
DWORD dNoOfBytesWritten = 0;     
dNoOFBytestoWrite = sizeof(ledson);
//burada char de�i�kenini string format�nda arduinoya g�nderir orada da 2 ve girilen led numaras� na ayr�larak ilgili yerlere g�nderilir.
WriteFile( hComm,ledson,dNoOFBytestoWrite,&dNoOfBytesWritten,NULL);
		
	}
//s�nd�relecek ledin numaras�n� alan fonksiyon	
	int sonledal(){
	
	int lednum2;
	printf("1 ile 8 arasinda sondurmek istediginiz led numarasini girin:");
	scanf("%d",&lednum2);
	
	
	return lednum2;	
		
	}

// ----------------------------istenilen s�rede istenilen ledi yakan fonksiyon----------------------------------

	void sureliyak(HANDLE hComm ,int lednum3,int sure){
	//bir char dizisi tan�mlar al�nan de�erleri tutar.burada char dizisi �eklinde tan�malamam�n sebebi al�nan de�erleri string format�nda arduinoya g�ndermek. 	
	char gonder[10];
	//fonkgir de�i�keni ile 3 de�erini al�r.burada 3 yazmam�n sebebi arduinoya g�nderdi�imiz zaman s�reyle led yakma k�sm�na girmesini sa�lamak. 
	int fonkgir=3;
	
	//bu fonksiyon ile ilk olarak fonkgir de�i�kenini stringe,sonrada lednum3 de�i�kenini stringe son olarakta sure de�i�kenin stringe d�n��t�rerek s�ras�yla ledson dizisine aktrar�r.	
	sprintf(gonder,"%d%d%d",fonkgir,lednum3,sure);
		
DWORD dNoOFBytestoWrite;         
DWORD dNoOfBytesWritten = 0;     
dNoOFBytestoWrite = sizeof(gonder);

//burada char de�i�kenini string format�nda arduinoya g�nderir orada da 3,girilen led numaras� ve s�reye ayr�larak ilgili yerlere g�nderilir.
WriteFile( hComm,gonder,dNoOFBytestoWrite,&dNoOfBytesWritten,NULL);
		             
}

//istenilen s�rede yak�lacak ledin numaras�n� al�r.
int ledal(){
	int lednum3;
	printf("1 ile 8 arasinda yakmak istediginiz led numarasini girin:");
	scanf("%d",&lednum3);
	
	return lednum3;
}

////istenilen s�rede yak�lacak ledin s�resini al�r.
int sureal(){
	int sure;
	printf("ledin 10-1000 ms arasinda yanmasini istediginiz sureyi giriniz:");
	scanf("%d",&sure);	
	
	return sure;
	
}

//-----------------------------istenilen seneryoda led yakma fonksiyonu-------------------------

/* NOT:burada de�erleri sprintf fonksiyonuna altarnetif olarak farkl� bir �ekilde dizinin i�ine aktard�m burada 3 de�i�ken olarak yap�labilir.
Yukar�daki fonksiyonlarda da bu y�ntemle yapabirdik ama orada 8 farkl� de�i�ken olaca�� i�in algoritman�n mant���na ayk�r� olurdu.*/

void seneryo(HANDLE hComm){
		//burada gene string �eklinde tan�mlayaca��m�z i�in char dizisi a��yoruz.
		char seneryo[3];
	
		
	printf("\n\nuygulamak istediginiz seneryoyu girin:");
	scanf("%s",seneryo);
	
	//e�er ilk �� se�enekten biri girildiyse if'e girer ve ilgili de�eri log4 fonksiyonuna g�nderir.
	if(seneryo[0]=='1' || seneryo[0]=='2' || seneryo[0]=='3'){
	
	//e�er 1 girildiyse seneryonun i�ine string format�nda 41 atanacak ve arduinoya g�nderilince orada 4 ve 1 olarak ayr�lacak ve ilgili k�s�mlara g�nderilecek. 
	if(seneryo[0]=='1'){
	
	char seneryo1[3]="41";
	strcpy(seneryo,seneryo1);
}
	//e�er 2 girildiyse seneryonun i�ine string format�nda 42 atanacak ve arduinoya g�nderilince orada 4 ve 2 olarak ayr�lacak ve ilgili k�s�mlara g�nderilecek. 
	if(seneryo[0]=='2'){
	
	char seneryo2[3]="42";
	strcpy(seneryo,seneryo2);
}
	//e�er 3 girildiyse seneryonun i�ine string format�nda 43 atanacak ve arduinoya g�nderilince orada 4 ve 3 olarak ayr�lacak ve ilgili k�s�mlara g�nderilecek. 
	if(seneryo[0]=='3'){
	
	char seneryo3[3]="43";
	strcpy(seneryo,seneryo3);
}

log4(seneryo);

}

//e�er yanl�� bir se�enek girildiyse eror mesaj�n� ekrana yazd�r�r, ledi yakmaz ve txt dosyas�na yazd�rmaz.
else{

system("CLS");
erorsec();
}

DWORD dNoOFBytestoWrite;         
DWORD dNoOfBytesWritten = 0;     
dNoOFBytestoWrite = sizeof(seneryo);
//burada char de�i�kenini string format�nda arduinoya g�nderir orada da 4 ve girilen seneryo numaras� ilgili yerlere g�nderilir.
WriteFile( hComm,seneryo,dNoOFBytestoWrite,&dNoOfBytesWritten,NULL);
	
}

//kullan�c�ya yanl�� bir de�er girdi�ini ekrana yazd�rarak bilgi verir.
void erornum(){
	
	printf("yanlis bir led numarasi girdiniz!!\nlutfen 1 ile 8 arasinda bir deger giriniz\n");
}
//kullan�c�ya yanl�� bir de�er girdi�ini ekrana yazd�rarak bilgi verir.
void erorsure(){
	printf("yanlis bir deger girdiniz!!\nlutfen 10 ile 1000 arasinda bir deger giriniz\n");
}
// kullan�c�ya yanl�� bir de�er girdi�ini ekrana yazd�rarak bilgi verir.
void erorsec(){
	printf("yanlis bir secenek sectiniz!!\nlutfen 1 ile 3 arasinda bir deger giriniz\n");
}

//yak�lan led numaras�n� o an�n tarih ve saatinde txt dosyas�na yazd�r�ran fonksiyon 
void log1(int lednum1){
	
	FILE *dosya;
	//arduino ad�nda ekleme format�nda bir dosya a�ar
	dosya=fopen("arduino.txt","a");
	
	// time_t tipinde bir de�i�ken olu�turur.
	time_t t;
  // zamanbil ad�nda bir struct yap�s� tan�mlan�r.	
  struct tm *zamanbil;
  //time fonksiyonuile takvim zaman�n� al�r.	
  time (&t);
  //local time fonksiyonu ile takvim zaman�n� yerel zamana d�n��t�r�r ve zamanbil de�i�kenine atar.
  zamanbil = localtime (&t);
  
  //anl�k s�reyi txt dosyas�na yazd�r�r. 	
  fprintf(dosya,"tarih:%d/%02d/%d  saat:%02d:%02d:%02d ",zamanbil->tm_mday,zamanbil->tm_mon+1,zamanbil->tm_year+1900,zamanbil->tm_hour,zamanbil->tm_min,zamanbil->tm_sec);
  //led numaras�n� txt dosyas�na yazd�r�r.
  fprintf(dosya,"%d.led yak�ld� \n",lednum1);
  

	//dosyay� kapat�r.
	fclose(dosya);	
	
	
}

//s�nd�r�len led numaras�n� o an�n tarih ve saatinde txt dosyas�na yazd�r�ran fonksiyon 
void log2(int lednum2){
	
	FILE *dosya;
	//arduino ad�nda ekleme format�nda bir dosya a�ar
	dosya=fopen("arduino.txt","a");
	// time_t tipinde bir de�i�ken olu�turur.
	time_t t;
  // zamanbil ad�nda bir struct yap�s� tan�mlan�r.			
  struct tm *zamanbil;
  //time fonksiyonuile takvim zaman�n� al�r.	
  time (&t);
  //local time fonksiyonu ile takvim zaman�n� yerel zamana d�n��t�r�r ve zamanbil de�i�kenine atar.
  zamanbil = localtime (&t);
  //anl�k s�reyi txt dosyas�na yazd�r�r. 	
  fprintf(dosya,"tarih:%d/%02d/%d  saat:%02d:%02d:%02d ",zamanbil->tm_mday,zamanbil->tm_mon+1,zamanbil->tm_year+1900,zamanbil->tm_hour,zamanbil->tm_min,zamanbil->tm_sec);
  //led numaras�n� txt dosyas�na yazd�r�r.
  fprintf(dosya,"%d.led s�nd� \n",lednum2);
  
	
	//dosyay� kapat�r.
	fclose(dosya);	
	
}
//yak�lan led numaras�n� ve s�reyi o an�n tarih ve saatinde txt dosyas�na yazd�r�ran fonksiyon 
void log3(int lednum3,int sure){
	
	
		FILE *dosya;
	//arduino ad�nda ekleme format�nda bir dosya a�ar
	dosya=fopen("arduino.txt","a");
	// time_t tipinde bir de�i�ken olu�turur.
	time_t t;
	// zamanbil ad�nda bir struct yap�s� tan�mlan�r.	
  struct tm *zamanbil;
  //time fonksiyonuile takvim zaman�n� al�r.	
  time (&t);
  //local time fonksiyonu ile takvim zaman�n� yerel zamana d�n��t�r�r ve zamanbil de�i�kenine atar.
  zamanbil = localtime (&t);
  //anl�k s�reyi txt dosyas�na yazd�r�r. 	
  fprintf(dosya,"tarih:%d/%02d/%d  saat:%02d:%02d:%02d ",zamanbil->tm_mday,zamanbil->tm_mon+1,zamanbil->tm_year+1900,zamanbil->tm_hour,zamanbil->tm_min,zamanbil->tm_sec);
  //led numaras�n� txt dosyas�na yazd�r�r.
  fprintf(dosya,"%d.led %dms yand�\n",lednum3,sure);
  
    //dosyay� kapat�r.
	fclose(dosya);		
	
}

//seneryo numaras�na g�re istenilen mesaj� o an�n tarih ve saatinde txt dosyas�na yazd�r�ran fonksiyon 
void log4(char seneryo[3]){
	
		FILE *dosya;
	//arduino ad�nda ekleme format�nda bir dosya a�ar
	dosya=fopen("arduino.txt","a");
	// time_t tipinde bir de�i�ken olu�turur.
	time_t t;
	// zamanbil ad�nda bir struct yap�s� tan�mlan�r.
  struct tm *zamanbil;
  //time fonksiyonuile takvim zaman�n� al�r.
  time (&t);
  //local time fonksiyonu ile takvim zaman�n� yerel zamana d�n��t�r�r ve zamanbil de�i�kenine atar.
  zamanbil = localtime (&t);
  //anl�k s�reyi txt dosyas�na yazd�r�r.
  fprintf(dosya,"tarih:%d/%02d/%d  saat:%02d:%02d:%02d ",zamanbil->tm_mday,zamanbil->tm_mon+1,zamanbil->tm_year+1900,zamanbil->tm_hour,zamanbil->tm_min,zamanbil->tm_sec);
  
  //burada girilen seneryo numaras�na g�re ilgili mesaj� txt dosyas�na yazd�r�r.
  if(seneryo[1]=='1')
  fprintf(dosya,"kara�im�ek \n");
  
  if(seneryo[1]=='2')
  fprintf(dosya,"s�ral� yakma \n");	
	
  if(seneryo[1]=='3')
  fprintf(dosya,"polis �akar� \n");	
	
	 //dosyay� kapat�r.
	fclose(dosya);	
	
}






