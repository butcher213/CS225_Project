#pragma once
#include "RedPiece.h"
#include "Piece.h"

class RedKing : public RedPiece {
private:
public:
	RedKing(Coordinate coord);
	~RedKing() {};

	void draw();
	void showMoves(bool jump = false);
};

