#ifndef AUTH_H
#define AUTH_H
#include "Definitions.h" // Definitions and common settings are here.
#include "Arduino.h"

class Authentication {
  public:

    Authentication(bool displayMsg);

    byte status(int RFID, int keypadPIN, int bluetoothPIN);
    String userName;
    byte userID;
    String method;

  private:
};
#endif

