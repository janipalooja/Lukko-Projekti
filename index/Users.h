struct User {
  // TODO: Add RFID identity here??
  byte id;
  int pin;
  char name[5];
} users[NUMBER_OF_USERS] = {
  // Id,  "Pin/Identifier", "Name"
  { 1, 1111, "Jani" },
  { 2, 2222, "Joni" },
  { 3, 3333, "Satu" }
};

