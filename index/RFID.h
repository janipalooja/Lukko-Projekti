#ifndef RFID_h
#define RFID_h
#include "Definitions.h" // Definitions and common settings are here.
#include <MFRC522.h>

struct rfid_id {
  uint32_t uid; // Our tags are Mifare Classic and use 4 byte UID
  byte key[6];
  int pin;
};

const rfid_id rfid_identity_table[] = {
  {0xA18497C6, {0xFE, 0xED, 0xCA, 0xFE, 0xBA, 0xBE}, 1111},
  {0xAB9001B9, {0xBE, 0xEF, 0xBC, 0xEF, 0xBE, 0xEF}, 2222},
  {0xAB87EB69, {0xFE, 0xFE, 0x1B, 0x6, 0x13, 0x57}, 1111} // Jani
};

// This is what is written to the PICC when the setup program is run.
// We read the block it should have been written to and compare it against this.
const byte rfid_secret[16] = {
  0x00, 0x01, 0x02, 0x03, 0xF0, 0x0D, 0xD0, 0x0F,
  0xAB, 0xBA, 0xAB, 0xBA, 0xC0, 0xFE, 0xEE, 0xEE
};

class RFID {
  public:
    RFID(bool displayMsg);
    void setup();
    int poll();
  private:
    int find_uid();
    bool validate_secret();
    bool auth(const int uid_index);
};
#endif
