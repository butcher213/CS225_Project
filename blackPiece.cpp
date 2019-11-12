#include "Piece.h"
#include "BlackPiece.h"

extern char board[8][8];

BlackPiece::BlackPiece(Coordinate coord) : Piece(coord) {
	board[coord.squarex][coord.squarey] = 'b';
	draw();
}

void BlackPiece::draw() {
	board[coord.x][coord.y] = 'b';
}

void BlackPiece::showMoves(bool jump) {

	if (coord.squarex + LEFT >= 0 && coord.squarey + DOWN < 8) {
		//look lower left to see if moves are available
		lookDirection(LEFT, DOWN, BLACK_ENEMY);
	}
	if (coord.squarex + RIGHT < 8 && coord.squarey + DOWN < 8) {
		//look lower right to see if moves are available
		lookDirection(RIGHT, DOWN, BLACK_ENEMY);
	}
	
}
