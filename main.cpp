// main.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "main.h"
#include "board.h"
#include "mousehandling.h"
#include<string>
//using namespace std;

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
#include "mousehandling.h"


char board[8][8] = {
	{ 'w','*','w','*','w','*','w','*' },
	{ '*','w','*','w','*','w','*','w' },
	{ 'w','*','w','*','w','*','w','*' },
	{ '*','w','*','w','*','w','*','w' },
	{ 'w','*','w','*','w','*','w','*' },
	{ '*','w','*','w','*','w','*','w' },
	{ 'w','*','w','*','w','*','w','*' },
	{ '*','w','*','w','*','w','*','w' },
};
State gameState = TURN_START;
void resetLocalSquares(Coordinate coord);

#define UP -1
#define DOWN 1
#define LEFT -1
#define RIGHT 1

#define BLACK_ENEMY 'R'
#define RED_ENEMY 'B'

class Piece {
protected:
	Coordinate coord;
	bool mouseFocus;
	int numMoves;
public:
	//Piece(Coordinate coord);
	Coordinate getCoordinate();
	virtual void draw() = 0;
	Coordinate move(Coordinate coord);
	void hide();
	bool lookDirection(int directX, int directY, char enemy, bool makeVisible = true, bool capture = false);
	int getNumMoves() { return numMoves; }
	void setNumMoves(int num) { this->numMoves = num; }
};


Coordinate Piece::getCoordinate() {
	return coord;
}

Coordinate Piece::move(Coordinate coord) {
	Coordinate temp;
	temp = coord - this->coord;
	if (abs(temp.squarex) > 1) {
		temp =  this->coord + temp / 2;
	}
	else {
		Coordinate temp;
		temp.squarex = -1;
		temp.squarey = -1;
	}
	board[this->coord.squarey][this->coord.squarex] = 'w';
	this->coord.squarex = coord.squarex;
	this->coord.squarey = coord.squarey;
	draw();
	return(temp);
}

bool Piece::lookDirection(int directX, int directY, char enemy, bool makeVisible, bool capture) {
	char location;
	if (this->mouseFocus == true) {
		location = 'w';
	}
	else {
		location = 'p';
	}
	
	int toLower = 'a' - 'A';


	//stores the current coordinate into a temporary vatirable for alteration
	Coordinate temp = coord;
	int x = temp.squarex;
	int y = temp.squarey;
	bool canJump = false;

	//test specified direction to see if there is an enemy piece to take
	if (board[y + directY][x + directX] == enemy || board[y + directY][x + directX] == (enemy + toLower)) {
		if (x + 2 * directX >= 0 && y + 2 * directY <= 8 && board[y + 2 * directY][x + 2 * directX] == 'w' || board[y + 2 * directY][x + 2 * directX] == 'p') {
			canJump = true;
			numMoves++;
			if (makeVisible) {
				board[y + 2 * directY][x + 2 * directX] = location;
			}
		}
		//do nothing
	}
	else if (board[y + directY][x + directX] == 'w' || board[y + directY][x + directX] == 'p' && !canJump) {
		if (makeVisible == true && !capture) {
			board[y + directY][x + directX] = location;
		}
		numMoves++;
		
	}

	return canJump;
}

class BlackPiece : public Piece {
protected:
	static int numPieces;
	bool isKing = 0;
	bool canJump = 0;
public:
	BlackPiece(Coordinate coord);
	BlackPiece() {};
	~BlackPiece() {};

	void hide();
	void draw();
	bool showMoves(bool makeVisible = true);
	void makeKing() { isKing = true; draw(); }
};
void BlackPiece::hide() {
	board[coord.squarey][coord.squarex] = 'w';
	coord.setHidden();
	numPieces--;
}
BlackPiece::BlackPiece(Coordinate coord) {
	numPieces++;
	numMoves = 0;
	this->coord = coord;
	this->mouseFocus = false;
	draw();
}

void BlackPiece::draw() {
	if (isKing) {
		board[coord.squarey][coord.squarex] = 'B';
	}
	else {
		board[coord.squarey][coord.squarex] = 'b';
	}
}

bool BlackPiece::showMoves(bool makeVisible) {
	bool temp = false;
	if (coord.squarex + LEFT >= 0 && coord.squarey + DOWN < 8) {
		//look lower left to see if moves are available
		temp = lookDirection(LEFT, DOWN, BLACK_ENEMY, makeVisible, temp);
	}
	if (coord.squarex + RIGHT < 8 && coord.squarey + DOWN < 8) {
		//look lower right to see if moves are available
		temp = temp | lookDirection(RIGHT, DOWN, BLACK_ENEMY, makeVisible, temp);
	}
	if (isKing && coord.squarex + LEFT >= 0 && coord.squarey + UP >= 0) {
		//look upper left to see if moves are available
		temp = temp | lookDirection(LEFT, UP, BLACK_ENEMY, makeVisible, temp);
	}
	if (isKing && coord.squarex + RIGHT < 8 && coord.squarey + UP >= 0) {
		//look upper right to see if moves are available
		temp = temp | lookDirection(RIGHT, UP, BLACK_ENEMY, makeVisible, temp);
	}
	if (temp) {
		resetLocalSquares(coord);
	}
	if (makeVisible == false) {
		
		return temp;
	}
	if (this->mouseFocus == true) {
		this->mouseFocus = false;
	}
	else {
		this->mouseFocus = true;
	}
	return 0;

}


class RedPiece : public Piece {
protected:
	static int numPieces;
	bool isKing = 0;
	bool canJump = 0;
public:
	RedPiece(Coordinate coord);
	RedPiece();
	~RedPiece() {};
	void hide();

	void draw();
	bool showMoves(bool makeVisible = true);
	void makeKing() { isKing = true; draw(); }

};
void RedPiece::hide() {
	board[coord.squarey][coord.squarex] = 'w';
	coord.setHidden();
	numPieces--;
}
RedPiece::RedPiece(){

}
RedPiece::RedPiece(Coordinate coord) {
	numPieces++;
	numMoves = 0;
	this->coord = coord;
	this->mouseFocus = false;
	draw();

}

void RedPiece::draw() {
	if (isKing) {
		board[coord.squarey][coord.squarex] = 'R';
	}
	else {
		board[coord.squarey][coord.squarex] = 'r';
	}
}

bool RedPiece::showMoves(bool makeVisible) {
	bool temp = false;
	if (coord.squarex + LEFT >= 0 && coord.squarey + UP >= 0) {
		//look upper left to see if moves are available
		temp = lookDirection(LEFT, UP, RED_ENEMY, makeVisible, temp);
	}
	if (coord.squarex + RIGHT < 8 && coord.squarey + UP >= 0) {
		//look upper right to see if moves are available
		temp = temp | lookDirection(RIGHT, UP, RED_ENEMY, makeVisible, temp);
	}

	if (isKing && coord.squarex + LEFT >= 0 && coord.squarey + DOWN < 8) {
		//look lower left to see if moves are available
		temp = temp | lookDirection(LEFT, DOWN, RED_ENEMY, makeVisible, temp);
	}
	if (isKing && coord.squarex + RIGHT < 8 && coord.squarey + DOWN < 8) {
		//look lower right to see if moves are available
		temp = temp | lookDirection(RIGHT, DOWN, RED_ENEMY, makeVisible, temp);
	}
	if (temp) {
		resetLocalSquares(coord);
	}
	if (makeVisible == false) {
		return temp;
	}
	if (this->mouseFocus == true) {
		this->mouseFocus = false;
	}
	else {
		this->mouseFocus = true;
	}
	return false;
}


int BlackPiece::numPieces = 0;
int RedPiece::numPieces = 0;

RedPiece redPieces[12];
BlackPiece blackPieces[12];
RedPiece * currentRedPiece;
BlackPiece * currentBlackPiece;
int turnCounter = 0;
void checkBlack() {
	int totalNumMoves = 0;
	for (int i = 0; i < PIECES_PER_PLAYER; i++) {
		bool canCapture = blackPieces[i].showMoves(false);
		totalNumMoves += blackPieces[i].getNumMoves();

		if (canCapture) {
			Coordinate coord = blackPieces[i].getCoordinate();
			if (board[coord.squarey][coord.squarex] == 'b') {
				board[coord.squarey][coord.squarex] = 'k';
			}
			else {
				board[coord.squarey][coord.squarex] = 'K';
			}
			gameState = CAPTURE_MOVES;
		}


	}
}
void checkRed() {
	int totalNumMoves = 0;
	for (int i = 0; i < PIECES_PER_PLAYER; i++) {
		bool canCapture = redPieces[i].showMoves(false);
		totalNumMoves += redPieces[i].getNumMoves();

		if (canCapture) {
			Coordinate coord = redPieces[i].getCoordinate();
			if (board[coord.squarey][coord.squarex] == 'r') {
				board[coord.squarey][coord.squarex] = 'q';
			}
			else {
				board[coord.squarey][coord.squarex] = 'Q';
			}
			gameState = CAPTURE_MOVES;
		}

	}
}

//is called at the end of reds turn to see if any red pieces can become kings
void checkRedKing() {
	for (int i = 0; i < PIECES_PER_PLAYER; i++) {
		if (redPieces[i].getCoordinate().squarey == 0) {
			redPieces[i].makeKing();
		}
	}
}

//is called at the end of blacks turn to see if any black pieces can become kings
void checkBlackKing() {
	for (int i = 0; i < PIECES_PER_PLAYER; i++) {
		if (blackPieces[i].getCoordinate().squarey == 7) {
			blackPieces[i].makeKing();
		}
	}
}
void resetLocalSquares(Coordinate coord) {
	if (coord.squarex + LEFT >= 0 && coord.squarey + UP >= 0) {
		//look upper left to see if moves are available
		if (board[coord.squarey + UP][coord.squarex + LEFT] == 'p') {
			board[coord.squarey + UP][coord.squarex + LEFT] = 'w';
		}
	}
	if (coord.squarex + RIGHT < 8 && coord.squarey + UP >= 0) {
		//look upper right to see if moves are available
		if (board[coord.squarey + UP][coord.squarex + RIGHT] == 'p') {
			board[coord.squarey + UP][coord.squarex + RIGHT] = 'w';
		}
	}

	if (coord.squarex + LEFT >= 0 && coord.squarey + DOWN < 8) {
		if (board[coord.squarey + DOWN][coord.squarex + LEFT] == 'p') {
			board[coord.squarey + DOWN][coord.squarex + LEFT] = 'w';
		}
	}
	if (coord.squarex + RIGHT < 8 && coord.squarey + DOWN < 8) {
		//look lower right to see if moves are available
		if (board[coord.squarey + DOWN][coord.squarex + RIGHT] == 'p') {
			board[coord.squarey + DOWN][coord.squarex + RIGHT] = 'w';
		}
	}
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GUITESTING, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GUITESTING));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GUITESTING));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_GUITESTING);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW^WS_MINIMIZEBOX^WS_MAXIMIZEBOX,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }
   // Resize window to cover the board
   SetWindowPos(hWnd, HWND_TOPMOST, 300,300, 8*SQUARE_SIZE+12, 9*SQUARE_SIZE+1,SWP_NOMOVE);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static RECT newRect;
	static RECT rcClient;
	POINT ptClientUL;
	POINT ptClientLR;
	
    switch (message)
    {
	case WM_CREATE:
		{
			// RUNS ONCE ON WINDOW CREATION
			SetRect(&newRect, 1, 1, 34, 34);
			GetClientRect(hWnd, &rcClient);
			ptClientUL.x = rcClient.left;
			ptClientUL.y = rcClient.top;
			ptClientLR.x = rcClient.right;
			ptClientLR.y = rcClient.bottom;
		}
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	// Mouse click case
	case WM_LBUTTONDOWN:
		{
		printf_s("hi");
			
			HDC hdc = GetDC(hWnd);
			SetCapture(hWnd);
			Coordinate mouseCoord = getMouseCoordinate(lParam);
			TCHAR buf[100];
			if (gameState == TURN_START) {
				_stprintf_s(buf, _T("x: %d; y: %d sx: %d, sy : %d          \nCurrent state: TURN_START"), mouseCoord.x, mouseCoord.y, mouseCoord.squarex, mouseCoord.squarey);
			}
			else if (gameState == SHOW_MOVES) {
				_stprintf_s(buf, _T("x: %d; y: %d sx: %d, sy : %d          \nCurrent state: SHOW_MOVES"), mouseCoord.x, mouseCoord.y, mouseCoord.squarex, mouseCoord.squarey);
			}
			else if (gameState == CAPTURE_MOVES) {
				_stprintf_s(buf, _T("x: %d; y: %d sx: %d, sy : %d          \nCurrent state: CAPTURE_MOVES"), mouseCoord.x, mouseCoord.y, mouseCoord.squarex, mouseCoord.squarey);
			}
			else if (gameState == SHOW_CAPTURE_MOVES) {
				_stprintf_s(buf, _T("x: %d; y: %d sx: %d, sy : %d          \nCurrent state: SHOW_CAPTURE_MOVES"), mouseCoord.x, mouseCoord.y, mouseCoord.squarex, mouseCoord.squarey);
			}
			// Check for valid click
			if (mouseCoord.x >= 0 && mouseCoord.y >= 0) {
				if (turnCounter % 2 == 0) {
					if (gameState == TURN_START) {
						for (int i = 0; i < PIECES_PER_PLAYER; i++) {
							Coordinate coord = redPieces[i].getCoordinate();
							if (coord.squarex == mouseCoord.squarex && coord.squarey == mouseCoord.squarey) {
								redPieces[i].showMoves();
								currentRedPiece = &redPieces[i];
								gameState = SHOW_MOVES;
								break;
							}
						}
						
					}
					else if (gameState == SHOW_MOVES) {
						Coordinate pieceCoordinate = currentRedPiece->getCoordinate();
						if (pieceCoordinate.squarex == mouseCoord.squarex && pieceCoordinate.squarey == mouseCoord.squarey) {
							currentRedPiece->showMoves();
							gameState = TURN_START;
						}
						else if (board[mouseCoord.squarey][mouseCoord.squarex] == 'p') {
							currentRedPiece->showMoves();

							Coordinate moveResult = currentRedPiece->move(mouseCoord);
							if(moveResult.squarex != -1 && moveResult.squarey != -1) {
								for (int i = 0; i < PIECES_PER_PLAYER; i++) {
									Coordinate coord = blackPieces[i].getCoordinate();
									if (coord.squarex == moveResult.squarex && coord.squarey == moveResult.squarey) {
										blackPieces[i].hide();
										break;
									}
								}
							}
							gameState = TURN_START;
							cleanBoard();
							//////////////////////////////////
							checkRedKing();
							checkBlack();
							turnCounter++;
							
						}
						
					}
					else if (gameState == CAPTURE_MOVES) {
						for (int i = 0; i < PIECES_PER_PLAYER; i++) {
							Coordinate coord = redPieces[i].getCoordinate();
							if (coord.squarex == mouseCoord.squarex && coord.squarey == mouseCoord.squarey && (board[mouseCoord.squarey][mouseCoord.squarex] == 'q' || board[mouseCoord.squarey][mouseCoord.squarex] == 'Q')) {
								redPieces[i].showMoves();
								currentRedPiece = &redPieces[i];
								gameState = SHOW_CAPTURE_MOVES;
								break;
							}
						}
					}
					else if (gameState == SHOW_CAPTURE_MOVES) {
						Coordinate pieceCoordinate = currentRedPiece->getCoordinate();
						if (pieceCoordinate.squarex == mouseCoord.squarex && pieceCoordinate.squarey == mouseCoord.squarey) {
							currentRedPiece->showMoves();
							gameState = CAPTURE_MOVES;
						}
						else if (board[mouseCoord.squarey][mouseCoord.squarex] == 'p') {
							currentRedPiece->showMoves();

							Coordinate moveResult = currentRedPiece->move(mouseCoord);
							if (moveResult.squarex != -1 && moveResult.squarey != -1) {
								for (int i = 0; i < PIECES_PER_PLAYER; i++) {
									Coordinate coord = blackPieces[i].getCoordinate();
									if (coord.squarex == moveResult.squarex && coord.squarey == moveResult.squarey) {
										blackPieces[i].hide();
										break;
									}
								}
							}
							gameState = TURN_START;
							cleanBoard();
							//////////////////////////////////
							checkRed();
							if (gameState != CAPTURE_MOVES) {
								turnCounter++;
								gameState = TURN_START;
								
								checkRedKing();
								checkBlack();
								
							}
						}
					}
				}
				else {
					if (gameState == TURN_START) {
						for (int i = 0; i < PIECES_PER_PLAYER; i++) {
							Coordinate coord = blackPieces[i].getCoordinate();
							if (coord.squarex == mouseCoord.squarex && coord.squarey == mouseCoord.squarey) {
								blackPieces[i].showMoves();
								currentBlackPiece = &blackPieces[i];
								gameState = SHOW_MOVES;
								break;
							}
						}
						
					}
					else if (gameState == SHOW_MOVES) {
						Coordinate pieceCoordinate = currentBlackPiece->getCoordinate();
						if (pieceCoordinate.squarex == mouseCoord.squarex && pieceCoordinate.squarey == mouseCoord.squarey) {
							currentBlackPiece->showMoves();
							gameState = TURN_START;
						}
						else if (board[mouseCoord.squarey][mouseCoord.squarex] == 'p') {
							currentBlackPiece->showMoves();
							Coordinate moveResult = currentBlackPiece->move(mouseCoord);
							if (moveResult.squarex != -1 && moveResult.squarey != -1) {
								for (int i = 0; i < PIECES_PER_PLAYER; i++) {
									Coordinate coord = redPieces[i].getCoordinate();
									if (coord.squarex == moveResult.squarex && coord.squarey == moveResult.squarey) {
										redPieces[i].hide();
										break;
									}
								}
							}
							cleanBoard();
							gameState = TURN_START;
							checkBlackKing();
							checkRed();
							turnCounter++;
						}
					}
					else if (gameState == CAPTURE_MOVES) {
						for (int i = 0; i < PIECES_PER_PLAYER; i++) {
							Coordinate coord = blackPieces[i].getCoordinate();
							if (coord.squarex == mouseCoord.squarex && coord.squarey == mouseCoord.squarey && (board[mouseCoord.squarey][mouseCoord.squarex] == 'k' || board[mouseCoord.squarey][mouseCoord.squarex] == 'K')) {
								blackPieces[i].showMoves();
								currentBlackPiece = &blackPieces[i];
								gameState = SHOW_CAPTURE_MOVES;
								break;
							}
						}
					}
					else if (gameState == SHOW_CAPTURE_MOVES) {
						Coordinate pieceCoordinate = currentBlackPiece->getCoordinate();
						if (pieceCoordinate.squarex == mouseCoord.squarex && pieceCoordinate.squarey == mouseCoord.squarey) {
							currentBlackPiece->showMoves();
							gameState = CAPTURE_MOVES;
						}
						else if (board[mouseCoord.squarey][mouseCoord.squarex] == 'p') {
							currentBlackPiece->showMoves();

							Coordinate moveResult = currentBlackPiece->move(mouseCoord);
							if (moveResult.squarex != -1 && moveResult.squarey != -1) {
								for (int i = 0; i < PIECES_PER_PLAYER; i++) {
									Coordinate coord = redPieces[i].getCoordinate();
									if (coord.squarex == moveResult.squarex && coord.squarey == moveResult.squarey) {
										redPieces[i].hide();
										break;
									}
								}
							}
							gameState = TURN_START;
							cleanBoard();
							//////////////////////////////////
							checkBlack();
							if (gameState != CAPTURE_MOVES) {
								turnCounter++;
								gameState = TURN_START;
								checkBlackKing();
								checkRed();
							}
						}
					}
				}
			}

			

			updateFrame(hWnd);
			//TCHAR greeting[] = _T(x);
			// TextOut(Frame, x, y, text, _tcslen
			TextOut(hdc, 50, 5, buf, _tcslen(buf));
			break;
		}
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
			TCHAR greeting[] = _T("Hello world!");
			int redCount = 0;
			int blackCount = 0;
			int squareCount = 1;
			for (int row = 0; row < 8; row++) {
				for (int column = 0; column < 8; column++) {
					
					if (squareCount % 2 != 0 && row > 4) {
						Coordinate coord;
						coord.squarex = column;
						coord.squarey = row;
						RedPiece tempRed(coord);
						redPieces[redCount] = tempRed;
						redCount++;
					}
					else if (squareCount % 2 != 0 && row < 3) {
						Coordinate coord;
						coord.squarex = column;
						coord.squarey = row;
						BlackPiece tempBlack(coord);
						blackPieces[blackCount] = tempBlack;
						blackCount++;
					}
					squareCount++;
				}
				squareCount++;
			}                                                                                                                                                                                                    
			updateFrame(hWnd);
			EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
