#include <SPI.h>
#include <LoRa.h>
#include<Arduino.h>
#include<pins_arduino.h>

#ifdef ARDUINO_SAMD_MKRWAN1300
#error "This example is not compatible with the Arduino MKR WAN 1300 board!"
#endif

void onReceive(int packetSize);
void setup() {
  Serial.begin(9600);
  SPI.begin(LORA_SCK,LORA_MISO,LORA_MOSI,LORA_CS);
LoRa.setSPI(SPI);
LoRa.setPins(LORA_CS, LORA_RST, LORA_IRQ);
  while (!Serial);

  Serial.println("LoRa Receiver Callback");

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  // register the receive callback
  LoRa.onReceive(onReceive);

  // put the radio into receive mode
  LoRa.receive();
}

void loop() {
  // do nothing
}

void onReceive(int packetSize) {
  // received a packet
  Serial.print("Received packet '");

  // read packet
  for (int i = 0; i < packetSize; i++) {
    Serial.print((char)LoRa.read());
  }

  // print RSSI of packet
  Serial.print("' with RSSI ");
  Serial.println(LoRa.packetRssi());
}

