#pragma once
#include "Piece.h"
#include "BlackPiece.h"
#include "Board.h"
#include "stdafx.h"
#include "mousehandling.h"


class BlackPiece : public Piece {
private:
public:
	BlackPiece(Coordinate coord);
	~BlackPiece() {};

	void draw();
	void showMoves(bool jump = false);
};
