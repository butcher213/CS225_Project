#include "Piece.h"

extern char board[8][8];

Piece::Piece(Coordinate coord) {
	this->coord = coord;
}

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
		if (x + 2*directX >= 0 && y + 2*directY <= 8 && board[x + 2*directX][y + 2*directY] == 'w') {
			
			board[x + 2 * directX][y + 2 * directY] == 'p';
		}
		//do nothing
	}
	else if (!jump && board[y + directY][x + directX] == 'w') {
		board[y + directY][x + directX] == 'p';
	}
}
