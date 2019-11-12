#pragma once
#include <string>
#include "Board.h"
#include "stdafx.h"
#include "mousehandling.h"

#define UP -1
#define DOWN 1
#define LEFT -1
#define RIGHT 1

#define BLACK_ENEMY 'R'
#define RED_ENEMY 'B'

class Piece {
protected:
	Coordinate coord;
	bool mouseFocus;
public:
	Piece(Coordinate coord);
	Coordinate getCoordinate();
	virtual void draw() = 0;
	virtual void showMoves() = 0;
	void move(int squareX, int squareY);
	void hide();
	void lookDirection(int directX, int directY, char enemy, bool jump = false);
};
