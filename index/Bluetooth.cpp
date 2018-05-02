#include "Bluetooth.h"

Bluetooth::Bluetooth(bool displayMsg) {
  // Instantiating object...
}

int Bluetooth::readPinFromSerial() {

  int pinCode = 0;

  if (Serial.available() > 0) {

    pinCode = Serial.parseInt();

  }
  return pinCode;
}


