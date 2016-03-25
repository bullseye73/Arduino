
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

/* 센서 추가 */
#define trigPin 2 // Trigger Pin
#define echoPin 3 // Echo Pin
 
#define maximumRange   500  // 최대 거리(Cm)
#define minimumRange   2 // 최소 거리(Cm)



// 프로그램 시작 - 초기화 작업
void setup()
{
  LCD_init();
  sensor_init();
}
 
// 계속 실행할 무한 루프
void loop()
{
  char buff[13] = {0,};
  double dHeight=0;

  dHeight = calc_height();

  if (dHeight >= maximumRange || dHeight <= minimumRange)
  {
    strcpy(buff, "out of range");
    Serial.println(buff);

    display_text(buff);
  }
  else 
  {
    Serial.println(dHeight);
    //sprintf(buff, "%s cm", d2str(dHeight));
    display_text(dHeight);  
  }
  
  
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

void sensor_init()
{
  /* 센서 추가 */
  Serial.begin(115200);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin, INPUT);
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
double calc_height(){
  long duration = 0; // 펄스 시간, 
  double distance; //거리 측정용 변수

  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
   
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
   
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
   
  // 측정된 시간을 mm으로 환산.
  distance = mmDistance(duration);
  
  return distance;
}

double mmDistance(long time) {
  // Calculates the Distance in mm
  // ((time)*(Speed of sound))/ toward and backward of object) * 10

  double DistanceCalc; // Calculation variable
  DistanceCalc = ((double)(time / 2.9) /(double) 2)/(double)10;    // Actual calculation in mm
   //DistanceCalc = (int)( time / 58.2);        // Actual calculation in Cm
  // DistanceCalc = time / 74 / 2;      // Actual calculation in inches
  
  return DistanceCalc; // return calculated value

}
