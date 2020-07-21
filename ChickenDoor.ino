int lightSensorPin = 2;  // P1.0
int upSensorPin = 5;     // P1.6
int lowSensorPin = 6;    // P1.7
int upRelayPin = 9;      // P1.3
int downRelayPin = 10;   // P1.2

float dayThreshHold = 0.25;    // in volts
float nightTreshHold = 1.5;    // in volts

int doorMovementDelay = 250;   // in ms
int updateDelay = 900000;      // 15 mins in ms = 15*60*1000

void setup() {
  pinMode(lightSensorPin, INPUT);
  pinMode(upSensorPin, INPUT);
  pinMode(lowSensorPin, INPUT);

  pinMode(upRelayPin, OUTPUT);
  pinMode(downRelayPin, OUTPUT);
}

void loop(){
  if(!isLow() && !isHigh()){
    goDown();
  }

  float voltage = getLightVoltage();
  if(isLow() && voltage < dayThreshHold){
    goUp();
  }
  if(isHigh() && voltage > nightThreshHold){
    goDown();
  }

  delay(updateDelay);
}

void goUp(){
  while(!isHigh()){
    digitalWrite(upRelayPin, HIGH);
    delay(doorMovementDelay);
  }
  digitalWrite(upRelayPin, LOW);
}

void goDown(){
  while(!isLow()){
    digitalWrite(downRelayPin, HIGH);
    delay(doorMovementDelay);
  }
  digitalWrite(downRelayPin, LOW);
}

float getLightVoltage(){
  float sensorValue = analogRead(lightSensorPin);
  float voltage = sensorValue * (3.0 / 1023.0);  
  return voltage;
}

bool isHigh(){
  return digitalRead(upSensorPin) == HIGH;
}

bool isLow(){
  return digitalRead(lowSensorPin) == HIGH;
}
