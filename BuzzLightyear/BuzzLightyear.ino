// File: BuzzLightyear.ino
// Summary: Buzzer that plays a tune when it goes dark
// Version: 1.0
// Owner: Niklas Karlsson
// ---------------------------------------------------------------

#include "light.h"

// SETTINGS
// These variables are changable
// If you put the pins elsewhere
#define LIGHT_PIN A2    // Light sensor pin
#define POT_PIN A0      // Potentiometer for selecting songs
#define BUZ_PIN 5       // Buzzer pin
#define THRESHOLD 40    // When considered "dark"
#define WAIT_TIME 5     // In seconds (not milli)

// all the pins for 7-segment
// D1 to D4
int pinArray[4] = { 8, 9, 10, 11 };
// pin 14 shift register
int data = 4;
// pin 12 shift register
int latch = 3;
// pin 11 shift register
int shift = 2;
// For later on
int oldPot = 0, oldTime = millis();

// Potentiometer
Potentiometer Pot(POT_PIN);
// Buzzer tunes.
BuzzLightyear ls1(BUZ_PIN, LIGHT_PIN, THRESHOLD);
// For the 7-segmnet with 4 digits.
// We need the information to light up the led
Segment seg1(pinArray, data, latch, shift);


void setup()
{
  Serial.begin(9600);
  // less than 4, could be euqal to 3 aswell
  for (int i = 0; i < 4; i++)
  {
    // it had to be here.
    pinMode(pinArray[i], OUTPUT);
    digitalWrite(pinArray[i], HIGH);
  }

  // Pin the latch, shift and data
  pinMode(latch, OUTPUT);
  pinMode(shift, OUTPUT);
  pinMode(data, OUTPUT);

}

void loop()
{
  int nowTime;
  unsigned int number; // cant count zero or below anyway
  // globbal variable, callable outside the loop
  int pot = Pot.readValue();

  // Read value from potentiometer and wait 15 seconds
  // for the tune to play again.
  // when this plays everything else stops. And thats fine
  ls1.pickSong(pot, 15);
  // Lets take 3 second to read the last value
  if ((pot != oldPot) && ((nowTime - oldTime) >= 3000))
  {
    // Dont want it just to vanish.
    seg1.Display(pot);
    oldTime = millis();
  }
  else
  {
    // This will display the data on the 7-segment
    seg1.Display(ls1.readValue());
  }
}
