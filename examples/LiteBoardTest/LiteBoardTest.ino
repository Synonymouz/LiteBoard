#include <LiteBoard.h>

LiteBoard panel();
int chessPattern[6][6][3] = 
{{{1, 0, 0}, {0, 0, 0}, {1, 0, 0}, {0, 0, 0}, {1, 0, 0}, {0, 0, 0}},
 {{0, 0, 0}, {1, 0, 0}, {0, 0, 0}, {1, 0, 0}, {0, 0, 0}, {1, 0, 0}},
 {{1, 0, 0}, {0, 0, 0}, {1, 0, 0}, {0, 0, 0}, {1, 0, 0}, {0, 0, 0}},
 {{0, 0, 0}, {1, 0, 0}, {0, 0, 0}, {1, 0, 0}, {0, 0, 0}, {1, 0, 0}},
 {{1, 0, 0}, {0, 0, 0}, {1, 0, 0}, {0, 0, 0}, {1, 0, 0}, {0, 0, 0}},
 {{0, 0, 0}, {1, 0, 0}, {0, 0, 0}, {1, 0, 0}, {0, 0, 0}, {1, 0, 0}}};

void setup() 
{
	Serial.begin(19200);
	panel.begin(6, 6, 1);
	panel.setLEDOutput(chessPattern);
}

void loop() 
{
	panel.sweep();
	Serial.println(panel.getMagnetInput);
}