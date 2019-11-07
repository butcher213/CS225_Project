#include "RedKing.h"

extern char board[8][8];

RedKing::RedKing(Coordinate coord) : RedPiece(coord) {
	board[coord.squarex][coord.squarey] = 'b';
	draw();
}

void RedKing::draw() {
	board[coord.x][coord.y] = 'R';
}

void RedKing::showMoves(bool jump) {

	if (coord.squarex + LEFT >= 0 && coord.squarey + DOWN < 8) {
		//look lower left to see if moves are available
		lookDirection(LEFT, DOWN, RED_ENEMY);
	}
	if (coord.squarex + RIGHT < 8 && coord.squarey + DOWN < 8) {
		//look lower right to see if moves are available
		lookDirection(RIGHT, DOWN, RED_ENEMY);
	}
	if (coord.squarex + LEFT >= 0 && coord.squarey + UP >= 0) {
		//look upper left to see if moves are available
		lookDirection(LEFT, UP, RED_ENEMY);
	}
	if (coord.squarex + RIGHT < 8 && coord.squarey + UP >= 0) {
		//look upper right to see if moves are available
		lookDirection(RIGHT, UP, RED_ENEMY);
	}

}
