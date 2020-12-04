// File: melodies.h
// Summary: File where all the tunes are located
// Version: 1.0
// Owner: Niklas Karlsson
// ---------------------------------------------------------------

#include "tones.h"
/*
    Songs we use for to play
    I have not made any of these.
*/

/*
   Song1 - Take on me
*/
int song1_tempo[] =
{
  8, 8, 8, 4, 4, 4,
  4, 5, 8, 8, 8, 8,
  8, 8, 8, 4, 4, 4,
  4, 5, 8, 8, 8, 8
};

int song1_melody[] =
{
  NOTE_FS5, NOTE_FS5, NOTE_D5,
  NOTE_B4, NOTE_B4, NOTE_E5,
  NOTE_E5, NOTE_E5, NOTE_GS5,
  NOTE_GS5, NOTE_A5, NOTE_B5,
  NOTE_A5, NOTE_A5, NOTE_A5,
  NOTE_E5, NOTE_D5, NOTE_FS5,
  NOTE_FS5, NOTE_FS5, NOTE_E5,
  NOTE_E5, NOTE_FS5, NOTE_E5
};
int song1_dur = 1000;

/*
    Song2
*/
int song2_melody[] =
{
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_G5, NOTE_C5,
  NOTE_D5, NOTE_E5, NOTE_F5,
  NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_D5, NOTE_D5, NOTE_E5,
  NOTE_D5, NOTE_G5
};

int song2_tempo[] =
{
  8, 8, 4, 8, 8,
  4, 8, 8, 8, 8,
  2, 8, 8, 8, 8,
  8, 8, 8, 16, 16,
  8, 8, 8, 8, 4,
  4
};

int song2_dur = 1000;

/*
   Song3 - We wish you a merry Christmas
*/

int song3_melody[] = {
  NOTE_B3,
  NOTE_F4, NOTE_F4, NOTE_G4,
  NOTE_F4, NOTE_E4, NOTE_D4,
  NOTE_D4, NOTE_D4, NOTE_G4,
  NOTE_G4, NOTE_A4, NOTE_G4,
  NOTE_F4, NOTE_E4, NOTE_E4,
  NOTE_E4, NOTE_A4, NOTE_A4,
  NOTE_B4, NOTE_A4, NOTE_G4,
  NOTE_F4, NOTE_D4, NOTE_B3,
  NOTE_B3, NOTE_D4, NOTE_G4,
  NOTE_E4, NOTE_F4
};

int song3_tempo[] =
{
  4, 4, 8, 8, 8, 8,
  4, 4, 4, 4, 8, 8,
  8, 8, 4, 4, 4, 4,
  8, 8, 8, 8, 4, 4,
  8, 8, 4, 4, 4, 2
};

int song3_dur = 900;

int song4_melody[] =
{
  NOTE_G4, NOTE_E4, NOTE_F4,
  NOTE_G4, NOTE_G4, NOTE_G4,
  NOTE_A4, NOTE_B4, NOTE_C5,
  NOTE_C5, NOTE_C5, NOTE_E4,
  NOTE_F4, NOTE_G4, NOTE_G4,
  NOTE_G4, NOTE_A4, NOTE_G4,
  NOTE_F4, NOTE_F4, NOTE_E4,
  NOTE_G4, NOTE_C4, NOTE_E4,
  NOTE_D4, NOTE_F4, NOTE_B3,
  NOTE_C4
};

int song4_tempo[] =
{
  8, 8, 8, 4, 4,
  4, 8, 8, 4, 4,
  4, 8, 8, 4, 4,
  4, 8, 8, 4, 2,
  4, 4, 4, 4, 4,
  2, 4, 1
};

int song4_dur = 1000;
