#include "tla2528.h"

#include <Wire.h>

TLA2528 tla2528(0x13);

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  Wire.begin();
}

// the loop routine runs over and over again forever:
void loop() {
  if(Serial.available()) {
    char action;
    Serial.readBytes(&action, 1);
    if (action == 'r'){
      char addr;
      Serial.readBytes(&addr, 1);
      addr = addr - '0';
      int resp = tla2528.read_from_register(addr);
      char str_resp[10];
      sprintf(str_resp, "%02X", resp);
      Serial.println(str_resp);
    }
    if (action == 'w'){
      char addr, data;
      Serial.readBytes(&addr, 1);
      data = Serial.parseInt();
      addr = addr - '0';
      tla2528.write_to_register(addr, data);
    }
    if (action == 'd'){
      char channel;
      Serial.readBytes(&channel, 1);
      Serial.println(tla2528.read_one_channel_data(channel - '0'));
    }
  }
}