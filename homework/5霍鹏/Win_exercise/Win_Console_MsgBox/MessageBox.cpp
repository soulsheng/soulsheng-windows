#include "stdio.h"
#include "iostream"
using namespace std;
int main()
{
	//printf("Hello World!");

	FILE * pFile;
	//方法一：
	char character;
	//方法二：
	int count = 0;//用于文件中字节计数
	int n = 0;
	char characters[21]={0};

	if( (pFile = fopen ("file.txt","r")) != NULL )
	{
		//******************************************************
		//方法一：putchar
		//while((character=getc(pFile))!=EOF)
		//	putchar(character);
		//******************************************************
		//方法二：fread
		while((character=getc(pFile))!=EOF)
		{
			count++;
			if(count == 20)		
			{
				fseek(pFile,20*n,SEEK_SET);//指向文件某一位置
				fread(characters,sizeof(char),count,pFile);
				printf("%s\n", characters);
				count = 0;
				n++;
			}
		}
		//printf("%d\n", n);
		for(int i=0;i<=20;i++)
			characters[i]=0;
		fseek(pFile,20*n,SEEK_SET);
		fread(characters,sizeof(char),count,pFile);
		printf("%s\n", characters);
		//******************************************************	
	}
	else
		printf("NULL");
	fclose(pFile); 
	system("pause");
	return 0;
}