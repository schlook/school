// File: light.h
// Summary: Generic class for the function that handles buzzer and light
//   Just sound fun with Buzz Lightyear.. since its from the movie
//   Toy Story.
// Version: 1.0
// Owner: Niklas Karlsson
// ---------------------------------------------------------------

class BuzzLightyear
{
  public:
    BuzzLightyear(int buzzer, int lPin, int treshold)
    {
      // Assign the treshold
      this->treshold = treshold;
      // Assign the treshold
      this->buzzer = buzzer;
      this->lPin = lPin;
    }

    int pickSong(int song, int wait);
    void playSong(int melody[], int tempo[], int dur, int len);
    // To read in the value to the variable
    void readLight(void)
    {
      this->lightValue = analogRead(lPin);
    }
    // To return the value
    int readValue(void)
    {
      return this->lightValue;
    }
  protected:  // Can be callable from friend or inheritance.
    byte lPin;
    // Looks cleaner when the variables are stacked up
    // Rather than a long row.
    int buzzer;
    // Just so it register right away when loading
    long int lastPlayed = millis() * 15 * 1000;
    int treshold;
    int songPlayed = 0;
    int songLength;
    int lightValue;
    long int nowTime = millis();
};

/*
   Could be merged with the above class
   We can add multiple potentiometers tho
   So I kept this one
*/
class Potentiometer
{
  public:
    Potentiometer(byte pPin)
    {
      this->pPin = pPin;
    }

    int readValue(void)
    {
      this->potValue = analogRead(pPin);
      return map(potValue, 0, 1023, 0, 255);
    }

  protected:
    byte pPin;
    int potValue;
};
