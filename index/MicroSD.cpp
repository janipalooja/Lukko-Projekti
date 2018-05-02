#include "MicroSD.h"

MicroSD::MicroSD(bool displayMsg) {
}

File myFile;

void MicroSD::initialization() {

// Debug printing
  #ifdef DEBUG
    Serial.print(F("[MicroSD_cpp] "));
    Serial.println(F("Initializing SD card..."));
  #endif

  if (!SD.begin(10)) {
// Debug printing
  #ifdef DEBUG
    Serial.print(F("[MicroSD_cpp] "));
    Serial.println(F("initialization failed!"));
    #endif
    
    return;
  }
// Debug printing
  #ifdef DEBUG
  Serial.print(F("[MicroSD_cpp] "));
  Serial.println(F("initialization done."));
  #endif
}

void MicroSD::logTheAuthData(byte authStatus, String method, byte userID, String userName) {

  if (authStatus == AUTH_FAILED) {
    userID = 0;
    userName = "AUTH_FAILED";
  }

  // only one file can be open at a time, so you have to close this one before opening another.
  myFile = SD.open("data.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
// Debug printing
  #ifdef DEBUG
    Serial.print(F("Writing to file..."));
  #endif
    myFile.print(authStatus);
    myFile.print(", ");
    myFile.print(method);
    myFile.print(", ");
    myFile.print(userID);
    myFile.print(", ");
    myFile.println(userName);
    
    // close the file:
    myFile.close();
// Debug printing
  #ifdef DEBUG
    Serial.println(F("Writing to file done."));
  #endif
  } else {
// Debug printing
  #ifdef DEBUG
    // if the file didn't open, print an error:
    Serial.println(F("[MicroSD_cpp] error opening file"));
  #endif
  }
}


