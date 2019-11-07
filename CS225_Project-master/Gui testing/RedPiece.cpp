#include "Piece.h"
#include "RedPiece.h"

extern char board[8][8];

RedPiece::RedPiece(Coordinate coord) : Piece(coord) {
	board[coord.squarex][coord.squarey] = 'b';
	draw();
	
}

void RedPiece::draw() {
	board[coord.x][coord.y] = 'r';
}

void RedPiece::showMoves(bool jump) {
	
	if (coord.squarex + LEFT >= 0 && coord.squarey + UP >= 0) {
		//look upper left to see if moves are available
		lookDirection(LEFT, UP, RED_ENEMY);
	}
	if (coord.squarex + RIGHT < 8 && coord.squarey + UP >= 0) {
		//look upper right to see if moves are available
		lookDirection(RIGHT, UP, RED_ENEMY);
	}
}
