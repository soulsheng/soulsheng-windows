// WinNote.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "WinNote.h"

#include "Windowsx.h"
#include <atlstr.h>
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

char text[1024];
int nCout;
RECT	rect;
RECT rectDIY;

int x_position;
int y_position;
int pos_num=0;
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
	MSG msg;//消息
	HACCEL hAccelTable;//快捷键

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WINNOTE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINNOTE));

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

	wcex.style			= CS_HREDRAW | CS_VREDRAW|CS_DBLCLKS;
	wcex.lpfnWndProc	= WndProc;//回调函数  窗体功能
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;//唯一的标识一个程序
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINNOTE));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WINNOTE);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	for (int i=0;i<1024;i++)
	{
		text[i]=0;
	}
	nCout=0;

	strcpy(text,"内容：");
	nCout = strlen("内容：");
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
	rectDIY.left=0;
	rectDIY.right=100;
	rectDIY.top=0;
	rectDIY.bottom=100;
	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
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
		break;
	case WM_LBUTTONDBLCLK:
		//MessageBox(NULL,"你按了鼠标键","示",MB_ICONERROR);
		if (pos_num>20)
		{
			pos_num=pos_num-20;
		}
	     x_position=GET_X_LPARAM(lParam);
		 y_position=GET_Y_LPARAM(lParam);
		pos_num++;
		/*hdc = BeginPaint(hWnd, &ps);
		DrawText(hdc,text,nCout,&rectDIY,0);
		EndPaint(hWnd, &ps);*/
		/*	hdc = BeginPaint(hWnd, &ps);
		MoveToEx(hdc,(int)pt.x,(int)pt.y,0);
		LineTo(hdc,pt.x,pt.y+100);

		MoveToEx(hdc,pt.x,pt.y+100,0);
		LineTo(hdc,pt.x+100,pt.y+100);

		MoveToEx(hdc,pt.x+100,pt.y+100,0);
		LineTo(hdc,pt.x+100,pt.y);

		MoveToEx(hdc,pt.x+100,pt.y,0);
		LineTo(hdc,pt.x,pt.y);
		EndPaint(hWnd, &ps);*/
		GetClientRect(hWnd,&rectDIY);
		InvalidateRect(hWnd, &rectDIY,TRUE);
		break;
		//return 0;
	case WM_LBUTTONDOWN:
	case  WM_LBUTTONUP:
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		rectDIY.left=x_position;
		rectDIY.right=x_position+300;
		rectDIY.top=y_position;
		rectDIY.bottom=y_position+200;
		// TODO: Add any drawing code here...
		//TextOut(hdc,0,0,"Hello World",nCout);
		DrawText(hdc,text,nCout,&rectDIY,0);
		
		MoveToEx(hdc,x_position,y_position,0);
		LineTo(hdc,x_position,y_position+200);

		MoveToEx(hdc,x_position,y_position+200,0);
		LineTo(hdc,x_position+300,y_position+200);

		MoveToEx(hdc,x_position+300,y_position+200,0);
		LineTo(hdc,x_position+300,y_position);

		MoveToEx(hdc,x_position+300,y_position,0);
		LineTo(hdc,x_position,y_position);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		//MessageBox(0,"确定退出吗","简单窗口",0);
		PostQuitMessage(0);
		break;
	case  WM_CHAR:
		text[nCout]=wParam;
		nCout++;
		
		GetClientRect(hWnd,&rect);
		InvalidateRect(hWnd, &rect,TRUE);
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
