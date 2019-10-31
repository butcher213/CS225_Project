#include "Piece.h"
#include "BlackPiece.h"

extern char board[8][8];

BlackPiece::BlackPiece(Coordinate coord, HWND wind) : Piece(coord, wind) {
	board[coord.squarex][coord.squarey] = 'b';
}

void BlackPiece::draw(HWND wind) {
	HDC hdc = GetDC(wind);
	Ellipse(hdc, coord.x, coord.y, coord.x + SQUARE_SIZE, coord.y + SQUARE_SIZE);
}
void BlackPiece::showMoves( HWND wind,Coordinate newCoord, bool jump) {
	//bool movesAvailable = true;

	HDC hdc = GetDC(wind);
	SetDCBrushColor(hdc, RGB(0,100,8);

	Coordinate temp = newCoord;
	int x = temp.squarex;
	int y = temp.squarey;

	if (x - 1 < 0 || x + 1 > 8 || y + 1 > 8) {
		//guccigang
	}
	else {
		//test lowerLeft to see if piece is there to take
		if (board[y + 1][x - 1] == 'r' || board[y + 1][x - 1] == 'R') {
			if (x-2 >= 0 && y+2 <= 8 && board[x - 2][y + 2] == 'w') {
				temp.squarex -= 2;
				temp.squarey += 2;
				temp.x -= 2 * SQUARE_SIZE;
				temp.y += 2 * SQUARE_SIZE;
				Rectangle(hdc, temp.x, temp.y, temp.x + SQUARE_SIZE, temp.y + SQUARE_SIZE);
				this->showMoves(wind, temp, true);
			}
			//do nothing
		}
		else if (!jump && board[y + 1][x - 1] == 'w') {
			Rectangle(hdc, temp.x, temp.y, temp.x + SQUARE_SIZE, temp.y + SQUARE_SIZE);
		}

		//test lowerRight to see if piece is there to take
		if (board[y + 1][x + 1] == 'r' || board[y + 1][x + 1] == 'R') {
			if (x + 2 >= 0 && y + 2 <= 8 && board[x + 2][y + 2] == 'w') {
				temp.squarex += 2;
				temp.squarey += 2;
				temp.x += 2 * SQUARE_SIZE;
				temp.y += 2 * SQUARE_SIZE;
				Rectangle(hdc, temp.x, temp.y, temp.x + SQUARE_SIZE, temp.y + SQUARE_SIZE);
				this->showMoves(wind, temp, true);
			}
			//do nothing
		}
		else if (!jump && board[y + 1][x - 1] == 'w') {
			Rectangle(hdc, temp.x, temp.y, temp.x + SQUARE_SIZE, temp.y + SQUARE_SIZE);
		}
	}
	

}

void BlackPiece::move(int squareX, int squareY) {

}