                                                                                                                                                                                                                                                                                                                                               #include <VirtualWire.h>

const int transmit_pin = 12;

void setup(){
  // put your setup code here, to run once:
vw_set_tx_pin(transmit_pin);
vw_setup(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
char message[] = "Hello World!";
vw_send((uint8_t*)message, strlen(message));
delay(1000);
}
