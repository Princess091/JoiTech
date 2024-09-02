#include <VirtualWire.h>
#include <AFMotor.h>

const int receive_pin = 11;

AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ); 
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

//int motorSpeedA = 0;
//int motorSpeedB = 0;

int data[2];

int a;

//int xValue;
//int yValue;

void setup() {
  Serial.begin(9600);
  vw_set_rx_pin(receive_pin);
  vw_setup(2000);
  vw_rx_start();
}

void loop() {
  delay(5);

  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  
   if(vw_get_message(buf, &buflen)){
    Serial.println("We're Ready!");
  
  for (int i = 0; i < buflen; i++){
    Serial.println(int(buf[i]));
    if(int(buf[i]) != 0){
      a =int(buf[i]);
    }
  }
    delay(10);

    if(a == 1){
      move_left();
    }
    else if(a == 2){
      move_right();
    }
    else if(a == 3){
      move_backward();
    }
    else if(a == 4){
      move_forward();
    }
    else{
      move_stop();
    }
  }
 }

 void move_forward(){
  motor1.setSpeed(255);
  motor1.run(FORWARD);
  motor2.setSpeed(255);
  motor2.run(FORWARD);
  motor3.setSpeed(255);
  motor3.run(FORWARD);
  motor4.setSpeed(255);
  motor4.run(FORWARD);
  delay(100);
}

 void move_stop(){
  motor1.setSpeed(RELEASE);
  motor2.setSpeed(RELEASE);
  motor3.setSpeed(RELEASE);
  motor4.setSpeed(RELEASE);
  delay(20);
  }

 void move_backward(){
  motor1.setSpeed(255);
  motor1.run(BACKWARD);
  motor2.setSpeed(255);
  motor2.run(BACKWARD);
  motor3.setSpeed(255);
  motor3.run(BACKWARD);
  motor4.setSpeed(255);
  motor4.run(BACKWARD);
  delay(20);
 }
  
 void move_right(){
//    motorSpeedA=xValue+yValue;
//    motorSpeedB=abs(xValue-yValue);
    
    motor1.setSpeed(255);
    motor1.run(FORWARD);
    motor2.setSpeed(255);
    motor2.run(FORWARD);
    motor3.setSpeed(155);
    motor3.run(BACKWARD);
    motor4.setSpeed(155);
    motor4.run(BACKWARD);
    delay(20);
 }

 void move_left(){
//    motorSpeedA=abs(xValue-yValue);
//    motorSpeedB=xValue+yValue;
    
    motor1.setSpeed(155);
    motor1.run(BACKWARD);
    motor2.setSpeed(155);
    motor2.run(BACKWARD);
    motor3.setSpeed(255);
    motor3.run(FORWARD);
    motor4.setSpeed(255);
    motor4.run(FORWARD);
    delay(20);
 }
  
