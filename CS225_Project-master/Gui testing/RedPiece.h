#pragma once
#include "Piece.h"
#include "Board.h"
#include "stdafx.h"
#include "mousehandling.h"


class RedPiece : public Piece {
private:
	//Coordinate coord;
public:
	RedPiece(Coordinate coord);
	~RedPiece() {};

	void draw();
	void showMoves(bool jump = false);

};
