#ifndef _MOUSEHANDLING_H_
#define _MOUSEHANDLING_H_

typedef struct {
	int x;
	int y;
	int squarex;
	int squarey;
} Coordinate;

Coordinate getMouseCoordinate(LPARAM param);

#endif