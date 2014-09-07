
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <Keypad.h>

// DISPLAY INIT
Adafruit_PCD8544 display = Adafruit_PCD8544(3, 4, 5, 6, 7);


// KEYPAD INIT
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns


char keys[ROWS][COLS] = {
  {
    '0','1','2','3'          }
  ,
  {
    '4','5','6','7'          }
  ,
  {
    '8','9','A','B'          }
  ,
  {
    'C','D','E','F'          }
};

byte rowPins[ROWS] = {
  8, 9, 10, 12}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {
  14, 15, 16, 17}; //connect to the column pinouts of the keypad

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// VARIABLES INIT

boolean keyState[16]; // Check if button is pressed
int keyValue[16] = {
  0, 1, 1, 2, 2, 3, 3, 4, 1, 3, 4, 5, 6, 8, 6, 7}; // Value inspired by Sicherman Dice theory

int keyValue2[16] = {
  1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4}; 

int keyValue3[16] = {
  6, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 1, 2, 3};


int calcul;
int keyCount;

boolean keyHold[16];

boolean showMessage;


unsigned long loopCount;

void setup()   {

  display.begin(); // LCD display
  // init done

  // you can change the contrast around to adapt the display
  // for the best viewing!
  display.setContrast(31);
  display.setTextSize(0);


  pinMode(13, OUTPUT);
  randomSeed(analogRead(5));

//Serial.begin(9600);

}


void loop() {
      digitalWrite(13, LOW);


  while(millis() < 700) { 
    display.display();
display.clearDisplay();  // Clear screen
      display.println("Je vais vous");
     display.println("parler de");
     display.println("votre avenir");
     display.println("");
      display.println(" Touchez-moi!");
          display.display();


  }


  if (kpd.getKeys())
  {
    for (int i=0; i<LIST_MAX; i++)   // Scan the whole key list.
    {
      if ( kpd.key[i].stateChanged )   // Only find keys that have changed state.
      {
        switch (kpd.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
        case PRESSED:
          keyState[i] = true;
          break;

        case HOLD:
keyHold[i] = true;
    
  break;

        case RELEASED:
          keyState[i] = false;
          keyHold[i] = false;
          break;

        case IDLE:
          keyState[i] = false;
          keyHold[i] = false;
        }
    
      }

    }
  }

  for (int i = 0; i<16; i++) {

    if ((keyHold[i] == true) && (keyCount < 4)) {
      keyCount++;
   
int randNum = random(0, 2);

      switch(randNum) {
      case 0 :
        calcul += keyValue[i];
        break;
      case 1 : 
        calcul += keyValue2[i];
        break;
      case 2 : 
        calcul += keyValue3[i];
        break;
      
    }
    }
  }
  

  if (keyCount >= 3) {
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(75);
    digitalWrite(13, HIGH);
    delay(50);
    digitalWrite(13, LOW);
keyCount = 0;
    calcul += (random(0,12));
    showMessage = true;

  
    switch(calcul) {
      
default : 
              display.clearDisplay();  // Clear screen

      display.println("Fortune Not Found  Abort Retry Ignore ?");
      display.display();
      break;
      
    case 0 :
               display.clearDisplay();  // Clear screen

      display.println("A votre place je consulterai Madame SOLEIL");
      display.display();

      break;     
      
    case 1 :
                  display.clearDisplay();  // Clear screen

           display.println("Il faut aimer les pigeons pour comprendre mes predictions");
           display.display();

      break;       

    case 2 :
                   display.clearDisplay();  // Clear screen

      display.println("J existe car je m alimente");
      display.display();

      break;     

    case 3 :
                   display.clearDisplay();  // Clear screen

      display.println("Fortune Not Found  Abort Retry Ignore ?");
      display.display();

      break;     

    case 4 :
                   display.clearDisplay();  // Clear screen

      display.println("Vous perdez votre temps je ne peux rien faire pour vous");
      display.display();

      break;

    case 5 :
                  display.clearDisplay();  // Clear screen

        display.println("Vous pouvez");
        display.println("retenter votre");
       display.println("chance mais le");
      display.println("succes n est pas");
     display.println("garanti");
     display.display();
 break;


    case 6 :
                 display.clearDisplay();  // Clear screen

      display.println("Je vois"); 
                display.display(); 
      delay(800);
      display.println("...");
                 display.display();
      delay(300);
      display.println("Vous attendez");
     display.println("beaucoup");
    display.println("de moi");
     display.display();
 break;

    case 7 :
                   display.clearDisplay();  // Clear screen

       display.println("Utilisez vos  doigts vous en avez 10");   
   
     display.display();
 break;

    case 8 :
                display.clearDisplay();  // Clear screen

      display.println("Faites un voeu");
    
     display.display();
 break;

    case 9 :
                  display.clearDisplay();  // Clear screen

          display.println("Recommencez,");
         display.println("je ne peux");
         display.println("vous reveler");
         display.println("cet avenir");  

     display.display();
 break;

    case 10 :
                  display.clearDisplay();  // Clear screen

        display.println("Vous allez me donner");
       display.println("BEAUCOUP d'argent"); 
     display.println("$$$$$$$$$$$");  
  
     display.display();
 break;

    case 11 :
               display.clearDisplay();  // Clear screen

        display.println("N oubliez pas d acheter");
       display.println("du PAIN");   
 
    display.display();
  break;

   case 12 :
   
               display.clearDisplay();  // Clear screen

      display.println("J ai oublie maprediction, cane devait pas etre important"); 
    display.display();
  break;

    case 13 :
                 display.clearDisplay();  // Clear screen

         display.println("Vous allez");
         display.println("bientot vous");
        display.println("rapprocher de");
       display.println("Jean Pierre");
      display.println("Foucault");   

    display.display();
  break;

    case 14 :
                display.clearDisplay();  // Clear screen

        display.println("Tournez 3 foissur vous meme et recommencez");   
   
     display.display();
 break;

    case 15 :
                  display.clearDisplay();  // Clear screen

      display.println("Ce projet a");
      display.print("ete casse-tete"); 
      display.print("Ne vous prenez");
     display.print("pas la tete!");   
     display.display();
 break;


    case 16 :
                      display.clearDisplay();  // Clear screen

      display.println("Vous allez surFacebook");
     display.println("au travail");   
     display.display();
 break;

    case 17 :
                  display.clearDisplay();  // Clear screen

      display.println("On m'appelle  HAL, enfin");
     display.println("j aimerai bien");   
    display.display();
  break;

    case 18 :
                      display.clearDisplay();  // Clear screen

      display.println("Adafruit c estpas tres bien");   
    display.display();
  break;

    case 19 :
                      display.clearDisplay();  // Clear screen

      display.println("Mon createur");
     display.println("est KiK.");
    display.println("Et toi ?"); 
    display.println("Qui t'a cree ?");   
    display.display();
  break;

    case 20 :
                      display.clearDisplay();  // Clear screen

      display.println("Je n en peux plus ils me font travailler jour et nuit");   
display.display();
      break;

    case 21 :                  display.clearDisplay();  // Clear screen

      display.println("Je suis ton");
      display.println("pere...");
      display.println("Enfin presque");   
display.display();
      break;

    case 22 :
                      display.clearDisplay();  // Clear screen

      display.println("Vous avez atteint la derniere prediction BRAVO");   
display.display();
      break;
   }

  }
//  for (int i = 0; i<16 ; i++) {
//    keyHold[i] = false;
//    keyState[i] = false;
//    loopCount = 0;        
//  }
  

  

  while(showMessage == true) {
    for (int i = 0; i<16; i++) {
    
      if ((kpd.key[i].stateChanged) && (loopCount > 500)) {
            calcul = 0;
digitalWrite(13, HIGH);
    delay(150);
    digitalWrite(13, LOW);
    delay(125);
digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(75);
    digitalWrite(13, HIGH);
    delay(50);
    digitalWrite(13, LOW);        showMessage = false;  
        asm volatile ("  jmp 0");      
      } 
    }
    loopCount++;
    delay(50);
  }



}

