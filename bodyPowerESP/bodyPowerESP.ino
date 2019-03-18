//inputs:bat1v, bat2v, backupv, shorev

//also set pin numbers
int bat1v;
int bat2v;
int backupv;
int shorev;

//also set realy pin numbers

bool battPower = false;   //default shore 
bool charging = true;
bool shorePower = true;


void setup() {
  //initialize logging SD
  //initilize wifi connection
  //set input pins
  //set outpust pins
}

void loop() {
  //if either battery voltage is too low go to shore and set charge
  //if shorev is high go to shore and set to charge
  //if shorev is low and and batteries have power disconnect charge and switch to batt

  //if shore set relay else toggle
  //if charging set relays else toggle

  //report if there is a significant update
  //listen for commands?
}
