// text.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "text.h"
#include <stdio.h>
#include <iostream>
#include <Windowsx.h>

#define MAX_LOADSTRING 100
using namespace std;
// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������
FILE *stream;
char textcontent[1024];
char textinformation[1024];
int nCount;
int xPosition[2];
int yPosition[2];
int choices=0;
int pchoice=0;
// �˴���ģ���а����ĺ�����ǰ������:
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

 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TEXT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEXT));

	// ����Ϣѭ��:
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
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
//  ע��:
//
//    ����ϣ��
//    �˴�������ӵ� Windows 95 �еġ�RegisterClassEx��
//    ����֮ǰ�� Win32 ϵͳ����ʱ������Ҫ�˺��������÷������ô˺���ʮ����Ҫ��
//    ����Ӧ�ó���Ϳ��Ի�ù�����
//    ����ʽ��ȷ�ġ�Сͼ�ꡣ
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
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

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
   strcpy(textinformation,"�������ѡ���ǩλ��");
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
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
		// �����˵�ѡ��:
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
				MessageBox(0,textcontent,_T("�ı�����"),0);
				fclose(stream);
			}
			else
			{
				MessageBox(0,"���ļ�ʧ��","��ʾ",0);
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
		// TODO: �ڴ���������ͼ����...
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

// �����ڡ������Ϣ�������
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
