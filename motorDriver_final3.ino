// motor driver pins
int headPin = 3;
int bodyPin = 11;
int tom1 = 7;
int tom2 = 10; 
//pager motors pins
int rightArm = 4;
int leftArm = 5;
int tubeArm = 6;

//shield extra pins
int headDir = 13;
int bodyDir = 12;
int headBrake = 8;
int bodyBrake = 9;

//states
int headState = LOW;
int bodyState = LOW;
int tom1State = LOW;
int tom2State = LOW;
int gongState = LOW;
int rimState = LOW;
int tubeState = LOW;

//intervals
long bodyTime;
long gongTime;
long rimTime;
long headTime;
long tomTime;
long tubeTime;

//previousesesess
long body;
long gong;
long rim;
long head;
long tom;
long tube;

//state vars
boolean bodying;
boolean gonging;
boolean rimming;
boolean heading;
boolean tomming;
boolean tubing;


//overall time interval
long beats;

//controls
int pots[] = {
  A8, A9, A10, A11, A12, A13};
float potVal[6];

void setup(){
  Serial.begin(9600);
  pinMode(headDir, OUTPUT);
  pinMode(bodyDir, OUTPUT);
  pinMode(rightArm, OUTPUT);
  pinMode(leftArm, OUTPUT);
  pinMode(bodyPin, OUTPUT);
  pinMode(headPin, OUTPUT);
  pinMode(tom1, OUTPUT);
  pinMode(tom2, OUTPUT);
  pinMode(tubeArm, OUTPUT);

  for (int i=0;i<6;i++){
    pinMode(pots[i], INPUT_PULLUP);
    potVal[i] = 1;
  }

  digitalWrite(headBrake, LOW);
  digitalWrite(bodyBrake, LOW);
  beats = 1000;

  bodyTime = 200;
  gongTime = 100;
  rimTime = 100;
  headTime = 200;
  tomTime = 200;
  tubeTime = 200;

  body = 0;
  gong = 0;
  rim = 0;
  head = 0;
  tom = 0;
  tube = 0;

  heading = false;
  bodying = false;
  gonging = false;
  rimming = false;
  tomming = false;
  tubing = false;

}

void loop(){
  readPots();

  long unsigned current = millis();
  //*******!!!!!
  //COLONEL CLANK
  //*!*@@#)@*#$)@#)%@)

  //HEAD!!!!!-----BUCKET, BLACK HOLE?!
  if(current - head > potVal[0]){
    head = current;
    headState = HIGH;
    heading = true;
    digitalWrite(headDir, headState);   //Sets direction of CH A
    analogWrite(headPin, 255);   //Moves CH A
  }
  if(heading && current - head > headTime){
    heading = false;
    headState=LOW;

    digitalWrite(headDir, headState);   //Sets direction of CH A
    analogWrite(headPin, 255);   //Moves CH A
  }

  //TOM TOM!!! MARBLES?!
  if(current - tom > potVal[1]){
    tom = current;
    tom1State = HIGH;
    tom2State = LOW;
    tomming = true;
    digitalWrite(tom1, tom1State);   //Sets direction of CH A
    digitalWrite(tom2, tom2State);   //Moves CH A
  }
  if(tomming && current - tom > tomTime){
    tomming = false;
    tom1State = LOW;
    tom2State = HIGH;
    digitalWrite(tom1, tom1State);   //Sets direction of CH A
    digitalWrite(tom2, tom2State);   //Moves CH A
  }

  //TUUUUUUUUUBEEEE ARMM!!!!!
  if(current - tube > potVal[2]){
    tube = current;
    tubeState=HIGH;
    tubing = true;
    digitalWrite(tubeArm, tubeState);   //Sets direction of CH A
  }
  if(tubing && current - tube > tubeTime){
    tubing = false;
    tubeState=LOW;

    digitalWrite(tubeArm, tubeState);   //Sets direction of CH A

  }


  //________________________________________________
  //        GONGZILLA
  //________________________________
  //GONG!!!!!!!!!!
  if(current - gong > potVal[3]){
    gong = current;
    gongState=HIGH;
    gonging = true;
    digitalWrite(rightArm, gongState);   //Sets direction of CH A
  }
  if(gonging && current - gong > gongTime){
    gonging = false;
    gongState=LOW;

    digitalWrite(rightArm, gongState);   //Sets direction of CH A

  }
  //rimshoooootttt  
  if(current - rim > potVal[4]){
    rim = current;
    rimState=HIGH;
    rimming = true;
    digitalWrite(leftArm, rimState);   //Sets direction of CH A
  }
  if(rimming && current - rim > rimTime){
    rimming = false;
    rimState=LOW;

    digitalWrite(leftArm, rimState);   //Sets direction of CH A

  }

  //KICKDRUM!!!!!
  if(current - body > potVal[5]){
    body = current;
    bodyState = HIGH;
    bodying = true;

    digitalWrite(bodyDir, bodyState);   //Sets direction of CH A
    analogWrite(bodyPin, 255);   //Moves CH A
  }

  if(bodying && current - body > bodyTime){
    bodying = false;
    bodyState=LOW;

    digitalWrite(bodyDir, bodyState);   //Sets direction of CH A
    analogWrite(bodyPin, 255);   //Moves CH A

  }
}

void readPots(){
      for (int i=0;i<6;i++){
      float val = analogRead(pots[i]);
      float mappedVal = map(val, 14, 230, 6,100);
      potVal[i] = mappedVal/28 *beats;
    }
}


















