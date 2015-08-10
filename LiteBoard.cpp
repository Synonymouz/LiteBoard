/*
  LiteBoard.h - Library using the Lite Board
  developed at the Edgerton Center for DEECS.
*/

#include "Arduino.h"
#include "LiteBoard.h"

LiteBoard::LiteBoard(){}

void LiteBoard::begin(int rows, int columns, int sweepTime) 
{
	_rows = rows;
	_columns = columns;
	_sweepTime = sweepTime;

	// set pinmodes
	for(int c = 0; c < columns; c++)
    {
    	pinMode(_columnPower[c], OUTPUT);
    	pinMode(_redGround[c], OUTPUT);
    	pinMode(_greenGround[c], OUTPUT);
    	pinMode(_blueGround[c], OUTPUT);
    	pinMode(_sensorPower[c], INPUT);
    	pinMode(_sensorGround[c], OUTPUT);
    	digitalWrite(_sensorPower[c], HIGH);
    }
    disableAllLEDs();
}

void LiteBoard::enableRedLED(int row, int column)
{
	digitalWrite(_redGround[row], LOW);
	digitalWrite(_columnPower[column], HIGH);
}

void LiteBoard::disableRedLED(int row, int column)
{
	digitalWrite(_redGround[row], LOW);
	digitalWrite(_columnPower[column], LOW);
}

void LiteBoard::enableGreenLED(int row, int column)
{
	digitalWrite(_greenGround[row], LOW);
	digitalWrite(_columnPower[column], HIGH);
}

void LiteBoard::disableGreenLED(int row, int column)
{
	digitalWrite(_greenGround[row], LOW);
	digitalWrite(_columnPower[column], LOW);
}

void LiteBoard::enableBlueLED(int row, int column)
{
	digitalWrite(_blueGround[row], LOW);
	digitalWrite(_columnPower[column], HIGH);
}

void LiteBoard::LiteBoard::disableBlueLED(int row, int column)
{
	digitalWrite(_blueGround[row], LOW);
	digitalWrite(_columnPower[column], LOW);
}

void LiteBoard::enableAllLEDs() 
{
	for(int r = 0; r < _rows; r++) 
	{
		digitalWrite(_redGround[r], LOW);
		digitalWrite(_greenGround[r], LOW);
		digitalWrite(_blueGround[r], LOW);
	}
	for(int c = 0; c < _columns; c++) 
	{
		digitalWrite(_columnPower[c], HIGH);
	}
}

void LiteBoard::disableAllLEDs() 
{
	for(int r = 0; r < _rows; r++) 
	{
		digitalWrite(_redGround[r], HIGH);
		digitalWrite(_greenGround[r], HIGH);
		digitalWrite(_blueGround[r], HIGH);
	}
	for(int c = 0; c < _columns; c++) 
	{
		digitalWrite(_columnPower[c], LOW);
	}
}

void LiteBoard::setLEDOutput(int LEDOutput[6][6][3])
{
	for(int r = 0; r < _rows; r++)
	{
		for(int c = 0; c < _columns; c++) 
		{
			for(int rgb = 0; rgb < 3; rgb++)
			{
				_LEDOutput[r][c][rgb] = LEDOutput[r][c][rgb];
			}
		}
	}
	
}

boolean LiteBoard::getMagnetInputAt(int column)
{
	if(digitalRead(_sensorPower[column]) == HIGH) 
	{
		return true;
	}
	else
	{
		return false;
	}
}

void LiteBoard::setSweepTime(int sweepTime)
{
	_sweepTime = sweepTime;
}

void LiteBoard::sweep()
{
	for(int r = 0; r < _rows; r++)
	{
		disableAllLEDs(); // wipe board
		for (int c = 0; c < _columns; c++)
		{
			// LED Control
			for (int rgb = 0; rgb < 3; rgb++) 
			{
				// turn on current row
				if(_LEDOutput[r][c][rgb] == 1 && rgb == 0) 
				{
					digitalWrite(_redGround[r], LOW);
					digitalWrite(_columnPower[c], HIGH);
				}
				else if(_LEDOutput[r][c][rgb] == 0 && rgb == 0) 
				{
					digitalWrite(_redGround[r], HIGH);
				}
				else if(_LEDOutput[r][c][rgb] == 1 && rgb == 1) 
				{
					digitalWrite(_greenGround[r], LOW);
					digitalWrite(_columnPower[c], HIGH);
				}
				else if(_LEDOutput[r][c][rgb] == 0 && rgb == 1) 
				{
					digitalWrite(_greenGround[r], HIGH);
				}
				else if(_LEDOutput[r][c][rgb] == 1 && rgb == 2) 
				{
					digitalWrite(_blueGround[r], LOW);
					digitalWrite(_columnPower[c], HIGH);
				}
				else if(_LEDOutput[r][c][rgb] == 0 && rgb == 2) 
				{
					digitalWrite(_blueGround[r], HIGH);
				}
			}

			// Magnet Control
			_MagnetInput[r][c] = getMagnetInputAt(c);
		}
		delay(_sweepTime); // delay for preset time
	}
}