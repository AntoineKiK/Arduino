/* 
-------------------------------------------------------------------------------

Prünô (Prison Booze Noise Generator)
By Antoine KiK (Brigade Neurale)
http://www.cargocollective.com/kik


This project uses fermentation of a liquid to generate random sounds, with a tick every seconds.

-------------------------------------------------------------------------------

There are a few electronic parts : a led, speaker and wire only
The recipe for your fermentation product is really important to hear the difference at diferents state of the process

I used the Jarvis Master recipe "poem", I just changed the bread by some pastry yeast, to get something drinkable and chimically stable 

The code use Interupt mode, to pause every seconds the code and playback a sound.

This code uses the White Noise module of Sleepduino project by Gareth Halfacree
http://gareth.halfacree.co.uk/2012/02/introducing-the-sleepduino


*/

#include <avr/io.h>
#include <avr/interrupt.h>

#define LEDPIN 11

#define speakerPin 3

unsigned long int reg; // White noise variable

const int capteur = 19; // Analog Input 



int pruno[] = {0,0,255}; // Pruno values : current, min, max

int delayTone = 50; // Change note duration

int randoms[] = {0,0}; // Random variables to generate events

int counter[] = {0,0,0,0}; // Counter to create interactions

void setup()
{
  randomSeed(analogRead(0)); // Initialize a random seed to get real random numbers

Serial.begin(9600);

  pinMode(speakerPin, OUTPUT);

  // White Noise Variable
  reg = 0x55aa55aaL; //The seed for the bitstream. It can be anything except 0.

  pinMode(LEDPIN, OUTPUT); // Reacts to Pruno Sounds


// INTERUPT CODE for TIMER 1 - Tick every seconds

  // initialize Timer1
  cli();          // disable global interrupts
  TCCR1A = 0;     // set entire TCCR1A register to 0
  TCCR1B = 0;     // same for TCCR1B

  // set compare match register to desired timer count:
  OCR1A = 15624;
  // turn on CTC mode:
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler:
  TCCR1B |= (1 << CS10);
  TCCR1B |= (1 << CS12);
  // enable timer compare interrupt:
  TIMSK1 |= (1 << OCIE1A);
  // enable global interrupts:
  sei();

  // Fin config TIMER 1
}

void loop() {
  int  data = analogRead(capteur); // Read values from 5V and AnalogPin into the liquid
  

Serial.println(data);
  pruno[0] = map(data, 0, 1023,0, 255);
  delay(10+randoms[1]);
  if (pruno[0] > 200) { 
    counter[1]++; 
  }
  if ( 100 < pruno[0] < 199) { 
    counter[2]++; 
  }
  if (pruno[0] < 99) {
    counter[3]++; 
  }

  analogWrite(LEDPIN, randoms[0]);


  generateNoise();

  if (randoms[0] == counter[1] || pruno[0]) {
    counter[3]++;
    counter[2] = counter[2]*counter[1];
    counter[1] = 0;
    tone(speakerPin, 10000, randoms[0]);
    delay(1000);
  }

  if (data = 111*randoms[1] && randoms[0] == 66) {
    tone(speakerPin, 666, 666); 
    digitalWrite(LEDPIN, HIGH);
    delay(66);
    digitalWrite(LEDPIN, LOW);
  }

  if (randoms[0] < 10 || randoms[0] > 245) {
    tone(speakerPin, 100, 100);
    for (int i=0; i < 4;i++) {
    digitalWrite(LEDPIN, HIGH);
    delay(delayTone);
    digitalWrite(LEDPIN, LOW);
    }
  }

  if (counter[1] > 100) {
    tone(speakerPin, 7500, 200);
    counter[1] = 0; 
    delay(delayTone);
    delay(700);
  }
  if (counter[2] > 100 && counter[1] < 50) {
    tone(speakerPin, 8000, 200);
    counter[2] = 0; 
    delay(delayTone);
    delay(500);
  }
  if (counter[3] > 100 && counter[2] < 50) {
    tone(speakerPin, 5000, 200);
    counter[3] = 0; 
    delay(delayTone);
    delay(1000);
  }
  
}

ISR(TIMER1_COMPA_vect)
{ 
  counter[0]++;

  tone(speakerPin, 6440+pruno[0], delayTone);

  randoms[1] = random(1,7);
  randoms[0] = random (5, 255);

  if (counter[0] == randoms[1]) {
    tone(speakerPin, 7500, delayTone);

  }
}

void generateNoise(){
  unsigned long int newr;
  unsigned char lobit;
  unsigned char b31, b29, b25, b24;
  b31 = (reg & (1L << 31)) >> 31;
  b29 = (reg & (1L << 29)) >> 29;
  b25 = (reg & (1L << 25)) >> 25;
  b24 = (reg & (1L << 24)) >> 24;
  lobit = b31 ^ b29 ^ b25 ^ b24;
  newr = (reg << 1) | lobit;
  reg = newr;
  digitalWrite (speakerPin, reg & 1);
  if (pruno[0] > randoms[0]) {
    delayMicroseconds (pruno[0]+randoms[0]); // Changing this value changes the frequency.
  }
  else {
    delayMicroseconds(randoms[0] - pruno[0]);
  }

}




