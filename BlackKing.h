#pragma once
#include "BlackPiece.h"
#include "Piece.h"

class BlackKing : public BlackPiece {
private:
public:
	BlackKing(Coordinate coord);
	~BlackKing() {};

	void draw();
	void showMoves(bool jump = false);
};

