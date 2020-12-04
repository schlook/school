// File: BuzzLightyear.ino
// Summary: Buzzer that plays a tune when it goes dark
// Version: 1.0
// Owner: Niklas Karlsson
// ---------------------------------------------------------------

#include "light.h"
#include <SevSegShift.h>

// SETTINGS
// These variables are changable
// If you put the pins elsewhere
#define LIGHT_PIN A2    // Light sensor pin
#define POT_PIN A0      // Potentiometer for selecting songs
#define BUZ_PIN 5       // Buzzer pin
#define THRESHOLD 40    // When considered "dark"
#define WAIT_TIME 5     // In seconds (not milli)
#define SHIFT_PIN_SHCP 2
#define SHIFT_PIN_STCP 3
#define SHIFT_PIN_DS   4
// For later on
int oldPot = 0, oldPet = 0, oldTime = millis();
int pot = 1, pet = 1;
int outPot; // the output
unsigned long nowTime = 0;

// Potentiometer
Potentiometer Pot(POT_PIN);
// Buzzer tunes.
BuzzLightyear ls1(BUZ_PIN, LIGHT_PIN, THRESHOLD);
// for the display
SevSegShift sevseg(SHIFT_PIN_DS, SHIFT_PIN_SHCP, SHIFT_PIN_STCP, 1, true);

void setup()
{
  Serial.begin(9600);

  byte numDigits = 4;
  byte digitPins[] = {11, 10, 9, 8}; // These are the PINS of the ** Arduino **
  byte segmentPins[] = {0, 1, 2, 3, 4, 5, 6, 7}; // these are the PINs of the ** Shift register **
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_CATHODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(100);
}

void loop()
{
  int n, rev = 0, remainder;
  int pot = Pot.readValue();
  int pet = ls1.readValue();
  ls1.pickSong(pot, 15);

  unsigned int number; // cant count zero or below anyway
  // globbal variable, callable outside the loop
  // Read value from potentiometer and wait 15 seconds
  // for the tune to play again.
  // when this plays everything else stops. And thats fine

  // Lets take 3 second to read the last value
  if ((int)pot != (int)oldPot)
  {
    if (millis() >= nowTime + 500)
    {
      outPot = pot;
      nowTime += 500;
    }
    if ((int)pot == (int)oldPot)
    {
      nowTime += 1500;
    }
    // Comparison so that we can read it
    oldPot = pot;
  }
  else if (pet != oldPet)
  {
    if (millis() >= nowTime + 500)
    {
      outPot = pet;
      nowTime += 500;
    }
    oldTime = millis();
    oldPot = pet;
  }

  sevseg.setNumber((int)reverse(outPot));
  sevseg.refreshDisplay();
}

int reverse(int n)
{
  int rev = 0, remainder;
  while (n != 0)
  {
    remainder = n % 10;
    rev = rev * 10 + remainder;
    n /= 10;
  }

  return rev;
}
