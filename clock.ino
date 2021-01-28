//piny od 2 do 7 są z lcd, pin 11 z IRremote

#include<LiquidCrystal.h>
#include<DS3231.h>
#include "DHT.h"
#define DHT11_PIN 12
LiquidCrystal lcd(2,3,4,5,6,7);
DS3231 rtc(SDA, SCL);
DHT dht;

int przestepne[12]={31,29,31,30,31,30,31,31,30,31,30,31};
int nieprzestepne[12]={31,28,31,30,31,30,31,31,30,31,30,31};
void setup() {
  
  //Serial.begin(9600);
//  pinMode(A1, OUTPUT);
//  pinMode(A2, OUTPUT);
//  pinMode(A3, OUTPUT);
//  pinMode(A4, OUTPUT);
  pinMode(11, INPUT_PULLUP);
  pinMode(A0, OUTPUT);
  pinMode(13, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  dht.setup(DHT11_PIN);
  rtc.begin();
  rtc.setTime(18,15,0);
  rtc.setDate(28,2,2020);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Witaj w zegarku!");
  delay(3000);
  
}

int menu=0;
int godzina=0;
int minuty=0;
String budzik="--.--";
String sgodz="";
String sminu="";
bool flaga_budzika=false;
bool jasnosc=false;
int ustawgodz=0;
int ustawmin=0;
int rok=2000;
int miesiac=1;
int dzien=1;

void loop(){
  lcd.clear();
  lcd.setCursor(0,0);
  if (menu==0){
    rok=2000;
    miesiac=1;
    dzien=1;
    rok=2000;
    miesiac=1;
    dzien=1;
    ustawgodz=0;
    ustawmin=0;
    godzina=0;
    minuty=0;
    lcd.print("data: ");
    lcd.print(data());
    lcd.setCursor(0,1);
    lcd.print("godz: ");
    lcd.print(godz());
    czy_budzik(flaga_budzika);
    delay(200);
  }
  
  else if (menu==1){
    
    lcd.print("Ustaw budzik ");
    lcd.setCursor(0,1);
    //lcd.print(budzik);
    if(godzina<10){
      lcd.print("0"+String(godzina));
      sgodz="0"+String(godzina);
    }
    else{
      lcd.print(godzina);
      sgodz=String(godzina);
    }
    lcd.print(":");
    if(minuty<10){
      lcd.print("0"+String(minuty));
      sminu="0"+String(minuty);
    }
    else{
      lcd.print(minuty);
      sminu=String(minuty);
    }

    if(digitalRead(8)==LOW){
      if(godzina==23){
        godzina=0;
      }
      else{
        godzina+=1;
      }
    }

    if(digitalRead(9)==LOW){
      if(minuty==59){
        minuty=0;
      }
      else{
      minuty+=1;
      }
    }

    if((digitalRead(11)==LOW)&&(flaga_budzika==false)){
      budzik=sgodz+":"+sminu+":00";
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("budzik na: ");
      lcd.setCursor(0,1);
      lcd.print(budzik);
      menu=0;
      flaga_budzika=true;
      delay(3000);
    }
    
    if((digitalRead(11)==LOW)&&(flaga_budzika==true)){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("budzik");
      lcd.setCursor(0,1);
      lcd.print("usuniety");
      budzik="--.--";
      flaga_budzika=false;
      delay(3000);
    }
    if(digitalRead(10)==LOW){
      lcd.setCursor(0,0);
      lcd.print("ustawiony na");
      lcd.setCursor(0,1);
      lcd.print(budzik);
      delay(2000);
    }
    czy_budzik(flaga_budzika);
    delay(200);
  }

    else if(menu==2){
    godzina=0;
    minuty=0;
    lcd.print("Ustaw godzine");
    lcd.setCursor(0,1);
    if(ustawgodz<10){
      lcd.print("0"+String(ustawgodz));
      sgodz="0"+String(ustawgodz);
    }
    else{
      lcd.print(ustawgodz);
      sgodz=String(ustawgodz);
    }
    lcd.print(":");
    if(ustawmin<10){
      lcd.print("0"+String(ustawmin));
      sminu="0"+String(ustawmin);
    }
    else{
      lcd.print(ustawmin);
      sminu=String(ustawmin);
    }

    if(digitalRead(8)==LOW){
      if(ustawgodz==23){
        ustawgodz=0;
      }
      else{
        ustawgodz+=1;
      }
    }

    if(digitalRead(9)==LOW){
      if(ustawmin==59){
        ustawmin=0;
      }
      else{
      ustawmin+=1;
      }
    }
    czy_budzik(flaga_budzika);
    if(digitalRead(11)==LOW){
      rtc.setTime(ustawgodz, ustawmin, 0);
      lcd.setCursor(0,0);
      lcd.print("godz. ustawiona");
      lcd.setCursor(0,1);
      lcd.print("milego dnia");
      ustawgodz=0;
      ustawmin=0;
      menu=0;
      delay(3000);
      
    }
    delay(200);
    
  }

  else if(menu==3){
    ustawgodz=0;
    ustawmin=0;
    lcd.print("Ustaw date");
    lcd.setCursor(0,1);
    if(dzien<10){
      lcd.print("0"+String(dzien));
    }
    else{
      lcd.print(dzien);
    }
    if(miesiac<10){
      lcd.print(".0"+String(miesiac));
    }
    else{
      lcd.print("."+String(miesiac));
    }
    lcd.print("."+String(rok));
    czy_budzik(flaga_budzika);
    if(digitalRead(8)==LOW){
      if(przestepny(rok)==true){
        if(dzien==przestepne[miesiac-1]){
          dzien=0;
        }
        else{
          dzien++;
        }
      }
      else{
        if(dzien==nieprzestepne[miesiac-1]){
          dzien=1;
        }
        else{
          dzien++;
        }
      }
    }
    if(digitalRead(9)==LOW){
      if(miesiac==12){
        miesiac=1;
      }
      else{
        miesiac++;
      }
    }
    if (digitalRead(10)==LOW){
      if(rok==2100){
        rok=2000;
      }
      else{
        rok++;
        if((przestepny(rok)==false) && (dzien>nieprzestepne[miesiac-1])){
          dzien=dzien-1;
        }
      }
    }
    if(digitalRead(11)==LOW){
      rtc.setDate(dzien, miesiac, rok);
      lcd.setCursor(0,0);
      lcd.print("Data ustawiona");
      lcd.setCursor(0, 1);
      lcd.print("milego dnia");
      menu=0;
      delay(3000);
    }
    delay(200);
  }
  ////////
  else if (menu==4){
    rok=2000;
    miesiac=1;
    dzien=1;
    lcd.print("Temp: ");
    lcd.print(temp()+String(" C"));
    lcd.setCursor(0,1);
    lcd.print("Wilg: ");
    lcd.print(wilg()+String(" %RH"));
    czy_budzik(flaga_budzika);
    delay(1500);
  }
//////////
  
  if(godz()==budzik){
    while(digitalRead(11)==HIGH){
      digitalWrite(A0, HIGH);
      budzik="--.--";
      flaga_budzika=false;
    }
      digitalWrite(A0, LOW);
  }
  
  if(digitalRead(13)==LOW){
    if(menu==4){
      menu=0;
      muzyczka();
    }
    else{
      menu++;
    }
  }

//  int y=map(analogRead(A0), 0, 1023, 0, 255);
//  analogWrite(A1, y);
//  analogWrite(A2, y);
//  analogWrite(A3, y);
//  analogWrite(A4, y);

}

bool przestepny(int rok){
  if((rok%4==0 && rok%100!=0) || rok%400==0){
    return true;
  }
  return false;
}
void czy_budzik(bool flaga_budzika){
  if(flaga_budzika==true){
    lcd.setCursor(15,1);
    lcd.print("V");
  }
  else if(flaga_budzika==false){
    lcd.setCursor(15, 1);
    lcd.print("X");
  }
}
int temp(){
  return dht.getTemperature();
}
int wilg(){
  return dht.getHumidity();
}
String godz(){
  return rtc.getTimeStr();
}
String data(){
  return rtc.getDateStr();
}

void muzyczka(){
  tone(A0, 2000);
  delay(1000);
  noTone(A0);
}
