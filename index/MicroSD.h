#ifndef MICRO_SD_H
#define MICRO_SD_H
#include "Definitions.h" // Definitions and common settings are here.
#include <SD.h>

class MicroSD {
  public:

    // Constructor
    MicroSD(bool displayMsg);

    // Methods
    void initialization();

    void logTheAuthData(byte authStatus, String method, byte userID, String userName);

  private:
};
#endif

