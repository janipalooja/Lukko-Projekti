#include "Bluetooth.h"

Bluetooth::Bluetooth(bool displayMsg) {
  // Instantiating object...
}

int Bluetooth::readPinFromSerial() {

  int pinCode;

  if (Serial.available() > 0) {

    pinCode = Serial.parseInt();

  }
  return pinCode;
}


