#pragma once
#include<iostream>
#include"Windows.h"
using namespace std;
COORD getxy(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	GetConsoleScreenBufferInfo(hConsole, &bufferInfo);
	return bufferInfo.dwCursorPosition;
}
void gotoxy(int xpos, int ypos) {
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos;
	scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}
class ProcessBar {
public:
	int TotalSize;
	int Parts;
	int x;
	int y;
	int Current;
	ProcessBar(int TotalSize, int Parts, int x, int y) {
		this->TotalSize = TotalSize;
		this->Parts = Parts;
		this->x = x;
		this->y = y;
		Current = 0;
	}
	void Begin() {
		gotoxy(x, y);
		printf("[");
		for (int i = 0; i <= Parts; i++)printf("_");
		printf("]");
	}
	void Update(int pos) {
		if (pos > Current * (TotalSize / Parts)) {
			gotoxy(Current + 1 + x, y);
			printf( "#");
			Current++;
		};
	};
};