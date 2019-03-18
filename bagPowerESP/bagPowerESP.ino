int shoreV;

//set analog pins
int bat1v;
int bat2v;
int bat3v;
int bat4v;
int bat5v;
int bat6v;

//set relay pins
bool shorePwr = true;
bool battPwr = false;

bool bank1chg = true;
bool bank2chg = true;
bool bank3chg = true;


void setup() {
  //initialize logging SD
  //initilize wifi connection
  //set input pins
  //set output pins
}

void loop() {
  //if there is shore power
    //set all banks to charge
    //switch to shore power
  //else
    //see if there is a bank with adiquate voltage 
      //switch to it and set all others to charge

  //log data
  //send changes
}
