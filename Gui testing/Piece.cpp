#include <string>
#include "board.h"
#include "stdafx.h"



class Piece {
	int team;  //team 1 = 0; team 2 = 1;
	int x;    //each piece has a x and a y coordinate
	int y;    //
	bool isKing;    // boolean ture = king, false = regular piece;
public:
	int getTeam() { return team; }
	int getX() { return x; }
	int getY() { return y; }
	bool isKing() { return isKing; }
	
	void setX(int xChange) { x = xChange / SQUARE_SIZE; }
	void setY(int yChange) { y = yChange / SQUARE_SIZE; }
};