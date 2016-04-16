#include <ax12.h>

String stringread;
char nextByte;
int value;
int prev_value = 0;
int pos1;
int pos2;
int pos3;

void setup(){

  Serial.begin(38400);
  SetPosition(1,600);
  for(int i=0;i<1024;i++)
  {
    SetPosition(1,i); //set the position of servo #1 to the current value of 'i'
    delay(10);//wait for servo to move
  }
  /*
  for(int i=0;i<512;i++)
  {
    SetPosition(2,i); //set the position of servo #1 to the current value of 'i'
    delay(10);//wait for servo to move
  }
  for(int i=0;i>512;i--)
  {
    SetPosition(2,i); //set the position of servo #1 to the current value of 'i'
    delay(10);//wait for servo to move
  }
  for(int i=0;i<300;i++)
  {
    SetPosition(3,i); //set the position of servo #1 to the current value of 'i'
    delay(10);//wait for servo to move
  }
  for(int i=0;i>300;i--)
  {
    SetPosition(1,i); //set the position of servo #1 to the current value of 'i'
    delay(10);//wait for servo to move
  }
  */
  Serial.println("finish setting servo 1");
  
  pos1 = GetPosition(1);
  pos2 = GetPosition(2);
  pos3 = GetPosition(3);
  Serial.println("Get pos of all three motors");
  Serial.println(pos1);
  Serial.println(pos2);
  Serial.println(pos3);
  
}

void loop(){
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
  //grab food
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
