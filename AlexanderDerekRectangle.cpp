// AlexanderDerekRectangle.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
#include "AlexanderDerekRectangle.h"
#include "RECTANGLE.h"
#include "BRUSH.h"
#include "PEN.h"
#include "PAINT.h"




#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

bool g_drawRectangles = false;
bool g_drawEllipses = false;
bool g_timer = false;
bool g_extraCredit = false;
bool g_drawLines = false;
bool g_concentric = false;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


void doPaint(HWND hWnd);


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
    LoadStringW(hInstance, IDC_ALEXANDERDEREKRECTANGLE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ALEXANDERDEREKRECTANGLE));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ALEXANDERDEREKRECTANGLE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ALEXANDERDEREKRECTANGLE);
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

 // Parse the menu selections:
LRESULT doCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{	
	
	LRESULT result = 0;
	    
    int wmId = LOWORD(wParam);
       
    switch (wmId)
    {
	case ID_OPTIONS_TIMER:
			SetTimer(hWnd, 0, 250, NULL);
			g_timer = TRUE;
			CheckMenuItem(GetMenu(hWnd), wmId, MF_BYCOMMAND | MF_CHECKED);


			break;


	case ID_OPTIONS_CONCENTRIC:
	case ID_OPTIONS_RECTANGLE:
	case ID_OPTIONS_ELLIPSE:
	case ID_OPTIONS_LINES:
	case ID_OPTIONS_EXTRACREDIT:

		//manipulate the boolean variables based on the item wmId selected
		g_drawRectangles =(wmId == ID_OPTIONS_RECTANGLE);
		g_drawEllipses =(wmId == ID_OPTIONS_ELLIPSE);
		g_drawLines =(wmId == ID_OPTIONS_LINES);
		g_extraCredit =(wmId == ID_OPTIONS_EXTRACREDIT);
		g_concentric = (wmId == ID_OPTIONS_CONCENTRIC);
		
		//turn all of the items off
		CheckMenuItem(GetMenu(hWnd), ID_OPTIONS_ELLIPSE,	 MF_BYCOMMAND | MF_UNCHECKED);
		CheckMenuItem(GetMenu(hWnd), ID_OPTIONS_EXTRACREDIT, MF_BYCOMMAND | MF_UNCHECKED);
		CheckMenuItem(GetMenu(hWnd), ID_OPTIONS_LINES,		 MF_BYCOMMAND | MF_UNCHECKED);
		CheckMenuItem(GetMenu(hWnd), ID_OPTIONS_RECTANGLE,	 MF_BYCOMMAND | MF_UNCHECKED);
		CheckMenuItem(GetMenu(hWnd), ID_OPTIONS_CONCENTRIC,  MF_BYCOMMAND | MF_UNCHECKED);

		//and end with turning on the one item wmid that is selected
		CheckMenuItem(GetMenu(hWnd), wmId, MF_BYCOMMAND | MF_CHECKED);
		InvalidateRect(hWnd, NULL, TRUE);

	break;

		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);

    }
        
	return result;

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
    switch (message)
    {
    case WM_COMMAND:

		return doCommand(hWnd, message, wParam, lParam);
		break;

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

    case WM_PAINT:
        {
            // TODO: Add any drawing code that uses hdc here...
			doPaint(hWnd);
        }
        break;

	case WM_TIMER:

		InvalidateRect(hWnd, NULL, TRUE);	

		break;

	case WM_CREATE:

		CheckMenuItem(GetMenu(hWnd),ID_OPTIONS_ELLIPSE,		MF_BYCOMMAND|MF_UNCHECKED);
		CheckMenuItem(GetMenu(hWnd),ID_OPTIONS_LINES,		MF_BYCOMMAND|MF_UNCHECKED);
		CheckMenuItem(GetMenu(hWnd),ID_OPTIONS_EXTRACREDIT, MF_BYCOMMAND|MF_UNCHECKED);
		CheckMenuItem(GetMenu(hWnd),ID_OPTIONS_CONCENTRIC,	MF_BYCOMMAND | MF_UNCHECKED);
		CheckMenuItem(GetMenu(hWnd),ID_OPTIONS_RECTANGLE,	MF_BYCOMMAND|MF_CHECKED);

		break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}



void doPaint(HWND hWnd )
{

	PAINT paint( hWnd );
	RECT rect;
	GetClientRect(hWnd, &rect);
	RECTANGLE cr( rect.left, rect.top, rect.right, rect.bottom );
	BRUSH brush;
	PEN pen;


	for (int i = 0; i < 100; i++)
	{
		RECTANGLE rr = RECTANGLE::random(cr);


		paint.usePen(pen, rand() % 256, rand() % 256, rand() % 256);
		paint.useBrush(brush, rand() % 256, rand() % 256, rand() % 256);

		if (g_drawEllipses)
			paint.drawCircle(rr);


		else if (g_drawLines)
			paint.drawLine( (rand() % cr.width() ),(rand() % cr.heigth() ),
							(rand() % cr.width() ),(rand() % cr.heigth() ) );

				else
			paint.drawRectangle(rr);
	}
	
	if (g_concentric)
	{
		while ((cr.width() > 0) | (cr.heigth() > 0))
		{

			paint.usePen(pen, rand() % 256, rand() % 256, rand() % 256);
			paint.useBrush(brush, rand() % 256, rand() % 256, rand() % 256);

			paint.drawRectangle(cr);

			cr.inflate(-10, -10);

			if ((cr.width() < 0) | (cr.heigth() < 0))
				break;
		}
	}
	
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
