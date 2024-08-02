#include <LiquidCrystal.h>
int rs = 2;
int en = 3;
int d4 = 4;
int d5 = 5;
int d6 = 6;
int d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int trigPin1 = 9;
int echoPin1 = 10;
int trigPin2 = 12;
int echoPin2 = 13;

int buzzPin = 11;

int pingTravelTime1;
int pingTravelTime2;

String msg1 = "Dst.1= ";
String msg2 = "Dst.2= ";

int distance1;
int distance2;

int dt = 50;

void setup() {
  // put your setup code here, to run once:
lcd.begin(16,2);
pinMode(buzzPin,OUTPUT);
pinMode(trigPin1,OUTPUT);
pinMode(echoPin1,INPUT);
pinMode(trigPin2,OUTPUT);
pinMode(echoPin2,INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(trigPin1,LOW);
delayMicroseconds(10);
digitalWrite(trigPin1,HIGH);
delayMicroseconds(10);
digitalWrite(trigPin1,LOW);
pingTravelTime1=pulseIn(echoPin1,HIGH);
distance1=(0.5*pingTravelTime1*0.034);

digitalWrite(trigPin2,LOW);
delayMicroseconds(10);
digitalWrite(trigPin2,HIGH);
delayMicroseconds(10);
digitalWrite(trigPin2,LOW);
pingTravelTime2=pulseIn(echoPin2,HIGH);
distance2=(0.5*pingTravelTime2*0.034);

        if (pingTravelTime1<=1000){
          lcd.clear();
          
          Serial.println("");
          Serial.println("COLLISION AT LEFT SENSOR!");
          Serial.println("");

          Serial.print("Distance1 = ");
          Serial.print(distance1); 
          Serial.print("cm");
          Serial.println("");
          
          lcd.setCursor(0,0);
          lcd.print("LEFT SENSOR!");
          
          digitalWrite(buzzPin,HIGH);
          delay(dt);
          digitalWrite(buzzPin,LOW);
          delay(dt);
          digitalWrite(buzzPin,HIGH);
          delay(dt);
          digitalWrite(buzzPin,LOW);
          delay(dt);

          lcd.clear();

        }
        
            else {
              Serial.print("Distance1 = ");
              Serial.print(distance1); 
              Serial.print("cm");
              Serial.println("");

              lcd.setCursor(0,0);
              lcd.print("Dst.1= ");
              lcd.print(distance1);
              lcd.print(" cm");          
              digitalWrite(buzzPin,LOW);

            }

    if (pingTravelTime2<=1000){
      lcd.clear();
      
      Serial.println("");
      Serial.println("COLLISION AT RIGHT SENSOR!");
      Serial.println("");

      Serial.print("Distance2 = ");
      Serial.print(distance2); 
      Serial.print("cm");
      Serial.println("");

      lcd.setCursor(0,1);
      lcd.print("RIGHT SENSOR!");
      
      digitalWrite(buzzPin,HIGH);
      delay(dt);
      digitalWrite(buzzPin,LOW);
      delay(dt);
      digitalWrite(buzzPin,HIGH);
      delay(dt);
      digitalWrite(buzzPin,LOW);
      delay(dt);

      lcd.clear();
   
    }
    
        else {
          Serial.print("Distance2 = ");
          Serial.print(distance2);
          Serial.print("cm");
          Serial.println("");

          lcd.setCursor(0,1);
          lcd.print("Dst.2= ");
          lcd.print(distance2);          
          lcd.print(" cm");          
          digitalWrite(buzzPin,LOW);

        }

  }
