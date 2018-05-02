#include "Keypad.h"

KeypadAuth::KeypadAuth(bool displayMsg) {
}

byte numbersEntered = 0;
char pinCodeArray[4];

const byte ROWS = 4; // NeljÃ¤ vaaka (ROW) riviÃ¤
const byte COLS = 3; // Kolme pysty (COL) riviÃ¤

char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {8, 7, 6, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int KeypadAuth::keypadPin() {
  int pinCode = 0;
  char key = keypad.getKey();
  if (key != NO_KEY) {
    pinCodeArray[numbersEntered] = key;
    numbersEntered++;

    if (numbersEntered == 4) {
      pinCode = atoi(pinCodeArray);
      numbersEntered = 0;
      pinCodeArray[4] = {0};
    }
  }
  return pinCode;
}

