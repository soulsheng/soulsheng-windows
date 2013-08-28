// WinNote.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "WinNote.h"
#include "Windowsx.h"
#include <windows.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

///////////
char text[1024];
//int xPosition[1024],yPosition[1024];

int nCount;   //字符计数
int mCount;   //鼠标点计数




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



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINNOTE));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WINNOTE);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
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
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   for (int i=0;i<1024;i++)
   {
	   text[i]=0;
   }
   nCount=0;

   /*for (int i=0;i<1024;i++)
   {
	   xPosition[i]=0;
	   yPosition[i]=0;
   }
   mCount=0;
*/
   strcpy(text,"Hello Symbol!");
   nCount=strlen("Hello Symbol!");


   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	RECT rect,rectDIY;

	static POINT posStart;  
	static POINT posCur;  
	static BOOL bMouseDown = FALSE;  
	static HPEN hPen = NULL;  
	static int iRight ,iBottom;  
	static RECT rectClient;  
	static HDC hPaintDc;  
	static HDC hOrignalDc = NULL;  
	static HBITMAP hPaintBit;  
	static HBITMAP hOriginalBit;  
	static HBRUSH hBrush;  
	RECT reErase;  
	HDC hdcTemp;  
	RECT re;  
	HDC  test;  
//	static char acName[100]="G:\\";  
//	char strNum[20];  
//	static int num =0;  
//	string str;  



	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:

	case WM_CREATE:  
		hPen = CreatePen(PS_DASHDOTDOT,4,RGB(0,0,0));  
		rectClient.left = 0;  
		rectClient.top = 0;  
		hdcTemp    = GetDC(hWnd);  
		hOrignalDc = CreateCompatibleDC(hdcTemp);  
		hPaintDc   = CreateCompatibleDC(hdcTemp);  
		SelectObject(hPaintDc,hPen);  
		// hBrush =(HBRUSH) GetStockObject(NULL_BRUSH);   
		//SelectObject(hPaintDc,hBrush);   
		ReleaseDC(hWnd,hdcTemp);  

		break;  

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

	case WM_SIZE:  
		OutputDebugStringA("size\n");  
		rectClient.right = LOWORD(lParam);  
		rectClient.bottom = HIWORD(lParam);  
		if(hPaintBit !=NULL)  
		{  
			DeleteObject(hPaintBit);  
		}  
		if(hOriginalBit !=NULL)  
		{  
			DeleteObject(hOriginalBit);  
		}  
		hdcTemp = GetDC(hWnd);  
		hOriginalBit = CreateCompatibleBitmap(hdcTemp,rectClient.right,rectClient.bottom);  
		hPaintBit    = CreateCompatibleBitmap(hdcTemp,rectClient.right,rectClient.bottom);  
		SelectObject(hPaintDc,hPaintBit);  
		SelectObject(hOrignalDc,hOriginalBit);  
		PatBlt  (hPaintDc,0,0,rectClient.right,rectClient.bottom,PATCOPY);  
		PatBlt(hOrignalDc,0,0,rectClient.right,rectClient.bottom,PATCOPY);  
		ReleaseDC(hWnd,hdcTemp);  


	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);


		// TODO: Add any drawing code here...


/////////////////////////////////////////////////////

		//SelectObject(hdc,hPen);   
		//Rectangle(hdc,posStart.x,posStart.y,posCur.x,posCur.y);   
		if(ps.rcPaint.left == 0 && ps.rcPaint.right == rectClient.right && ps.rcPaint.top==0 && ps.rcPaint.bottom == rectClient.bottom)  
		{  
			//全部无效   
			StretchBlt(hdc,0,0,rectClient.right,rectClient.bottom,hOrignalDc,0,0,rectClient.right,rectClient.bottom,SRCCOPY);   
			OutputDebugStringA("redraw\n");  
		}  
		else  
		{   
	//		//StretchBlt(hdc,0,0,rectClient.right,rectClient.bottom,hOrignalDc,0,0,rectClient.right,rectClient.bottom,SRCCOPY);      
	//		StretchBlt(hdc,posStart.x,posStart.y,posCur.x-posStart.x,posCur.y-posStart.y,hOrignalDc,posStart.x,posStart.y,posCur.x-posStart.x,posCur.y-posStart.y,SRCCOPY);   
			StretchBlt(hdc,posStart.x,posStart.y,posCur.x-posStart.x,posCur.y-posStart.y,hPaintDc,posStart.x,posStart.y,posCur.x-posStart.x,posCur.y-posStart.y,SRCAND);  

		
			
		}  

		rectDIY.left=posStart.x+10;
		rectDIY.right=posCur.x-5;
		rectDIY.top=posStart.y+10;
		rectDIY.bottom=posCur.y-5;

		DrawText(hdc,text,nCount,&rectDIY,0);

		InvalidateRect(hWnd,&rectDIY,FALSE);

	//	DrawText(hdc,text,nCount,&rectDIY,0);
		
//		GetClientRect(hWnd,&rectDIY);
//		InvalidateRect(hWnd,&rectDIY,FALSE);

		EndPaint(hWnd, &ps);
		break;
	
		case WM_CHAR:
		text[nCount]= wParam;
		nCount++;

//		GetClientRect(hWnd,&reErase);
//		InvalidateRect(hWnd,&reErase,TRUE);
		break;

	case WM_LBUTTONDOWN:
		
		SetCapture(hWnd);  
		bMouseDown = true;  
		

		posStart.x = GET_X_LPARAM(lParam); 
		posStart.y = GET_Y_LPARAM(lParam);
		iRight = posStart.x;  
		iBottom = posStart.y;  

		
			for (int i=0;i<1024;i++)
			{
				text[i]=0;
			}
			nCount=0;
		

		break;

	case  WM_MOUSEMOVE:  
		if(bMouseDown==TRUE)  
		{  
			posCur.x = GET_X_LPARAM(lParam); 
			posCur.y = GET_Y_LPARAM(lParam); 
			if(posCur.x > iRight)  
			{  
				iRight =posCur.x;  
			}  
			if(posCur.y > iBottom)  
			{  
				iBottom = posCur.y;  
			}  
			reErase.left = posStart.x;  
			reErase.right = iRight;  
			reErase.top = posStart.y;  
			reErase.bottom = iBottom;  

			Rectangle(hPaintDc,posStart.x,posStart.y,posCur.x,posCur.y);  
			InvalidateRect(hWnd,&reErase,TRUE);  
		}  
		break;  
	case WM_LBUTTONUP:  
		ReleaseCapture();  
		bMouseDown = false;  
	
		posCur.x = GET_X_LPARAM(lParam);   
		posCur.y = GET_Y_LPARAM(lParam); 
		if(posCur.x > iRight)  
		{  
			iRight =posCur.x;  
		}  
		if(posCur.y > iBottom)  
		{  
			iBottom = posCur.y;  
		}  
		reErase.left = posStart.x;  
		reErase.right = iRight;  
		reErase.top = posStart.y;  
		reErase.bottom = iBottom;  

		/*	test = GetDC(NULL);  
		hdcTemp = GetDC(hWnd);  
		BitBlt(hOrignalDc,0,0,rectClient.right,rectClient.bottom,hdcTemp,0,0,SRCCOPY);  
		ReleaseDC(hWnd,test);  
		ReleaseDC(hWnd,hdcTemp);  */

		InvalidateRect(hWnd,&reErase,TRUE);  

		break;  

	case WM_DESTROY:
		//	MessageBox(0,"是否保存当前修改","提示",0);

		DeleteObject(hPen);  
		DeleteObject(hPaintBit);  
		DeleteObject(hOriginalBit);  
		// DeleteObject(hBrush);   
		DeleteDC(hPaintDc);  
		DeleteDC(hOrignalDc);  


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
