#include <iostream>
#include "stdafx.h"
#include <WindowsX.h>
#include "mousehandling.h"
#include "board.h"


Coordinate getMouseCoordinate(LPARAM param) {
	using namespace std;
	Coordinate coord;
	coord.x = GET_X_LPARAM(param);
	coord.y = GET_Y_LPARAM(param);
	coord.squarex = 0;
	coord.squarey = 0;
	for (int i = 1; i < 8; i++) {
		if (coord.x < i*SQUARE_SIZE) {
			coord.squarex = i-1;
			break;
		}
	}
	for (int i = 0; i < 8; i++) {
		if (coord.y < i*SQUARE_SIZE) {
			coord.squarey = i-1;
			break;
		}
	}
	return(coord);
}
