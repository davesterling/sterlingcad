#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"

DFRobotDFPlayerMini myDFPlayer;

const int trigPin = 32;
const int echoPin = 33;
const int Btn = 25;

float distance; // Declare distance as a global variable

int limit = 1;
int Lower_limit, Upper_limit;
bool Start = false, flag_L = false, flag_U = false, U = false, L = false, mid = false;
int REPS, range;
bool flagBtn = true;
unsigned long prevmlsBtn;
short result = -1;

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(Btn, INPUT_PULLUP);
  delay(2000);
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(Serial2)) {
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
  }

  // Set volume (optional)
  myDFPlayer.volume(15); // Set volume to 15 (adjust as needed)
}

void loop() {
  Read_Button();
  Get_Distance();

  delay(100);
}

void Read_Button() {
  result = Btn_state();

  if (result == 1) {
    if (Start != true) {
      Start = true;
      limit = 0;
      Serial.println("\tDevice ON!\t");
    } else if (limit == 0) {
      Lower_limit = distance;
      limit = 1;
      flag_L = true;
      Serial.println((String)"Lower Limit Set to :" + Lower_limit);
      delay(1000);
    } else if (limit == 1) {
      Upper_limit = distance;
      limit = 0;
      flag_U = true;
      Serial.println((String)"Upper Limit Set to :" + Upper_limit);
      delay(1000);
    }
  } else if (result == -1) {
    Start = false;
    Serial.println("\tDevice OFF!\t");
  }
}

int Btn_state() {
  int state = 0;
  if (digitalRead(Btn) == LOW && flagBtn == true) {
    flagBtn = false;
    prevmlsBtn = millis();

  } else if (digitalRead(Btn) == HIGH && flagBtn == false) {
    flagBtn = true;

    if (millis() - prevmlsBtn < 1000) {
      state = 1;
    } else if (millis() - prevmlsBtn > 2000) {
      state = -1;
    }
  }
  return state;
}

void Get_Distance() {
  if (Start == true) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    float duration = pulseIn(echoPin, HIGH);
    distance = (duration * 0.0343) / 2;

    int pitch = map(distance, Lower_limit, Upper_limit, 100, 1000); // Map distance to pitch range

    if (pitch < 100) pitch = 100;
    if (pitch > 1000) pitch = 1000;

    myDFPlayer.stop(); // Stop any previously playing tone
    myDFPlayer.playMp3Folder(1); // Play a silent mp3 to stop any previous sound
    delay(10);
    myDFPlayer.outputDevice(DFPLAYER_DEVICE_U_DISK); // Set output to U-disk (speaker) to play custom tone

    myDFPlayer.volume(15); // Set volume to a fixed value

    myDFPlayer.playMp3Folder(2); // Play the MP3 file at index 2 (adjust as needed)

    Serial.print("Distance: ");
    Serial.print((int)distance);
    Serial.print(" cm, Pitch: ");
    Serial.println(pitch);
  }
}
