// WindowsProject1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "WindowsProject1.h"
#include "Header.h"
#include "Tile.h"
#include "Board.h"
#include "TileMaker.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HDC imageDC;
HBITMAP imageBmp;
int i = 0;


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void				loadImage(const char*);
void				loadImage2(const char*);
void				cleanUpImage();
Board*				GameBoard;
BOOL				GameOn = false;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
	loadImage("2048 Tiles.bmp");
	
	
    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

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

	cleanUpImage();
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
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
			case IDM_Classic:
				GameBoard = new Board(4, 4);
				GameBoard->PrepBoard();
				GameOn = true;
				InvalidateRect(hWnd, NULL, true);
				UpdateWindow(hWnd);
				break;
			case IDM_Adventure:
				GameBoard = new Board(5, 5);
				GameBoard->PrepBoard();
				GameOn = true;
				InvalidateRect(hWnd, NULL, true);
				UpdateWindow(hWnd);
				break;
			case IDM_Challenge:
				GameBoard = new Board(5, 3);
				GameBoard->PrepBoard();
				GameOn = true;
				InvalidateRect(hWnd, NULL, true);
				UpdateWindow(hWnd);
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
			if (GameOn) 
			{
				GameBoard->PrintBoard(hdc, imageDC);
				TCHAR MyText[256];
				swprintf_s(MyText, 256, L"Game Score: %d", GameBoard->score);
				TextOut(hdc, 1, 1, MyText, wcslen(MyText));
				if(GameBoard->Win()) {
					TextOut(hdc, 1, 32 + (64 * GameBoard->y), L"Dragon Slayer Recruited!", 24);
				}
				if (GameBoard->Lose()) {
					TextOut(hdc, 1, 32+(64*GameBoard->y), L"Game Over!", 10);
				}
			}
			else 
			{
				
				TextOut(hdc, 150, 144 + 0, L"The Red Dragon Agnolon is terrorizing the country side!", 55);
				TextOut(hdc, 150, 144 + 16, L"Gather a peasant army to resist him, when an army gets", 54);
				TextOut(hdc, 150, 144 + 32, L"large enough a mighty Dragon Slayer will emerge.", 49);
				TextOut(hdc, 150, 144 + 48, L"When you are ready to begin use the Game menu above to select a game mode.", 75);
				TextOut(hdc, 150, 144 + 64, L"Use the arrow keys to manuver your recruits,", 45);
				TextOut(hdc, 150, 144 + 80, L"all units will move in the direction you select.", 50);
				TextOut(hdc, 150, 144 + 96, L"When two of the same units run into each other they will join together.", 71);
				TextOut(hdc, 150, 144 + 112, L"Single units will join into double units. Double units will promote.", 69);
				TextOut(hdc, 150, 144 + 128, L"Farmers promote to Woodsmen.  Woodsmen to Spearmen.", 51);
				TextOut(hdc, 150, 144 + 144, L"Spearmen to Sergants. Sergants to Phalanx.", 42);
				TextOut(hdc, 150, 144 + 160, L"And Phalanx to the legendary Dragon Slayer.", 43);
				TextOut(hdc, 150, 144 + 176, L"After recruiting a Dragonslayer you may continue playing", 56);
				TextOut(hdc, 150, 144 + 192, L"trying for a Double Dragon Slayer, a Ruby Dragon Slayer,", 56);
				TextOut(hdc, 150, 144 + 208, L"an Emerald Dragon Slayer and ultimatly a Diamond Dragon Slayer!", 63);
				BitBlt(hdc, 0, 0, 64, 8*64, imageDC, 0, 64, SRCCOPY);
				BitBlt(hdc, 64, 32, 64, 7*64, imageDC, 0, 9 * 64, SRCCOPY);
			}
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_KEYDOWN:
		{
			if (GameOn) {
				if (wParam == VK_LEFT) {
					GameBoard->Move(L);
				}
				if (wParam == VK_RIGHT) {
					GameBoard->Move(R);
				}
				if (wParam == VK_UP) {
					GameBoard->Move(U);
				}
				if (wParam == VK_DOWN) {
					GameBoard->Move(D);
				}

				InvalidateRect(hWnd, NULL, true);
				UpdateWindow(hWnd);
			}
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

void loadImage(const char* pathname)
{
	imageDC = CreateCompatibleDC(NULL);     // create an offscreen DC

	imageBmp = (HBITMAP)LoadImageA(NULL, pathname, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);

	//imageBmpOld = (HBITMAP)SelectObject(imageDC, imageBmp);  // put the loaded image into our DC
	SelectObject(imageDC, imageBmp);
}

void cleanUpImage()
{
	//SelectObject(imageDC, imageBmpOld);      
	DeleteObject(imageBmp);                 // delete the bmp we loaded
	DeleteDC(imageDC);                      // delete the DC we created
}