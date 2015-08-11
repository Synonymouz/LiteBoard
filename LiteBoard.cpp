/*
  LiteBoard.h - Library using the Lite Board
  developed at the Edgerton Center for DEECS.
*/

#include "Arduino.h"
#include "LiteBoard.h"

LiteBoard::LiteBoard(){}

void LiteBoard::begin(int rows, int columns, int colors, int sweepTime) 
{
	_rows = rows;
	_columns = columns;
	_colors = colors;
	_sweepTime = sweepTime;

	// set pinmodes
	for(int c = 0; c < _columns; c++)
  	{
    	for(int r = 0; r < _rows; r++)
    	{
      		for(int l = 0; l < _colors; l++)
      		{
		        pinMode(_LEDColumns[c],OUTPUT);
		        digitalWrite(_LEDColumns[c], LOW);
		        pinMode(_MagColumns[c],OUTPUT);
		        digitalWrite(_MagColumns[c], LOW);
		        pinMode(_LEDRows[r][l],OUTPUT);
		        digitalWrite(_LEDRows[r][l], HIGH);
		        pinMode(_MagRows[r],INPUT);
      		}
    	}
    }
}

void LiteBoard::enableLED(int row, int column, int color)
{
	_DisplayOutput[row][column][color] = 1;
}

void LiteBoard::disableLED(int row, int column, int color)
{
	_DisplayOutput[row][column][color] = 0;
}

void LiteBoard::enableAllLEDs() 
{
	for(int r = 0; r < _rows; r++)
	{
		for(int c = 0; c < _columns; c++) 
		{
			for(int l = 0; l < _colors; l++)
			{
				_DisplayOutput[r][c][l] = 1;
			}
		}
	}
}

void LiteBoard::disableAllLEDs() 
{
	for(int r = 0; r < _rows; r++)
	{
		for(int c = 0; c < _columns; c++) 
		{
			for(int l = 0; l < _colors; l++)
			{
				_DisplayOutput[r][c][l] = 0;
			}
		}
	}
}

void LiteBoard::setLEDOutput(int LEDOutput[6][6][3])
{
	for(int r = 0; r < _rows; r++)
	{
		for(int c = 0; c < _columns; c++) 
		{
			for(int l = 0; l < _colors; l++)
			{
				_DisplayOutput[r][c][l] = LEDOutput[r][c][l];
			}
		}
	}
}

int LiteBoard::getMagnetInputAt(int row, int column)
{
	return _MagSwitch[row][column];
}

void LiteBoard::setSweepTime(int sweepTime)
{
	_sweepTime = sweepTime;
}

void LiteBoard::sweep()
{
  	for(int c = 0; c < _columns; c++)
  	{
    	digitalWrite(_MagColumns[c], HIGH);
    	digitalWrite(_LEDColumns[c], HIGH);
    
    	for(int r = 0; r < _rows; r++)
    	{
      		for(int l = 0; l < _colors; l++)
      		{
        		if(_DisplayOutput[c][r][l] == 1)
        		{
          			digitalWrite(_LEDRows[r][l], LOW);
        		}
        		else
        		{
					digitalWrite(_LEDRows[r][l], HIGH);	
        		}
      		}

      		if(digitalRead(_MagRows[r]) == 1)
	      	{
	        	_MagSwitch[c][r] = 1;
	      	}
	      	else if(digitalRead(_MagRows[r]) == 0)
	      	{
	        	_MagSwitch[c][r] = 0;
	      	}
      	}

	    delay(_sweepTime);
	    digitalWrite(_MagColumns[c], LOW);
	    digitalWrite(_LEDColumns[c], LOW);
  	}
}