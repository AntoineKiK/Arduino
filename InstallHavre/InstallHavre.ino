/* TETRIS Installation 
 
 June 10, 2014
 
 */

unsigned long time;


int counter[5] =  {
  10000, 20000, 50000, 5000, 20000};
// furby power trig, furby bend trig x2, toy silence,

int counterVal[5];

// FURBY

int furby[4] = { 
  11, 2, 3, 4};
// power, bend1, bend2

boolean furbyMAD1 = false;
boolean furbyMAD2 = false;

// TOYZ

int toyON[3] = {
  8, 9, 10}; // OUTPUT ON / OFF

const int toySound[3] = {
  A0, A2, A1}; // INPUT LISTENING

int toyValue[3] = {
  0, 0, 0};

int thresold[3] = {
  1, 1, 30}; // Analog Triggering

int potDelay = A4; // Delay between state change

int ctrlLED = 13;

boolean test = false;

void setup() {
  
  Serial.begin(9600);
  
  pinMode(ctrlLED, OUTPUT);
  
   randomSeed(analogRead(0)); // Initialize a random seed to get real random numbers

  for (int i=0; i<3; i++) {

    pinMode(furby[i], OUTPUT);

  }

  for (int i=0; i<3; i++) {

    pinMode(toyON[i], OUTPUT);

  }

  for (int i=0; i<2; i++) {
    pinMode(toySound[i], INPUT);
  }
    pinMode(potDelay, INPUT);

  
}

void loop () {
    // digitalWrite(furby[0], HIGH);

  
  
  for (int i=0; i<5; i++) {
  counterVal[i]++;
  }
  
  toyValue[0] = analogRead(toySound[0]); // Animals
  toyValue[1] = analogRead(toySound[1]); // Guitare
  
Serial.println(toyValue[0]);
Serial.println(toyValue[1]);

  int potValue = analogRead(potDelay);
   toyIN();

  furbyON(); // furby is reboot every x second to generate sounds 

//  furbyMadness();
  // COUNTERS : delay, bend 1 or 2, power


  // Analog Read of toys outputs
 
Serial.println(test);
  // Toy OUT
  toyJam();



}



void toyIN() { // Listening to sound from toys
  for (int i=0; i<1; i++) {
   
    if ( (toyValue[0] > thresold[0]) || (toyValue[1] > thresold[1])){
//      for (int i=0; i<3; i++) {
//      digitalWrite(toyON[i], HIGH); 
//      } 
      test = true;
//    digitalWrite(furby[0], LOW);
//    digitalWrite(ctrlLED, LOW);
    }
    else {
      test = false;
//      for (int i=0; i<3; i++) {
//      digitalWrite(toyON[i], LOW);
      
      } 
      
    }
  }


void furbyON() {

  if (test == false) {
    Serial.println("Furby talking");
    for (int i=0; i<3; i++) {
      digitalWrite(toyON[i], LOW);  
    }
    digitalWrite(furby[0], HIGH);
    
    int rando = random(1,15);
    
    if (rando < 4) {
    
    digitalWrite(furby[rando],HIGH);
    delay(300);
        digitalWrite(furby[rando],LOW);
    }
  
    digitalWrite(ctrlLED, HIGH);
    
    


  }
}


void toyJam() {
  if (test == true) {

    Serial.println("Toys playing");
    for (int i=0; i<3; i++) {
      digitalWrite(toyON[i], HIGH);
      digitalWrite(furby[i], LOW);
    }
      delay(200);

      
    }
        

  }


