# IntroductionToRobotics (2021 - 2022)
Introduction to Robotics laboratory homeworks, taken in the 3rd year at the Faculty of Mathematics and Computer Science, University of Bucharest. Each homework includes requirements, implementation details, code and image files.


## Homework 1

### Components

RBG led (1 minimum), potentiometers (3 minimum), resistors and wires (per logic).

### Technical Task

Use a separat potentiometer in controlling each of the color of the RGB led (Red, Green and Blue). The control must be done with digital electronics (aka you must read the value of the potentiometer with Arduino, and write a mapped value to each of the pins connected to the led.

### Setup
<img src="Homework_1/RGB1.jpeg" width= "500" >

<img src="Homework_1/RGB2.jpeg" width= "500" >

You can find the code [here](https://github.com/AlexandruMihai22/IntroductionToRobotics/blob/main/Homework_1/Homework_1.ino)

### Video
You can find a demo at: [youtube](https://www.youtube.com/shorts/NxNfzfaFPoc)

<br>

## Homework 2

### Components

5 LEDs, 1 button, 1 buzzer, resistors and wires (per logic)

### Technical Task

Building  the  traffic  lights  for  a  crosswalk.   Youwill use 2 LEDs to represent the traffic lights for people (red and green)and 3 LEDs to represent the traffic lights for cars (red, yellow and green).

The system has the following states:
1. State 1(default, reinstated after state 4 ends):  green light for cars,red  light  for  people,  no  sounds.   Duration:  indefinite,  changed  bypressing the button.
2. State 2(initiated by counting down 10 seconds after a button press):the  light  should  be  yellow  for  cars,  red  for  people  and  no  sounds.Duration:  3 seconds.
3. State 3(iniated after state 2 ends): red for cars, green for people anda beeping sound from the buzzer at a constant interval.  Duration:10 seconds.
4. State 4(initiated after state 3 ends):  red for cars,blinking greenfor people and a beeping sound from the buzzer, at a constant inter-val, faster than the beeping in state 3.

### Setup
You can find the code [here](https://github.com/AlexandruMihai22/IntroductionToRobotics/blob/main/Homework_2/Homework_2.ino)

### Video
You can find a demo at: [youtube](https://www.youtube.com/shorts/SMoA_wwZwWM)
