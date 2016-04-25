#include <ax12.h>


void setup(){
  //set up
  SetPosition(1,1000);
  SetPosition(2,512);
  SetPosition(3,512);
  delay(1000);
}

void loop(){
  //grab food 
  //1. down
  for (int i = 512; i > 305; i--){
    SetPosition(3,i);
    SetPosition(2,512-(i-512));
    delay(5);
  }
  for (int i = 306; i > 99; i--){
    SetPosition(3,i);
    SetPosition(2,718-(306-i));
    delay(5);
  }
  for (int i = 512; i > 289; i--){
    SetPosition(2,i);
    if(100-(i-512)<251){SetPosition(3,100-(i-512));}
    delay(5);
  } 
  //SetPosition(2,290);
  //SetPosition(3,250);
  
  //2. grab
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
  for (int i = 70; i > 61; i--){
    SetPosition(2,i);
    delay(10);
  }
  for (int i = 62; i < 512; i++){
    SetPosition(2,i);
    SetPosition(3,650-(i-62));
    delay(10);
  }
  for (int i = 200; i < 513; i++){
    SetPosition(3,i);
    SetPosition(3,i);
    delay(10);
  }
  //SetPosition(2,512);
  //SetPosition(3,200);
}
