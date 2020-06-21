#ifndef _SNAKE_PROGRAM_h
#define _SNAKE_PROGRAM_H
//-----------------------------------
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <memory.h>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <cstring>
#include "graphic.h"
#include<iostream>
using namespace std;
//------------------------------------

//------------------------------------
#define MAX_SIZE 24             // Kích thước tối đa của con rắn
#define MAX_LEVEL 5             // Cấp độ tối đa
#define type 237                // Kí tự đặc biệt
#define LenInit 5               // Độ dài ban đầu của con rắn bất kì

enum Direction { W = 119, S = 115, D = 100, A = 97, enter = 13, esc = 27 , P = 112}; 
enum MODE{CLASSICAL, CHALLENGE, ADVANCED};         // Chế độ chơi
enum STATE{PLAY, PAUSE, EXIT};                     // Trạng thái trò chơi

struct point {                                     // Tọa độ
	int x;
	int y;
};

struct Info                                        // Record lưu file nhị phân
{
	point snake[MAX_SIZE];
	point fruit;
	int size;
	int score;
	int speed;
	int level;
	int dir;
	int Highscore;
	MODE mode;
};

point* SNAKE;                         // Mang con tro luu giu vi tri node ran
point  FRUIT;                         // Con tro luu giu vi tri food nho
point BFRUIT;                         // Luu vi tri trai cay to (CLASSICAL)

point  CAVE[5] = {{10,15},{20,15},{30,15},{40,15},{50,15}};
const char* MSSV = "D191204771912048419120495";

int	 Size;                           // kích thước con rắn hiện tại
string name;                       // tên người chơi
int  Speed;                          // Toc do con ran hien tai
int  Score;                          // Luu diem nguoi choi
int  HighScore;                      //Xem xet su dung sau
int  Level;                          // level tang sau moi man

STATE State;                         //Trang thai game: false = thua hoac dung, true = tiep tuc choi
                          
int	 Dir;                            //Biến di chuyển hiện tại 
int  file;                           //số lượng game đã lưu
MODE Mode;
bool New_game;
//int time_rec;                      // thời gian vẽ hình chữ nhật
//int time_snake;                    // thời gian vẽ chữ Snake

//-------------------------------------------

// Ham in ra 1 phan tu kieu Point
ostream& operator <<(ostream & devOut, point &p) {
	gotoXY(p.x, p.y); 
	devOut << (char)type;
	return devOut;
}

bool operator == (point a, point b) {// so sánh hai giá trị point
	if (a.x == b.x && a.y == b.y)
		return true;
	return false;
};
// Vẽ hình chữ nhật từ tọa độ x,y và có chiều cao height và chiều rộng width 
void draw_rectangle(int x, int y, int width, int height, int color);

// ------------------ HAM LOAD FILE ----------------------------------
void load_file(string* file, int& numFile) {// tải file game đã lưu
	// Khoi tao lai SNAKE
	if(SNAKE != NULL)
		delete[] SNAKE;

	SNAKE = new point[MAX_SIZE];

	// Doc toan bo ten file vao mang
	string fileName;
	fstream file_game("data/user.txt", ios::in);
	numFile = 0; // Bien luu giu so file trong user.txt

	while (!file_game.eof())
	{
		file_game >> fileName;
		file[numFile++] = fileName;
	};

	file_game.close();
};
// --------------------------------------------------------


// ------------ HAM KHOI TAO CON RAN NEW GAME --------------
void InitialSnake() {// khởi tạo con rắn cho hàm new game
	// Cap phat bo nho cho con ran
	SNAKE = new point[MAX_SIZE];
	//memset(SNAKE, 0, sizeof(point) * MAX_SIZE);
	for (register int i = MAX_SIZE - 1; i >= 0; --i)
	{
		SNAKE[i].x = 0;
		SNAKE[i].y = 0;
	};

	Size = LenInit;

	srand((int)time(NULL));
	//Size = LenInit;
	// Set up vi tri dau
	SNAKE[0].x = rand() % 39 + 12;  
	SNAKE[0].y = rand() % 13 + 2;

	for (register int i = 1; i < LenInit; ++i) 
	{  
		SNAKE[i].x = SNAKE[0].x - i;  
		SNAKE[i].y = SNAKE[0].y;  
	};
};
// -----------------------------------------------


// ----------- HAM TAO TRAI CAY MOI --------------
void InitialGrey() 
{
	bool flag;

	srand((int)time(NULL));

	while(true)
	{
		flag = false;

		FRUIT.x = rand() % 82 + 3;
		FRUIT.y = rand() % 27 + 2;

		for (register int i = 0; i < Size; ++i)
		{
			if (FRUIT == SNAKE[i])
			{
				flag = true;
				break;
			};
		};

		if (flag != false)
		{
			continue;
		}
		else
		{
			break;
		};
	};

	textcolor(13);
	cout << FRUIT;
	textcolor(7);
};
// -------------------------------------------------

// -------- HAM TAO TRAI CAY TO (CLASSICAL) --------
void InitialBigGrey()
{
	bool flag;

	srand((int)time(NULL));

	while (true)
	{
		flag = false;

		BFRUIT.x = rand() % 82 + 3;
		BFRUIT.y = rand() % 27 + 2;

		for (register int i = 0; i < Size; ++i)
		{
			if (BFRUIT == SNAKE[i])
			{
				flag = true;
				break;
			};
		};

		if (flag != false)
		{
			continue;
		}
		else
		{
			break;
		};
	};

	textcolor(12);
	gotoXY(BFRUIT.x, BFRUIT.y);
	cout << "*";
	textcolor(7);
};
// ----------------------------------------------------

// ---- HAM TAO HANG DONG QUA LEVEL MOI (CHALLENGE) ----
void InitialCave(bool UP = false, bool DOWN = false) {// khởi tạo cái hang cho con rắn
	int n = 154;

	textcolor(14);
	gotoXY(CAVE[Level - 1].x, CAVE[Level - 1].y);
	cout << (char)n;

	if (UP != false && DOWN == false) {
		gotoXY(CAVE[Level - 1].x - 1, CAVE[Level - 1].y);
		cout << (char)n;
		gotoXY(CAVE[Level - 1].x + 1, CAVE[Level - 1].y);
		cout << (char)n;
		gotoXY(CAVE[Level - 1].x - 1, CAVE[Level - 1].y - 1);
		cout << (char)154;
		gotoXY(CAVE[Level - 1].x + 1, CAVE[Level - 1].y - 1);
		cout << (char)154;
	}
	if (UP == false && DOWN != false) {
		gotoXY(CAVE[Level - 1].x - 1, CAVE[Level - 1].y);
		cout << (char)n;
		gotoXY(CAVE[Level - 1].x + 1, CAVE[Level - 1].y);
		cout << (char)n;
		gotoXY(CAVE[Level - 1].x - 1, CAVE[Level - 1].y + 1);
		cout << (char)154;
		gotoXY(CAVE[Level - 1].x + 1, CAVE[Level - 1].y + 1);
		cout << (char)154;
	}
	if (UP == false && DOWN == false) {
		gotoXY(CAVE[Level - 1].x, CAVE[Level - 1].y);
		cout << " ";
		gotoXY(CAVE[Level - 1].x - 1, CAVE[Level - 1].y);
		cout << " ";
		gotoXY(CAVE[Level - 1].x + 1, CAVE[Level - 1].y);
		cout << " ";
		gotoXY(CAVE[Level - 1].x - 1, CAVE[Level - 1].y - 1);
		cout << " ";
		gotoXY(CAVE[Level - 1].x + 1, CAVE[Level - 1].y - 1);
		cout << " ";
		gotoXY(CAVE[Level - 1].x - 1, CAVE[Level - 1].y + 1);
		cout << " ";
		gotoXY(CAVE[Level - 1].x + 1, CAVE[Level - 1].y + 1);
		cout << " ";
	};
	textcolor(7);
};

                // Ham kiem tra con ran dung hang
bool collision_cave(bool up = false, bool down = false) {// kiểm tra rắn chạm hang
	if (up != false && down == false) {
		if (SNAKE[0].x == CAVE[Level - 1].x - 1 && SNAKE[0].y == CAVE[Level - 1].y) return true;
		if (SNAKE[0].x == CAVE[Level - 1].x + 1 && SNAKE[0].y == CAVE[Level - 1].y) return true;
		if (SNAKE[0].x == CAVE[Level - 1].x - 1 && SNAKE[0].y == CAVE[Level - 1].y-1) return true;
		if (SNAKE[0].x == CAVE[Level - 1].x + 1 && SNAKE[0].y == CAVE[Level - 1].y-1) return true;
	};

	if (up == false && down != false) {
		if (SNAKE[0].x == CAVE[Level - 1].x - 1 && SNAKE[0].y == CAVE[Level - 1].y) return true;
		if (SNAKE[0].x == CAVE[Level - 1].x + 1 && SNAKE[0].y == CAVE[Level - 1].y) return true;
		if (SNAKE[0].x == CAVE[Level - 1].x - 1 && SNAKE[0].y == CAVE[Level - 1].y + 1) return true;
		if (SNAKE[0].x == CAVE[Level - 1].x + 1 && SNAKE[0].y == CAVE[Level - 1].y + 1) return true;
	}
	return false;
};
// -------------------------------------------------------------------------------------------------


// -------------- HAM TANG DO DAI CON RAN VA CAP NHAT TOA DO CELL -----------
void update_snake(int size = 0) 
{
	if (size != 0 && size <= MAX_SIZE)
	{
		++Size;
	};

	for (int i = Size - 1; i > 0; --i) {
		SNAKE[i] = SNAKE[i - 1];
	};
}
// ------------------------------------------------------------------


// -------- HAM VE O CHU NHAT KICH THUOC BAT KI ---------------------
void draw_rectangle(int x, int y, int wid, int hei, int color) 
{
	setTextColor(color);

	wid = wid + x;
	hei = hei + y;

	gotoXY(x, y); 
	cout << (char)178;
	gotoXY(wid, y); 
	cout << (char)178;
	gotoXY(wid, hei); 
	cout << (char)178;
	gotoXY(x, hei); 
	cout << (char)178;

	for (int i = x + 1; i < wid; i++) 
	{
		gotoXY(i, y); cout << (char)205;
		gotoXY(wid - i + x, hei); cout << (char)205;
		Sleep(5);
	};

	for (int i = y + 1; i < hei; i++) 
	{
		gotoXY(x, i); cout << (char)186;
		gotoXY(wid ,hei - i + y); cout << (char)186;
		Sleep(5);
	};
	/*gotoXY(wid + 2, y + 2); cout << "name: ";
	gotoXY(wid + 2, y + 3); cout << "lol_game";
	gotoXY(wid + 2, y + 5); cout << "level:";
	gotoXY(wid + 2, y + 6); cout << 999;*/

	textcolor(7);
};

// xóa một điểm trên màn hình
void delete_point(int x, int y)
{
	gotoXY(x, y); 
	cout << " ";
};

// hàm xóa phần bên trong cái khung ben phai
void delete_inside_table(int x, int y, int wid, int hei) 
{
	for (int i = x; i <= x + wid; i++) 
	{
		for (int j = y; j <= y + hei; j++) 
		{
			gotoXY(i, j);
			cout << " ";
		};
	};
};

//  ---------------- CAC HAM IN CON RAN ------------------
            // IN CON RAN CLASSICAL
void print_snake(int length)
{
	textcolor(10);
	for (register int i = 0; i < length; ++i)
		cout << SNAKE[i];
	textcolor(7);
};

            // IN CON RAN CHALLENGE
void print_mssv(int length) {// in ra mssv
	for (register int i = 0; i < length; ++i) 
	{
		gotoXY(SNAKE[i].x, SNAKE[i].y);
		if (i == 0)
		{
			textcolor(10);
			cout << (char)type;
		}
		else
		{
			textcolor(14);
			cout << MSSV[i];
		};
	};

	textcolor(7);
};
// -----------------------------------------------------------

// --------------------- HAM LUU GAME ---------------------------------
void save_game() 
{
	draw_rectangle(17, 12, 54, 4, 10); // Ve bang luu file
	gotoXY(18, 13);
	cout << "                                                     ";
	gotoXY(18, 14);
	cout << "                                                     ";
	gotoXY(18, 15);
	cout << "                                                     ";
	gotoXY(18, 13);
	cout << "         Do you want save game in new file?          ";

	// Bat dau thao tac save game
	int i = 0;
	while (true) {
		if (i == 0) {
			gotoXY(28, 14); setTextColor(4); cout << "YES";
			gotoXY(58, 14); setTextColor(7); cout << "NO";
		}
		if (i == 1) {
			gotoXY(28, 14); setTextColor(7); cout << "YES";
			gotoXY(58, 14); setTextColor(4); cout << "NO";
		}
		int c = _getch();
		if (c == D) {
			i++;
			if (i == 2) i = 0;
		}
		if (c == A) {
			--i;
			if (i < 0) i = 1;
		}
		if (c == enter)
		{
			if (i == 0)
			{
				break; // Chon YES thi thoat ra
			}
			else
			{
				return; // Chon NO thi thoat ham
			};
		};
	};
	
	// Xóa thông tin trong bảng chọn
	delete_inside_table(17, 12, 54, 4);

	// ---------- TẠO FILE NHỊ PHÂN SAO LƯU DỮ LIỆU ------------------- 
	Info game;

	// Sao lưu con rắn
	for (register int i = 0; i < MAX_SIZE; ++i)
	{
		game.snake[i].x = SNAKE[i].x;         // Sao lưu tọa độ từng đốt rắn
		game.snake[i].y = SNAKE[i].y;
	};
	game.fruit.x = FRUIT.x;                   // Sao lưu tọa độ trái cây
	game.fruit.y = FRUIT.y;

	game.score = Score;           // Sao lưu điểm
	game.size = Size;             // Sao lưu kích thước hiện tại
	game.speed = Speed;           // Sao lưu màn chơi 
	game.level = Level;           // Sao lưu tốc độ
	game.mode = Mode;             // Sao lưu chế độ chơi
	game.dir = Dir;               // Hướng chạy con rắn

	string fileName = name + ".dat";     // Tên tệp tin dữ liệu người chơi
	string address = "data/" + fileName; // Địa chỉ lưu file: data/file_user.dat

	// Bắt đầu kiểm tra file đã tồn tại chưa?
	fstream file_game("data/user.txt", ios::in);
	string oldFile;
	bool identical = false;

	while (!file_game.eof())
	{
		file_game >> oldFile; // Doc ten file da co trong user.txt

		if (oldFile == fileName) // Neu da co ten file xuat hien
		{
			identical = true;
			break;
		};
	};
	file_game.close();
	// ---------- Ket thuc check ---------

	// Nếu không trùng file, viết thêm tên vào file user.txt
	if (identical == false)
	{
		file_game.open("data/user.txt", ios::out | ios::app);
		file_game << fileName << "\n";
		file_game.close();

		// Lưu tập tin nhị phân
		file_game.open(address, ios::out | ios::binary);
		file_game.write(reinterpret_cast<char*>(&game), sizeof(game)); // Chép bản ghi vào tập tin
		file_game.close();
	}
	else // Nếu file đã tồn tại: ghi đè hoặc lưu file mới
	{
		draw_rectangle(17, 12, 54, 4, 10); // Ve bang luu file
		gotoXY(18, 13);
		cout << "                                                     ";
		gotoXY(18, 14);
		cout << "                                                     ";
		gotoXY(18, 15);
		cout << "                                                     ";
		gotoXY(35, 13);
		cout << "FILE ALREADY EXISTS !";

		// Bat dau thao tac save game
		int i = 0;
		while (true) {
			if (i == 0) {
				gotoXY(28, 15); setTextColor(4); cout << "OVERRIDE";
				gotoXY(58, 15); setTextColor(7); cout << "NEW FILE";
			}
			if (i == 1) {
				gotoXY(28, 15); setTextColor(7); cout << "OVERRIDE";
				gotoXY(58, 15); setTextColor(4); cout << "NEW FILE";
			}
			int c = _getch();
			if (c == D) {
				i++;
				if (i == 2) i = 0;
			}
			if (c == A) {
				--i;
				if (i < 0) i = 1;
			}
			if (c == enter)
			{
				if (i == 0)   // Chọn ghi đè
				{
					file_game.open(address, ios::out | ios::binary);
					file_game.write(reinterpret_cast<char*>(&game), sizeof(game)); // Ghi đè file
					file_game.close();
					break; 
				}
				else
				{
					delete_inside_table(17, 12, 54, 4);
					draw_rectangle(35, 13, 16, 4, 10);
					textcolor(9);
					gotoXY(36, 14); cout << "ENTER YOUR NAME";
					gotoXY(36, 15);	cout << "---------------";
					gotoXY(36, 15); cin >> name;
					textcolor(7);
					delete_inside_table(35, 13, 16, 4);

					fileName = name + ".dat";
					address = "data/" + fileName;

					file_game.open("data/user.txt", ios::out | ios::app);
					file_game << fileName << "\n";
					file_game.close();

					file_game.open(address, ios::out | ios::binary);
					file_game.write(reinterpret_cast<char*>(&game), sizeof(game));      // Ghi RECORD vao file
					file_game.close();
					break;
				};
			};
		};

		// Xóa thông tin trong bảng chọn
		delete_inside_table(17, 12, 54, 4);
	};
};
// ---------------------------------------------------

// hiển thị tọa độ cho dễ làm việc
void show_coord(int x = 106, int y = 35) 
{
	for (int i = 0; i < x; i++) 
	{
		gotoXY(i, 0);
		if(i%10 == 0)setTextColor(4);
		cout << i % 10;
		setTextColor(14);
	}
	for (int i = 0; i < y; i++) {
		gotoXY(0, i);
		if (i % 10 == 0)setTextColor(4);
		cout << i % 10;
		setTextColor(14);
	}
};

#endif