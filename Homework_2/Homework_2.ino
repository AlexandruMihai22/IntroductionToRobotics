//variables for used pins and constant values 
const int buzzerPin = 11;
const int ledRedPin1 = 7;
const int ledYellowPin1 = 8;
const int ledGreenPin1 = 9;
const int ledRedPin2 =  12;
const int ledGreenPin2 = 13;
const int buttonPin = 2;
//variables to store components states
bool buttonState = HIGH;
bool buzzerState = LOW;
int buzzerTone = 3000;
int buzzerDuration = 100;
//button uses a pullup resistor
bool lastButtonState = HIGH; 
int reading = 1;  
bool ledRedState1 = LOW;
bool ledYellowState1 = LOW;
bool ledGreenState1 = LOW;
bool ledRedState2 = LOW;
bool ledGreenState2 = LOW;
//variables for system states
bool inState1 = HIGH;
bool inState2 = LOW;
bool inState3 = LOW;
bool inState4 = LOW;
bool buttonPressedInState1 = LOW;
// variables used for debounce
unsigned int lastDebounceTime = 0;
unsigned int debounceDelay = 50;
//variables for timers
unsigned long previousMillis = 0;
unsigned long lastBeepMillis = 0;
unsigned int timeState1 = 10000;
unsigned int timeState2 = 3000;
unsigned int timeState3 = 10000;
unsigned int timeState4 = 5000;
const int firstBeepInterval = 700;
const int secondBeepInterval = 300;


void setup() {
  //set input and output pins and initialize serial communication
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledRedPin1, OUTPUT);
  pinMode(ledYellowPin1, OUTPUT);
  pinMode(ledGreenPin1, OUTPUT);
  pinMode(ledRedPin2, OUTPUT);
  pinMode(ledGreenPin2, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // read the state of the switch into a local variable:
  reading = digitalRead(buttonPin);
  Serial.println(reading);
  // check to see if the button was pressed
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  //wait until debounceTime passed and keep the reading
  if ((millis() - lastDebounceTime) > debounceDelay) {
    
    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;
      
      // check if the button was press and the system is in first state      
      if (buttonState == LOW && inState1) {
        buttonPressedInState1 = !buttonPressedInState1;
        //reset the timer
        previousMillis = millis();
      }
    }
  }
  //save last reading
  lastButtonState = reading;

  if(inState1) {
    //light up leds from state1
    state1();
  }

  //if the button was pressed in state 1 and a time interval has passed
  if (buttonPressedInState1 && millis() - previousMillis > timeState1) {
    //switch lights to state 2
    inState1 = LOW;
    buttonPressedInState1 = !buttonPressedInState1;
    state2();
    inState2 = HIGH;
    //reset the timer
    previousMillis = millis();
  }

  //if system is in state 2 and a time interval has passed
  if(inState2 && millis() - previousMillis > timeState2) {
    //switch lights to state 3
    state3();
    inState2 = LOW;
    inState3 = HIGH;
    //reset the timer
    previousMillis = millis();
  }

  if(inState3) {
    //check if is time to change buzzer state
    if (millis() - lastBeepMillis >= firstBeepInterval) {
      lastBeepMillis = millis();
      // if the buzzer is off turn it on and vice-versa:
      if (buzzerState == LOW) {
        buzzerState = HIGH;
        tone(buzzerPin, buzzerTone, buzzerDuration);
      } 
      else {
        noTone(buzzerPin);
        buzzerState = LOW;
      }  
    }
    //if the system has been in state 3 for time interval 
    if (millis() - previousMillis > timeState3) {
    //switch lights to state 4
    state4();
    inState3 = LOW;
    inState4 = HIGH;
    //reset the timer
    previousMillis = millis();
    }
  }

  if(inState4) {
    if (millis() - lastBeepMillis >= secondBeepInterval) {
      //blink led and beep the buzzer at a certain interval
      lastBeepMillis = millis();
      // if the LED is off turn it on and turn off sound
      if (ledGreenState2 == LOW) {
        ledGreenState2 = HIGH;
        noTone(buzzerPin);
      } 
      else {
        // if the LED is on turn it off and turn on sound :
        ledGreenState2 = LOW;
        tone(buzzerPin, buzzerTone, buzzerDuration);
      }
    // set the LED with the ledGreenState2 of the variable:
    digitalWrite(ledGreenPin2, ledGreenState2);  
    }
    if (millis() - previousMillis > timeState4) {
    //if state 4 is finished, switch back to state 1
    state1();
    noTone(buzzerPin);
    inState4 = LOW;
    inState1 = HIGH;
    }
  }

}

//function to turn on only leds from state 1
void state1() {    
  digitalWrite(ledGreenPin1, HIGH);
  digitalWrite(ledRedPin2, HIGH);
  digitalWrite(ledGreenPin2, LOW);
  digitalWrite(ledRedPin1, LOW);
  digitalWrite(ledYellowPin1, LOW);
}

//function to turn on only leds from state 2
void state2() {
  digitalWrite(ledYellowPin1, HIGH);
  digitalWrite(ledRedPin2, HIGH);
  digitalWrite(ledGreenPin2, LOW);
  digitalWrite(ledGreenPin1, LOW);
  digitalWrite(ledRedPin1, LOW);
}

//function to turn on only leds from state 3
void state3() {
  digitalWrite(ledRedPin1, HIGH);
  digitalWrite(ledGreenPin2, HIGH);
  digitalWrite(ledGreenPin1, LOW);
  digitalWrite(ledYellowPin1, LOW);
  digitalWrite(ledRedPin2, LOW);
}

//function to turn on only leds from state 4
void state4() {
  digitalWrite(ledRedPin1, HIGH);
  digitalWrite(ledGreenPin2, LOW);
  digitalWrite(ledGreenPin1, LOW);
  digitalWrite(ledYellowPin1, LOW);
  digitalWrite(ledRedPin2, LOW);
}