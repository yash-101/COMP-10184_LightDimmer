// 
//  I Yash Chaudhary, 000820480 certify that this material is my original work. 
//  No other person's work has been used without due acknowledgement.
//  I have not made my work available to anyone else."
// 
#include <Arduino.h> 

bool buttonOnOff; // false represent off and true represent on
int buttonPreviousState = 1;  // whether button is in pressed state or not. 0 represent IN pressed state and 1 represent not pressed

void setup() { 
  // configure the USB serial monitor 
  Serial.begin(115200); 
 
  // configure pin D5 as digital input - this is the pushbutton 
  pinMode(D5, INPUT_PULLUP); 

  // configure pin D4 as a digital output - this is the LED 
  pinMode(D4, OUTPUT); 
 
  // set default PWM range 
  analogWriteRange(1023);
  
  // Turned off at startup
  buttonOnOff = false;   
} 
 
 
void loop() { 

  int buttonPressed = digitalRead(D5); // 0 represent pressed state, 1 represent not pressed

  // Switch turn on/off logic when button pressed
  if(buttonPressed == 0 ){   
    // this check is to avoid switching recursivley when the button is in pressed state for long period (which is going to happen almost every time as a human we are not faster than computer)
    if(buttonPreviousState != 0){
      buttonOnOff = !buttonOnOff;
      buttonPreviousState = 0;  // mark the button in pressed state for next itteration
    }   
  } else { 
    buttonPreviousState = 1;
  }

  
  if(buttonOnOff){
    // read digitized value from the D1 Mini's A/D convertor
    int iVal = analogRead(A0);
    // set the PWM pulse width
    analogWrite(D4, iVal);
  } else{
      digitalWrite(D4, 1); // turned off
  }

  delay(1);
} 