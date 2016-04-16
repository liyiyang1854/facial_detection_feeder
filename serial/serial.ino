#include <ax12.h>

String stringread;
char nextByte;
int value;
int prev_value = 0;
int pos1;
int pos2;
int pos3;

void setup(){
  //set up
  Serial.begin(38400);
  SetPosition(1,1000);
  SetPosition(2,512);
  SetPosition(3,200);
}


void loop(){
  
  Serial.println("serial start");
  //SetPosition(1,0);
  pos1 = GetPosition(1);
  Serial.println("Get pos1");
  Serial.println(pos1);
  delay(100);
  /*
  if (Serial.available()){
    nextByte = Serial.read();
    
    if (nextByte == ','){  
      value = prev_value;
      prev_value = 0;
      Serial.print("x value is: ");
      Serial.println(value);
    }
    else if (nextByte == '.'){
      value = prev_value;
      prev_value = 0;
      Serial.print("y value is: ");
      Serial.println(value);
    }
    else{
       prev_value = prev_value*10+nextByte-48; 
    }
    
  } // serial available
  */
  //===============================================================
  //1. wait until the pos error is small
  //2. grab food
  //3. move to the position
  //4. hold for some time
  //5. move back
  
  /*
  SetPosition(1,0); // face the food
  for(int i=0;i<1024;i++)
  {
    SetPosition(1,i); //set the position of servo #1 to the current value of 'i'
    delay(10);//wait for servo to move
  }
  SetPosition(3,250);
  */
  //===============================================================
  /*
  SetPosition(1,512);
  SetPosition(2,512);
  SetPosition(3,512);
  */
  
}
