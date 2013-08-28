// OpenTxt_sec.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "OpenTxt_sec.h"
#include <windows.h> 
#include <commdlg.h>
#define MAX_LOADSTRING 100
#include <string>
// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
/*static*/ OPENFILENAME ofn;
// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);



void open_file(char szPath[MAX_PATH]);
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
	LoadString(hInstance, IDC_OPENTXT_SEC, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OPENTXT_SEC));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OPENTXT_SEC));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_OPENTXT_SEC);
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
BOOL openDlg(HWND hwnd, TCHAR* fullPath, TCHAR* fileName) {
	
	static TCHAR szFilter[] = TEXT("Text Files(*.txt)\0*.txt\0") \
		TEXT("All Files(*.*)\0*.*\0\0");
	// 确定结构的大小

	ofn.lStructSize = sizeof(OPENFILENAME);
	// 指定它的父窗口

	ofn.hwndOwner = hwnd;
	// 一般为NULL，表示我们使用的是通用对话框

	// ，当然我们也可以自定义对话框，此时hInstance指示

	// 资源的handle。

	ofn.hInstance = NULL;
	// 指示打开或者保存文件时的过滤器，比如说：

	// static TCHAR szFilter[] = TEXT("Text Files(*.txt)\0*.txt\0") \

	//    TEXT("All Files(*.*)\0*.*\0\0");

	// 结构是这样的:描述\0过滤\0, 最后一项必须是两个\0,

	// 详情请参考MSDN。

	ofn.lpstrFilter = szFilter;
	// 一般为NULL

	ofn.lpstrCustomFilter = NULL;
	// 一般为0

	ofn.nMaxCustFilter = 0;
	// 指示默认过滤器为第几项

	ofn.nFilterIndex = 0;
	// 用于保存文件的完事路径及文件名

	ofn.lpstrFile = fullPath;
	// 指示上面结构的大小

	ofn.nMaxFile = MAX_PATH;
	// 用于保存文件名，不包括路径

	ofn.lpstrFileTitle = fileName;
	// 指示上面结构的大小

	ofn.nMaxFileTitle = MAX_PATH;
	// 指示打开对话框的第一路径，

	// 我发现为NULL时，初始化路径总是

	// “我的文档”。

	ofn.lpstrInitialDir = NULL;
	// 指示对话框的caption, 我们一般为NULL，

	// 让系统指示， 当然也可以自己设置。

	ofn.lpstrTitle = NULL;
	// 这个东西在打开保存等有点不同，下面是为了打开而设置的

	// 我们以后会看到保存时此项的设置。

	ofn.Flags = OFN_HIDEREADONLY;
	// 为0就可以了

	ofn.nFileOffset = 0;
	// 为0就可以了

	ofn.nFileExtension = 0;
	// 如果你保存的时候忘记加.txt时，

	// 它会自动给你加上。

	ofn.lpstrDefExt = TEXT("txt");
	// 为0就可以了

	ofn.lCustData = 0;
	// 为NULL就可以了

	ofn.lpfnHook = NULL;
	// 如果想定制对话框， 下面的就不能为NULL了

	// 但是我们一般为NULL。

	ofn.lpTemplateName = NULL;

	return GetOpenFileName(&ofn);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	static TCHAR fullPath[MAX_PATH], fileName[MAX_PATH];
	TCHAR* pText;
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
		case ID_OPEN:
			//MessageBox(hWnd,"01234","读取文本文件",0);
			
			if(!openDlg(hWnd, fullPath, fileName)) {
			MessageBox(NULL, TEXT("can not open file."),
			TEXT("Error"), MB_ICONERROR);
			fullPath[0] = '\0';
			fileName[0] = '\0';
			}
			open_file(fullPath);
			
			/*
			if(!openReadFile(hwndEdit, fullPath)) {
			MessageBox(NULL, TEXT("error read file."),
			TEXT("Error"), MB_ICONERROR);
			fullPath[0] = '\0';
			fileName[0] = '\0';
			return 0;
			}
			break;*/
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
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
void open_file(char szPath[MAX_PATH])
{
	HANDLE hFile;
	//TCHAR szPath[MAX_PATH] = TEXT("E:\\info.txt");
	hFile = CreateFile(szPath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE) {
		DWORD dwSize;
		dwSize = GetFileSize(hFile, NULL);
		if (dwSize > 0) {
			LPTSTR lpStr;
			lpStr = (LPTSTR)GlobalAlloc(GPTR, dwSize + 1);
			if (lpStr != NULL) {
				DWORD dwRead;
				if (ReadFile(hFile, lpStr, dwSize, &dwRead, NULL)) {
					MessageBoxA(GetActiveWindow(), lpStr, "提示", MB_OK);
				}
				GlobalFree(lpStr);
			}
		}
		CloseHandle(hFile);
	}
}