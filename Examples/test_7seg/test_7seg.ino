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
 


void testFloat(){
  float i;
  for(i = 1.235; i<15;i++){
    my4x7seg.writeFloat(i);
    my4x7seg.refresh(1000);
  }
  i += 0.5;
  for(; i>-15;i--){
    my4x7seg.writeFloat(i);
    my4x7seg.refresh(1000);
  }
}

void testInt(){
  my4x7seg.writeInt(-12346);
  my4x7seg.refresh(1000);
  my4x7seg.writeInt(46);
  my4x7seg.refresh(1000);
  my4x7seg.writeInt(-6);
  my4x7seg.refresh(1000);
  my4x7seg.writeInt(19969);
  my4x7seg.refresh(1000);
}

void testAlphabet(){
  char data[5];
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

/* Main program */
void loop()
{
  testAlphabet();
  testInt();
  testFloat();
}
