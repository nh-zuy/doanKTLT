#ifndef _GRAPHIC
#define _GRAPHIC

#pragma once
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <vector>


#define BLACK_COLOR			0
#define DARK_BLUE_COLOR		1
#define DARK_GREEN_COLOR	2
#define DARK_CYAN_COLOR		3
#define DARK_RED_COLOR		4
#define DARK_PINK_COLOR		5
#define DARK_YELLOW_COLOR	6
#define DARK_WHITE_COLOR	7
#define GREY_COLOR			8
#define BLUE_COLOR			9
#define GREEN_COLOR			10
#define CYAN_COLOR			11
#define RED_COLOR			12
#define PINK_COLOR			13
#define YELLOW_COLOR		14
#define WHITE_COLOR			15

#define KEY_UP		1072
#define KEY_DOWN	1080
#define KEY_LEFT	1075
#define KEY_RIGHT	1077
#define KEY_NONE	-1

// HAM BAT SU KIEN BAN PHIM
int inputKey()
{
	if (_kbhit())
	{
		int key = _getch();

		if (key == 224)		
		{
			key = _getch();
			return key + 1000;
		};

		return key;
	};

	return KEY_NONE;
}

// delete screen
void clrscr() {
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = { 0,0 };
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
};

// Di chuyen con tro toi toa do (x,y)
void gotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};


int whereX() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.X;
	return -1;
};
int whereY() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.Y;
	return -1;
};

// Xoa con tro nhap nhay tren console
void noCursorType() {
	CONSOLE_CURSOR_INFO info;
	info.bVisible = FALSE;
	info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
};

// Chuyen mau text in ra console
void setTextColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
};

// Khoa kich thuoc console
void fix_console_window() {
	HWND consolewindow = GetConsoleWindow();
	LONG style = GetWindowLong(consolewindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) &~(WS_THICKFRAME);
	SetWindowLong(consolewindow, GWL_STYLE, style);

}

// Thay doi kich co console
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
};

void textcolor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
};

void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x - 1,y - 1 };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
};

#endif