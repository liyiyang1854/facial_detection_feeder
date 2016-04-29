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
  delay(10);
  Serial.setTimeout(10);
  SetPosition(1,1000);
  SetPosition(2,512);
  SetPosition(3,512);
  delay(1000);
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
  
    
    //count = 10;
    if (count == 10){
      //x= random(140,220);
      //y = random(70,105);
      Serial.print("x: ");
      Serial.println(x);
      Serial.print("y: ");
      Serial.println(y); 
      //Serial.println("small small small");
      
      //grab food
      Serial.println("grab food"); 
      //1. down
      Serial.println("down"); 
      for (int i = 512; i > 305; i--){
        SetPosition(3,i);
        SetPosition(2,512-(i-512));
        delay(8);
      }
      for (int i = 306; i > 99; i--){
        SetPosition(3,i);
        SetPosition(2,718-(306-i));
        delay(8);
      }
      for (int i = 512; i > 289; i--){
        SetPosition(2,i);
        if(100-(i-512)<251){SetPosition(3,100-(i-512));}
        delay(8);
      } 
      //SetPosition(2,290);
      //SetPosition(3,250);
    
      //2. grab
      Serial.println("grab");
      for (int i = 290; i > 269; i--){
        SetPosition(2,i);
        delay(10);
      }
      for (int i = 250; i < 651; i++){
        SetPosition(3,i);
        if (i%2 == 0){SetPosition(2,270-(i-250)/2);}
        delay(10);
      }
      //SetPosition(2,70);
      //SetPosition(3,650);
  
      //3. back  
      Serial.println("back");
      for (int i = 70; i > 61; i--){
        SetPosition(2,i);
        delay(10);
      }
      for (int i = 62; i < 512; i++){
        SetPosition(2,i);
        SetPosition(3,650-(i-62));
        delay(10);
      }
      /*
      for (int i = 200; i < 513; i++){
        SetPosition(3,i);  
        SetPosition(3,i);
        delay(10);
      }
      */
      
      //3. move to the position
      // start at (1000,512,200)
      /*
      Xmin, Xmax, Ymin, Ymax
      
      */
      
      
      //turn 
      
      delay(1000);
      Serial.println("turn1");
      int desire_turn_pos1 = 940 - x; // formula
      Serial.print("desure_turn_pos1: ");
      Serial.println(desire_turn_pos1); 
      for (int i = 1000; i > desire_turn_pos1; i--){
        //Serial.println("set 1");
        SetPosition(1,i);
        delay(10);
      }
      
      //move forward
      
      for (int i = 512; i > 480; i--){
        SetPosition(2,i);
        SetPosition(3,200+(512-i));
        delay(10);
      }
      
       Serial.println("turn3");
      int temp_turn3 = 430-1.43*y;
      int desire_turn_pos3 = (int) temp_turn3;
      Serial.print("desure_turn_pos3: ");
      Serial.println(desire_turn_pos3);
      for (int i = 232; i < desire_turn_pos3; i++){
        SetPosition(3,i);
        delay(10);
      }
      
      Serial.println("turn2");
      int desire_turn_pos2 = y + 352;
      Serial.print("desure_turn_pos2: ");
      Serial.println(desire_turn_pos2);
      for (int i = 480; i > desire_turn_pos2; i--){
        SetPosition(2,i);
        delay(10);
      }
      
     
      
      //4. hold for some time
      Serial.println("hold for 5 sec");
      delay(5000);
      
      //5. move back
      Serial.println("move back");
      for (int i = desire_turn_pos1; i < 1000; i++){
        SetPosition(1,i);
        delay(10);
      }
      
      if (desire_turn_pos2 < 512){
        for (int i = desire_turn_pos2; i < 512; i++){
          SetPosition(2,i);
          delay(10);
        }
      }
      else if (desire_turn_pos2 > 511){
        for (int i = desire_turn_pos2; i > 511; i--){
            SetPosition(2,i);
            delay(10);
         }
      }
      
      if (desire_turn_pos3 < 512){
        for (int i = desire_turn_pos3; i < 512; i++){
          SetPosition(3,i);
          delay(10);
        }
      }
      else if (desire_turn_pos3 > 511){
        for (int i = desire_turn_pos3; i > 511; i--){
            SetPosition(3,i);
            delay(10);
         }
      }
 
      
      
    }//count == 10
  
  //===============================================================
  //1. wait until the pos error is small
  //2. grab food
  //3. move to the position
  //4. hold for some time
  //5. move back
 // SetPosition(1,760);
  //SetPosition(2,420);
  //SetPosition(3,330);
}
