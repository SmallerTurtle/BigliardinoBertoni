#define ON     HIGH
#define OFF    LOW
#define NUM_OF_GND 4
#define PAUSE  400
#define MAX_SCORE 10
#define MAX_SET 2

typedef enum {LEFT, RIGHT, SIDES} SIDE;
typedef enum {SCORE, SET} LED_TYPE;

const int NUM_OF_LEDS = (MAX_SCORE + MAX_SET)*2;
const int LED_PER_GND = NUM_OF_LEDS/NUM_OF_GND;
const int GND_PIN[NUM_OF_GND] = {12,11,13,10};
const int CTRL_PIN[LED_PER_GND] = {2,3,4,5,6,7};
int score[SIDES];
int set[SIDES];
SIDE side;
int i,j;
int gndPin, ctrlPin;
int gndPinStatus[NUM_OF_GND];

void setup() {
  
  //set mode of pins for controlling ground voltage
  for(i=0; i< NUM_OF_GND; i++) {
    pinMode(GND_PIN[i], OUTPUT);
    digitalWrite(GND_PIN[i], OFF);
  }

  //set mode of pins of the LED sequence
  for(i = 0; i< LED_PER_GND; i++) {
    pinMode(CTRL_PIN[i], OUTPUT);
    digitalWrite(CTRL_PIN[i], LOW);
  }

  score[LEFT] =7;
  score[RIGHT] = 5;

  set[LEFT] = 0;
  set[RIGHT]= 0;
  

  digitalWrite(GND_PIN[i], ON);
  digitalWrite(CTRL_PIN[j], HIGH);

  Serial.begin(9600);

  side = LEFT;

}

void loop() {

  //set score1 according to potentiometer value

  //score1 = int(float(analogRead(A0) - 1)/1023 * (NPIN+1));
  //Serial.println(score1);

  

  for(i=0;i<score[side]; i++) {
    getPins(side, i, SCORE, &gndPin, &ctrlPin);
    digitalWrite(GND_PIN[gndPin], ON);
    digitalWrite(CTRL_PIN[ctrlPin], HIGH);
  }

  delay(PAUSE);

  for(i=0;i<MAX_SCORE; i++) {
    getPins(side, i, SCORE, &gndPin, &ctrlPin);
    digitalWrite(GND_PIN[gndPin], OFF);
    digitalWrite(CTRL_PIN[ctrlPin], LOW);
  }

  for(i=0;i<MAX_SET; i++) {
    getPins(side, i, SET, &gndPin, &ctrlPin);
    digitalWrite(GND_PIN[gndPin], OFF);
    digitalWrite(CTRL_PIN[ctrlPin], LOW);
  }

  
  for(i = 0; i < set[side]; i++) {
    getPins(side, i, SET, &gndPin, &ctrlPin);
    digitalWrite(GND_PIN[gndPin], ON);
    digitalWrite(CTRL_PIN[ctrlPin], HIGH);
  }

  delay(PAUSE);
  
  for(i=0;i<MAX_SCORE; i++) {
    getPins(side, i, SCORE, &gndPin, &ctrlPin);
    digitalWrite(GND_PIN[gndPin], OFF);
    digitalWrite(CTRL_PIN[ctrlPin], LOW);
  }

  for(i=0;i<MAX_SET; i++) {
    getPins(side, i, SET, &gndPin, &ctrlPin);
    digitalWrite(GND_PIN[gndPin], OFF);
    digitalWrite(CTRL_PIN[ctrlPin], LOW);
  }

  if(side == RIGHT) {
    side = LEFT;
  } else
    side = RIGHT;
  
}




void getPins(SIDE side, int ledIndex, LED_TYPE type, int* gndPin, int* ctrlPin) {
  
  if(type == SET)
    ledIndex = MAX_SCORE + ledIndex;
  if(side == LEFT) {
    *gndPin = 0;
  }
  else {
    *gndPin = NUM_OF_GND/2;
  }

  *gndPin += ledIndex/LED_PER_GND;

  *ctrlPin = ledIndex%LED_PER_GND;
}


