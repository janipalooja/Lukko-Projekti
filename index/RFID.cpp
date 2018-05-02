#include "RFID.h"

MFRC522 pcd(RFID_SDA, RFID_RST);

RFID::RFID(bool displayMsg) {
}

void RFID::setup() {
  pcd.PCD_Init();
  #ifdef DEBUG
  Serial.println(F("[RFID] PCD Initialized"));
  #endif
}

// First checks if there is a PICC to read. If so, tries to authenticate for it.
// Then reads the block designated to hold the secret. If the read block matches
// the secre, returns the PIN of the user the PICC belongs to.
int RFID::poll() {
  int pin = 0;
  if (!pcd.PICC_IsNewCardPresent()) {
    return pin;
  }
  #ifdef DEBUG
  Serial.println(F("[RFID] New PICC found"));
  #endif

  // Reads the UID to pcd.uid, returns true on success
  if (!pcd.PICC_ReadCardSerial()) {
    return pin;
  }

  // Size has to match ours
  if (pcd.uid.size != 4) {
    pcd.PICC_HaltA();
    return pin;
  }

  // Find the read UID from our UIDs and keep its index
  int uid_index = find_uid();
  if (uid_index == -1) {
    pcd.PICC_HaltA();
    return pin;
  }

  // Authenticate using the key stored in rfid_identity_table
  if (!auth(uid_index)) {
    pcd.PICC_HaltA();
    pcd.PCD_StopCrypto1();
    return pin;
  }

  // Read and check secret. Open lock if OK
  if (!validate_secret()) {
    pcd.PICC_HaltA();
    pcd.PCD_StopCrypto1();
    return pin;
  }

  pin = rfid_identity_table[uid_index].pin;
  pcd.PICC_HaltA();
  pcd.PCD_StopCrypto1();
  return pin;
}

// Finds the read UID from saved UIDs and returns its index.
//
// Returns: -1 if UID not found.
int RFID::find_uid() {
  // The MFRC522 library has kindly read the UID into a byte buffer for us. Let's use it as integer
  uint32_t uid;
  memcpy(&uid, pcd.uid.uidByte, 4);

  #ifdef DEBUG
  Serial.print(F("[RFID] UID: "));
  Serial.println(uid, HEX);
  #endif

  // Find the read UID from our saved UIDs and save its index
  int table_size = sizeof(rfid_identity_table) / sizeof(rfid_identity_table[0]);
  int uid_index = -1;
  for (int i = 0; i < table_size; i++) {
    if (rfid_identity_table[i].uid == uid) {
      uid_index = i;
      break;
    }
  }

  #ifdef DEBUG
  if (uid_index == -1) {
    Serial.println(F("[RFID] UID not found"));
  }
  #endif

  return uid_index;
}

// Reads the data from RFID_SECRET_BLOCK and checks it against our stored secret.
//
// Returns: True if read secret matches stored secret.
bool RFID::validate_secret() {
  byte buffer[18]; // 16 bytes for data, 2 for return value
  byte buffer_size = 18; // The library writes the number of bytes read to this

  MFRC522::StatusCode status = (MFRC522::StatusCode) pcd.MIFARE_Read(RFID_SECRET_BLOCK, buffer, &buffer_size);

  #ifdef DEBUG
  Serial.print(F("[RFID] Read secret: "));
  Serial.println(pcd.GetStatusCodeName(status));
  #endif

  if (status != MFRC522::STATUS_OK) {
    return false;
  }

  for (int i = 0; i < 16; i++) {
    if (buffer[i] != rfid_secret[i]) {
      #ifdef DEBUG
      Serial.println(F("[RFID] Secret mismatch"));
      #endif

      return false;
    }
  }

  return true;
}

// Authenticates against RFID_SECTOR_TRAILER.
// Remember to call PCD_StopCrypto1() after stopping communication.
// uid_index: the index in rfid_identity_table to authenticate with
//
// Returns: True on successfull authentication
bool RFID::auth(const int uid_index) {
  // Make the key for authenticating from our saved key
  MFRC522::MIFARE_Key key;
  memcpy(key.keyByte, rfid_identity_table[uid_index].key, 6);

  // Authenticate for the block RFID_SECTOR_TRAILER and save the status
  MFRC522::StatusCode status = (MFRC522::StatusCode) pcd.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, RFID_SECTOR_TRAILER, &key, &(pcd.uid));

  #ifdef DEBUG
  Serial.print(F("[RFID] Authenticate: "));
  Serial.println(pcd.GetStatusCodeName(status));
  #endif

  if (status != MFRC522::STATUS_OK) {
    return false;
  }

  return true;
}
