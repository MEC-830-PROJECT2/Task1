//MEC830 Project 2 - Edwin, Grady, Daniel, Albert
//Mobile Robot - 3 Tasks (Remote control, set path, obstacle avoidance)

//Libraries
#include <Servo.h>
#include <Stepper.h>
#include "IRremote.h"
#include "IR.h"

//IR Receiver and Remote Initialization
IRrecv irrecv(RECEIVER);     // create instance of 'irrecv'
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
          task_1();
          }
        //Move Backwards  
        if(results.value == 0xFFA857){
          //myStepper.step(-100);
          previousCount = 0;
          Serial.println("Move Backwards");
          task_1();
          }
        //Move Right
        if(results.value == 0xFFC23D){
          Serial.println("Moving Right");
          previousCount += 1;
          task_1();
          }
        //Move Left
        if(results.value == 0xFF22DD){
          Serial.println("Moving Left");
          previousCount -= 1;
          task_1();
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

void task_1(){
  Serial.print("Previous Count =");
  Serial.println(previousCount);
}

void task_2(){}

void task_3(){}
