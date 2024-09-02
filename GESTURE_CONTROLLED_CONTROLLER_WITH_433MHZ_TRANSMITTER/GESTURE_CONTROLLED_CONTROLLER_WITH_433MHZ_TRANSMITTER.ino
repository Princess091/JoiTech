#include <VirtualWire.h>
#include <Wire.h>

const int MPU = 0x68; // MPU6050 I2C address
float accRawX, accRawY, accRawZ;
float accErrorX, accErrorY;
float AccX, AccY, AccZ;
float accAngleX, accAngleY;
float elapsedTime, currentTime, previousTime;

const int transmit_pin = 12;

int i;

//int xValue;
//int yValue;

// Define thresholds for different directions
const int directionThreshold1 = 15; // Example threshold for direction 1
const int directionThreshold2 = 30; // Example threshold for direction 2
const int directionThreshold3 = 45; // Example threshold for direction 3
const int directionThreshold4 = 60; // Example threshold for direction 4

void setup() {
  Serial.begin(9600);
  vw_set_tx_pin(transmit_pin);
  vw_setup(2000);

  Wire.begin(); // Initialize communication
  Wire.beginTransmission(MPU); // Start communication with MPU6050
  Wire.write(0x6B); // Talk to the register 6B
  Wire.write(0x00); // Make reset - place a 0 into the 6B register
  Wire.endTransmission(true); // End the transmission

  // Configure Accelerometer Sensitivity - Full Scale Range (default +/- 2g)
  Wire.beginTransmission(MPU);
  Wire.write(0x1C); // Talk to the ACCEL_CONFIG register (1C hex)
  Wire.write(0x10); // Set the register bits as 00010000 (+/- 8g full scale range)
  Wire.endTransmission(true);

  calibrateMPU6050();
  delay(20);
}

void loop() {
  delay(5);
  // === Read accelerometer data === //
  Wire.beginTransmission(MPU);
  Wire.write(0x3B); // Start with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true); // Read 6 registers total, each axis value is stored in 2 registers

  // For a range of +-2g, we need to divide the raw values by 16384, according to the datasheet
  AccX = (Wire.read() << 8 | Wire.read()) / 16384.0; // X-axis value
  AccY = (Wire.read() << 8 | Wire.read()) / 16384.0; // Y-axis value
  AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0; // Z-axis value

  // Calculating Roll and Pitch from the accelerometer data
  accAngleX = (atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / PI) - accErrorX; // Apply calibration offset
  accAngleY = (atan(-1 * AccX / sqrt(pow(AccY, 2) + pow(AccZ, 2))) * 180 / PI) + accErrorY; // Apply calibration offset

  // Determine direction based on accelerometer angles
  int direction = i;
  if (abs(accAngleX) < directionThreshold1 && abs(accAngleY) < directionThreshold1) {
    direction = 5; // Neutral or default direction
  } else if (abs(accAngleX) > abs(accAngleY)) {
    if (accAngleX > directionThreshold3) {
      direction = 1; // Send direction 1
    } else if (accAngleX < -directionThreshold3) {
      direction = 2; // Send direction 2
    } else {
      direction = 5; // Neutral direction
    }
  } else {
    if (accAngleY > directionThreshold3) {
      direction = 3; // Send direction 3
    } else if (accAngleY < -directionThreshold3) {
      direction = 4; // Send direction 4
    } else {
      direction = 5; // Neutral direction
    }
  }

  // Send the direction
  vw_send((uint8_t *)&direction, sizeof(direction));
  vw_wait_tx(); // Wait until the message is sent

  // Print the values on the serial monitor
  Serial.print("X angle: ");
  Serial.print(accAngleX);
  Serial.print(" Y angle: ");
  Serial.println(accAngleY);
  Serial.print("Direction: ");
  Serial.println(direction);

  xValue = map(accAngleX,-90,+90,0,255);
  yValue = map(accAngleY,-90,+90,0,255);

  delay(1000); // Delay for a second
}

void calibrateMPU6050() {
  int calibrateIterations = 200;
  float accErrorX = 0, accErrorY = 0;

  for (int i = 0; i < calibrateIterations; ++i) {
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 14, true);

    int16_t accRawX = Wire.read() << 8 | Wire.read();
    int16_t accRawY = Wire.read() << 8 | Wire.read();
    int16_t accRawZ = Wire.read() << 8 | Wire.read();

    accErrorX += atan(accRawY / sqrt(pow(accRawX, 2) + pow(accRawZ, 2))) * 180 / PI;
    accErrorY += atan(-1 * accRawX / sqrt(pow(accRawY, 2) + pow(accRawZ, 2))) * 180 / PI;

    delay(10);
  }

  accErrorX /= calibrateIterations;
  accErrorY /= calibrateIterations;

  Serial.println("MPU6050 Calibration Results:");
  Serial.print("Accelerometer Error(X-axis): ");
  Serial.println(accErrorX);
  Serial.print("Accelerometer Error(Y-axis): ");
  Serial.println(accErrorY);
}
