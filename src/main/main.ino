#include <Wire.h>

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  Wire.begin();
}

// the loop routine runs over and over again forever:
void loop() {
  if(Serial.available()) {
    int addr = Serial.parseInt();
    Wire.beginTransmission(0x13);
    Wire.write(0x10);
    Wire.write(addr);
    Wire.endTransmission(true);
    Serial.println(Wire.requestFrom(0x13, 100, true));
    Serial.println(Wire.available());
    int resp;
    char str_resp[10];
    while (Wire.available()) {
      resp = Wire.read();
      sprintf(str_resp, "%02X", resp);
      Serial.println(str_resp);
    }
  }
}
