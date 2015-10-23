/*
||
|| @author Alexis Paques
|| @version 1.0
||
*/
#include <ASCIIDic.h>
#include "NX7Seg.h"

nx7seg::nx7seg(int latch, int clk, int data, bool _reverse){
  latchPin  = byte(latch);
  clockPin  = byte(clk);
  dataPin = byte(data);
  reverse = _reverse;
  clear();
}

void nx7seg::clear(){
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
    if(reverse)
      shiftOut(dataPin, clockPin, MSBFIRST, digits[n_7seg-1-i]);
    else
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
  if(val == 45)
    return dic_numbers[11];
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
  clear();
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
// Value : int to convert 
// Result : Char to store the result
// ToWrite : Limit of chars
char nx7seg::intToChars(int value, char* result, int toWrite){
  // Handle negative
  if(value < 0){
    toWrite--;
  }

  // Avoid overflow
  int MaxInt = ceil(log(abs(value))/log(10))+1;
  while(MaxInt > toWrite){
    value /= 10;
    MaxInt--;
  }
  
  // Print int to char
  dtostrf(value, toWrite, 0, result);
}

void nx7seg::writeInt(int value, int toWrite){
  char data[toWrite+1];
  intToChars(value, data, toWrite);
  write(data, toWrite);
}

/* Any FLOAT */
char nx7seg::floatToChars(float value, char* result, int toWrite){
  // Handle negative
  if(value < 0){
    toWrite--;
  }

  // Avoid overflow
  int MaxInt = ceil(log(abs(value))/log(10))+1;
  while(MaxInt > toWrite){
    value /= 10;
    MaxInt--;
  }

  int MaxFloat = toWrite-MaxInt;
  
  // Print int to char
  dtostrf(value, toWrite, MaxFloat, result);
}

void nx7seg::writeFloat(float value, int toWrite){
  toWrite++;
  char data[toWrite+1];
  floatToChars(value, data, toWrite);
  write(data, toWrite);
}

/* From 0 to 10 */
void nx7seg::writeDigit(int value, int digit, bool point){
  byte data = dic_numbers[value];
  if(point)
    data = data & dic_numbers[10];
  buffer(digit, data);
}
