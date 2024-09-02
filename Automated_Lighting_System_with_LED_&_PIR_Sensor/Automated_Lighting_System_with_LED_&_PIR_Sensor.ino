const int pirSensor = 7;   // the pin that OUTPUT pin of sensor is connected to
int relay = 4;
int pinStateCurrent; // current state of pin
int pinStatePrevious; // previous state of pin

int dt = 500;

void setup() {
  Serial.begin(9600);            // initialize serial
  pinMode(pirSensor, INPUT); // set arduino pin to input mode to read value from OUTPUT pin of sensor
  pinMode(relay,OUTPUT);
}

void loop() {
  pinStatePrevious = pinStateCurrent; // store old state
  pinStateCurrent = digitalRead(pirSensor);   // read new state

  if (pinStatePrevious == LOW && pinStateCurrent == HIGH) {   // pin state change: LOW -> HIGH
    Serial.println("Motion detected!");
    
    digitalWrite(relay,HIGH);
    delay(dt);
   
    // TODO: turn on alarm,  light or activate a device ... here
  }
  else 
  if (pinStatePrevious == HIGH && pinStateCurrent == LOW){   // pin state change: HIGH -> LOW
    Serial.println("Motion stopped!");
    
    digitalWrite(relay,LOW);
    delay(dt);

    // TODO: turn off alarm, light or deactivate a device ... here
  }
}
