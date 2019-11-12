#include "mousehandling.h"
#include "Pieces.h"

Coordinate Piece::getCoordinate() {
	return coord;
}

void Piece::move(int squareX, int squareY) {
	this->coord.x = squareX;
	this->coord.y = squareY;
}
void Piece::hide() {
	board[coord.x][coord.y] = 'w';
}

void Piece::lookDirection(int directX, int directY, char enemy, bool jump) {
	int toLower = 'a' - 'A';


	//stores the current coordinate into a temporary vatirable for alteration
	Coordinate temp = coord;
	int x = temp.squarex;
	int y = temp.squarey;


	//test specified direction to see if there is an enemy piece to take
	if (board[y + directY][x + directX] == enemy || board[y + directY][x + directX] == (enemy + toLower)) {
		if (x + 2 * directX >= 0 && y + 2 * directY <= 8 && board[y + 2 * directY][x + 2 * directX] == 'w') {

			board[y + 2 * directY][x + 2 * directX] = 'p';
		}
		//do nothing
	}
	else if (!jump && board[y + directY][x + directX] == 'w') {
		board[y + directY][x + directX] = 'p';
	}
}

BlackPiece::BlackPiece(Coordinate coord) {
	this->coord = coord;
	draw();
}

void BlackPiece::draw() {
	board[coord.squarey][coord.squarex] = 'b';
}

void BlackPiece::showMoves(bool jump) {

	if (coord.squarex + LEFT >= 0 && coord.squarey + DOWN < 8) {
		//look lower left to see if moves are available
		board[1][1] = 'r';
		lookDirection(LEFT, DOWN, BLACK_ENEMY);
	}
	if (coord.squarex + RIGHT < 8 && coord.squarey + DOWN < 8) {
		//look lower right to see if moves are available
		board[0][0] = 'r';
		lookDirection(RIGHT, DOWN, BLACK_ENEMY);
	}

}

BlackKing::BlackKing(Coordinate coord) : BlackPiece(coord) {
	draw();
}

void BlackKing::draw() {
	board[coord.squarey][coord.squarex] = 'B';
}

void BlackKing::showMoves(bool jump) {

	if (coord.squarex + LEFT >= 0 && coord.squarey + DOWN < 8) {
		//look lower left to see if moves are available
		lookDirection(LEFT, DOWN, BLACK_ENEMY);
	}
	if (coord.squarex + RIGHT < 8 && coord.squarey + DOWN < 8) {
		//look lower right to see if moves are available
		lookDirection(RIGHT, DOWN, BLACK_ENEMY);
	}
	if (coord.squarex + LEFT >= 0 && coord.squarey + UP >= 0) {
		//look upper left to see if moves are available
		lookDirection(LEFT, UP, BLACK_ENEMY);
	}
	if (coord.squarex + RIGHT < 8 && coord.squarey + UP >= 0) {
		//look upper right to see if moves are available
		lookDirection(RIGHT, UP, BLACK_ENEMY);
	}
}

RedPiece::RedPiece(Coordinate coord) {
	this->coord = coord;
	draw();

}

void RedPiece::draw() {
	board[coord.squarey][coord.squarex] = 'r';
}

void RedPiece::showMoves(bool jump) {

	if (coord.squarex + LEFT >= 0 && coord.squarey + UP >= 0) {
		//look upper left to see if moves are available

		board[0][0] = 'b';
		lookDirection(LEFT, UP, RED_ENEMY);
	}
	if (coord.squarex + RIGHT < 8 && coord.squarey + UP >= 0) {
		//look upper right to see if moves are available
		board[0][1] = 'B';
		lookDirection(RIGHT, UP, RED_ENEMY);
	}
}


RedKing::RedKing(Coordinate coord) : RedPiece(coord) {
	draw();
}

void RedKing::draw() {
	board[coord.squarey][coord.squarex] = 'R';
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
