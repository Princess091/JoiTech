// assign input pins to their respectuve digital pins
const int S0 = 4;
const int S1 = 5;
const int S2 = 6;
const int S3 = 7;
const int signal = 8;

const int buzzPin = 10;

// declare variables
unsigned long red;
unsigned long blue;
unsigned long green;
unsigned long clear;

void setup() { // put your setup code here, to run once:
  // set pin modes
  pinMode(S0,OUTPUT);
  pinMode(S1,OUTPUT);
  pinMode(S2,OUTPUT);
  pinMode(S3,OUTPUT);
  pinMode(signal,INPUT);
  pinMode(buzzPin,OUTPUT);
  
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);

  // initialize serial communication
  Serial.begin(9600);
}

void loop() { // put your main code here, to run repeatedly:
  /* cycle through each filter type and use the pulseIn command to measure pulse length.
  Frequency *increases* with more light, so the pulse length will *decrease*.
  /  S2 S3 | Photodiode Type
     L  L  | Red
     L  H  | Blue
     H  L  | Clear (no filter)
     H  H  | Green
  */
  
  // clear
  digitalWrite(S2,HIGH);
  digitalWrite(S3,LOW);
  clear = pulseIn(signal,HIGH);
  
  // red
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  red = pulseIn(signal,HIGH);

  // green
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  green = pulseIn(signal,HIGH);

  // blue
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  blue = pulseIn(signal,HIGH);

  /* map the red, green, and blue values to a more intuitive 0-100 range where
     0 means less light and 100 means more. This part will require calibration
     depending on your colored surfaces and ambient light levels.
  */
  red = map(red,1720,85,0,100);
  green = map(green,2500,99,0,100);
  blue = map(blue,2100,170,0,100);
    
  // constrain values to 100
  red = constrain(red,0,100);
  green = constrain(green,0,100);
  blue = constrain(blue,0,100);

  // print readings
  Serial.print("Red: ");
  Serial.print(red);
  Serial.print(" | Green: ");
  Serial.print(green);
  Serial.print(" | Blue: ");
  Serial.println(blue);
  
  // add delay
  delay(500);

if(green == 100){  // non-approved green detected
      digitalWrite(buzzPin,HIGH);
      delay(500);
      digitalWrite(buzzPin,LOW);
      delay(500);
      digitalWrite(buzzPin,HIGH);
      delay(500);
      digitalWrite(buzzPin,LOW);
      delay(500);
  }

}
