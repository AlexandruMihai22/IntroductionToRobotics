// declare all the joystick pins
const int pinSW = 8; // digital pin connected to switch output
const int pinX = A0; // A0 - analog pin connected to X output
const int pinY = A1; // A1 - analog pin connected to Y output

// states of the button press
bool swState = HIGH;
bool lastSwState = HIGH;
int reading = 1;
unsigned int lastDebounceTime = 0;  // initialize debounce values used for switch input
unsigned int debounceDelay = 50; 
int xValue = 0;
int yValue = 0;

bool joyMovedOx = false;
bool joyMovedOy = false;
int digit = 0;
int minThreshold= 300;
int maxThreshold= 700;

const int latchPin = 11; // STCP to 12 on Shift Register
const int clockPin = 10; // SHCP to 11 on Shift Register
const int dataPin = 12; // DS to 14 on Shift Register

const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;
int displayDigits[] = {
  segD1, segD2, segD3, segD4
};
const int displayCount = 4;

int digitArray[20] = {
//A B C D E F G DP 
  B11111100, // 0
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
  B11111101, // 0.
  B01100001, // 1.
  B11011011, // 2.
  B11110011, // 3.
  B01100111, // 4.
  B10110111, // 5.
  B10111111, // 6.
  B11100001, // 7.
  B11111111, // 8.
  B11110111 // 9.
};

// variables for timers
unsigned long previousMillis = 0;
unsigned long lastBeepMillis = 0;
// variables for display states
int displayNumber[4];
int currentDisplay = 0;
int currentDisplayNumber = 0;
int displayState = 0;


void setup() {
  pinMode(pinSW, INPUT_PULLUP); // activate pull-up resistor on the push-button pin
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  for (int i = 0; i < displayCount; i++) {
    pinMode(displayDigits[i], OUTPUT);
    digitalWrite(displayDigits[i], LOW);
  }
  Serial.begin(9600);
}

void loop() {
  reading = digitalRead(pinSW);
  // check to see if the button was pressed
  if (reading != lastSwState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  // wait until debounceTime passed and keep the reading
  if ((millis() - lastDebounceTime) > debounceDelay) {
    
    // if the button state has changed:
    if (reading != swState) {
      swState = reading;

      // only change the display state if the new state is LOW      
      if (swState == LOW) {
        displayState = !displayState;
      }
    }
  }
  // save last reading
  lastSwState = reading;
  
  if(displayState == 0) {
    // if in first state
    joyMovedAxisOx();   // check if joystick moved on OX axis and update current display
    if (millis() - lastBeepMillis < 300) {
      showDigit(currentDisplay);
      writeReg(digitArray[currentDisplayNumber]);   // // write digit without dp
      delay(5);
    }

    if (millis() - lastBeepMillis > 300 && millis() - lastBeepMillis < 600) {
      showDigit(currentDisplay);
      writeReg(digitArray[currentDisplayNumber + 10]); // write digit with dp
      delay(5);
    }

    if (millis() - lastBeepMillis > 600) {
      lastBeepMillis = millis();  // reset the timer
    }

  } else {
    // if in second state
    showDigit(currentDisplay);
    writeReg(digitArray[currentDisplayNumber+10]); // write number on current display
    delay(5);
    digit = currentDisplayNumber; // save current digit
    joyMovedAxisOy(); // check if joystick moved on OY axis and update digit
    displayNumber[currentDisplay] = digit; 
    currentDisplayNumber = displayNumber[currentDisplay];
  }

  for (int i = 0; i < 4; i ++) {
      int number = displayNumber[i];
      showDigit(i);
      writeReg(digitArray[number]);  // write number on each display 
      delay(5);
  }

}

void joyMovedAxisOx() {
  xValue = analogRead(pinX);
  // On Ox axis, if the value is lower than a chosen min threshold, then
  // increase by 1 the currentDisplay value.
  if (xValue < minThreshold && joyMovedOx == false) {
    if (currentDisplay < 3) {
      currentDisplay++;
      currentDisplayNumber = displayNumber[currentDisplay];
    }
    joyMovedOx = true;
  }
  // On Ox axis, if the value is bigger than a chosen max threshold, then
  // decrease by 1 the currentDisplay value
  if (xValue > maxThreshold && joyMovedOx == false) {
    if (currentDisplay > 0) {
    currentDisplay--;
    currentDisplayNumber = displayNumber[currentDisplay];
    } 
    joyMovedOx = true;
  }
  if (xValue >= minThreshold && xValue <= maxThreshold) {
    joyMovedOx = false;
  }
  delay(1);
}

void joyMovedAxisOy() {
  yValue = analogRead(pinY);
  // On Oy axis, if the value is lower than a chosen min threshold, then
  // decrease by 1 the digit value.
  if (yValue < minThreshold && joyMovedOy == false) {
    if (digit > 0) {
      digit--;
    } else {
      digit = 9;
    }
    joyMovedOy = true;
  }
  // On Oy axis, if the value is bigger than a chosen max threshold, then
  // increase by 1 the digit value
  if (yValue > maxThreshold && joyMovedOy == false) {
    if (digit < 9) {
    digit++;
    } else {
      digit = 0;
    }
    joyMovedOy = true;
  }
  if (yValue >= minThreshold && yValue <= maxThreshold) {
    joyMovedOy = false;
  }
  delay(1);
}

void showDigit(int displayNumber) {
  for (int i = 0; i < displayCount; i++) {
    digitalWrite(displayDigits[i], HIGH);
  }
  digitalWrite(displayDigits[displayNumber], LOW);
}

void writeReg(int digit) {
  digitalWrite(latchPin, LOW);

  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  
  digitalWrite(latchPin, HIGH);
}
