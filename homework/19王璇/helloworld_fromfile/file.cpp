#include "windows.h"
#include "stdio.h"
#include "windows.h"
char line[30];
int WINAPI WinMain (_In_  HINSTANCE hInstance,
  _In_  HINSTANCE hPrevInstance,
  _In_  LPSTR lpCmdLine,
  _In_  int nCmdShow)
   { FILE *fp;
    fp=fopen("file.txt", "r");
	if(fp!=NULL){
    fread(line,sizeof(char),20,fp);
	MessageBox(0,line,"windows´°¿Ú",0);
	}
		return 0;
}