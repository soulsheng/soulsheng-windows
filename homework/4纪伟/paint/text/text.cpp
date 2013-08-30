// text.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "text.h"
#include <stdio.h>
#include <iostream>
#include <Windowsx.h>

#define MAX_LOADSTRING 100
using namespace std;
// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名
FILE *stream;
char textcontent[1024];
char textinformation[1024];
int nCount;
int xPosition[2];
int yPosition[2];
int choices=0;
int pchoice=0;
// 此代码模块中包含的函数的前向声明:
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

 	// TODO: 在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TEXT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEXT));

	// 主消息循环:
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
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
//  注释:
//
//    仅当希望
//    此代码与添加到 Windows 95 中的“RegisterClassEx”
//    函数之前的 Win32 系统兼容时，才需要此函数及其用法。调用此函数十分重要，
//    这样应用程序就可以获得关联的
//    “格式正确的”小图标。
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEXT));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_TEXT);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 将实例句柄存储在全局变量中

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   for (int i=0;i<1024;i++)
   {
	   textcontent[i]=0;
	   textinformation[i]=0;
   }
   nCount=0;
   xPosition[0]=0;
   yPosition[0]=0;
   xPosition[1]=0;
   yPosition[1]=0;
   strcpy(textinformation,"请用鼠标选择便签位置");
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect,rectdiy;
	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_YES:
			choices=1;
			break;
		case ID_NO:
			choices=0;
			break;
		case ID_LINE:
			pchoice=1;
			break;
		case ID_RECTANGLE:
			pchoice=2;
			break;
		case ID_ELL:
			pchoice=3;
			break;


		case ID_OPEN:
			if (choices==0)
			{
				if( (stream  = fopen( "1.txt", "r" )) != NULL )
			{
				nCount=nCount+fread(textcontent,sizeof(char),1024,stream);
				MessageBox(0,textcontent,_T("文本内容"),0);
				fclose(stream);
			}
			else
			{
				MessageBox(0,"打开文件失败","提示",0);
			}
			}
			
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		GetClientRect(hWnd,&rectdiy);
		InvalidateRect(hWnd,&rectdiy,TRUE);
		break;
	case WM_PAINT:
		if (choices==0)
		{
			hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此添加任意绘图代码...
		TextOut(hdc,0,0,textinformation,strlen(textinformation));
		MoveToEx(hdc,xPosition[0],yPosition[0],0);
		LineTo(hdc,xPosition[1],yPosition[0]);
		LineTo(hdc,xPosition[1],yPosition[1]);
		LineTo(hdc,xPosition[0],yPosition[1]);
		LineTo(hdc,xPosition[0],yPosition[0]);
		if (yPosition[1]!=0)
		{
			rectdiy.bottom=yPosition[1];
			rectdiy.left=xPosition[0]+10;
			rectdiy.right=xPosition[1];
			rectdiy.top=yPosition[0]+10;
			DrawText(hdc,textcontent,nCount,&rectdiy,0);
		}


		EndPaint(hWnd, &ps);
		}
		if (pchoice==1)
		{
			hdc = BeginPaint(hWnd, &ps);
			MoveToEx(hdc,xPosition[0],yPosition[0],0);
			LineTo(hdc,xPosition[1],yPosition[1]);
			EndPaint(hWnd, &ps);
		}
		else if (pchoice==2)
		{
			hdc = BeginPaint(hWnd, &ps);
			Rectangle(hdc,xPosition[0],yPosition[0],xPosition[1],yPosition[1]);
			EndPaint(hWnd, &ps);
		}
		else if (pchoice==3)
		{
			hdc = BeginPaint(hWnd, &ps);
			Ellipse(hdc,xPosition[0],yPosition[0],xPosition[1],yPosition[1]);
			EndPaint(hWnd, &ps);
		}
		break;
		

	case WM_LBUTTONDOWN:
		xPosition[0]=GET_X_LPARAM(lParam);
		yPosition[0]=GET_Y_LPARAM(lParam);
		break;
	case WM_LBUTTONUP:
		xPosition[1]=GET_X_LPARAM(lParam);
		yPosition[1]=GET_Y_LPARAM(lParam);
		GetClientRect(hWnd,&rect);
		InvalidateRect(hWnd,&rect,TRUE);
		
		break;
	case WM_CHAR:
		textcontent[nCount]=wParam;
		nCount++;
		GetClientRect(hWnd,&rectdiy);
		InvalidateRect(hWnd,&rectdiy,TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
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
