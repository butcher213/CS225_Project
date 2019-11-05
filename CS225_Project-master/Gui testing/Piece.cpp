#include "Piece.h"


Piece::Piece(Coordinate coord, HWND wind) {
	this->coord = coord;
	draw(wind);
	
}


Coordinate Piece::getCoordinate() { 
	return coord;
}

void Piece::hide(HWND wind) {
	HDC hdc = GetDC(wind);
	SetDCBrushColor(hdc, BLACK);
	Rectangle(hdc, coord.x, coord.y, coord.x + SQUARE_SIZE, coord.y + SQUARE_SIZE);
}