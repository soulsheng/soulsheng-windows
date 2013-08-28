#include "windows.h"
//win32项目 空项目
int WINAPI WinMain (_In_  HINSTANCE hInstance,
	_In_  HINSTANCE hPrevInstance,
	_In_  LPSTR lpCmdLine,
	_In_  int nCmdShow)
{
	MessageBox(0,"hello world!","windows窗口",0);
	return 0;
}