#include "stdafx.h"
#include "board.h"

extern char board[8][8];

void cleanBoard(void) {
	for (int row = 0; row < 8; row++) {
		for (int column = 0; column < 8; column++) {
			if (board[column][row] == 'p') {
				board[column][row] = 'w';
			}
			else if (board[column][row] == 'q') {
				board[column][row] = 'r';
			}
			else if (board[column][row] == 'Q') {
				board[column][row] = 'R';
			}
			else if (board[column][row] == 'k') {
				board[column][row] = 'b';
			}
			else if (board[column][row] == 'K') {
				board[column][row] = 'B';
			}
		}
	}
}

void updateFrame(HWND hwnd) {
	HDC hdc = GetDC(hwnd);

	SelectObject(hdc, GetStockObject(DC_BRUSH));
	int squareCount = 0;
	for (int row = 0; row < 8; row++) {
		for (int column = 0; column < 8; column++) {
			if (squareCount % 2 != 0) {
				SetDCBrushColor(hdc, RGB(0, 0, 0));
			}
			else {
				SetDCBrushColor(hdc, RGB(255, 255, 255));
			}

			Rectangle(hdc, row * SQUARE_SIZE, column * SQUARE_SIZE, row * SQUARE_SIZE + SQUARE_SIZE, column*SQUARE_SIZE + SQUARE_SIZE);
			

			COLORREF sqColor = GetDCBrushColor(hdc);
			switch (board[column][row]) {
				case 'q':
					SetDCBrushColor(hdc, RGB(10, 180, 10));
					Rectangle(hdc, row * SQUARE_SIZE, column * SQUARE_SIZE, row * SQUARE_SIZE + SQUARE_SIZE, column*SQUARE_SIZE + SQUARE_SIZE);
				case 'r':
					SetDCBrushColor(hdc, RGB(255, 0, 0));
					Ellipse(hdc, row * SQUARE_SIZE+3, column * SQUARE_SIZE+3, row * SQUARE_SIZE + SQUARE_SIZE-3, column*SQUARE_SIZE + SQUARE_SIZE-3);
					break;
				case 'k':
					SetDCBrushColor(hdc, RGB(10, 180, 10));
					Rectangle(hdc, row * SQUARE_SIZE, column * SQUARE_SIZE, row * SQUARE_SIZE + SQUARE_SIZE, column*SQUARE_SIZE + SQUARE_SIZE);
				case 'b':
					SetDCBrushColor(hdc, RGB(0, 0, 0));
					Ellipse(hdc, row * SQUARE_SIZE+3, column * SQUARE_SIZE+3, row * SQUARE_SIZE + SQUARE_SIZE-3, column*SQUARE_SIZE + SQUARE_SIZE-3);
					break;
				case 'Q':
					SetDCBrushColor(hdc, RGB(10, 180, 10));
					Rectangle(hdc, row * SQUARE_SIZE, column * SQUARE_SIZE, row * SQUARE_SIZE + SQUARE_SIZE, column*SQUARE_SIZE + SQUARE_SIZE);
				case 'R':
					SetDCBrushColor(hdc, RGB(255, 0, 0));
					Ellipse(hdc, row * SQUARE_SIZE, column * SQUARE_SIZE, row * SQUARE_SIZE + SQUARE_SIZE, column*SQUARE_SIZE + SQUARE_SIZE);
					SetDCBrushColor(hdc, RGB(220, 220, 0));
					Ellipse(hdc, row * SQUARE_SIZE + (.5-.25)*SQUARE_SIZE, column * SQUARE_SIZE + (.5-.25)*SQUARE_SIZE, row * SQUARE_SIZE +(.5+.25)*SQUARE_SIZE, column*SQUARE_SIZE +(.5+.25)*SQUARE_SIZE);
					break;
				case 'p':
					SetDCBrushColor(hdc, RGB(10, 180, 10));
					Rectangle(hdc, row * SQUARE_SIZE, column * SQUARE_SIZE, row * SQUARE_SIZE + SQUARE_SIZE, column*SQUARE_SIZE + SQUARE_SIZE);
					break;
				case 'K':
					SetDCBrushColor(hdc, RGB(10, 180, 10));
					Rectangle(hdc, row * SQUARE_SIZE, column * SQUARE_SIZE, row * SQUARE_SIZE + SQUARE_SIZE, column*SQUARE_SIZE + SQUARE_SIZE);
				case 'B':
					SetDCBrushColor(hdc, RGB(0, 0, 0));
					Ellipse(hdc, row * SQUARE_SIZE, column * SQUARE_SIZE, row * SQUARE_SIZE + SQUARE_SIZE, column*SQUARE_SIZE + SQUARE_SIZE);
					SetDCBrushColor(hdc, RGB(220, 220, 0));
					Ellipse(hdc, row * SQUARE_SIZE + (.5 - .25)*SQUARE_SIZE, column * SQUARE_SIZE + (.5 - .25)*SQUARE_SIZE, row * SQUARE_SIZE + (.5 + .25)*SQUARE_SIZE, column*SQUARE_SIZE + (.5 + .25)*SQUARE_SIZE);
					break;
			}
			SetDCBrushColor(hdc, sqColor);
			squareCount++;

		}
		squareCount++;
	}
}