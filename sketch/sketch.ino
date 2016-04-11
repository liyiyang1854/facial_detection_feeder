#include <Servo.h>
#include <Wire.h>

#define SRF_ADDRESS 0x70 //Address of the SRF08

Servo myservo1;
Servo myservo2;
char nextByte;
char direction = 'r';
bool ready = false;
int value = 0;
int miss = 0;
int prev_x = -1;
int prev_area = -1;
char stat;
unsigned long prev_time = 0;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  myservo1.attach(2);
  myservo1.write(0);
  myservo2.attach(12);
  myservo2.write(90);
  pinMode(3, OUTPUT);
  pinMode(13, INPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  analogWrite(3, 0);
}

void servo1_adjust(int val){
  int next_pos = myservo1.read() + val;
  if (next_pos < 0){
    next_pos = 0;
    direction = 'r';
  }  
  else if (next_pos > 160){
    next_pos = 160;
    direction = 'l';
  }
  myservo1.write(next_pos);
}

void servo2_adjust(){
  int next_pos = 180 - myservo1.read()*8/9.0;
  if (next_pos < 35){
    next_pos = 35;
  }  
  else if (next_pos > 145){
    next_pos = 145;
  }
  myservo2.write(next_pos);
}

void loop() {
  stat = digitalRead(13);
  if (Serial.available()){
    nextByte = Serial.read();
    if (nextByte == '.'){
      if (stat){
        miss += 1;
      }
    }
    else if (nextByte == ','){
      prev_x = value;
      value = 0;
    }
    else if (nextByte == '/'){
      prev_area = value;
      value = 0; 
    }
    /*else if (nextByte == ';'){
      myservo2.write(160);  
      prev_time = millis();
      while (millis() - prev_time < 1000){
        analogWrite(3, 255);
      }
      analogWrite(3, 0);
    }*/
    else {
      miss = 0;
      value = value*10 + nextByte - 48; 
    }
    
    if (stat && prev_area < 14000){
      digitalWrite(7, HIGH);
      digitalWrite(8, LOW);
      if (nextByte == '/'){
        ready = false;
        if ((myservo1.read() == 160 && prev_x > 320) || (myservo1.read() == 0 && prev_x < 320)){
          ready = true;  
        }
        else if (abs(prev_x - 320) < 20){
          ready = true;  
        }
        servo1_adjust((prev_x - 320)/(30+sqrt(32000/prev_area))); 
        servo2_adjust();
      }
      else if (miss > 35){
        ready = false;
        if (direction == 'r'){
          servo1_adjust(25);  
        }
        else if (direction == 'l'){
          servo1_adjust(-25); 
        }
        miss -= 35;
      }
      
      if (ready && miss < 5){
        analogWrite(3, 255); 
      }
      else{
        analogWrite(3, 0);
      }
    }
    else{
      digitalWrite(7, LOW);
      digitalWrite(8, HIGH);
      analogWrite(3, 0);
    }
  }
}
