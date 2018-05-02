#define DEBUG // Comment out this line to disable all debug printing on arduino serial monitor.

// Memory regions on the PICC
#define RFID_SECTOR_TRAILER 11
#define RFID_SECRET_BLOCK 8

// PCD to Arduino pins
#define RFID_SDA A0
#define RFID_RST UINT8_MAX
// SCK = 13
// MOSI = 11
// MISO = 12

#define RELAY_CONTROL_PIN 9
#define RFID_SS_PIN A0
#define MICROSD_SS_PIN 10

#define NUMBER_OF_USERS 3
#define AUTH_SUCCEEDED 1
#define AUTH_FAILED 2
