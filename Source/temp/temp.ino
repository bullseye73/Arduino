/*
 * Temp sample
 */
// 프로그램 시작 - 초기화 작업
#include <DHT11.h>    //라이브러리 불러옴

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <string.h>
 
// I2C LCD 기본 어드레스는 0x27
LiquidCrystal_I2C lcd(0x27);


int pin=A5;            //Signal 이 연결된 아두이노의 핀번호
DHT11 dht11(pin);        
void setup()
{
   Serial.begin(115200); //통신속도 설정
   LCD_init();
}
 
void loop()
{
  int err;
  float temp, humi;
  if((err=dht11.read(humi, temp))==0) //온도, 습도 읽어와서 표시
  {
    char strBuf[13] = {0,};
    sprintf(strBuf, "temp: %d02, %d %%", temp, humi);

    Serial.println(strBuf);
    display_text(strBuf);
    /*
    Serial.print("temperature:");
    Serial.print(temp);
    Serial.print(" humidity:");
    Serial.print(humi);
    Serial.println();
    */
  }
  else                                //에러일 경우 처리
  {
    Serial.println();
    Serial.print("Error No :");
    Serial.print(err);
    Serial.println();    
  }
  delay(1000);                        //1초마다 측정
}

 // I2C address 찾기
byte GetAddress()
{
     Wire.begin();
   for (byte i = 1; i < 120; i++)
   {
     Wire.beginTransmission(i);
     if (Wire.endTransmission() == 0)
     {
       Serial.print("Found address: ");
       Serial.print(i, DEC);
       Serial.print(" (0x");
       Serial.print(i, HEX);
       Serial.println(")");
       return i;
       delay(10);
     }
   }
}

void LCD_init(){
  // 자동으로 I2C address 설정
  lcd = LiquidCrystal_I2C(GetAddress());
 
  // I2C LCD 모듈은 여러 종류인데 이 실험에서는 1을 사용
  lcd.setBoardType(1);
  lcd.begin (16,2); // 16 x 2
  lcd.setBacklight(HIGH);
  
}

void display_text(String msg){
  lcd.setCursor(0,0);
  lcd.print("Hi! Hello");
  lcd.setCursor(0,1);
  lcd.print("                 ");
  //lcd.clear();
  lcd.setCursor(0,1);
  lcd.print(msg);
  //delay(1000);
  //lcd.setBacklight(LOW);
  //delay(1000);
}
