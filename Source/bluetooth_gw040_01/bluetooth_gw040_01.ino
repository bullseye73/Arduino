#include <SoftwareSerial.h>
#include <stdlib.h>

#define TEST_FLG 1
#define BUFF_SIZE 256

SoftwareSerial BTSerial(4, 5); // ㅅTX | RX

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

  delay(100);
/*        
      switch (BluetoothData){
        case '1':                                   // 받은 데이터가 A라면
          digitalWrite(LEDPIN, HIGH);        // 해당 상태로 red led를 전환합니다.
          break;
        default: 
          digitalWrite(LEDPIN, LOW);
          break;
      }
    }
    else {
      //Serial.println("BTserial disavailable!");
    }
    delay(100);
    */
}
