#ifndef BLUETOOTH_H
#define BLUETOOTH_H
#include "Definitions.h" // Definitions and common settings are here.
#include "Arduino.h"

class Bluetooth {
  public:

    // Constructor
    Bluetooth(bool displayMsg);

    // Methods
    int readPinFromSerial();

  private:
};
#endif

