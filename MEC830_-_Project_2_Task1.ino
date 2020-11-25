//MEC830 Project 2 - Edwin, Grady, Daniel, Albert
//Mobile Robot - 3 Tasks (Remote control, set path, obstacle avoidance)

//Libraries
#include <Servo.h>
#include <Stepper.h>
#include "IRremote.h"
#include "IR.h"

const int in1=9;
const int in2=10;
const int in3=11;
const int in4=12;

const int trigPin=6;
const int echoPin=5;


int k=0;
int step_num=0;
Servo servo;
int adj=5;
int ang1=83;
int ang2=83;
int Cangle;

//Ultrasonic Sensor


long duration;
double distance;





int RECEIVER2=13;

//IR Receiver and Remote Initialization
IRrecv irrecv(RECEIVER2);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

int revolutionSteps = 200;
int previousCount = 0;

Stepper myStepper(revolutionSteps, 7, 9, 8, 10);
//Servo myServo(5);

void setup() {
  
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode");
  irrecv.enableIRIn();
  myStepper.setSpeed(100);
  Serial.println("Robot Start");
  delay(100);

  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  servo.attach(7);
  servo.write(83);
}

void loop() {
 // Dist();
  //Receives input from remote
  int tmpValue;
  if (irrecv.decode(&results)) // have we received an IR signal?
  {
    //Serial.println(keyValue[0]);
    //Serial.println(results.value);
    //Serial.println(KEY_NUM);
    for (int i = 0; i < 23; i++)
    {
      //Serial.println(keyValue[i]);
      //Serial.println(results.value);
      if ((keyValue[i] == results.value) && (i<KEY_NUM))
      {
        //Move Forward
        if(results.value == 0xFF629D){
          Serial.println("Move Forward");
          FWD();
          delay(10);
          }
        //Move Backwards  
        if(results.value == 0xFFA857){
          Serial.println("Move Backwards");
          REV();
          delay(10);
          }
        //Move Right
        if(results.value == 0xFFC23D){
          Serial.println("Moving Right");
          ang2=ang2+adj;
          if (ang2>150){
            ang2=150;
          }
          Serial.println(ang2);
          servo.write(ang2);
          delay(10);
          }
        //Move Left
        if(results.value == 0xFF22DD){
          Serial.println("Moving Left");
          ang1=ang1-adj;
          if (ang1<30){
            ang1=30;
          }
          servo.write(ang1);
          delay(10);
          }
        if(results.value == 0xFF02FD){
          Serial.println("Straighten Wheel"); 
          servo.write(83);
          delay(10);
//          ang1=65;
//          ang2=115;
          ang1=83;
          ang2=83;
          }
        tmpValue = results.value;
      }
   
    }
    irrecv.resume(); // receive the next value
  }

  
}

void FWD(){
    while(k<2048/2){
    OneStep(true);
    delay(2);
    k=k+1;
    }
    k=0;
    Serial.println("FWD");
}

void REV(){
    while(k<2048/2){
    OneStep(false);
    delay(2);
    k=k+1;
    }
    k=0;
    Serial.println("REV");
}



void OneStep(bool dir){
  if(dir){
    switch(step_num){
      case 0:
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW);
      break;
      case 1:
      digitalWrite(in1,LOW);
      digitalWrite(in2,HIGH);
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW);
      break;
      case 2:
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);
      break;
      case 3:
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,HIGH);
      break;
    }
  }
  else{
      switch(step_num){
      case 0:
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,HIGH);
      break;
      case 1:
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);
      break;
      case 2:
      digitalWrite(in1,LOW);
      digitalWrite(in2,HIGH);
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW);
      break;
      case 3:
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW);
      break;
    }
  }
  step_num++;
  if(step_num>3){
    step_num=0;
  }
}


void Dist(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);

  duration=pulseIn(echoPin,HIGH);
  distance=duration*0.034/2;
  Serial.println(distance);
  if (distance ==1196){
    distance=0;
    
  }
}



void task_1(){
  Serial.print("Previous Count =");
  Serial.println(previousCount);
}

void task_2(){}

void task_3(){}
