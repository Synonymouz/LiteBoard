/*
  LiteBoard.h - Library using the Lite Board
  developed at the Edgerton Center for DEECS.
					
			0,0		Columns
				  - - - - - -
				  - - - - - -
			Rows  - - - - - - 
				  - - - - - - 
				  - - - - - - 
				  - - - - - -

*/

#ifndef LiteBoard_h
#define LiteBoard_h

#include "Arduino.h"

struct DisplayOutput
{
  int output[6][6][3];
};
struct MagSwitch
{
  int input[6][6]; // [row, column]  
};

class LiteBoard
{
  public:
    // input and output states of the board
    LiteBoard();
    void begin(int rows, int columns, int colors, int sweepTime, int cycleTime);
    void enableLED(int row, int column, int color);
    void disableLED(int row, int column, int color);
    void enableAllLEDs();
    void disableAllLEDs();
    void setLEDOutput(int LEDOutput[6][6][3]);
    void cycleLEDOutput(int LEDOutput[6][6][3], int cycles);
    int getMagnetInputAt(int row, int column);
    void setSweepTime(int sweepTime);
    void setCycleTime(int cycleTime);
    DisplayOutput _DisplayOutput;
    MagSwitch _MagSwitch;
    DisplayOutput getDisplayOutput();
    MagSwitch getMagnetInput();

  private:
    void sweep(); // sweeps pattern left to right and top down
    void allOff();
    void cycle(int cycles);

  	// physical constants
  	int _sweepTime; // in milliseconds
    int _cycleTime;
  	int _rows;
  	int _columns;
    int _colors;

  	// pins
  	// Input
    int _MagColumns[6] = {A0, A1, A2, A3, A4, A5};
    int _MagRows[6] = {A8, A9, A10, A11, A12, A13};
  	// Output
    int _LEDColumns[6] = {14, 15, 16, 17, 18, 19};
    int _LEDRows[6][3]=
    {{36, 8, 43},
     {34, 9, 45},
     {32, 10, 47},
     {30, 11, 49},
     {28, 12, 51},
     {26, 13, 53}};
};

#endif