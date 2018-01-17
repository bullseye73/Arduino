int r=0, g=0, b=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(4) == HIGH){
    ++r;
    if (r > 255) {
      r = 0;    
    }
  }

  if (digitalRead(3) == HIGH){
    ++g;
    if (g > 255) {
      g = 0;    
    }
  }

  if (digitalRead(2) == HIGH){
    Serial.println("BBBBBBBBBBBBB\n");
    ++b;
    if (b > 255) {
      b = 0;    
    }
  }

  analogWrite(11, g);
  analogWrite(10, r);
  analogWrite(9, b);

  delay(10);
}
