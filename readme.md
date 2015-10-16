Arduino ASCII Driver for 3641BS 4x 7 segments
=======================================

*Do not forget to include the ASCII Dictionary*

You are now able to drive your 3641BS 4 times 7 segments driven by two 595 shift registers easily.

Actually you only have the ability to write `char` and `char[]`. 

Commas are shown by a . directly in the last char.

Functions
--------

### nx7seg nx7seg(latch, clock, data)
Constructor : If you don't have a latch (not a 595 shift register), give a pin and don't use it. 

Latch could be named : RCLCK

Clock could be named : SCLK

### void buffer(digit, data)
Write a byte in the digits buffer

### void send()
Show the digit buffer on the 7 segment : Less than a millisecond. Use this if you are time dependant. Call it multiple times between time dependant steps to show the message.

### byte cypher(char)
Convert a char into a byte coded for the 7 segments

### void refresh(time = 500) // in ms
Show the digit buffer on the 7 segment during some time (in ms). It is approximative. It uses delay and nothing else is done.

### void write(char[], int sizeArray)
Write a char[] into the buffer array, coded by cypher. Specify the size array.

### void writeChar(char value, int digit, bool point = false);
Write a char into the buffer array, coded by cypher, at the digit wanted. If wanted, add a point.

### void writeDigit(int value, int digit, bool point = false);
Write a number (0 to 10) into the buffer array, coded by cypher, at the digit wanted. If wanted, add a point.

## TODO 
* Change the direction of the chars. Right to left instead of left to right for some 3641BS soldered differently.
* Add write(int) and write(float) functions

Credits
-------
Alexis Paques (@AlexisTM)