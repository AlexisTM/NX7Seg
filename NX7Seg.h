/*
||
|| @author Alexis Paques
|| @version 1.0
||
*/
#ifndef nx7seg_H
#define NUMBER_OF_SEG 4
#define nx7seg_H

/* Since the 3641BS is a 4 digit, the precision should be 10000 */
#define N_DECIMAL_POINTS_PRECISION (1000) 

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class nx7seg {
  public:
    nx7seg( int latch, int clk, int data); 
    ~nx7seg(){};
    void buffer(int n, byte out);
    void send();
    byte cypher(char value);
    void refresh(int time = 500);
    void write(int value);
    void write(float value);
    void write(char value[], int sizeArray);
    void writeChar(char value, int digit, bool point = false);
    void writeDigit(int value, int digit, bool point = false);
      
  private:
    byte n_7seg = NUMBER_OF_SEG;
    byte latchPin;
    byte clockPin;
    byte dataPin;
    byte buffer_data[NUMBER_OF_SEG];
    const byte digits[NUMBER_OF_SEG] = {0xF1,0xF2,0xF4,0xF8};
};

#endif
