/* Ryhmä 3 */
#include "Definitions.h" // Definitions and common settings are here.
#include "RFID.h"
#include "Bluetooth.h"
#include "Keypad.h"
#include "Authentication.h"
#include "MicroSD.h"

RFID rfid(true);
Bluetooth bluetooth(true);
KeypadAuth keypadauth(true);
Authentication authentication(true);
MicroSD microsd(true);

void openTheLock(int theTimeTheDoorIsOpen){
    digitalWrite (RELAY_CONTROL_PIN, LOW);
    delay(theTimeTheDoorIsOpen);
    digitalWrite (RELAY_CONTROL_PIN, HIGH);
  }

void setup() {
  Serial.begin(9600);
  
  pinMode(RELAY_CONTROL_PIN, OUTPUT);
  digitalWrite(RELAY_CONTROL_PIN, HIGH);

  pinMode(RFID_SS_PIN, OUTPUT);
  digitalWrite(RFID_SS_PIN, HIGH);
  
  pinMode(MICROSD_SS_PIN, OUTPUT);
  microsd.initialization();
  
  rfid.setup();
}

void loop() {

  int rfidPIN = rfid.poll();
  int keypadPIN = keypadauth.keypadPin();
  int bluetoothPIN = bluetooth.readPinFromSerial();

  byte authStatus = authentication.status(rfidPIN, keypadPIN, bluetoothPIN);

  // Authentication required
  if (authStatus == AUTH_SUCCEEDED) {

  // Debug printing
    #ifdef DEBUG
      Serial.print(F("[index_ino] authStatus = "));
      Serial.println(authStatus);
      Serial.print(F("[index_ino] userName = "));
      Serial.println(authentication.userName);
      Serial.print(F("[index_ino] method = "));
      Serial.println(authentication.method);
    #endif
    
    // Log authentication succeeded to SD
    microsd.logTheAuthData(authStatus, authentication.method, authentication.userID, authentication.userName);

    // Open the lock
    openTheLock(500);
  }
  else if (authStatus == AUTH_FAILED) {
    // Log authentication failed to SD
    microsd.logTheAuthData(authStatus, authentication.method, authentication.userID, authentication.userName);
  }

}

