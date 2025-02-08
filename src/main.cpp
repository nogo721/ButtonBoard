#include <PicoGamepad.h>
#include <Arduino.h>

PicoGamepad buttonBoard; //Were are just going to use the predefined PicoGamepad class cause I don't want to make a new one

// 16 bit integer for holding input values
int val;

int REEF_FAR_LEFT = 0;      //Pin values for the buttons/switches
int REEF_FAR_CENTER = 1;
int REEF_FAR_RIGHT = 2;
int REEF_NEAR_LEFT = 3;
int REEF_NEAR_CENTER = 4;
int REEF_NEAR_RIGHT = 5;

int AUTO_SWITCH = 6;

int LEVEL_1L = 7;
int LEVEL_1R = 8;
int LEVEL_2L = 9;
int LEVEL_2R = 10;
int LEVEL_3L = 11;
int LEVEL_3R = 12;
int LEVEL_4L = 13;
int LEVEL_4R = 14;          //Pin values for the buttons/switches

void setup() {  
  Serial.begin(115200);
  
  pinMode(LED_BUILTIN, OUTPUT);


 
  pinMode(REEF_FAR_LEFT, PinMode::PullDown); //sets all the pins to be pull down resistors (If you don't know what that means, then ask Nova or Noah)
  pinMode(REEF_FAR_CENTER, PinMode::PullDown);
  pinMode(REEF_FAR_RIGHT, PinMode::PullDown);
  pinMode(REEF_NEAR_LEFT, PinMode::PullDown);
  pinMode(REEF_NEAR_CENTER, PinMode::PullDown);
  pinMode(REEF_NEAR_RIGHT, PinMode::PullDown);

  pinMode(AUTO_SWITCH, PinMode::PullDown);

  pinMode(LEVEL_1L, PinMode::PullDown);
  pinMode(LEVEL_1R, PinMode::PullDown);
  pinMode(LEVEL_2L, PinMode::PullDown);
  pinMode(LEVEL_2R, PinMode::PullDown);
  pinMode(LEVEL_3L, PinMode::PullDown);
  pinMode(LEVEL_3R, PinMode::PullDown);
  pinMode(LEVEL_4L, PinMode::PullDown);
  pinMode(LEVEL_4R, PinMode::PullDown);
}

void loop() {
  
  //Logic system to decide which inputs to send to the computer

  int x = 0;                    //Selects the reef side, does nothing if two inputs are pressed simultaneously
  for(int i = REEF_FAR_LEFT; i < REEF_NEAR_RIGHT; i++){
    x+=digitalRead(i);
    }
  if(x==HIGH){
    for(int i = 0; i < 16; i++){
    if(digitalRead(i)==HIGH){
      buttonBoard.SetButton(i, HIGH);
    }
    else{
      buttonBoard.SetButton(i, LOW);
    }
  }

  buttonBoard.SetButton(AUTO_SWITCH, digitalRead(AUTO_SWITCH)); //Sets the switch value in the data sent to the computer

int x = 0;                    //Selects the reef level, does nothing if two inputs are pressed simultaneously
  for(int i = LEVEL_1L; i <= LEVEL_4R; i++){
    x+=digitalRead(i);
    }
  if(x==HIGH){
    for(int i = 0; i < 16; i++){
    if(digitalRead(i)==HIGH){
      buttonBoard.SetButton(i, HIGH);
    }
    else{
      buttonBoard.SetButton(i, LOW);
    }
  }

  // Send all inputs on HID object
  // Nothing is send to the computer until this is called.
  buttonBoard.send_update();

  // Flash the LED just for fun
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); 
  delay(100);
  }
}
