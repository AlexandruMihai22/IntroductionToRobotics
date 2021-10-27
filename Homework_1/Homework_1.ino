//variables for used pins and constant values
const int maxDutyCycle = 255;
const int maxVoltageValue = 1023;
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;
const int potPinRed = A2;
const int potPinGreen = A1;
const int potPinBlue = A0;
//variables to store the read value from the potentiometers
int potValueRed;
int potValueGreen;
int potValueBlue;
//variables to send brightness value to led
int ledValueRed;
int ledValueGreen;
int ledValueBlue;

void setup() {
  //set input and output pins and initialize serial communication
  pinMode(potPinRed, INPUT);
  pinMode(potPinGreen, INPUT);
  pinMode(potPinBlue, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  //store read value for each potentiometer
  potValueRed = analogRead(potPinRed);
  potValueGreen = analogRead(potPinGreen);
  potValueBlue = analogRead(potPinBlue);
  //map read values to analogWrite range
  ledValueRed = map(potValueRed, 0, maxVoltageValue, 0, maxDutyCycle);
  ledValueGreen = map(potValueGreen, 0, maxVoltageValue, 0, maxDutyCycle);
  ledValueBlue = map(potValueBlue, 0, maxVoltageValue, 0, maxDutyCycle);
  //set intensity of the led using mapped values
  analogWrite(redPin, ledValueRed);
  analogWrite(greenPin, ledValueGreen);
  analogWrite(bluePin, ledValueBlue);
}
