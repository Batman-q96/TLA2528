#include "tla2528.h"

#include <stdint.h>
#include <Wire.h>

TLA2528::TLA2528(uint8_t TLA2528_address) {
  this->TLA2528_address = TLA2528_address;
}

uint8_t TLA2528::read_from_register(uint8_t reg_addr, bool release_wire) {
  int RESPONSE_SIZE = 1;

  Wire.beginTransmission(this->TLA2528_address);
  Wire.write(0x10);
  Wire.write(reg_addr);
  Wire.endTransmission(release_wire);
  Wire.requestFrom(this->TLA2528_address, RESPONSE_SIZE);
  return Wire.read();
}

void TLA2528::write_to_register(uint8_t reg_addr, uint8_t data, bool release_wire) {
  Wire.beginTransmission(this->TLA2528_address);
  Wire.write(0x08);
  Wire.write(reg_addr);
  Wire.write(data);
  Wire.endTransmission(release_wire);
}

uint16_t TLA2528::read_one_channel_data(uint8_t channel_num){
  int RESPONSE_SIZE = 2;

  write_to_register(MANUAL_CH_SEL_ADDRESS, channel_num, false);
  Wire.requestFrom(this->TLA2528_address, RESPONSE_SIZE);
  uint16_t data = Wire.read() << 8 | Wire.read();
  return data;
}