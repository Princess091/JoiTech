#include <Servo.h>

Servo myServo1;
Servo myServo2;
Servo myServo3;
Servo myServo4;

int servoPin1 = 7;
int servoPin2 = 5;
int servoPin3 = 9;
int servoPin4 = 11;

int VRx = A0;
int VRy = A1;
int VRx1 = A2;
int VRy1 = A3;

int WRx;
int WRy;
int WRx1;
int WRy1;

int Xval;
int Yval;
int Xval1;
int Yval1;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(VRx,INPUT);
pinMode(VRy,INPUT);
pinMode(VRx1,INPUT);
pinMode(VRy1,INPUT);

pinMode(servoPin1,OUTPUT);
pinMode(servoPin2,OUTPUT);
pinMode(servoPin3,OUTPUT);
pinMode(servoPin4,OUTPUT);

myServo1.attach(servoPin1);
myServo2.attach(servoPin2);
myServo3.attach(servoPin3);
myServo4.attach(servoPin4);
}

void loop() {
  // put your main code here, to run repeatedly:
WRx=analogRead(VRx);
WRy=analogRead(VRy);
WRx1=analogRead(VRx1);
WRy1=analogRead(VRy1);

Xval=map(WRx, 0, 1023, 0, 180);
Yval=map(WRy, 0, 1023, 0, 180);
Xval1=map(WRx1, 0, 1023, 0, 180);
Yval1=map(WRy1, 0, 1023, 0, 180);

myServo1.write(Xval);
myServo2.write(Yval);
myServo3.write(Xval1);
myServo4.write(Yval1);

Serial.print("Xval is: ");
Serial.print(Xval);
Serial.print(" Yval is: ");
Serial.println(Yval);
Serial.print("Xval1 is: ");
Serial.print(Xval1);
Serial.print(" Yval1 is: ");
Serial.println(Yval1);

delay(250);
}
