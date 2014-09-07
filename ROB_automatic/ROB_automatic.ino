/* 
-------------------------------------------------------------------------------

Arduino R.O.B (Nintendo NES - Robotic Automatic Buddy)
By Antoine KiK (Brigade Neurale)
http://www.cargocollective.com/kik

Complete construction details will be published on my Website

The H Bridges are the 3 Chips labelled IR2C25 
By sending 5V on pin 1 and 4 you can control direction of one of the 3 motors

-------------------------------------------------------------------------------

There's a lot of LED and illuminations because the R.O.B I found was incomplete,
the front part of its face was missing so I put something on it and a lot of led behind

The code is published as it is, with all the mess !

You need 6 digital output to control the status of the motor, one for each direction
Left / Right - Up / Down - Open / Close the Claw
By changing state the integrated R.O.B H-Bridge choose the right direction
Careful if you don't use a joystick or controller, don't put HIGH Left and Right at the same time 
or do something in your code to prevent it.

R.O.B is also kind of "aware" of its position. There's a series of counter that check the approximate position 
of the robot. It's a bit unstable but it's working and that prevent the misuse of the robot.


Control the Nintendo Robot R.O.B with a NES controller. 
This code uses the library NES Pad by Rob Duarte
https://code.google.com/p/nespad/



*/
#include <NESpad.h>

//-----------
Nes pad variables
NESpad nintendo = NESpad(2,3,4);

byte state = 0;
//-----------

int tim = 35; // If you edit that delay() you'll have to reevaluate the limits

// Limits of the 3 R.O.B motors : 0, max Left/Right, max Up/Down, max Claw
int limit[4] = {0, 21, 45, 15};

// Counter for positions of the motors : Left/Right, Up/Down, Open / Close Claw
int count[3];

// Pins to control the motors
int ctrl[6] = {7,8,9,10,11,12};

// Head leds - 13 is for Eyes - The others control animations
int led[6] = {13,14,15,16,17,18};


void setup() {

  // ROB CONTROL  
  
  for (int i=0; i<6;i++) {
    pinMode(ctrl[i], OUTPUT);
  }

  // LED
for (int j=0; j<6; j++) {
  pinMode(led[j], OUTPUT);
}


}

void dance() {

int rand[3];  
  
rand[0] = random(limit[0], count[0]);
rand[1] = random(limit[0], count[1]);
rand[2] = random(limit[0], count[2]);

 center(); // Place R.O.B on center to get position (

  // RANDOM X
  

  digitalWrite(led[0], HIGH);
  
  digitalWrite(led[2], HIGH);
  
  digitalWrite(ctrl[4], HIGH);
  
  delay(tim*11*rand[0]);
  
  digitalWrite(led[2], LOW);
  
  digitalWrite(ctrl[4], LOW);
  
  digitalWrite(led[5], HIGH);
  
  digitalWrite(ctrl[5], HIGH);
  
  delay(tim*11*rand[0]);
  
  digitalWrite(ctrl[5], LOW);
  
  digitalWrite(led[5], LOW);

  // RANDOM Y
  digitalWrite(ctrl[1], HIGH);
  
  digitalWrite(led[0], HIGH);
  digitalWrite(led[2], HIGH);
  digitalWrite(led[5], HIGH);
  
  delay(tim*6*rand[1]);
  
  digitalWrite(ctrl[0], HIGH);
  
  digitalWrite(ctrl[1], LOW);
  
  digitalWrite(led[2], LOW);
  digitalWrite(led[5], LOW);
  
  delay(tim*6*rand[1]);
  
  digitalWrite(ctrl[0], LOW);

  // RANDOM CLAW
  digitalWrite(ctrl[2], HIGH);
  
  digitalWrite(led[0], HIGH);
  digitalWrite(led[2], HIGH);
  digitalWrite(led[5], HIGH);
  
  delay(tim*5*rand[2]);
  
  digitalWrite(ctrl[2], LOW);
  
  digitalWrite(ctrl[3], HIGH);
  
  delay(tim*5*rand[2]);
  
  digitalWrite(ctrl[3], LOW);
  
  digitalWrite(led[0], LOW);
  
  digitalWrite(led[2], LOW);
  
  digitalWrite(led[5], LOW);


  rand[0] = count[0];
  rand[1] = count[1];
  rand[2] = count[2];

}


// CYLON
void cylon() { 
  
   for (int i=1;i<6;i++) {
   digitalWrite(led[i], HIGH);
   delay(tim);
   digitalWrite(led[i + 1], HIGH);
   delay(tim);
   digitalWrite(led[i], LOW);
   delay(tim);
  }
  for (int j=6;j>1;j--) {
   digitalWrite(led[j], HIGH);
   delay(tim);
   digitalWrite(led[j - 1], HIGH);
   delay(tim);
   digitalWrite(led[j], LOW);
   delay(tim);

  }
  
}

void left() {
  
  digitalWrite(led[0], LOW);
  for (int i = 6; i>1; i--) {
    digitalWrite(led[i],HIGH);
    delay(tim);
    digitalWrite(led[i - 1], HIGH);
    delay(tim);
    digitalWrite(led[i], LOW);
    delay(tim);
    digitalWrite(led [i - 1], LOW);     
}

}

void right() {
    digitalWrite(led[0], LOW);
   for (int i=1;i<6;i++) {
   digitalWrite(led[i], HIGH);
   delay(tim);
   digitalWrite(led[i + 1], HIGH);
   delay(tim);
   digitalWrite(led[i], LOW);
   delay(tim);
   digitalWrite(led[i + 1], LOW);
   }
    
}

void up() {
  digitalWrite(led[0], LOW);
  
  for (int i=1; i<3; i++) {
  digitalWrite(led[i], HIGH);
  digitalWrite(led[i+(4/i)], HIGH);
  delay(tim);  
  digitalWrite(led[i], LOW);
  digitalWrite(led[i+(4/i)], LOW);
  delay(tim);
    }
    digitalWrite(led[3], HIGH);
    delay(tim);
   digitalWrite(led[3], LOW);

}

void down() {
  digitalWrite(led[0], LOW);
  
  digitalWrite(led[3], HIGH);
    delay(tim);
   digitalWrite(led[3], LOW);
  
  for (int i=2; i>0; i--) {
  digitalWrite(led[i], HIGH);
  digitalWrite(led[i+(4/i)], HIGH);
  delay(tim);  
  digitalWrite(led[i], LOW);
  digitalWrite(led[i+(4/i)], LOW);
  delay(tim);
    }

}

void panic() {
    digitalWrite(led[0], LOW);
  for(int i=1;i<6;i++) {
  digitalWrite(led[i], HIGH);
  }
  delay(tim);
  for (int j=1; j<6; j++) {
  digitalWrite(led[j],LOW);
  }
  delay(tim);
  
}

void center() {
  if (count[0] <= limit[1]/2) { // LEFT

    digitalWrite(ctrl[4], HIGH); 
    // LED
    digitalWrite(led[0], LOW);
    
    digitalWrite(led[1], HIGH);
    digitalWrite(led[5], HIGH);
    
    delay(tim*11*((limit[1]/2)-count[0]));
    
    digitalWrite(ctrl[4], LOW);
    count[0] = limit[1]/2;
  }
  if (count[0] >= limit[1]/2) { // RIGHT
    digitalWrite(ctrl[5], HIGH);
    // LED
    digitalWrite(led[0], LOW);
    
    digitalWrite(led[1], HIGH);
    digitalWrite(led[5], HIGH);  
    
    delay(tim*11*(count[0]-(limit[1]/2)));
    
    digitalWrite(ctrl[5],LOW);
    count[0]=limit[1]/2;
  }
  if (count[1] <= limit[2]/2) {  // DOWN
  
    digitalWrite(ctrl[0], HIGH);
    
    // LED
    digitalWrite(led[0], LOW);
    
    digitalWrite(led[2], HIGH);
    digitalWrite(led[4], HIGH);
    
    delay(tim*6*((limit[2]/2)-count[1]));
    digitalWrite(ctrl[0], LOW);
    count[1]=limit[2]/2;
  }
  if (count[1] >= limit[2]/2) { // UP
    digitalWrite(ctrl[1], HIGH);
    // LED
    digitalWrite(led[0], LOW);
    
    digitalWrite(led[2], HIGH);
    digitalWrite(led[4], HIGH);
    
    delay(tim*6*(count[1]-(limit[2]/2)));
    
    digitalWrite(ctrl[1],LOW);
    count[1]=limit[2]/2;
  }
  if (count[2] <= limit[3]/2) {  // A
    digitalWrite(ctrl[2], HIGH);
    // LED
    digitalWrite(led[0], LOW);
    digitalWrite(led[3], HIGH);
    delay(tim*5*((limit[3]/2)-count[2]));
    digitalWrite(ctrl[2], LOW);
    count[2]=limit[3]/2;
  }
  if (count[2] >= limit[3]/2) {  // B
    digitalWrite(ctrl[3], HIGH);
    // LED
    digitalWrite(led[0], LOW);
    digitalWrite(led[3], HIGH);
    delay(tim*5*(count[2]-(limit[3]/2)));
    
    digitalWrite(ctrl[3],LOW);
    count[2]=limit[3]/2;
  }
  
 for (int j=1; j<6; j++) {
  digitalWrite(led[j],LOW);
  }
}


void loop() {

  if (state != 0) {
    digitalWrite(led[0], LOW); 
  }
  else {
    digitalWrite(led[0], HIGH);
    
    for (int j=1; j<6; j++) {
  digitalWrite(led[j],LOW);
  }

  }

  state = nintendo.buttons();


  if (count[2] >= limit[3]) {
    digitalWrite(ctrl[2], LOW);
    count[2]=limit[3];  
  }
 
  else {
    digitalWrite(ctrl[2],  state & NES_A );
  }  
  if (count[2] <= limit[0] ) {
    count[2] = limit[0];
    digitalWrite(ctrl[3], LOW);
  }
  else {
    digitalWrite(ctrl[3], state & NES_B); 
  }  
  if (count[1] >= limit[2]) {
    count[1] = limit[2];
    digitalWrite(ctrl[0],  LOW);
  }
  else {
    digitalWrite(ctrl[0], state & NES_UP );
  }
  if (count[1] <= limit[0]) {
    count[1] = 0;
    digitalWrite(ctrl[1], LOW);
  }
  else {
    digitalWrite(ctrl[1], state & NES_DOWN );
  }
  if (count[0] >= limit[1]) {
    digitalWrite(ctrl[4], LOW);
  }
  else {
    digitalWrite(ctrl[4], state & NES_LEFT );
  }
  if (count[0] <= limit[0]) {
    digitalWrite(ctrl[5], LOW);
  }
  else {
    digitalWrite(ctrl[5], state & NES_RIGHT );
 
  }

  delay(1);

  if (state & NES_A && count[2] < limit[3]) {
    digitalWrite(led[2], HIGH);
    digitalWrite(led[5], HIGH);
    count[2]++;
    delay(100);
  }
  
  
  if (state & NES_B && count[2] > limit[0]) {
    digitalWrite(led[2], HIGH);
    digitalWrite(led[5], HIGH);
    count[2]--;
    delay(100);

  }

// Animations - LED + Unique moves

//A
if (state & NES_A && count[2] == limit[3]) {
  panic();
      digitalWrite(ctrl[2], LOW);
  
}

//B 
if (state & NES_B && count[2] == limit[0]) {
  panic();
      digitalWrite(ctrl[3], LOW);
}

//SELECT
  if (state & NES_SELECT) {
    center();
    cylon(); 
  }
  
// START  
  if (state & NES_START) {
    dance();
  }
  
// UP
if (state & NES_UP && count[1] < limit[2]) {
    up();
    count[1]++; 
  }
  
    if (state & NES_UP && count[1] == limit[2]) {
      panic();
    }

// DOWN
  if (state & NES_DOWN && count[1] > limit[0]) {
    down();
    count[1]--;
  }
   if (state & NES_DOWN && count[1] == limit[0]) {
     panic();
   }
  
//LEFT
if (state & NES_LEFT && count[0] < limit[1]) {
    left();
    count[0]++;
  }
  if (state & NES_LEFT && count[0] == limit[1]) {
    panic();
  }
// RIGHT   
  if (state & NES_RIGHT && count[0] > limit[0]) {
    right();
    count[0]--;
  }
  if (state & NES_RIGHT && count[0] == limit[0]) {
panic();
  }


}
