// winDraw.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "winDraw.h"
#include "Windowsx.h "
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
int d_flag;
RECT rect;
int xPaintpos[2];
int yPaintpos[2];

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WINDRAW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDRAW));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}




ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDRAW));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WINDRAW);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{ 
	d_flag=0;
   HWND hWnd;
  
   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case ID_DRAW_LINE:
			d_flag=1;
			break;
		case ID_DRAW_REC:
			d_flag=2;
			break;
		case ID_DRAW_Ellipse:
			d_flag=3;
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
		break;
	case WM_LBUTTONDOWN :		
		{
			xPaintpos[0]=GET_X_LPARAM(lParam);      
			yPaintpos[0]=GET_Y_LPARAM(lParam);	

		}
		break;

	case WM_LBUTTONUP :
		{
			xPaintpos[1]=GET_X_LPARAM(lParam);      
			yPaintpos[1]=GET_Y_LPARAM(lParam);
			GetClientRect(hWnd,&rect);

			InvalidateRect(hWnd,&rect,TRUE);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		
		switch(d_flag)
		{
		case 1:
		MoveToEx(hdc,xPaintpos[0],yPaintpos[0],0);
		LineTo(hdc,xPaintpos[1],yPaintpos[1]);
			
		break;
	   case 2:
		Rectangle(hdc,xPaintpos[0],yPaintpos[0],xPaintpos[1],yPaintpos[1]) ;
		
		break;
		case 3:
		Ellipse(hdc,xPaintpos[0],yPaintpos[0],xPaintpos[1],yPaintpos[1]) ;
		
		break;
		default:
			//Rectangle(hdc,40,40,100,100) ;
			break;
		}
		/*if (d_flag==1)
		{
		MoveToEx(hdc,xPaintpos[0],yPaintpos[0],0);
		LineTo(hdc,xPaintpos[1],yPaintpos[1]);
		}
		else if (d_flag==2)
		{
		Rectangle(hdc,xPaintpos[0],yPaintpos[0],xPaintpos[1],yPaintpos[1]) ;
		}
		else if (d_flag==3)
		{
		Ellipse(hdc,xPaintpos[0],yPaintpos[0],xPaintpos[1],yPaintpos[1]) ;
		}*/
			//MoveToEx(hdc,xPaintpos[0],yPaintpos[0],0);
			//LineTo(hdc,xPaintpos[1],yPaintpos[1]);
		//	Rectangle(hdc,40,40,100,100) ;
		//	break;
		//case 2:
		//	//Rectangle(hdc,xPaintpos[0],yPaintpos[0],xPaintpos[1],yPaintpos[1]) ;
		//	Rectangle(hdc,40,40,100,100) ;
		//	break;
		//case 3:
		//	//Ellipse(hdc,xPaintpos[0],yPaintpos[0],xPaintpos[1],yPaintpos[1]) ;
		//	Rectangle(hdc,40,40,100,100) ;
		//	break;
		//default:
		//	Rectangle(hdc,40,40,100,100) ;
		//	break;
		//}
		
		EndPaint(hWnd, &ps);
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
