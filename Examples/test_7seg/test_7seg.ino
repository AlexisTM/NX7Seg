#include <ASCIIDic.h>
#include "NX7Seg.h"

#define LATCH_DIO 4
#define CLK_DIO 7
#define DATA_DIO 8

nx7seg my4x7seg = nx7seg(LATCH_DIO,CLK_DIO,DATA_DIO);
 
void setup ()
{
  /* Set DIO pins to outputs */
  pinMode(LATCH_DIO,OUTPUT);
  pinMode(CLK_DIO,OUTPUT);
  pinMode(DATA_DIO,OUTPUT);
  Serial.begin(9600);
}
 
/* Main program */
void loop()
{
  char data[5] = "a";
  int i=65;
  while( i<100 ) {
    for(int k=0; k<4;k++){
      data[k] = (char)(i);
      i++;
    }
    my4x7seg.write(data,4);
    my4x7seg.refresh(1500);
  }
}

