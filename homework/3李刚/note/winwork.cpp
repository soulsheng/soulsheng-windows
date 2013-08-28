// winwork.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "winwork.h"
#include <stdio.h>
#include "stdafx.h"
#include "Windowsx.h "
#define MAX_LOADSTRING 100
#include <atlstr.h>
#include <string>
#include <cstring>
#include <string>

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
char textcontent[1024];                         //存储打开txt文件的 内容 
int nCount[3];                                  //3个便笺的内容长度计数
int xPosition[1024],yPosition[1024];            //记录鼠标的坐标
char greeting[1024];                            //存储3个便笺的内容
char greeting1[1024];
char greeting2[1024];

char welcome[1024];                               //显示提示信息
int welCount;                                     //提示信息 的长度

RECT rect, rectdiy;                         
int nbCount;                                      //记录便笺的个数

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
	LoadString(hInstance, IDC_WINWORK, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINWORK));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINWORK));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WINWORK);
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

                                                      //下面是进行相应的初始化
	for (int i=0;i<1024;i++)
	{
		xPosition[i]=0;
		yPosition[i]=0;;
	}
	for (int i=0;i<1024;i++)
	{
		greeting[i]=0;
		greeting1[i]=0;
		greeting2[i]=0;
	}

	nCount[0]=0;
	nCount[1]=0;
	nCount[2]=0;
	nbCount=1;

	strcpy(welcome,"说明:菜单Open来打开一个固定的文件，鼠标来进行创建便笺,键盘输入便笺内容，最多3个.");
	welCount=strlen(welcome);

	strcpy(greeting,"");
	strcpy(greeting1,"");
	strcpy(greeting2,"");
	nCount[0]=strlen(greeting)-1;
	nCount[1]=strlen(greeting1)-1;
	nCount[2]=strlen(greeting2)-1;


   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW|WS_VISIBLE,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

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
	FILE *stream;   
	int i=1;

	RECT welrect;                                     //提示信息显示区域


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
		case ID_OPEN_OPENTXT:      //打开并读取txt文件 
			if( (stream  = fopen( "aaa.txt", "r" )) != NULL )
			{
				//MessageBox(0,mes,_T("文件"),0);
				int i=fread(textcontent,sizeof(char),1024,stream);
				MessageBox(0,textcontent,_T("文件"),0);                         //将文件内容输出到messagebox中去

				fclose(stream);
			}
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
	hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
	welrect.left=0;
	welrect.right=800;
	welrect.top=0;
	welrect.bottom=20;
	 DrawText(hdc,welcome,welCount,&welrect,0);
		/*
		rectdiy.left=200;
		rectdiy.right=500;
		rectdiy.top=200;
		rectdiy.bottom=500;
		*/
	/*
		if (xPosition[nbCount*2-3]<xPosition[2*nbCount-2])
		{
			rectdiy.left=xPosition[nbCount*2-3]+5;
			rectdiy.right=xPosition[2*nbCount-2];
		}
		else
		{
			rectdiy.left=xPosition[2*nbCount-2]+5;
			rectdiy.right=xPosition[nbCount*2-3];
		}
		if (yPosition[nbCount*2-3]<yPosition[2*nbCount-2])
		{
			rectdiy.top=yPosition[nbCount*2-3]+5;
			rectdiy.bottom=yPosition[2*nbCount-2];
		}
		else
		{
			rectdiy.top=yPosition[2*nbCount-2]+5;
			rectdiy.bottom=yPosition[nbCount*2-3];
		}
		*/
		
		/*
		for (int i=1;i<nCount-1;i++)
		{
			MoveToEx(hdc,xPosition[i-1],yPosition[i-1],0);
			LineTo(hdc,xPosition[i],yPosition[i]);
		}
		*/

	for(int n=2;n<=4;n++)                                    //绘制便笺框
		{
	   MoveToEx(hdc,xPosition[2*n-3],yPosition[2*n-3],0);
		LineTo(hdc,xPosition[2*n-2],yPosition[2*n-3]);
		MoveToEx(hdc,xPosition[2*n-2],yPosition[2*n-3],0);
		LineTo(hdc,xPosition[2*n-2],yPosition[2*n-2]);
		MoveToEx(hdc,xPosition[2*n-2],yPosition[2*n-2],0);
		LineTo(hdc,xPosition[2*n-3],yPosition[2*n-2]);
		MoveToEx(hdc,xPosition[2*n-3],yPosition[2*n-2],0);
		LineTo(hdc,xPosition[2*n-3],yPosition[2*n-3]);


		if (xPosition[n*2-3]<xPosition[2*n-2])                  //确定 便笺的区域
		{
			rectdiy.left=xPosition[n*2-3]+5;
			rectdiy.right=xPosition[2*n-2];
		}
		else
		{
			rectdiy.left=xPosition[2*n-2]+5;
			rectdiy.right=xPosition[n*2-3];
		}
		if (yPosition[n*2-3]<yPosition[2*n-2])
		{
			rectdiy.top=yPosition[n*2-3]+5;
			rectdiy.bottom=yPosition[2*n-2];
		}
		else
		{
			rectdiy.top=yPosition[2*n-2]+5;
			rectdiy.bottom=yPosition[n*2-3];
		}
		//int m=strlen(greeting);
          if (n==2)                                                  //输出便笺的内容
          {
			  DrawText(hdc,greeting,nCount[n-2],&rectdiy,0);
          } 
          else if(n==3)
          {
			    DrawText(hdc,greeting1,nCount[n-2],&rectdiy,0);
          }
		  else if(n==4)
		  {
			    DrawText(hdc,greeting2,nCount[n-2],&rectdiy,0);
		  }

		}	


		
	//	MessageBox(0,g[1],NULL,0);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN :
		{
			if (nbCount>=4)
			{
				nbCount=1;
			} 

			switch(nbCount)
			{
			case 1:
				{
					strcpy(greeting,"");			 
					nCount[0]=strlen(greeting)-1;
					break;
				}
			case  2:
				{
					strcpy(greeting1,"");
					nCount[1]=strlen(greeting1)-1;
					break;
				}
			case 3:
				{
					strcpy(greeting2,"");
					nCount[2]=strlen(greeting2)-1;
					break;
				}
			}

				xPosition[2*nbCount-1]=GET_X_LPARAM(lParam);              //获取左键按下时的坐标
			    yPosition[2*nbCount-1]=GET_Y_LPARAM(lParam);	
			
			break;
		}
	case WM_LBUTTONUP :
		{
			xPosition[2*nbCount]=GET_X_LPARAM(lParam);                    //获取左键抬起时的坐标
			yPosition[2*nbCount]=GET_Y_LPARAM(lParam);

			nbCount++;
		//	GetClientRect(hWnd,&rect);

		//	InvalidateRect(hWnd,&rect,TRUE);

		}
	case  WM_CHAR :
		if (nbCount==2)                                                     //获取键盘输入的字符
		{
			greeting[nCount[0]]=wParam;
			nCount[0]++;
		} 
		else if(nbCount==3)
		{
			greeting1[nCount[1]]=wParam;
			nCount[1]++;
		}
		else if (nbCount==4)
		{
			greeting2[nCount[2]]=wParam;
			nCount[2]++;
		}
	

		GetClientRect(hWnd,&rect);

		InvalidateRect(hWnd,&rect,TRUE);
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
