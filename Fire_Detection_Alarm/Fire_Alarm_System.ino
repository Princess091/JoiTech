#include <LiquidCrystal.h>
int rs = 7;
int en = 8;
int d4 = 9;
int d5 = 10;
int d6 = 11;
int d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int flamePin = 4;
int buzzPin = 3;
int flameVal;
int dt = 250;
int dt2 = 25; 

void setup() {
  // put your setup code here, to run once:
lcd.begin(16,2);
Serial.begin(9600);
pinMode(flamePin,INPUT);
pinMode(buzzPin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
flameVal=digitalRead(flamePin);
Serial.println(flameVal);

if (flameVal == 0){
  lcd.setCursor(0,0);
  lcd.print("FIRE!");
  delay(dt);
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("FIRE!");
  delay(dt);
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("FIRE!");
  delay(dt);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("FIRE!");
  
  digitalWrite(buzzPin,HIGH);
  delay(dt);
  digitalWrite(buzzPin,LOW);
  delay(dt2);
  digitalWrite(buzzPin,HIGH);
  delay(dt);
  digitalWrite(buzzPin,LOW);
  delay(dt2);
}

if (flameVal == 1){
  lcd.setCursor(0,0);
  lcd.print("We're safe");
  digitalWrite(buzzPin,LOW);
  delay(500);
}
  lcd.clear();
  
}
