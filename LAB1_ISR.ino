/*lab1 Program
 */
const int LEDB=10;
const int LEDG=9;
const int LEDR=8;
const int ButtonL=2;
const int ButtonR=3;
int Left=0;
int Right=0;

// test

volatile int State=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //BAUD RATE
  pinMode(ButtonL,INPUT_PULLUP);
  pinMode(ButtonR,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ButtonL),ISR_Lbutton,FALLING);
  attachInterrupt(digitalPinToInterrupt(ButtonR),ISR_Rbutton,FALLING);
  pinMode(LEDR,OUTPUT);
  pinMode(LEDG,OUTPUT);
  pinMode(LEDB,OUTPUT);
  State=0;
  digitalWrite(LEDR,HIGH);
  digitalWrite(LEDG,HIGH);
  digitalWrite(LEDB,HIGH);
}

//determine the state of the LEDs.
void loop() {
  // put your main code here, to run repeatedly:  
    if(State==1){
        digitalWrite(LEDR,LOW);
        digitalWrite(LEDG,LOW);
        digitalWrite(LEDB,LOW);
        delay(200);
        digitalWrite(LEDR,HIGH);
        delay(200);
        digitalWrite(LEDR,LOW);
    }
    else{
        if(State==2){
        digitalWrite(LEDG,LOW);
        digitalWrite(LEDR,LOW);
        digitalWrite(LEDB,LOW);
        delay(333);
        digitalWrite(LEDB,HIGH);
        delay(333);
        digitalWrite(LEDB,LOW);
        }
    }
  if(State==3){
      digitalWrite(LEDB,LOW);
      digitalWrite(LEDR,LOW);
      digitalWrite(LEDG,LOW);
      delay(500);
      digitalWrite(LEDG,HIGH);
      delay(500);
      digitalWrite(LEDG,LOW);
  }
    
}

//check if the opposite button was pressed or not
int CRight(int Status){
   Right=1;
   Right=digitalRead(ButtonR);
   delay(1000);
   if (Right==LOW){
      Status=3;
   }
   else{
      Status=1;  
   }
  return Status;
}
//check if the opposite button was pressed
int CLeft(int Status){
   Left=1;
   Left=digitalRead(ButtonL);
   delay(1000);
   if (Left==LOW){
      Status=3;
   }
   else{
      Status=2;  
   }
  return Status;
}



void ISR_Lbutton(){
  State=CRight(State);       
}
void ISR_Rbutton(){
  State=CLeft(State);  
}
