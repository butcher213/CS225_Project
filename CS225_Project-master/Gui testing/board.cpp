#include "stdafx.h"
#include "board.h"

extern char board[8][8];

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
			if (board[column][row] == 'r') {
				SetDCBrushColor(hdc, RGB(255, 0, 0));
				Ellipse(hdc, row * SQUARE_SIZE, column * SQUARE_SIZE, row * SQUARE_SIZE + SQUARE_SIZE, column*SQUARE_SIZE + SQUARE_SIZE);
			} else if(board[column][row] == 'b') {
				SetDCBrushColor(hdc, RGB(0, 0, 0));
				Ellipse(hdc, row * SQUARE_SIZE, column * SQUARE_SIZE, row * SQUARE_SIZE + SQUARE_SIZE, column*SQUARE_SIZE + SQUARE_SIZE);
			} else if (board[column][row] == 'R') {
				SetDCBrushColor(hdc, RGB(255, 0, 0));
				Ellipse(hdc, row * SQUARE_SIZE, column * SQUARE_SIZE, row * SQUARE_SIZE + SQUARE_SIZE, column*SQUARE_SIZE + SQUARE_SIZE);
				SetDCBrushColor(hdc, RGB(220, 220, 0));
				Ellipse(hdc, row * SQUARE_SIZE + (.5-.25)*SQUARE_SIZE, column * SQUARE_SIZE + (.5-.25)*SQUARE_SIZE, row * SQUARE_SIZE +(.5+.25)*SQUARE_SIZE, column*SQUARE_SIZE +(.5+.25)*SQUARE_SIZE);
			}
			else if (board[column][row] == 'B') {
				SetDCBrushColor(hdc, RGB(0, 0, 0));
				Ellipse(hdc, row * SQUARE_SIZE, column * SQUARE_SIZE, row * SQUARE_SIZE + SQUARE_SIZE, column*SQUARE_SIZE + SQUARE_SIZE);
				SetDCBrushColor(hdc, RGB(220, 220, 0));
				Ellipse(hdc, row * SQUARE_SIZE + (.5 - .25)*SQUARE_SIZE, column * SQUARE_SIZE + (.5 - .25)*SQUARE_SIZE, row * SQUARE_SIZE + (.5 + .25)*SQUARE_SIZE, column*SQUARE_SIZE + (.5 + .25)*SQUARE_SIZE);

			}
			SetDCBrushColor(hdc, sqColor);
			squareCount++;

		}
		squareCount++;
	}
}