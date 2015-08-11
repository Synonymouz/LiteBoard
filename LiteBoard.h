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

class LiteBoard
{
  public:
    LiteBoard();
    void begin(int rows, int columns, int colors, int sweepTime);
    void enableLED(int row, int column, int color);
    void disableLED(int row, int column, int color);
    void enableAllLEDs();
    void disableAllLEDs();
    void setLEDOutput(int LEDOutput[6][6][3]);
    int getMagnetInputAt(int row, int column);
    void setSweepTime(int sweepTime);
    void sweep(); // sweeps pattern left to right and top down

  private:
  	// physical constants
  	int _sweepTime; // in milliseconds
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
    {{36, 8, 53},
     {34, 9, 51},
     {32, 10, 50},
     {30, 11, 49},
     {28, 12, 47},
     {26, 13, 45}};
  	
  	// input and output states of the board
  	int _DisplayOutput[6][6][3] ; // [row, column, color(r,g,b)]
  	int _MagSwitch[6][6]; // [row, column]
};

#endif