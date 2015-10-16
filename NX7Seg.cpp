/*
||
|| @author Alexis Paques
|| @version 1.0
||
*/
#include <ASCIIDic.h>
#include "NX7Seg.h"

nx7seg::nx7seg(int latch, int clk, int data){
  latchPin  = byte(latch);
  clockPin  = byte(clk);
  dataPin = byte(data);
  for(int i=0;i < n_7seg; i++){
    buffer(i, 0xFF);
  }
}


void nx7seg::buffer(int n, byte in){
  buffer_data[n] = in;
}

void nx7seg::send(){
  for(int i=0;i < n_7seg; i++){
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, buffer_data[i]);
    shiftOut(dataPin, clockPin, MSBFIRST, digits[i] );
    digitalWrite(latchPin, HIGH);
  }
}

byte nx7seg::cypher(char value){
  int val = int(value);
  if(val >= 48 && val <= 57)
    return dic_numbers[val-48];
  if(val >= 65 && val <= 90)
    return dic_letters[val-65];
  if(val >= 97 && val <= 122)
    return dic_letters[val-97];
  if(val == 46)
    return dic_numbers[10];
  return 0xFF; 
}

void nx7seg::refresh(int time){
  time = time/2;
  for(int i=0;i < time; i++){
    send();
    delay(1);
  }
}

void nx7seg::write(char value[], int sizeArray){
  int posChar = 0;
  for(int i = 0; i< n_7seg; i++){
    // No overflow
    if(posChar == sizeArray)
      break;
    if(i == n_7seg)
      break;
      
    byte data = cypher(value[posChar]);
    
    // If we got a point for next value
    if(posChar+1 != sizeArray){
      if(value[posChar+1] == '.'){
        data = data & dic_numbers[10];
        posChar++;
      }
    }
    buffer(i, data);
    posChar++;
  }
}

void nx7seg::writeChar(char value, int digit, bool point){
  byte data = cypher(value);
  if(point)
    data = data & dic_numbers[10];
  buffer(digit, data);
}

/* Any INT */
void nx7seg::write(int value){
  // NOT IMPLEMENTED
}

/* Any FLOAT */
void nx7seg::write(float value){
  // NOT IMPLEMENTED
}

/* From 0 to 10 */
void nx7seg::writeDigit(int value, int digit, bool point){
  byte data = dic_numbers[value];
  if(point)
    data = data & dic_numbers[10];
  buffer(digit, data);
}
