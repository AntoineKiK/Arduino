#include <MIDI.h>

// ATMEGA Power pins
// VCC (5V) : 7 & 20
// GROUND : 8 & 22

int led = 10; // Can be wired directly to 3,3 or 5V
int capteur = A0; // Photoresistor
// ATMEGA Chip pins : 23

int pot = A1; // Potentiometer to select octave / note range
// ATMEGA Chip pins : 24

int potDuration = A2; // control note duration - BPM
// ATMEGA Chip pins : 25

int speaker = 11; // speaker output
// ATMEGA Chip pins : 17

int midi = 12;
// ATMEGA Chip pins : 18

// MIDI configuration
int velocity = 100;
int channel = 1; 
// Buttons pinout
int butColors[8] = {
  2, 3, 4, 5, 6, 7, 8, 9}; 
  // ATMEGA Chip pins : 4, 5, 6, 11, 12, 13, 14, 15

// Note frequencies on seven Octaves + MIDI table for notes
int octOne[8] = {
  131, 147, 165, 175, 196, 220, 247, 0};

int midioctOne[8] = {
  24, 26, 28, 29, 31, 33, 35, 0};

int octTwo[8] = {
  262, 294, 330, 349, 392, 440, 494, 0};

int midioctTwo[8] = {
  36, 38, 40, 41, 43, 45, 47, 0 };

int octThree[8] = {
  524, 588, 660, 699, 784, 880, 988, 0};

int midioctThree[8] = {
  48, 50, 52, 53, 55, 57, 59, 0};

int octFour[8] = {
  1046, 1175, 1318, 1397, 1568, 1760, 1975, 0};

int midioctFour[8] = {
  60, 62, 64, 65, 67, 69, 71, 0};

int octFive[8] = {
  2093, 2349,  2637, 2794, 3136, 3520, 3951, 0};

int midioctFive[8] = {
  72, 74, 76, 77, 79, 81, 83, 0};

int octSix[8] = {
  4186, 4698, 5274, 5588, 6272, 7040, 7902, 0};

int midioctSix[8] = {
  84, 86, 88, 89, 91, 93, 95, 0};

int octSeven[8] = {
  8372, 9396, 10548, 11176, 12544, 14080, 15804, 0};

int midioctSeven[8] = {
  96, 98, 100, 101, 103, 105, 107, 0};


// Store values of different colors
int colors[8];

// Variables
int maxDelay = 200;

int thresold = 1; // Thresold to get a smoother reading of notes, especially if duration is < 10

void setup() {

  for (int i=0; i<8; i++) {

    pinMode(butColors[i], INPUT_PULLUP);
  }
  pinMode(led, OUTPUT);
  pinMode(capteur, INPUT);
  pinMode(pot, INPUT);
  pinMode(potDuration, INPUT);

  MIDI.begin(midi); 

}

void loop() {

  digitalWrite(led, HIGH);

  int duration = map(analogRead(potDuration), 0, 1023, 5, maxDelay); // Note length mapping

  int value = analogRead(capteur); // Photoresistor input color data

  int octPot = map(analogRead(pot), 0, 1023, 6, 0); // note octave mapping - Mapping is inverted because of the physical position of the potentiometer 

  Serial.print(duration); 
  Serial.print(","); 
  Serial.println(octPot);

  // Checking button state & calibrating colors
  for (int i=0; i<8; i++) {

    if (digitalRead(butColors[i]) == LOW) {

      colors[i] = value;

    }
  }

  // generate sound
  for (int i=0; i<8; i++) {

    int freq = 0;
    int octave = 0;
    switch(octPot) { // select octave / note range
    case 0 : 
      freq = octOne[i];
      octave = midioctOne[i];
      break;
    case 1 : 
      freq = octTwo[i];
      octave = midioctTwo[i];
      break;
    case 2 : 
      freq = octThree[i];
      octave = midioctThree[i];
      break;
    case 3 : 
      freq = octFour[i];
      octave = midioctFour[i];
      break;
    case 4 : 
      freq = octFive[i];
      octave = midioctFive[i];
      break;
    case 5 : 
      freq = octSix[i];
      octave = midioctSix[i];
      break;
    case 6 : 
      freq = octSeven[i];
      octave = midioctSeven[i];
      break;
    }

    if (value == colors[i] // Matching actual value of 
    || value + thresold == colors[i]
      || value - thresold == colors[i] 
      ) {

      tone(speaker, freq, duration); // generate sound based on the values of the selected octave and the lenght of the note
      MIDI.sendNoteOn(octave, velocity, channel);
      delay(maxDelay - duration); // the delay between two notes always correspond to max delay integer
      MIDI.sendNoteOff(octave, 0, channel);
     
    }
  }

}



