#include <SoftwareSerial.h> //serial lib
#include <DHT11.h>    // temperature lib

#define TEST_FLG 1

#define BT_TX 4
#define BT_RX 5
#define PIN_TEMP 2

SoftwareSerial BTSerial(BT_TX, BT_RX); // ㅅTX | RX
DHT11 dht11(PIN_TEMP);  

const int LEDPIN = A0;

void setup() 
{
#if TEST_FLG
      Serial.begin(9600);
      Serial.println("Sketch HC-0x_FC-114_01_9600");
      Serial.println("Arduino with HC-0x FC-114 is ready");
      Serial.println("Make sure Both NL & CR are set");
      Serial.println("");
#endif      
      // FC-114 default baud rate is 38400
      BTSerial.begin(9600);
      pinMode(LEDPIN, OUTPUT);
            
#if TEST_FLG      
     // BTSerial.getUUID();  
      Serial.println("BTserial started at 38400");
      Serial.println(">");
#endif
      
      
}

void loop()
{
  float fRet = 0;
  char strBuf[6]="";
  
  if (BTSerial.available()){ // if BT sends something
    
    char data = BTSerial.read();
    Serial.println(data);

    switch (data){
        case '1':                                   // 받은 데이터가 A라면
          digitalWrite(LEDPIN, HIGH);        // 해당 상태로 red led를 전환합니다.
          break;
        case '0':                                   // 받은 데이터가 A라면
          digitalWrite(LEDPIN, LOW);        // 해당 상태로 red led를 전환합니다.
          break;
        default: 
          digitalWrite(LEDPIN, LOW);
          break;
    }

  } else {
    //Serial.println("BTserial disavailable!");
  }

  fRet = localtemp();
 
  if (fRet > 0){
    dtostrf(fRet,5,2,strBuf);
    BTSerial.write(strBuf);
  }
  delay(1000);
}

float localtemp(){
    int err;
    float temp, humi;
    
    if((err=dht11.read(humi, temp))==0) //온도, 습도 읽어와서 표시
    {
      Serial.print("temperature:");
      Serial.println(temp);
      return temp;
    }
    else                                //에러일 경우 처리
    {
      Serial.print("Error No :");
      Serial.println(err);
    }
    return (float)err;
}

