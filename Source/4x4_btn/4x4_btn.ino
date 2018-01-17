#define pulse 8
#define data 9

int old  = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(pulse, OUTPUT);  
  pinMode(data, INPUT); 
}

void loop()
{
  int Key = getkey();
  
  if (Key!=0&Key!=old)
    Serial.println(Key);
  old = Key;
    
}


byte getkey(void)
{
  byte cnt;
  byte num = 0;
  for(cnt = 1; cnt < 17; cnt++)
  {
    digitalWrite(pulse, LOW); 
    
    if (digitalRead(data) == 0)
      num = cnt; 
    
    digitalWrite(pulse, HIGH);
  }  
  
  return num; 
}
