#define motor 8                                                                       //--------------------------//
#define reset 11                                                                      //GİRİŞ ÇIKIŞLAR AYARLANIYOR//
#define led 12                                                                        //                          //
#define data 13                                                                       //--------------------------//

int sensorDigit = 0, sensorDurum = 0, paraSayac = 0, bosta = 0,                       //DEĞİŞKENLER TANIMLANIYOR VE DEĞER ATANIYOR//
para = 0, paraDurum = 0, butonDurum = 0, butonSayac = 0;                              //------------------------------------------//
                                                                  
int buton, giris, sensor;                                                             //DEĞİŞKENLER ATANIYOR//
void setup() {//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
   Serial.begin(9600);                                                             //SERİ EKRAN KULLANILACAĞI ZAMAN AKTİF EDİLMESİ GEREK!!!//                                                        //
                                                                                                                                                                                                        //
  pinMode(motor, OUTPUT);                                                             //---------------------------------//                                                                             //
  pinMode(led, OUTPUT);                                                               //GPIO'LARIN I/O DURUMU AYARLANIYOR//                                                                             //
  pinMode(reset, INPUT);                                                              //                                 //                                                                             //
  pinMode(data, INPUT);                                                               //---------------------------------//                                                                             //
                                                                                                                                                                                                        //
  digitalWrite(motor,1);                                                              //BAŞLANGIÇ İÇİN HER İHTİMALE KARŞI MOTOR DURDURULUP//                                                            //
  digitalWrite(led,0);                                                                //LED SÖNDÜRÜLÜYOR----------------------------------//                                                            //
}                                                                                                                                                                                                       //
                                                                                                                                                                                                        //
void loop() {//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
  buton = digitalRead(reset);                                                         //OKUNMASI GEREKEN DEĞERLER OKUNUYOR//
  giris = digitalRead(data);                                                          //                                  //
  sensor = analogRead(A0);                                                            //----------------------------------//
  
  if (giris != paraDurum && giris == 1){                                              //BILL ACCEPTOR'DAN PARA OKUNUYOR//
    para = para+5;                                                                    //                               //
  }                                                                                   //                               //
  paraDurum = giris;                                                                  //                               //
  delay(25);                                                                          //-------------------------------//
                                                                                      //------------------------------------------------------------------------------------------//
  if (para > 0){                                                                      //BU KISIM PARA GİRER GİRMEZ DEVREYE GİRİYOR VE SIRASI İLE                                  //
                                                                                      //                                                                                          //
    if (sensor < 990){                                                                //SENSOR OKUNUP EĞER 990'DAN KÜÇÜKSE                                                        //
     sensorDigit = 1;                                                                 //1 OLARAK AYARLANIYOR                                                                      //
    }                                                                                 //                                                                                          //
    else{                                                                             //DEĞİLSE 0 OLARAK AYARLANIYOR                                                              //
      sensorDigit = 0;                                                                //                                                                                          //
    }                                                                                 //                                                                                          //
                                                                                      //                                                                                          //
    if (giris == paraDurum && giris == 0){                                            //"giriş" "paraDurum"'a eşitse ve "giriş" 0 ise                                             //
       digitalWrite (led, 1);                                                         //ledi yak                                                                                  //
                                                                                      //                                                                                          //
      if (buton != butonDurum && buton == 1){                                         //"buton" "butonDurum"'dan farklı ise ve "buton" 1 ise                                      //
        butonSayac = 1;                                                               //"butonSayac"'ı 1 yap                                                                      //
        digitalWrite (motor, 0);                                                      //motoru sür                                                                                //
        }                                                                             //                                                                                          //
        butonDurum = buton;                                                           //"butonDurum"'u "buton"'a eşitle                                                           //
        if (sensorDigit != sensorDurum && sensorDigit == 1 && butonSayac == 1){       //"sensorDigit" "sensurDurum"'a eşit değilse ve "sensorDigit" 1 ise ve "butonSayac 1 ise    //
            paraSayac = paraSayac+1;                                                  //"paraSayac"'ı 1 artır                                                                     //
                                                                                      //                                                                                          //
          if (paraSayac < para){                                                      //"paraSayac" "para"'dan küçükse                                                            //
            digitalWrite(motor, 0);                                                   //motoru sürdür                                                                             //
            }                                                                         //                                                                                          //
          else if (paraSayac == para || paraSayac > para){                            //eğer değil de  "paraSayac" "para"'ya eşitse veya "paraSayac" "para"'dan büyükse           //
            digitalWrite(motor, 1);                                                   //motoru durdur                                                                             //
            para = 0;                                                                 //"para" değişkenini 0'la                                                                   //
            paraSayac = 0;                                                            //"paraSayac" değişkenini 0'la                                                              //
            butonSayac = 0;                                                           //"butonSayac"'değişkenini 0'la                                                             //
            digitalWrite(led, 0);                                                     //ledi söndür                                                                               //
            }                                                                         //                                                                                          //
          }                                                                           //                                                                                          //
          sensorDurum = sensorDigit;                                                  //"sensorDurum"'u "sensorDigit"'e eşitle                                                    //
    }                                                                                 //------------------------------------------------------------------------------------------//
    
      Serial.println("");                                                           //-------------------------------------------------------------------//
      Serial.print("para= ");                                                       //                                                                   //
      Serial.println(para);                                                         //                                                                   //  
    //  Serial.print("sensorDigit= ");                                                //                                                                   //
    //  Serial.println(sensorDigit);                                                  //                                                                   //
    //  Serial.print("sensorDurum= ");                                                //BU KISIM BELİRTİLEN DURUMLAR BİLGİSAYARDA SERİ EKRANDA GÖSTERİLMEK //
    //  Serial.println(sensorDurum);                                                  //İSTEDİĞİ ZAMAN YUKARIDAKİ "Serial.begin(9600);" KISMI İLE BERABER  //
    //  Serial.print("paraSayac= ");                                                  //AKTİF EDİLMESİ GEREKMEKTEDİR!!!                                    //
    //  Serial.println(paraSayac);                                                    //                                                                   //
    //  Serial.print("buton= ");                                                      //                                                                   //
    //  Serial.println(buton);                                                        //                                                                   //
    //  Serial.print("butonsayac= ");                                                 //                                                                   //
    //  Serial.println(butonSayac);                                                   //-------------------------------------------------------------------//
    }
      Serial.println("");                                                           //-------------------------------------------------------------------//
      Serial.print("para= ");                                                       //                                                                   //
      Serial.println(para);                                                         //                                                                   //  
    
  }
