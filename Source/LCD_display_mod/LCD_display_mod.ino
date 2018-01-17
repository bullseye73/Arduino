
/*
 I2C LCD TEST
 LCD 에 텍스트 출력하고 1초마다 백라이트를 ON/OFF 하는 예제
 
 출처: http://whiteat.com/Arduino
 
 부품
 . Arduino UNO R3 : http://kit128.com/goods/view?no=71
 . I2C LCD : http://kit128.com/goods/view?no=80 
 
 연결
 Arduino UNO R3 I2C LCD
 -------------------------------------------------
 SCL I2C SCL
 SDA I2C SDA
 
*/ 
 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <string.h>

// I2C LCD 기본 어드레스는 0x27
LiquidCrystal_I2C lcd(0x27);

// 프로그램 시작 - 초기화 작업
void setup()
{
  LCD_init();
  display_text("Hello!");
  Serial.begin(115200);
  Serial.println("Initializing");
}
 
// 계속 실행할 무한 루프
void loop()
{
  
  delay(500);
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

void display_text(double dTall){
  lcd.setCursor(0,0);
  lcd.print("Hi! Hello");
  lcd.setCursor(0,1);
  lcd.print("                 ");
  //lcd.clear();
  lcd.setCursor(0,1);
  lcd.print(dTall,1);
  lcd.setCursor(5, 1);
  lcd.print("cm");
  //delay(1000);
  //lcd.setBacklight(LOW);
  //delay(1000);
}

void display_text(String msg){
  lcd.setCursor(0,0);
  lcd.print("Hi! Arduino!");
  lcd.setCursor(0,1);
  lcd.print("                 ");
  //lcd.clear();
  lcd.setCursor(0,1);
  lcd.print(msg);
  //delay(1000);
  //lcd.setBacklight(LOW);
  //delay(1000);
}

/*
void setup() {
  Serial.begin (115200);
 
  while (!Serial)
    {
    }
 
  Serial.println ();
  Serial.println ("I2C scanner. Scanning ...");
  byte count = 0;
 
  Wire.begin();
  for (byte i = 1; i < 120; i++)
  {
    Wire.beginTransmission (i);
    if (Wire.endTransmission () == 0)
      {
      Serial.print ("Found address: ");
      Serial.print (i, DEC);
      Serial.print (" (0x");
      Serial.print (i, HEX);
      Serial.println (")");
      count++;
      delay (10);  // maybe unneeded?
      } // end of good response
  } // end of for loop
  Serial.println ("Done.");
  Serial.print ("Found ");
  Serial.print (count, DEC);
  Serial.println (" device(s).");
}  // end of setup
 
void loop() {}
*/
