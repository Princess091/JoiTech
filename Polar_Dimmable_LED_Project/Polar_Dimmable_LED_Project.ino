int potPin = A0;
int ledPin = 2;
int ledPin2 = 3;
int potVal;
float ledVal;
float ledVal2;
  
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(potPin,INPUT);
pinMode(ledPin,OUTPUT);
pinMode(ledPin2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
potVal=analogRead(potPin);
ledVal=(255./1023.)*potVal;
ledVal2=(-(255./1023))*potVal;
analogWrite(ledPin,ledVal);
analogWrite(ledPin2,ledVal2);
Serial.println(ledVal);
Serial.println(potVal);
Serial.println(ledVal2);   
}
