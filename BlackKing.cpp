#include "BlackKing.h"

extern char board[8][8];

BlackKing::BlackKing(Coordinate coord) : BlackKing(coord) {
	board[coord.squarex][coord.squarey] = 'b';
	draw();
} 

void BlackKing::draw() {
	board[coord.x][coord.y] = 'B';
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
    if (coord.squarex + LEFT >= 0 && coord.squarey + UP >=0 ) {
        //look upper left to see if moves are available
        lookDirection(LEFT, UP, BLACK_ENEMY);
    }
    if (coord.squarex + RIGHT < 8 && coord.squarey + UP >= 0) {
        //look upper right to see if moves are available
        lookDirection(RIGHT, UP, BLACK_ENEMY);
    }

}
