// File: light.cpp
// Summary: Calculations is made here
// Version: 1.0
// Owner: Niklas Karlsson
// ---------------------------------------------------------------

#include "Arduino.h"    // For millis();
#include "light.h"      // For the class
#include "melodies.h"   // Our cute melodies

int BuzzLightyear::pickSong(int song, int wait)
{
  // debug(song, lastSong);
  long int nowTime = millis();
  readLight();
  // If turn on the potentiometer
  if ((lightValue > treshold) &&
      (songPlayed == 0) &&
      ((nowTime - lastPlayed) >= (wait * 1000)))
  {
    // This was not meant to be the main function but it takes up alot of
    // the work...
    // If somethings wrong. Check if the song is zero or less than zero
    // Since it's an int, it can be..
    if ((song == 0) || (song < 0))
    {
      songPlayed = 1;
      lastPlayed = millis();
    }
    // If pot stands between 1 and 49 then we play tis song
    else if ((song >= 0) && (song < 50))
    {
      songLength = sizeof(song1_melody) / sizeof(song1_melody[0]);
      playSong(song1_melody, song1_tempo, song1_dur, songLength);
      songPlayed = 1;
      lastPlayed = millis();
    }
    // If pot stands between 50 and 99 then we play tis song
    else if ((song >= 50) && (song < 100))
    {
      this->songLength = sizeof(song2_melody) / sizeof(song2_melody[0]);
      playSong(song2_melody, song2_tempo, song2_dur, songLength);
      this->songPlayed = 1;
      this->lastPlayed = millis();
    }
    // If pot stands between 100 and 149 then we play tis song
    else if ((song >= 100) && (song < 150))
    {
      this->songLength = sizeof(song3_melody) / sizeof(song3_melody[0]);
      playSong(song3_melody, song3_tempo, song3_dur, songLength);
      this->songPlayed = 1;
      this->lastPlayed = millis();
    }
    // If pot stands between 150 and 199 then we play tis song
    else if ((song >= 150) && (song < 200))
    {
      this->songLength = sizeof(song4_melody) / sizeof(song4_melody[0]);
      playSong(song4_melody, song4_tempo, song4_dur, songLength);
      this->songPlayed = 1;
      this->lastPlayed = millis();
    }
  }

  // If the light value is less than the treshold
  // then we can play the tune again.
  if (this->lightValue < this->treshold)
  {
    this->songPlayed = 0;
  }
}
/*
    Function to play the song.
    Accepts array of tones, array of tempo of each tones
    How long each tempo shall be and the song length.
*/
void BuzzLightyear::playSong(int melody[], int tempo[], int dur, int len)
{
  for (int thisNote = 0; thisNote < len; thisNote++)
  {
    // How long the sound shall be
    int duration = dur / tempo[thisNote];
    tone(buzzer, melody[thisNote], duration);
    // pause between notes
    int pause = duration * 1.3;
    delay(pause);
    // stop the tone
    noTone(buzzer);
  }
}


/*
    Segment functions goes right here aswell.
*/

void Segment::Display(unsigned int num)
{
/*
  // Turn off all
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(pinArray[i], LOW);
  }
*/
  // Could've looped it but wanted it to do it one by one.
  digitalWrite(pinArray[0], LOW);
  digitalWrite(latch, LOW);
  shiftOut(data, shift, MSBFIRST, segArray[num / 10]);
  digitalWrite(latch, HIGH);
   digitalWrite(pinArray[0], HIGH);
  delay(5);
  
  digitalWrite(pinArray[0], HIGH);
  digitalWrite(latch, LOW);
  shiftOut(data, shift, MSBFIRST, segArray[(num % 1000) / 100]);
  digitalWrite(latch, HIGH);
  delay(5);
  
  digitalWrite(pinArray[0], HIGH);
  digitalWrite(latch, LOW);
  shiftOut(data, shift, MSBFIRST, segArray[num % 100 / 10]);
  digitalWrite(latch, HIGH);
  delay(5);
  
  digitalWrite(pinArray[0], HIGH);
  digitalWrite(latch, LOW);
  shiftOut(data, shift, MSBFIRST, segArray[num % 10]);
  digitalWrite(latch, HIGH);
  delay(5);
}
