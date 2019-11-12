// main.cpp : Defines the entry point for the application.
//

#include<iostream>

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

char board[8][8] = {
	{ 'b','*','b','*','b','*','b','*' },
	{ '*','b','*','b','*','b','*','b' },
	{ 'b','*','b','*','B','*','b','*' },
	{ '*','w','*','w','*','w','*','w' },
	{ 'w','*','w','*','w','*','w','*' },
	{ '*','r','*','r','*','r','*','r' },
	{ 'r','*','R','*','r','*','r','*' },
	{ '*','r','*','r','*','r','*','r' },
};

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
			
			sprintf_s(buf, _T("x: %d; y: %d sx: %d, sy : %d               "), mouseCoord.x, mouseCoord.y, mouseCoord.squarex, mouseCoord.squarey);
			printf_s(buf);
			if (mouseCoord.x > 0 && mouseCoord.y > 0) {
				SetDCBrushColor(hdc, RGB(127, 127, 255));
				Rectangle(hdc, mouseCoord.squarex * SQUARE_SIZE, mouseCoord.squarey * SQUARE_SIZE, mouseCoord.squarex * SQUARE_SIZE + SQUARE_SIZE, mouseCoord.squarey*SQUARE_SIZE + SQUARE_SIZE);
			}
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
			// TextOut(Frame, x, y, text, _tcslen
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
