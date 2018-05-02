#include "Authentication.h"
#include "Users.h"

Authentication::Authentication(bool displayMsg) {
}

byte Authentication::status(int RFID, int keypadPIN, int bluetoothPIN) {

  int identifier = 0;
  byte authStatus = 0;
  byte pinMatch = 0;

  // RFID is primary authentication method...
  if (RFID != 0) {
    identifier = RFID;
    Authentication::method = "rfid";
  }
  // KEYPAD is second...
  else if (keypadPIN != 0) {
    identifier = keypadPIN;
    Authentication::method = "keypad";
  }
  // BLUETOOTH is third...
  else if (bluetoothPIN != 0) {
    identifier = bluetoothPIN;
    Authentication::method = "bluetooth";
  }

  if (identifier != 0) {
    for (int i = 0; i < NUMBER_OF_USERS; i++) {
      if (identifier == users[i].pin) {
        Authentication::userID = users[i].id;
        Authentication::userName = users[i].name;
        pinMatch++;
      }
      if (pinMatch > 0) {
        authStatus = AUTH_SUCCEEDED;
      } else {
        authStatus = AUTH_FAILED;
      }
    }
  }

  return authStatus;
}

