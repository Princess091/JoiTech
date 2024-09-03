#include <VirtualWire.h>

const int receive_pin = 11;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
vw_set_rx_pin(receive_pin);
vw_setup(2000);
vw_rx_start();
}

void loop() {
  // put your main code here, to run repeatedly:
uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;

if(vw_get_message(buf, &buflen)){
  Serial.print("Received!");
  for (int i = 0; i < buflen; i++){
    Serial.print(char(buf[i]));
  }
  Serial.println();
}
}
