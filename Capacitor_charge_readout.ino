#include <SevSeg.h>
SevSeg sevseg; //Instantiate a seven segment object
int lightgate1 = A0;
int lightgate2 = A1;
int AnalogLight1;
int AnalogLight2;
int transistor1 = A4;
int transistor2 = A3;
int go1 = 0;
int go2 = 0;
int voltpin = A5;
int voltage;

void setup() {
 // put your setup code here, to run once:
pinMode(transistor1, OUTPUT);
pinMode(transistor2, OUTPUT);
digitalWrite(transistor1,LOW);
digitalWrite(transistor2,LOW);
Serial.begin(9600);
  byte numDigits = 4;
  byte digitPins[] = {10, 11, 12, 13};
  // 1,2,3,4
  byte segmentPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
  // A,B,C,D,E,F,G,DP
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_CATHODE; // See README.md for options
  bool updateWithDelays = true; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected. Then, you only need to specify 7 segmentPins[]

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
}

void loop() {
  // put your main code here, to run repeatedly:
   voltage = analogRead(voltpin);
 
   sevseg.refreshDisplay(); // Must run repeatedly

     static unsigned long timer = millis();

  if (millis() >= timer) {
    timer += 500;
    sevseg.setNumber(voltage);
  }
    AnalogLight1 = analogRead(lightgate1);
AnalogLight2 = analogRead(lightgate2);
  if (AnalogLight1 <= 400){
    go1 = 1;
    digitalWrite(transistor1,go1);
    
  }
  else if (AnalogLight1 > 400){
    digitalWrite(transistor1,go1);
    go1= 0;
  }

    if (AnalogLight2 <= 700){
    go2 = 1;
    digitalWrite(transistor2,go2);
    
  }
  else if (AnalogLight2 > 700){
    digitalWrite(transistor2,go2);
    go2 = 0;
  }
Serial.print(AnalogLight1);
Serial.print("  :  ");
Serial.println(go1);
Serial.print(AnalogLight2);
Serial.print("  :  ");
Serial.println(go2);
//Serial.print(digitalRead(transistor1));
//Serial.println(digitalRead(transistor2));
}
