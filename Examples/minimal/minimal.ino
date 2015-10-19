#include <ASCIIDic.h>
#include <NX7Seg.h>

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
}

void loop(){
  // use my4x7seg object
}

