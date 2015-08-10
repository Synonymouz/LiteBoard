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
    void begin(int rows, int columns, int sweepTime);
    void enableRedLED(int row, int column);
    void disableRedLED(int row, int column);
    void enableGreenLED(int row, int column);
    void disableGreenLED(int row, int column);
    void enableBlueLED(int row, int column);
    void disableBlueLED(int row, int column);
    void enableAllLEDs();
    void disableAllLEDs();
    void setLEDOutput(int LEDOutput[6][6][3]);
    boolean getMagnetInputAt(int column); // just takes column
    boolean * getMagnetInput(); // returns the state of all magnet switches
    void setSweepTime(int sweepTime);
    void sweep(); // sweeps pattern left to right and top down

  private:
  	// physical constants
  	int _sweepTime; // in milliseconds
  	int _rows;
  	int _columns;

  	// pins
  	// cathodes
  	int _columnPower[6] = {14, 15, 16, 17, 18, 19};
  	int _sensorPower[6] = {A8, A9, A10, A11, A12, A13};
  	// anodes
  	int _redGround[6] = {36, 34, 32, 30, 28, 26};
  	int _greenGround[6] = {8, 9, 10, 11, 12, 13};
  	int _blueGround[6] = {53, 51, 50, 49, 47, 45};
  	int _sensorGround[6] = {A0, A1, A2, A3, A4, A5};
  	
  	// input and output states of the board
  	int _LEDOutput[6][6][3] ; // [row, column, color(r,g,b)]
  	boolean _MagnetInput[6][6]; // [row, column]
};

#endif