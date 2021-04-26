String veri="";
void ledyak(int led);
void ledsondur(int lednum2);
void ledsureyak(int lednum,int sure);
void karasimsek();
void siraliyakma();
void poliscakari();
void tumledlerisondur();

void setup() {
    //seri haberleşme hızını ayarlayarak arduino ile eşleşmesini sağlar.
    Serial.begin(9600);
    //tanımlı ledleri çıkış olarak tanımlar
    for(int i=2;i<=9;i++)   
  pinMode(i,OUTPUT);
}

void loop() {
    if(Serial.available()>0){
//gelen veriyi string formatında okur
      veri=Serial.readString();
//string formatının ilk verisini okuyup onu integer formatına dönüştürüp led değişkenine atar.
      int led=veri.substring(0,1).toInt();
      
//eğer led 1'e eşitse if e girer ve kullanıcıdan alınmış olunan ledi yakar      
    if(led==1 ){
//burada string verimizden 1 den 2'ye kadar yani 2.veriyi alır ve integer formatına dönüştürür.Buda led numarasına eşittir.Son olarak bu değeri lednum1 değişkenine atar.      
    int lednum1=veri.substring(1,2).toInt();
//ilednum1 değişkeninin içerisindeki led numarsını ledyak fonksiyonuna göndererek ilgili ledi yakar.    
    ledyak(lednum1);
    }
//eğerled 2'ye eşitse if e girer ve kullanıcıdan alınmış olunan ledi söndürür.    
    if(led==2){
//burada string verimizden 1 den 2 e kadar yani 2.veriyi alır ve integer formatına dönüştürür.Buda led numarasına eşittir.Son olarak bu değeri lednum2 değişkenine atar.
    int lednum2=veri.substring(1,2).toInt();
//lednum2 değişkeninin içerisindeki led numarsını ledsondur fonksiyonuna göndererek ilgili ledi söndürür.       
    ledsondur(lednum2);
    
    }

//eğer led 3'e eşitse if e girer ve kullanıcıdan alınmış olunan ledi kullanıcının istediği süre boyunca yakar.     
    if(led==3){
//burada string verimizden 1 den 2'ye kadar yani 2.veriyi alır ve integer formatına dönüştürür.Buda led numarasına eşittir.Son olarak bu değeri lednum3 değişkenine atar.     
    int lednum3=veri.substring(1,2).toInt();
//yine string verimizden 2 den sonraki verileri alarak integer formatına dönüştürür.Buda girilen süreye eşittir.Alınan değeride son olarak sure değişkenine atar.     
    int sure =veri.substring(2).toInt();
//eğer bir ledi yaktıysak ve söndürmediysek tekrar sorunsuz bir şekilde yakabilmek için tumledleri söndüren fonksiyon.    
    tumledlerisondur();
//ledlerin söndüğünü gözle görebilmek için kısa bir bekleme süresi.    
    delay(200);
//lednum3 değişkeni içerisindeki led numarasını ve sure değişkeni içersindeki süre'yi alıp ledsureyak fonksiyonunun içersine gönderir.    
    ledsureyak(lednum3,sure);
    }

    if(led==4){
//burada string verimizden 1 den 2'ye kadar yani 2.veriyi alır ve integer formatına dönüştürür.Buda seneryo numarasına eşittir.Son olarak bu değeri lednum4 değişkenine atar.     
    int lednum4=veri.substring(1,2).toInt(); 
//eğer lednum4 1'e eşitse öncesinde yanan led varsa tüm ledleri söndürür ve karasimsek fonksiyonunu çalıştırır.    
    if(lednum4==1){
    tumledlerisondur(); 
     karasimsek();
    }      
//eğer lednum4 2'ye eşitse öncesinde yanan led varsa tüm ledleri söndürür ve siraliiyakma fonksiyonunu çalıştırır. 
    if(lednum4==2){
     tumledlerisondur(); 
     siraliyakma();
    }
//eğer lednum4 3'e eşitse öncesinde yanan led varsa tüm ledleri söndürür ve poliscakari fonksiyonunu çalıştırır.   
     if(lednum4==3){
     tumledlerisondur(); 
     poliscakari();
     }
       
    }
     
}
}

---------------------------------------------------------------------------------------Fonksiyonlar-----------------------------------------------------------------------------------------------------------


//ilk ledi 2.pine tanımlayarak başladığımız için led numarasını 1 arttırarak ilgili ledi yakar.
void ledyak(int lednum1){
digitalWrite((lednum1+1),HIGH);

}
//ilk ledi 2.pine tanımlayarak başladığımız için led numarasını 1 arttırarak ilgili ledi söndürür.
void ledsondur(int lednum2){
  
  digitalWrite((lednum2+1),LOW);
  }

//ilk ledi 2.pine tanımlayarak başladığımız için led numarasını 1 arttırarak ilgili ledi yakar ve ardından girilen süre kadar gecikme yaparak ilgili ledi söndürür.
 void ledsureyak(int lednum3,int sure){
  
  digitalWrite((lednum3+1),HIGH);    
   delay(sure);
   digitalWrite((lednum3+1),LOW);
  
  
  } 

//burada karaşimşek görünümünü sağlyan kombinasyonlar yapılarak ilgili görünüm verilir.Bu kombinasyonu daha net algılanabilmesi için for döngüsü ile 5 defa döndürdüm.
    void karasimsek(){
    for(int i=0;i<5;i++){  
    for(int i=2;i<=9;i++){
    
      digitalWrite(i,HIGH);
      delay(35);
      digitalWrite(i+1,HIGH);
      delay(35);
      digitalWrite(i,LOW);       
    }
    
    for(int j=9;j>=2;j--){
    
      digitalWrite(j,HIGH);
      delay(35);
      digitalWrite(j-1,HIGH);
      delay(35);
      digitalWrite(j,LOW);

    }

    }

    

    
 }

//burada sıralıyakma görünümünü sağlyan kombinasyonlar yapılarak ilgili görünüm verilir.Bu kombinasyonu daha net algılanabilmesi için for döngüsü ile 5 defa döndürdüm.
    void siraliyakma(){
      
       for(int k=0;k<5;k++){  
    for(int i=2;i<=9;i++){
    
      digitalWrite(i,HIGH);
      delay(400);       
    }

    delay(1000);
    for(int j=2;j<=9;j++){

      digitalWrite(j,LOW);
       
    }

    delay(400);
    }
      
     
 }


//burada polisçakarı görünümünü sağlyan kombinasyonlar yapılarak ilgili görünüm verilir.Bu kombinasyonu daha net algılanabilmesi için for döngüsü ile 5 defa döndürdüm.
    void poliscakari(){

    for(int k=0;k<5;k++){  

    for(int i=0;i<2;i++){
    for(int i=2;i<=5;i++){
    
      digitalWrite(i,HIGH);
      delay(25);
      digitalWrite(i,LOW);
      delay(25);       
    }
    }
    for(int i=0;i<2;i++){
    for(int i=5;i<=9;i++){
    
      digitalWrite(i,HIGH);
      delay(25);
      digitalWrite(i,LOW);
      delay(25);       
    }
    }
        
    }


  }

  
//tumledleri sondürmeye yarayan fonksiyon 
  void tumledlerisondur(){
    for(int i=2;i<=9;i++)
    digitalWrite(i,LOW);
    }
    
