// declare all the segments pins
const int pinA = 2;
const int pinB = 3;
const int pinC = 4;
const int pinD = 5;
const int pinE = 6;
const int pinF = 7;
const int pinG = 8;
const int pinDP = 9;

const int numReadings = 5;
const int segSize = 8;
const int noOfDigits = 10;
int digit = 0;

// declare variables for buzzer and antena
int senseLimit = 100; // raise this number to decrease sensitivity (up to 1023 max)
int antennaPin = A0;
int val = 0; // reading from antennaPin
const int buzzerPin = 11;
int buzzerTone = 200;
int buzzerDuration = 100;

// variables for smoothing
int readings[numReadings];                
int index = 0;                           
int total = 0;                            
int average = 0;                     
int updateTime = 100;

// store the pins in an array for easier access
int segments[segSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

byte digitMatrix[noOfDigits][segSize - 1] = {
// a  b  c  d  e  f  g
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}, // 9
};

void displayNumber(byte digit) {
  for (int i = 0; i < segSize - 1; i++) {
  digitalWrite(segments[i], digitMatrix[digit][i]);
  }  
}

void setup() {
  // initialize all the pins
  for (int i = 0; i < segSize; i++) {
    pinMode(segments[i], OUTPUT);
  }
  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;     
  }
  pinMode(antennaPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);  // initiate serial connection
}

void loop() {
  val = analogRead(antennaPin);  // take a reading from the antennaPin

  if(val >= 1){                // if the reading isn't zero, proceed
    val = constrain(val, 0, senseLimit);
    val = map(val, 0, senseLimit, 0, noOfDigits-1);  // remap the constrained value
    total -= readings[index];    
    readings[index] = val; 
    total += readings[index];               
    index ++;                  

    if (index >= numReadings) {               
      index = 0;                            
    }
    average = total / numReadings;          // calculate the average
    displayNumber(average);                 // display the average
    Serial.println(average);
     if (average != 0){
      tone(buzzerPin, average * buzzerTone, buzzerDuration);
    }
    delay(updateTime);  
  }
}

