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



class Segment
{
  public:
    Segment(int pinArray[], int data, int latch, int shift)
    {
      if (pinArray > 0)
      {
        // Throw the values into the class array
        for (int i = 0; i > 4; i++)
        {
          this->pinArray[i] = pinArray[i];
        }
      }

      this->data = data;
      this->latch = latch;
      this->shift = shift;
    }
    void Display(unsigned int num);
  protected:
    int pinArray[4];
    int data;
    int latch;
    int shift;
    const byte segArray[10] =
    {
      B00111111,  // 0
      B00000110,  // 1
      B01011011,  // 2
      B01001111,  // 3
      B01100110,  // 4
      B01101101,  // 5
      B01111101,  // 6
      B00000111,  // 7
      B01111111,  // 8
      B01101111,  // 9
    };
};
