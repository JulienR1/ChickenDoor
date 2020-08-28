int lightSensorPin = A0;
int upSensorPin = 2;
int lowSensorPin = 3;
int upRelayPin = 8;
int downRelayPin = 9;

int doorMovementDelay = 250;   // in ms
int updateDelay = 10000;      // 15 mins in ms = 10*1000

int doorDirection = 0;  // -1: down, 0: up, 1: up

void setup() {
  setPins();
  Serial.begin(9600);
  resetDoor();
}

void loop(){
  determineDoorDirection();
  moveDoor();
  waitForNextStep();
}

void setPins(){
  pinMode(lightSensorPin, INPUT);
  pinMode(upSensorPin, INPUT);
  pinMode(lowSensorPin, INPUT);

  digitalWrite(upRelayPin, HIGH);
  digitalWrite(downRelayPin, HIGH);
  pinMode(upRelayPin, OUTPUT);
  pinMode(downRelayPin, OUTPUT);
}

void resetDoor(){
  if(!isUp() && !isDown()){
    doorDirection = -1;
    recordMovementStarted();
  }
}

void determineDoorDirection(){
  if(doorDirection == 0){
    doorDirection = getOnlineDoorDirection();
  }

  bool daytime = isDay();
  if(daytime){
    recordDayTime(daytime);
  }
  
  if(doorDirection == 0){    
    if(daytime && !isUp()){
      doorDirection = 1;
      recordMovementStarted();      
    }else if(!daytime && !isDown()){
      doorDirection = -1;
      recordMovementStarted();
    }    
  }else if((isDown() && doorDirection < 0) || (isUp() && doorDirection > 0)){
    recordMovementComplete(doorDirection < 0);
    doorDirection = 0;
  }
}

void moveDoor(){
  digitalWrite(upRelayPin, doorDirection > 0 ? LOW : HIGH);
  digitalWrite(downRelayPin, doorDirection < 0 ? LOW : HIGH);
}

void waitForNextStep(){
  if(doorDirection == 0){
    delay(updateDelay);
  }else{
    delay(doorMovementDelay);
  }
}

bool isUp(){
  return digitalRead(upSensorPin) == HIGH;
}

bool isDown(){
  return digitalRead(lowSensorPin) == HIGH;
}

bool isDay(){
  return digitalRead(lightSensorPin) == LOW;
}

int getOnlineDoorDirection(){
  // https://jrousseau.ca/chickendoor/php/arduino_doorDirection.php
}

void recordMovementComplete(int doorState){
  // https://jrousseau.ca/chickendoor/php/arduino_recordMovement.php?doorState=
}

void recordMovementStarted(){
 // https://jrousseau.ca/chickendoor/php/arduino_recordMovement.php?doorDirection=
}

void recordDayTime(bool isDay){
  // https://jrousseau.ca/chickendoor/php/arduino_daytime.php?daytime=
}
