#pragma once
#include "Piece.h"
#include <string>
#include "Board.h"
#include "stdafx.h"
#include "mousehandling.h"

class Piece {
private:
	Coordinate coord;
	bool mouseFocus;
public:
	Piece(Coordinate coord);
	Coordinate getCoordinate();
	void draw(HWND wind);
	virtual void showMoves() = 0;
	void move(int squareX, int squareY);
	void hide(HWND wind);
};
