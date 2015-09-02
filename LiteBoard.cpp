/*
  LiteBoard.h - Library using the Lite Board
  developed at the Edgerton Center for DEECS.
*/

#include "Arduino.h"
#include "LiteBoard.h"

LiteBoard::LiteBoard(){}

void LiteBoard::begin(int rows, int columns, int colors, int sweepTime, int cycleTime) 
{
	_rows = rows;
	_columns = columns;
	_colors = colors;
	_sweepTime = sweepTime;
	_cycleTime = cycleTime;

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
	_DisplayOutput.output[row][column][color] = 1;
}

void LiteBoard::disableLED(int row, int column, int color)
{
	_DisplayOutput.output[row][column][color] = 0;
}

void LiteBoard::enableAllLEDs() 
{
	for(int r = 0; r < _rows; r++)
	{
		for(int c = 0; c < _columns; c++) 
		{
			for(int l = 0; l < _colors; l++)
			{
				_DisplayOutput.output[r][c][l] = 1;
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
				_DisplayOutput.output[r][c][l] = 0;
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
				_DisplayOutput.output[r][c][l] = LEDOutput[r][c][l];
			}
		}
	}
	sweep();
}

void LiteBoard::cycleLEDOutput(int LEDOutput[6][6][3], int cycles)
{
	for(int r = 0; r < _rows; r++)
	{
		for(int c = 0; c < _columns; c++) 
		{
			for(int l = 0; l < _colors; l++)
			{
				_DisplayOutput.output[r][c][l] = LEDOutput[r][c][l];
			}
		}
	}
	cycle(cycles);
}

int LiteBoard::getMagnetInputAt(int row, int column)
{
	sweep();
	return _MagSwitch.input[row][column];
}

void LiteBoard::setSweepTime(int sweepTime)
{
	_sweepTime = sweepTime;
}

void LiteBoard::setCycleTime(int cycleTime)
{
	_cycleTime = cycleTime;
}

void LiteBoard::allOff()
{
	for(int i = 0; i < _rows; i++)
	{
		digitalWrite(_LEDRows[i][0], HIGH);
		digitalWrite(_LEDRows[i][1], HIGH);
		digitalWrite(_LEDRows[i][2], HIGH);
		digitalWrite(_LEDColumns[i], LOW);
	}
}

void LiteBoard::sweep()
{
  	for(int r = 0; r < _rows; r++)
  	{
  		digitalWrite(_MagColumns[r], HIGH);
  		for(int l = 0; l < _colors; l++)
  		{
  			allOff();
			digitalWrite(_LEDRows[r][l], LOW);
			for(int c = 0; c < _columns; c++)
			{
    			if(_DisplayOutput.output[c][r][l] == 1)
    			{
      				digitalWrite(_LEDColumns[c], HIGH);
    			}
    			else
    			{
					digitalWrite(_LEDColumns[c], LOW);
    			}
    			if(digitalRead(_MagRows[c]) == 1)
    			{
    				_MagSwitch.input[c][r] = 1;
    			}
    			else if(digitalRead(_MagRows[c]) == 0) 
    			{
    				_MagSwitch.input[c][r] = 0;
    			}
  			}
  			delay(_sweepTime);
  		}
  		digitalWrite(_MagColumns[r], LOW);
  	}
}

void LiteBoard::cycle(int cycles)
{
	for(int i = 0; i < cycles; i++)
	{
		sweep();
		delay(_cycleTime);
	}
}

DisplayOutput LiteBoard::getDisplayOutput()
{
	return _DisplayOutput;
}

MagSwitch LiteBoard::getMagnetInput()
{
	sweep();
	return _MagSwitch;
}