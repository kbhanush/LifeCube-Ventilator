/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.
 
 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/
 
#include <Servo.h>
 
const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];    
char messageFromPC[numChars] = {0};
int integerFromPC = 0;
int respirationRate = 0;
int tVolume = 0;
int pauseBB = 0;
int power = 1;
float floatFromPC = 0.0;
 
boolean newData = false;
 
Servo myservoR; // Right side servo marked 'R' on motor
Servo myservoL;  // Left side servo marked 'L' on motor
// Note that each servo has a different initial position due to how the motors are attached
//and how they initialize with the arms wide apart
 
int ServoR_pos = 0; // This determines right arms actual position at any given time
int ServoL_pos = 0;    // This determines left arms actual position at any given time
 
 
int initialServoR = 40; // Right arm starts at rightmost position. This is the max it goes out
 
 
 
int ServoR_max = 8; //ServoR_max mean how close to the center the right servo arm gets.
                    //5 means perpendicular this should not go below 5.
                    //Increase this for lighter breaths
 
int initialServoL = 5; //Left arm starts at leftmost position. This is the max it goes out
int ServoL_max = 37; //ServoL_max mean how close to the center the left servo arm gets.
                     // X means perpendicular. This should no go above this X
                     // Decrease this propotionate to ServoR_max for lighter breaths
                     
int rate = 25;
int pause_after_inhale = 1000;
int pause_after_exhale = 1000;
void setup() {
  Serial.begin(9600);
  Serial.println("<Arduino is ready>");
  myservoR.attach(9);
  myservoL.attach(11);  // attaches the servo on pin 9 to the servo object
}
 
void loop() {
 
    recvWithStartEndMarkers();
    if (newData == true) {
        strcpy(tempChars, receivedChars);
            // this temporary copy is necessary to protect the original data
            //   because strtok() used in parseData() replaces the commas with \0
        parseData();
        showParsedData();
        newData = false;
    }
 
  if (power == 1) {
     
      for (ServoR_pos = initialServoR, ServoL_pos = initialServoL; ServoR_pos >= ServoR_max && ServoL_pos <= ServoL_max; ServoR_pos -= 1, ServoL_pos += 1)
      {
        myservoR.write(ServoR_pos);  
        myservoL.write(ServoL_pos);  //            
        delay(rate);
      }
   
      delay(pause_after_inhale);
      for (ServoR_pos = ServoR_max, ServoL_pos = ServoL_max; ServoR_pos <= initialServoR && ServoL_pos >= initialServoL; ServoR_pos += 1, ServoL_pos -= 1)
      {
        myservoR.write(ServoR_pos);
        myservoL.write(ServoL_pos); //
        delay(rate);                      
      }
     
     delay(pause_after_exhale);
 
  }
}
 
 
void updateData() {
 
    Serial.println(respirationRate);
    Serial.println(tVolume);
    Serial.println(pauseBB);
 
    switch (respirationRate) {
      case 6:
        rate = 150;
        break;
      case 7:
        rate = 125;
        break;
      case 8:
        rate = 105;
        break;
      case 9:
        rate = 90;
        break;
      case 10:
        rate = 80;
        break;
      case 11:
        rate = 70;
        break;
      case 12:
        rate = 60;
        break;
      case 13:
        rate = 50;
        break;
      case 14:
        rate = 40;
        break;
      case 15:
        rate = 40;
        break;                                
    }
    switch (tVolume) {
      case 3:
        ServoR_max = 2;
        ServoL_max = 28;
        break;
      case 2:
        ServoR_max = 10;
        ServoL_max = 20;
        break;
      case 1:
        ServoR_max = 15;
        ServoL_max =  15;
        break;  
    }
 
    if (pauseBB >= 0 && pauseBB < 4) {
      pause_after_exhale = pauseBB * 1000;
    }
}
 
void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
 
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();
 
        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }
 
        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}
 
void parseData() {      // split the data into its parts
 
    char * strtokIndx; // this is used by strtok() as an index
 
    strtokIndx = strtok(tempChars,",");      // get the first part - the string
    //strcpy(messageFromPC, strtokIndx); // copy it to messageFromPC
    power = atoi(strtokIndx);
 
    strtokIndx = strtok(NULL, ",");
    respirationRate = atoi(strtokIndx);
 
    strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
    tVolume = atoi(strtokIndx);     // convert this part to an integer
 
    strtokIndx = strtok(NULL, ",");
    pauseBB = atoi(strtokIndx);     // convert this part to a float
   
}
 
void showParsedData() {
    Serial.print("respirationRate: ");
    Serial.println(respirationRate);
    Serial.print("tVolume: ");
    Serial.println(tVolume);
    Serial.print("pause b/w breath: ");
    Serial.println(pauseBB);
    Serial.print("power:");
    Serial.println(power);
    updateData();
}
