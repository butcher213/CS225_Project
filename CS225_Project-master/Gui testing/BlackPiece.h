#pragma once
#include "Piece.h"
#include "BlackPiece.h"
#include "Board.h"
#include "stdafx.h"
#include "mousehandling.h"


class BlackPiece : public Piece {
private:
	Coordinate coord;
public:
	BlackPiece(Coordinate coord, HWND wind);
	~BlackPiece() {};

	void draw(HWND wind);
	void showMoves(HWND wind, Coordinate newCoord = this->coord,  bool jump = false);
	void move(int squareX, int squareY);


};
