#ifndef _BOARD_H_
#define _BOARD_H_

#define SQUARE_SIZE 64 // Pixels
#define PIECES_PER_PLAYER 12

// Globalschar board[8][8];

typedef enum state { TURN_START, SHOW_MOVES, CAPTURE_MOVES, SHOW_CAPTURE_MOVES } State;

void cleanBoard(void);
void updateFrame(HWND hwnd);

#endif