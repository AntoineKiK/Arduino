/* ATtiny85 - 1 Mhz - Internal Oscillator
KiK (Brigade Neurale)
http://www.cargocollective.com/kik
*/

int sensorPin = 3;    // select the input pin for the mic
int led1 = 0;
int led2 = 1;

/* ATTiny pins : 
sensorPin : Pin 2
led1 : Pin 5
led2 : Pin 6
*/

int sensorValue = 0;  // variable to store the value coming from the sensor

int thresold = 630;
void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(led1, OUTPUT);  
  pinMode(led2, OUTPUT);
  

}

void loop() {
     

  sensorValue = analogRead(sensorPin);    
  
  if (sensorValue > thresold) {
  int pwmVal = map(sensorValue, thresold, (thresold+150), 0, 127);
    analogWrite(led1, pwmVal);
    analogWrite(led2,0);
   delay(pwmVal/3);
    analogWrite(led2, pwmVal);
    analogWrite(led1,0);
    delay(pwmVal/3);
  }
  else {

  analogWrite(led1, 0);  
  
  analogWrite(led2, 0);
  
}
}
