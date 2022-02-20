/*
 This code is a basic implementation of a DTMF decoder for detecting the 16
 character DTMF code from the analog pin A0 and gives the decoded output by
 checking for all the Upper and lower tones in the DTMF matrix and gives us the
 corresponding number by turning on the corresponding digital bit for the
 numbers 0-9 and by Serially printing the rest of the characters. This work is
 entirely based on the Kevin Banks code found at
  http://www.embedded.com/design/embedded/4024443/The-Goertzel-Algorithm
  so full credit to him for his generic implementation and breakdown.
  The Goertzel algorithm is long standing so see
  http://en.wikipedia.org/wiki/Goertzel_algorithm for a full description.
  It is often used in DTMF tone detection as an alternative to the Fast
  Fourier Transform because it is quick with low overheard because it
  is only searching for a single frequency rather than showing the
  occurrence of all frequencies.
  * THIS CODE IS Made/modified by "Mian Mohammad Shoaib" and  Released into the
 public domain.
  * for any querries related to the code feel free to ask at

  MMSHOAIB8452@GMAIL.COM
 */

#include <Goertzel.h>

const int sensorPin = A0;

// number of samples to take
// adjust for sensitivity
// WARN: if large, it can slow the Arduino
const int N = 200;

// minimum tone amplitude to be detected
// adjust for senstivity
const float threshold = 1700.0;

// maximum detectable frequency is the sampling rate/2
// Arduino Uno with 16 Mhz can support sampling upto 8900 Hz
const float sampling_freq = 8900.0;

// initialize arrays high and low tone frequencies, associate with row and column numbers
const int high_frequencies[4] = {1209, 1336, 1477, 1633};
const int low_frequencies[4] = {697, 770, 852, 941};

const int numpad[4][4] = {
  {1, 2, 3, 10},
  {4, 5, 6, 11},
  {7, 8, 9, 12},
  {14, 0, 15, 13}
};

void setup()
{
  // initalize blink led that shows if any tone is detected
  pinMode(13, OUTPUT);

  // initialize 10 pins as output to show the dtmf outputs from 0 to 9
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  // unused LED; just initialized to make turning all LEDs off easier
  pinMode(12, OUTPUT);

  Serial.begin(9600);
}

void blink(int pin)
{
  digitalWrite(pin, HIGH);
  delay(250);
  digitalWrite(pin, LOW);
}

bool detect_tone(float freq)
{
  Goertzel goertzel = Goertzel(freq, N, sampling_freq);

  goertzel.sample(sensorPin);
  float magnitude = goertzel.detect();

  if (magnitude > threshold)
  {
    // blink(13);
    Serial.print(magnitude);
    Serial.print(" strength signal detected at ");
    Serial.print(freq);
    Serial.println(" Hz");
    return true;
  }
  else
  {
    return false;
  }
}

void print_number(int row, int column)
{
  int number = numpad[row][column];

  // if the number < 10, turn on corresponding LED
  if (number < 10)
  {
    digitalWrite((number + 2), HIGH);
    Serial.println(number);
  }
  else if (number == 10)
    Serial.println('A');
  else if (number == 11)
    Serial.println('B');
  else if (number == 12)
    Serial.println('C');
  else if (number == 13)
    Serial.println('D');
  else if (number == 14)
    Serial.println('*');
  else if (number == 15)
    Serial.println('#');

  // delay(100);
  for (int i = 2; i <= 12; i++)
  {
    digitalWrite(i, LOW);
  }
}

int get_high_tone() {
  while (1)
  {
    // Serial.println(analogRead(sensorPin));
    for (int column = 0; column < 4; column++) {
      if (detect_tone(high_frequencies[column]))
        return column;
    }
  }
}

int get_low_tone() {
  while (1)
  {
    for (int row = 0; row < 4; row++) {
      if (detect_tone(low_frequencies[row]))
        return row;
    }
  }
}

void loop()
{
  int column = get_high_tone();
  int row = get_low_tone();

  print_number(row, column);
}
