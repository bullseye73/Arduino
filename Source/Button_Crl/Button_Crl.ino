
/*

 
*/ 
 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <string.h>
 
// I2C LCD 기본 어드레스는 0x27
LiquidCrystal_I2C lcd(0x27);

const int buttonPin = 2;
int buttonState = 0;

// 프로그램 시작 - 초기화 작업
void setup()
{
  LCD_init();

//  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  pinMode(buttonPin, INPUT);
}
 
// 계속 실행할 무한 루프
void loop()
{
  display_text("Hello", "Arduino");
  buttonState = digitalRead(buttonPin);

  Serial.println(buttonState);
  if (buttonState == HIGH) {
    lcd.setBacklight(HIGH);
  } else {
    lcd.setBacklight(LOW);
  }

  if (Serial.available())
  {
    //Serial.write(Serial.read());
    lcd.write(Serial.read());
  }

  delay(1000);
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

void display_text(String strRow1, String strRow2){
  lcd.setCursor(0,0);
  lcd.print(strRow1);
  lcd.setCursor(0,1);
  lcd.print("                 ");
  //lcd.clear();
  lcd.setCursor(0,1);
  lcd.print(strRow2);
  //delay(1000);
  //lcd.setBacklight(LOW);
  //delay(1000);
}

