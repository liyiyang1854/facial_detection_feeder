/***************************
 * AXSimpleTest
 * This sketch sends positional commands to the AX servo 
 * attached to it - the servo must set to ID # 1
 * The sketch will send a value, i, to the servo.
 * 'For' loops are used to increment and decrement the value of 'i'
 ***************************/

//import ax12 library to send DYNAMIXEL commands
#include <ax12.h>

int pos;
void setup()
{
  
  // up & down
  SetPosition(1,0); //set the position of servo # 1 to '0'
  delay(100);//wait for servo to move
  SetPosition(2,200);
  SetPosition(3,512);
  /*
  
  //------------------------------------------
  //forward & backward
  SetPosition(2,680);
  SetPosition(3,60);
  delay(1000);
  */
  /*
  //------------------------------------------
  //speed control
  SetPosition(2,680);
  SetPosition(3,60);
  delay(1000);
  */
}

void loop()
{
  
  //------------------------------------------
  /*
  //speed control
  for(int i=680;i>199;i--)
  {
    SetPosition(2,i); //set the position of servo #1 to the current value of 'i'
    if (60+680-i<513){SetPosition(3,60+680-i);}
    delay(50);//wait for servo to move
  }
  for(int i=200;i<681;i++)
  {
    SetPosition(2,i); //set the position of servo #1 to the current value of 'i'
    if (512+200-i>59){SetPosition(3,512-(i-200));}
    delay(5);//wait for servo to move
  } 
  */
  /*
  //------------------------------------------
  //forward & backward
  for(int i=680;i>199;i--)
  {
    SetPosition(2,i); //set the position of servo #1 to the current value of 'i'
    if (60+680-i<513){SetPosition(3,60+680-i);}
    delay(10);//wait for servo to move
  }
  for(int i=200;i<681;i++)
  {
    SetPosition(2,i); //set the position of servo #1 to the current value of 'i'
    if (512+200-i>59){SetPosition(3,512-(i-200));}
    delay(10);//wait for servo to move
  } 
  */
  
  // up & down
  for(int i=200;i<357;i++)
  {
    SetPosition(2,i); //set the position of servo #1 to the current value of 'i'
    SetPosition(3,i+512-200);
    delay(10);//wait for servo to move
  }
  for(int i=356;i<513;i++)
  {
    SetPosition(2,i); //set the position of servo #1 to the current value of 'i'
    SetPosition(3,668+356-i);
    delay(10);//wait for servo to move
  } 
  for(int i=512;i>355;i--)
  {
    SetPosition(2,i); //set the position of servo #1 to the current value of 'i'
    SetPosition(3,512-(i-512));
    delay(10);//wait for servo to move
  }
  for(int i=356;i>200;i--)
  {
    SetPosition(2,i); //set the position of servo #1 to the current value of 'i'
    SetPosition(3,668+(i-356));
    delay(10);//wait for servo to move
  } 
  
  //------------------------------------------
  
}



