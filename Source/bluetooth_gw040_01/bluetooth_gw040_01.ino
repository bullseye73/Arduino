#include <SoftwareSerial.h>
SoftwareSerial BTSerial(4, 5); // RX | TX


char c = ' ';
boolean NL = true;

void setup() 
{
      Serial.begin(9600);
      Serial.println("Sketch HC-0x_FC-114_01_9600");
      Serial.println("Arduino with HC-0x FC-114 is ready");
      Serial.println("Make sure Both NL & CR are set");
      Serial.println("");
      
      // FC-114 default baud rate is 38400
      BTSerial.begin(38400);  
      Serial.println("BTserial started at 38400");
      Serial.println("");
      
}

void loop()
{

    // Read from the Bluetooth module and send to the Arduino Serial Monitor
    if (BTSerial.available())
    {
        c = BTSerial.read();
        Serial.write(c);
    }
    
      
  
    // Read from the Serial Monitor and send to the Bluetooth module
    if (Serial.available())
    {
        c = Serial.read();
        BTSerial.write(c);   
        
        // Echo the user input to the main window. The ">" character indicates the user entered text.
        if (NL) { Serial.print(">");  NL = false; }
        Serial.write(c);
        if (c==10) { NL = true; }
    }

}
