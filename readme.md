Arduino ASCII Driver for 3641BS 4x 7 segments
=======================================

## *Do not forget to include the [ASCII Dictionary](github.com/AlexisTM/ASCIIDic)*

You are now able to drive your 3641BS 4 times 7 segments driven by two 595 shift registers easily.

Actually you only have the ability to write `char` and `char[]`. 

Commas are shown by a . directly in the last char.

Example
---------


```C++
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

/* Main program */
void loop()
{
  my4x7seg.writeInt(46);
  my4x7seg.refresh(1000);
  my4x7seg.write("abcd",4);
  my4x7seg.refresh(1000);
  my4x7seg.writeFloat(i);
  my4x7seg.refresh(1000);
}
```


Functions
--------

### nx7seg nx7seg(int latch, int clock, int data, bool reverse = false)
Constructor : If you don't have a latch (not a 595 shift register), give a pin and don't use it. If the 7 segment is reverse, then gives the argument reverse to true.

Latch could be named : RCLCK

Clock could be named : SCLK

### void buffer(digit, data)
Write a byte in the digits buffer

### void clear()
Clear the 7 segment buffer

### void send()
Show the digit buffer on the 7 segment : Less than a millisecond. Use this if you are time dependant. Call it multiple times between time dependant steps to show the message.

### byte cypher(char)
Convert a char into a byte coded for the 7 segments

### void refresh(time = 500) // APPROXIMATIVE in ms
Show the digit buffer on the 7 segments during some time (in ms). It is approximative. It is a loop with delay(1), time times. Nothing can be done while showing numbers.

### void write(char[], int sizeArray = 4)
Write a char[] into the buffer array, coded by cypher. Specify the size array.

### void writeChar(char value, int digit, bool point = false);
Write a char into the buffer array, coded by cypher, at the digit wanted. If wanted, add a point.

### void writeDigit(int value, int digit, bool point = false);
Write a number (0 to 10) into the buffer array, coded by cypher, at the digit wanted. If wanted, add a point.

### void writeFloat(float value, int toWrite = 4)
Write the float value to 7 segment buffer. (refresh() or send() to show)

### void writeInt(int value, int toWrite = 4)
Write the float value to 7 segment buffer. (refresh() or send() to show)

## TODO 
* Change the direction of the chars. Right to left instead of left to right for some 3641BS soldered differently.

Credits
-------
Alexis Paques (@AlexisTM)
