#ifndef KEYPAD_AUTH_H
#define KEYPAD_AUTH_H
#include "Definitions.h" // Definitions and common settings are here.
#include <Keypad.h>

class KeypadAuth {
  public:

    // Constructor
    KeypadAuth(bool displayMsg);

    // Methods
    int keypadPin();

  private:
};
#endif
