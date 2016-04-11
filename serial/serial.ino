#include <ax12.h>

String stringread;
char nextByte;
int value;
int prev_value = 0;
void setup(){

  Serial.begin(38400);


}

void loop(){
  
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
    
  
  }
}
