#ifndef _MOUSEHANDLING_H_
#define _MOUSEHANDLING_H_

class Coordinate {
public:
	int x;
	int y;
	int squarex;
	int squarey;
	Coordinate operator-(Coordinate coord);
	Coordinate operator+(Coordinate coord);
	Coordinate operator/(int div);
	void setHidden(void);
};

Coordinate getMouseCoordinate(LPARAM param);

#endif