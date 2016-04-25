#include <ax12.h>

String stringread;
char nextByte;
int value;
int prev_value = 0;
int pos1;
int pos2;
int pos3;
int x;
int y;
int prev_x = 0;
int prev_y = 0;
char count = 0;
boolean small = 1;
boolean nextx = 0;


void setup(){
  //set up
  Serial.begin(38400);
  SetPosition(1,1000);
  SetPosition(2,512);
  SetPosition(3,200);
}


void loop(){
  //pos1 = GetPosition(1);
  //Serial.println("Get pos1");
  //Serial.println(pos1);
  //delay(100);
  //Serial.println("loop");
  
  if (Serial.available()){
    //Serial.println("serial available");
    nextByte = Serial.read();
    
    if (nextByte == ','){  
      nextx = 1;
      value = prev_value;
      prev_value = 0;
      Serial.print("x value is: ");
      Serial.println(value);
      x= value;
    }
    else if (nextByte == '.'){
      value = prev_value;
      prev_value = 0;
      Serial.print("y value is: ");
      Serial.println(value);
      y = value;
    }
    else{
      nextx = 0;
      prev_value = prev_value*10+nextByte-48; 
    }
  }
    /*
    //1. wait until the pos error is small
    if (nextx == 1){
      Serial.println("check error");
      if (abs(prev_x - x) > 8){
        Serial.println("not small");
        
        count = 0;
      }
      else{count ++;}
      prev_x = x;
    }
    */
    /*
    count = 3;
    if (count == 3){
      Serial.println("small small small");
      //2. grab food
      //set up
      SetPosition(1,1000);
      SetPosition(2,512);
      SetPosition(3,200);
      delay(1000);
      //1. move servo 2 to 330
      for (int i = 512; i >330; i--){
        SetPosition(2,i);
        delay(10);
      }
      //2. move servo 3 to get the food
      for (int i = 200; i < 400; i++){
        SetPosition(3,i);
        delay(10);
      }
      delay(1000);
      //3. move servo 2 back to 512 and servo 3 back to 200
      int j = 400;
      for (int i = 330; i < 512; i++){
        SetPosition(2,i);
        SetPosition(3,j);
        j--;
        delay(10);
      }
      
      
    }
    */
 // } // serial available
  
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
