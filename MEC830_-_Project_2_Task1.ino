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
int k=0;
int step_num=0;
Servo servo;


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
  servo.attach(7);
  servo.write(90);
}

void loop() {

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
         //myStepper.step(100);
          previousCount = 0;
          Serial.println("Move Forward");
          while(k<500){
            OneStep(true);
            delay(2);
            k=k+1;
          }
          k=0;
          //task_1();
          
          }
        //Move Backwards  
        if(results.value == 0xFFA857){
          //myStepper.step(-100);
          previousCount = 0;
          Serial.println("Move Backwards");
          //task_1();
          while(k<500){
            OneStep(false);
            delay(2);
            k=k+1;
          }
          k=0;
          }
        //Move Right
        if(results.value == 0xFFC23D){
          Serial.println("Moving Right");
          servo.write(135);
          delay(10);
          }
        //Move Left
        if(results.value == 0xFF22DD){
          Serial.println("Moving Left");
          servo.write(45);
          delay(10);
          }
        if(results.value == 0xFF02FD){
          Serial.println("Straighten Wheel");
          servo.write(90);
          delay(10);
          }
        tmpValue = results.value;
      }
      else if(REPEAT==i)
      {
        results.value = tmpValue;
        Serial.println("Hi Daniel");
      }
    }
    irrecv.resume(); // receive the next value
  }
  
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




void task_1(){
  Serial.print("Previous Count =");
  Serial.println(previousCount);
}

void task_2(){}

void task_3(){}
