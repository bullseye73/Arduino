/*
 * aarduino nano sample
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <string.h>

// I2C LCD 기본 어드레스는 0x27
LiquidCrystal_I2C lcd(0x27);

 const int ledPin = 13;
 const int inputPin = 2;
 int npre = 0;
 
void setup() {
  // put your setup code here, to run once:
  LCD_init();
  display_text("Hello!");

  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  pinMode(inputPin, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  	int val = digitalRead(inputPin);
  	char buff[16] = {0,};
  	sprintf(buff, "%d, %d", val, npre);
  	//Serial.parseInt();
	Serial.println(buff);

  if(val == HIGH){
  	if(val != npre){
  		display_text("LED ON!");
  	    npre = val;
  	}
    digitalWrite(ledPin, HIGH);
  }
  else {
  	if(val != npre){
	  	display_text("LED OFF!");
  		npre = val;
  	}
  	digitalWrite(ledPin, LOW);
  }

  

  delay(100);
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
