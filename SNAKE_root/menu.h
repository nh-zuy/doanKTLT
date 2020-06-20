#ifndef _MENU_H
#define _MENU_H

#include<iostream>
#include<conio.h>
#include<string>
#include<time.h>
#include<stdlib.h>
#include"graphic.h"
#include<fstream>
using namespace std;

#define WIDTH  800           // Chieu rong man hinh console
#define HEIGHT 600           // Chieu cao man hinh console 
#define width	83           // Chieu rong khung menu
#define height	28           // Chieu cao khung menu
#define x_rec 2              // Toa do x theo hinh chu nhat
#define y_rec 1              // Tao do y theo hinh chu nhat

// ----------- XOA MENU ----------------------
void delete_menu(int y1 = 1, int y2 = height)
{
	for (register int i = y1; i < y2; ++i) 
	{
		gotoXY(x_rec + 1, y_rec + i);
		cout << "                                                                                  ";
	};
};
// -------------------------------------------

// ---------------- EXIT GAME ----------------
void exit_game(int state = 0, int choose = 0)
{
	if (state != 0)
	{
		if (choose == 0)
		{
			delete_inside_table(87, 2, 16, 26);
			setTextColor(7);
			gotoXY(87, 13);
			textcolor(13);
			cout << " SNAKE GOOD BYE! ";
			textcolor(7);
		}
		else
		{
			delete_menu();
			draw_rectangle(24, 8, 40, 10, 12);
			int i = 0;
			while (true) {
				delete_inside_table(25, 11, 38, 1);
				delete_inside_table(87, 2, 16, 26);
				textcolor(10);
				gotoXY(34, 11); cout << "DO YOU WANT EXIT GAME?";
				if (i == 0)
				{
					setTextColor(4); gotoXY(30, 14); cout << "YES";
					setTextColor(10); gotoXY(58, 14); cout << "NO";
				}
				if (i == 1)
				{
					setTextColor(10); gotoXY(30, 14); cout << "YES";
					setTextColor(4); gotoXY(58, 14); cout << "NO";
				}
				int key = _getch();
				if (key == D)
				{
					i++; if (i == 2) i = 0;
				}
				if (key == A)
				{
					if (i == 0) i = 2;
					i--;
				}
				if (key == enter)
					if (i == 0)
					{
						delete[] SNAKE;
						SNAKE = NULL;
						clrscr();
						exit(0);
					}
					else
					{
						State = PLAY;
						return;
					};
			};
			textcolor(7);
		};
	};
};
// ----------------------------------------------------------

// --------------------- PAUSE GAME -------------------------
void pause_game()
{
	draw_rectangle(24, 8, 40, 10, 12);
	int choose = 0;
	while (true) {
		delete_inside_table(25, 9, 38, 7);

		textcolor(10);
		gotoXY(39, 11); cout << "PAUSE GAME";

		if (choose == 0)
		{
			setTextColor(4); gotoXY(30, 14); cout << "CONTINUE";
			setTextColor(10); gotoXY(50, 14); cout << "BACK TO MENU";
		}
		else if (choose == 1)
		{
			setTextColor(10); gotoXY(30, 14); cout << "CONTINUE";
			setTextColor(4); gotoXY(50, 14); cout << "BACK TO MENU";
		};

		int key = _getch();
		if (key == D)
		{
			++choose; 
			if (choose == 2) 
				choose = 0;
		}
		else if (key == A)
		{
			if (choose == 0) 
				choose = 2;
			--choose;
		}
		else if (key == enter)
		{
			
			if (choose == 0)
			{
				delete_inside_table(24, 8, 40, 10);
				State = PLAY;
				return;
			}
			else
			{
				delete_inside_table(24, 8, 40, 10);
				delete_inside_table(87, 2, 16, 26);
				return;
			};
		};
	};
	
	textcolor(7);
};
// ----------------------------------------------------------

// ------------------- HAM BAT SU KIEN ----------------------
void take_event(int &n)
{
	int key = inputKey();

	if (key == A || key == S || key == D || key == W || key == 27 || key == P)
	{
		if (key == A && n == D) return;
		if (key == D && n == A) return;
		if (key == W && n == S) return;
		if (key == S && n == W) return;
		n = key;
	};
};
// -----------------------------------------------------------


// -------------- KIEM TRA VA CHAM --------------------------
bool check_collision()
{
	if (SNAKE[0].x == 2 || SNAKE[0].x == 85 || SNAKE[0].y == 1 || SNAKE[0].y == 29)
	{
		return true;
	};

	for (int i = 3; i < Size; i++)
	{
		if (SNAKE[0] == SNAKE[i])
		{
			return true;
		};
	};

	return false;
};
// --------------------------------------------------------------


// ---------------- HAM IN, XOA THOI GIAN -----------------------
      /* Hien thi thoi gian */
void showTime(int timer)
{
	if (timer < 10)
	{
		gotoXY(74, 21);
		cout << " ";
	}
	
	gotoXY(73, 21);
	cout << timer;
};
     /* Xoa thoi gian */
void hideTime(int timer)
{
	gotoXY(72, 21);
	cout << "    ";
};
// -------------------------------------------

// ------------------ CLASSICAL ---------------------
void play_classical(int mssv = 0, int n = D)
{
	// Xoa MENU
	delete_menu();
	// Xoa bang thong tin trong menu
	delete_inside_table(87, 2, 16, 26);

	// In che do choi
	textcolor(12);
	gotoxy(91, 5);
	cout << "CLASSICAL";
	textcolor(7);

	// In ten
	textcolor(14);
	gotoXY(90, 11);
	cout << " NAME:" << name;
	gotoxy(88, 13);
	std::cout << " --------------- ";
	textcolor(7);

	textcolor(8);
	gotoXY(89, 20);
	cout << "P : Pause";
	gotoXY(89, 22);
	cout << "Esc: Save";
	textcolor(7);

	// Khoi tao fruit TO, bo dem thoi gian
	short int timer = 30;
	short int counter = 0;
	bool available = false;

	// Ve con ran CLASSICAL
	print_snake(Size);

	// An phim bat ki de bat dau
	_getch();

	// Khoi tao trai cay nho dau tien
	InitialGrey();
	// Vong lap chinh cua CLASSICAL
	while (true)
	{
		//InitialGrey();
		// Hien thi LEVEL, SCORE, SIZE o o ben canh
		textcolor(12);
		gotoXY(89, 14);
		cout << char(16) << " LEVEL: " << Level;
		gotoXY(89, 16);
		cout << char(16) << " SCORE: " << Score;
		gotoXY(89, 18);
		cout << char(16) << " SIZE: " << Size;
		textcolor(11);

		// Lay toa do duoi
		point tail = SNAKE[Size - 1];

		// Doc su kien ban phim
		take_event(n);

		switch (n)
		{
		case A: // Sang trai
		{
			Dir = n;
			update_snake();
			--SNAKE[0].x;
			// Cham bien trai thi di ra bien phai
			if (SNAKE[0].x == 2)
			{
				SNAKE[0].x = 84;
			};
			break;
		};
		case S: // Di xuong
		{
			Dir = n;
			update_snake();
			++SNAKE[0].y;
			// Cham bien duoi thi ra bien tren
			if (SNAKE[0].y == 29)
			{
				SNAKE[0].y = 2;
			};
			break;
		};
		case D: // Sang phai
		{
			Dir = n;
			update_snake();
			++SNAKE[0].x;
			// Neu cham bien phai thi ra bien trai
			if (SNAKE[0].x == 85)
			{
				SNAKE[0].x = 3;
			};
			break;
		};
		case W: // Di len
		{
			Dir = n;
			update_snake();
			--SNAKE[0].y;
			// Neu cham bien tren thi ra bien duoi
			if (SNAKE[0].y == 1)
			{
				SNAKE[0].y = 28;
			};
			break;
		};
		case P:
			State = PAUSE;
			return;
		case 27:
			return;				//return ve ham new_game
		};

		// Dieu chinh toc do con ran
		Sleep(Speed);

		// Xoa duoi con ran
		delete_point(tail.x, tail.y);

		// In lai vi tri con ran moi
		print_snake(Size);

		// Kiem tra va cham voi than SNAKE
		for (register int i = 3; i < Size; ++i)
		{
			if (SNAKE[0] == SNAKE[i])
			{
				State = EXIT;

				// Xu li khi con ran chet
				timer = 0;

				while (timer < 3)
				{
					// Giat 1 lan
					textcolor(12);
					for (register int cell = 0; cell < Size; ++cell)
					{
						cout << SNAKE[cell];
					};

					Sleep(300);

					// Giat lan 2
					textcolor(7);
					for (register int cell = 0; cell < Size; ++cell)
					{
						cout << SNAKE[cell];
					};

					Sleep(200);

					++timer;
				};

				return;
			};
		};

		// Neu SNAKE an trung FRUIT
		if (SNAKE[0] == FRUIT)
		{
			++Score;
			++counter;

			if (Score % 4 == 0 && Level < MAX_LEVEL) // Toi da 5 level
			{
				++Level; // Tang level
				Speed -= 35; // Tang toc
			};
			update_snake(Size);

			InitialGrey();
		};

		// Neu an du 5 trai cay nho thi hien 1 trai cay TO
		if (counter == 5)
		{
			// Random vi tri trai cay to
			InitialBigGrey();
			available = true;
			counter = 0; // Xoay lai bo dem ve 0
		};

		// Neu trai cay to san sang
		if (available)
		{
			// Dem thoi gian
			showTime(timer);
			--timer;

			// Neu het thoi gian
			if (timer == 0)
			{
				// Xoa thoi gian, xoa trai cay
				hideTime(timer);
				
				// Xoa trai cay to
				gotoXY(BFRUIT.x, BFRUIT.y);
				cout << " ";

				// Khoi tai lai co che
				available = false;
				timer = 30;

				// In ra trai cay nho khac
				InitialGrey();
			};
		};

		// Xu li khi con ran an dc trai cay to
		if (SNAKE[0] == BFRUIT && available == true)
		{
			Score += 8; // An duoc trai cay to thi dc tang 8 diem

			hideTime(timer); // Xoa thoi gian

			// Khoi tao lai tu dau
			available = false; // Set up lai dieu kien trai cay to
			timer = 30;  // Set up lai thoi gian
			counter = 0; // Set up lai bo dem
		};
	};
};
// ---------------------------------------------------------------------


// ------------------------ CHALLENGE ----------------------------------
void play_game(bool mssv = 0, int n = D)
{
	// Xoa menu
	delete_menu();
	// Xoa thong tin trong menu
	delete_inside_table(87, 2, 16, 26);

	// In che do choi
	textcolor(12);
	gotoxy(91, 5);
	cout << "CHALLENGE";
	textcolor(7);

	textcolor(14);
	gotoXY(90, 11); 
	cout << " NAME:" << name;
	gotoxy(88, 13);
	std::cout << " --------------- ";
	textcolor(7);

	textcolor(8);
	gotoXY(89, 20); cout << "P: PAUSE";
	gotoXY(89, 22); cout << "Esc: SAVE";
	textcolor(7);

	textcolor(11);

	// In con ran
	print_mssv(Size);

	_getch();

	bool flag;

	while (true)
	{
		flag = false;

		if (Score % 4 != 0 || Score == 0)
		{
			InitialGrey(); // Tao fruit
		}
		else
		{
			InitialCave(1); // Du diem, VE HANG DONG
			flag = true;
		};

		textcolor(12);
		gotoXY(89, 14); 
		cout << char(16) << " LEVEL: " << Level;
		gotoXY(89, 16);
		cout << char(16) << " SCORE: " << Score;
		gotoXY(89, 18);
		cout << char(16) << " SIZE: " << Size;
		textcolor(11);

		while (true)
		{
			// Lay toa do duoi
			point tail = SNAKE[Size - 1];

			// Doc su kien ban phim
			take_event(n);

			switch (n)
			{
			case A: // Sang trai
				Dir = n;
				update_snake();
				SNAKE[0].x--;
				break;
			case S: // Di xuong
				Dir = n;
				update_snake();
				SNAKE[0].y++;
				break;
			case D: // Sang phai
				Dir = n;
				update_snake();
				SNAKE[0].x++;
				break;
			case W: // Di len
				Dir = n;
				update_snake();
				SNAKE[0].y--;
				break;
			case P:
			{
				State = PAUSE;
				return;
			};
			case 27:
				return;				//return ve ham new_game
			};

			// Dieu chinh toc do con ran
			Sleep(Speed);

			// Xoa duoi con ran
			delete_point(tail.x, tail.y);

			// In con ran tai vi tri moi
			print_mssv(Size);

			// Ham kiem tra va cham
			if (check_collision())
			{
				State = EXIT;

				// Xu li khi con ran chet
				int timer = 0;
				while (timer < 3)
				{
					// Giat 1 lan
					textcolor(12);
					for (register int cell = 0; cell < Size; ++cell)
					{
						gotoXY(SNAKE[cell].x, SNAKE[cell].y);

						if (cell == 0)
						{
							cout << SNAKE[cell];
						}
						else
						{
							cout << MSSV[cell];
						};
					};

					Sleep(300);

					// Giat lan 2
					textcolor(7);
					for (register int cell = 0; cell < Size; ++cell)
					{
						gotoXY(SNAKE[cell].x, SNAKE[cell].y);

						if (cell == 0)
						{
							cout << SNAKE[cell];
						}
						else
						{
							cout << MSSV[cell];
						};
					};

					Sleep(200);

					++timer;
				};

				return;		//return ve ham new_game
			};

			if (SNAKE[0] == FRUIT && flag == false)
			{
				++Score;
				update_snake(Size);
				break;
			};

			// Neu dung trung cai cong thi thua
			if (collision_cave(true) && flag)
			{
				State = EXIT;

				// Xu li khi con ran chet
				int timer = 0;
				while (timer < 3)
				{
					// Giat 1 lan
					textcolor(12);
					for (register int cell = 0; cell < Size; ++cell)
					{
						gotoXY(SNAKE[cell].x, SNAKE[cell].y);

						if (cell == 0)
						{
							cout << SNAKE[cell];
						}
						else
						{
							cout << MSSV[cell];
						};
					};

					Sleep(300);

					// Giat lan 2
					textcolor(7);
					for (register int cell = 0; cell < Size; ++cell)
					{
						gotoXY(SNAKE[cell].x, SNAKE[cell].y);

						if (cell == 0)
						{
							cout << SNAKE[cell];
						}
						else
						{
							cout << MSSV[cell];
						};
					};

					Sleep(200);

					++timer;
				};

				return;
			};

			// Neu vao cong dung theo huong mac dinh thi len level
			if (flag && SNAKE[0].x == CAVE[Level - 1].x && SNAKE[0].y == CAVE[Level - 1].y)
			{
				if (n == W)
				{
					return;
				};

				++Score;
				Speed -= 25;// tang speed

				for (register int j = Size - 1; j > 0; --j)
				{
					delete_point(SNAKE[j].x, SNAKE[j].y);
					Sleep(Speed);//SPEED
				};

				InitialCave(); // Xoa cai cong
				InitialCave(0, 1); // Ve cong ra

				for (register int j = 0; j < Size; ++j)
				{
					take_event(n);

					switch (n)
					{
					case A:
						Dir = n;
						update_snake();
						--SNAKE[0].x;
						break;
					case S:
						Dir = n;
						update_snake();
						++SNAKE[0].y;
						break;
					case D:
						Dir = n;
						update_snake();
						++SNAKE[0].x;
						break;
					case W:
						Dir = n;
						update_snake();
						--SNAKE[0].y;
						break;
					case P:
					{
						State = PAUSE;
						return;
					};
					case 27: 
					{
						save_game();
						return;
					};
					};

					for (register int length = 0; length <= j; ++length) 
					{
						if (mssv == 0) 
							print_snake(length);
						else 
							print_mssv(length);
					};

					Sleep(Speed);
					if (collision_cave(0, 1))
					{
						State = EXIT;

						int timer = 0;
						while (timer < 3)
						{
							// Giat 1 lan
							textcolor(12);
							for (register int cell = 0; cell < Size; ++cell)
							{
								cout << SNAKE[cell];
							};

							Sleep(300);

							// Giat lan 2
							textcolor(7);
							for (register int cell = 0; cell < Size; ++cell)
							{
								cout << SNAKE[cell];
							};

							Sleep(300);

							++timer;
						};

						return;
					};
				};

				InitialCave(); // Xoa cai cong ra
				
				if (Level <= MAX_LEVEL)
				{
					++Level;
				}
				else
				{
					// Hien thi chien thang
					delete_menu();

				};

				break;
			};
		};
	};
};
// -----------------------------------------------------------


// -------------------- NEW GAME ------------------------------
void new_game(int state = 0, int choose = 0)
{
	if (state != 0)
	{
		if (choose == 0)
		{
			delete_inside_table(87, 2, 16, 26);
			setTextColor(7);
			gotoXY(88, 12);
			textcolor(13);
			cout << " PLAYING NOW " << char(3);
			gotoXY(87, 14);	cout << " ---------------";
			textcolor(12);
			gotoXY(87, 16);	cout << "   TURN OFF ";
			gotoXY(87, 18);	cout << "   CAPS LOCK ";
			gotoXY(87, 20); cout << "   BEFORE PLAY !";

			textcolor(7);
		}
		else
		{
			New_game = true;

			delete_menu();

			draw_rectangle(24, 13, 40, 5, 14);
			textcolor(10);
			gotoXY(34, 14); cout << "CHOOSE GAME MODE:";
			int pointer = 0;
			while (true)
			{
				delete_inside_table(25, 16, 38, 1);
				if (pointer == 0)
				{
					setTextColor(4); gotoXY(26, 16); cout << "CLASSICAL";
					setTextColor(7); gotoXY(40, 16); cout << "CHALLENGE";
					setTextColor(7); gotoXY(54, 16); cout << "ADVANCED";
				}
				else if (pointer == 1)
				{
					setTextColor(7); gotoXY(26, 16); cout << "CLASSICAL";
					setTextColor(4); gotoXY(40, 16); cout << "CHALLENGE";
					setTextColor(7); gotoXY(54, 16); cout << "ADVANCED";
				}
				else if (pointer == 2)
				{
					setTextColor(7); gotoXY(26, 16); cout << "CLASSICAL";
					setTextColor(7); gotoXY(40, 16); cout << "CHALLENGE";
					setTextColor(4); gotoXY(54, 16); cout << "ADVANCED";
				};

				int key = _getch();

				if (key == D)
				{
					++pointer;

					if (pointer == 3)
					{
						pointer = 0;
					};
				};

				if (key == A)
				{
					if (pointer == 0)
					{
						pointer = 3;
					};

					--pointer;
				};

				if (key == enter)
				{
					if (pointer == 2)
					{
						return;
					};

					InitialSnake();

					Score = 0;
					Speed = 170;
					Level = 1;

					delete_menu();

					draw_rectangle(35, 13, 16, 4, 10);
					textcolor(9);
					gotoXY(36, 14); cout << "ENTER YOUR NAME";
					gotoXY(36, 15);	cout << "---------------";
					gotoXY(36, 15); cin >> name;
					textcolor(7);

					if (pointer == 0)
					{
						State = PLAY;
						Mode = CLASSICAL;

						while (true)
						{
							play_classical(0, Dir);

							if (State == PAUSE)
							{
								pause_game();
								if (State != PLAY)
								{
									return;
								};
							}
							else if (State == EXIT)
							{
								exit_game(1, 1);
								return;
							}
							else
							{
								save_game();
							};
	
							cin.ignore();
						};
					}
					else if (pointer == 1)
					{
						State = PLAY;
						Mode = CHALLENGE;

						while (true)
						{
							play_game(1, Dir);

							if (State == PAUSE)
							{
								pause_game();
								if (State != PLAY)
								{
									return;
								};
							}
							else if (State == EXIT)
							{
								exit_game(1, 1);
								return;
							}
							else
							{
								save_game();
							};

							cin.ignore();
						};
					};
				};
			};
		};
	};
};
// --------------------------------------------------------


// ------------------ CONTINUE GAME -----------------------
void continue_game(int state = 0, int choose = 0)
{
	if (state != 0)
	{
		if (choose == 0)
		{
			delete_inside_table(87, 2, 16, 26);
			setTextColor(7);
			textcolor(10);
			gotoXY(87, 14); cout << " TO BE CONTINUE !";
			textcolor(7);
		}
		else
		{
			New_game == false;
			// Xoa menu chuan bi cho frame moi
			delete_inside_table(87, 2, 16, 26);
			gotoXY(88, 14); cout << "  Press A or D ";
			gotoXY(88, 15); cout << "     to CHECK   ";
			gotoXY(88, 16); cout << " ENTER to choose";

			// Xoa menu, ve o chu nhat moi
			delete_menu();
			draw_rectangle(17, 12, 54, 4, 11);

			// Lay thong tin file nguoi choi ngay khi nhan CONTINUE
			// Khoi tao lai SNAKE
			if (SNAKE != NULL)
				delete[] SNAKE;
			SNAKE = new point[MAX_SIZE];

			// Doc toan bo ten file vao mang

			// Thao tac tai du lieu
			string File[25];
			int numFile = 0; // Bien luu giu so file trong user.txt

			string fileName;
			fstream file_game("data/user.txt", ios::in);

			while (!file_game.eof())
			{
				file_game >> fileName;
				File[numFile++] = fileName;
			};

			file_game.close();

			/*while (true)
			{
				gotoXY(18, 14);
				cout << "                                                     ";
				gotoXY(43, 15); cout << "   ";

				if (k == 0)
				{
					gotoXY(43, 14); cout << "MENU";
				}
				else
				{
					load_file(File, numFile);

					gotoXY(18, 14); cout << "<| ";
					gotoXY(22, 14); cout << "Name: ";
					gotoXY(29, 14); cout << name;
					gotoXY(45, 14); cout << "Score: ";
					gotoXY(54, 14); cout << Score;
					gotoXY(58, 14); cout << "Level: ";
					gotoXY(66, 14); cout << Level;
					gotoXY(68, 14); cout << " |>";
				};

				int c;
				c = _getch();

				if (c == D)
				{
					++k;
					if (k == file + 1)
					{
						k = 0;
					};
				};

				if (c == A)
				{
					--k;
					if (k < 0)
					{
						k = file;
					};
				};

				if (c == enter)
				{
					if (k == 0)
					{
						delete_menu();
						return;
					}
					else
					{
						play_game(0, Dir);
						save_game();
						return;
					};
				};
			};*/

			int pointer = 0;
			Info game;
			int flag = -1;
			string address;

			while (true)
			{
				for (register int i = 0; i < numFile; ++i)
				{
					if (pointer == i)
					{
						// Xoa thong tin file truoc
						gotoXY(22, 14); cout << "                             ";
						gotoXY(45, 13); cout << "                       ";
						gotoXY(45, 15); cout << "                       ";
			
						// Doc thong tin file nguoi choi
						address = "data/" + File[i];
						file_game.open(address, ios::in | ios::binary);
						file_game.read(reinterpret_cast<char*>(&game), sizeof(game));
						file_game.close();

						// Hien du lieu file hien tai
						textcolor(9);
						gotoXY(18, 14); cout << "<| ";
						textcolor(9);
						gotoXY(22, 14); cout << "Name: ";
						textcolor(12);
						gotoXY(29, 14); cout << File[i];
						textcolor(9);
						gotoXY(45, 13); cout << "Score: ";
						textcolor(14);
						gotoXY(53, 13); cout << game.score;
						textcolor(9);
						gotoXY(45, 15); cout << "Level: ";
						textcolor(14);
						gotoXY(53, 15); cout << game.level;
						textcolor(9);
						gotoXY(68, 14); cout << " |>";
					};
				};

				while (true)
				{
					if (_kbhit())
					{
						char key = _getch();

						if (key == 'a')
						{
							--pointer;

							if (pointer < 0)
							{
								pointer = numFile - 1;
							};
							break;
						}
						else if (key == 'd')
						{
							++pointer;

							if (pointer == numFile - 1)
							{
								pointer = 0;
							};
							break;
						}
						else if (key == 13)
						{
							flag = 0; // Danh dau 

							// Khoi tao game voi du lieu vua doc
							Size = game.size;        // Khoi tao do dai snake
							Level = game.level;      // Khoi tao level
							Score = game.score;      // Khoi tao score
							Mode = game.mode;        // Khoi tao che do choi
							Speed = game.speed;      // Khoi tao toc do

							// Khoi tao toa do con ran
							for (register int i = 0; i < MAX_SIZE; ++i)
							{
								SNAKE[i].x = game.snake[i].x;
								SNAKE[i].y = game.snake[i].y;
							};
							// Khoi tao trai cay
							FRUIT.x = game.fruit.x;
							FRUIT.y = game.fruit.y;

							// Thao tac lay direction
							int dx = SNAKE[0].x - SNAKE[1].x;
							int dy = SNAKE[0].y - SNAKE[1].y;
							// Phan tich
							if (dx == 0)
							{
								if (dy > 0)
								{
									Dir = S; // Di xuong
								}
								else
								{
									Dir = W; // Di len
								};
							}
							else
							{
								if (dx > 0)
								{
									Dir = D; // Di qua phai
								}
								else
								{
									Dir = A; // Di qua trai
								};
							};
							cout << FRUIT; // In ra trai cay
							break;
						}
						else
						{
							break;
						};
					};
				};

				if (flag == 0) // Neu da chon file thi thoat
				{
					break;
				};
			};

			// Bat dau chay game
			while (true)
			{
				State = PLAY;

				if (Mode == CLASSICAL)
				{
					play_classical(0, Dir);
				}
				else if (Mode == CHALLENGE)
				{
					play_game(1, Dir);
				}
				else if (Mode == ADVANCED)
				{
					//
				};

				if (State == PAUSE)
				{
					pause_game();

					if (State != PLAY)
					{
						return;
					};
				}
				else if (State == EXIT)
				{
					exit_game(1, 1);
					return;
				}
				else
				{
					save_game();
				};
				cin.ignore();
			};
		};
	};
};
// -------------------------------------------------------------

// ------------------------ HAM LOAD DIEM ----------------------
void load_score()
{

};

// ------------------------ HIGH SCORE -------------------------
void high_score(int state = 0, int choose = 0)
{
	if (state != 0)
	{
		if (choose == 0)
		{
			//delete_menu();
			delete_inside_table(87, 2, 16, 26);
			setTextColor(7);
			textcolor(10);
			gotoXY(89, 14);
			cout << "HIGHEST SCORE";
			gotoXY(91, 16);
			textcolor(10);
			cout << HighScore;
			textcolor(7);
		}
		else
		{
			// Bat dau doc file nguoi choi -> Trich xuat diem
			string File[25];              // Mang file nguoi choi
			int numFile = 0;              // So file nguoi choi co trong user.txt
			string file_name;             // Ten file
			fstream file_game("data/user.txt", ios::in);
			while (!file_game.eof())
			{
				file_game >> file_name;
				File[numFile++] = file_name;
			};
			file_game.close();
			// Ket thuc doc file

			// Bat dau trich xuat diem trong file
			Info game;
			int Score[25];
			int numScore = 0;
			for (register int i = 0; i < numFile; ++i)
			{
				file_game.open("data/" + File[i], ios::in);
				file_game.read(reinterpret_cast<char*>(&game), sizeof(game));
				Score[numScore++] = game.score;
				file_game.close();
			};

			delete_menu();

			_getch();
		};
	}
	else
	{
		return;
	};
};
// ---------------------------------------------------


// ----------------- ABOUT ---------------------------
void about_game(int state = 0, int choose = 0)
{
	if (state != 0)
	{
		if (choose == 0)
		{
			delete_inside_table(87, 2, 16, 26);
			setTextColor(7);
			textcolor(10);
			gotoXY(87, 8);	cout << "   TEAM : 3D    ";
			gotoXY(87, 9); cout << "  ============   ";
			gotoXY(87, 12); cout << "   Le Van DINH  ";
			gotoXY(87, 13); cout << "    19120477    ";
			gotoXY(87, 16); cout << " Nguyen Nhat DUY";
			gotoXY(87, 17); cout << "    19120495    ";
			gotoXY(87, 19); cout << "  Tram Huu DUC  ";
			gotoXY(87, 20); cout << "    19120484    ";
			textcolor(7);
		}
		else
		{
			delete_inside_table(87, 2, 16, 26);
			delete_menu();

			textcolor(10);

			gotoXY(28, 8); cout << "DO AN CUOI KI KY THUAT LAP TRINH";
			gotoXY(35, 9); cout << "TRO CHOI CON RAN";
			gotoXY(28, 10); cout << "HUONG DAN: GV TRUONG TOAN THINH";
			gotoXY(28, 12); cout << "TEAM : 3D       LOP : 19CTT3";
			gotoXY(28, 13); cout << "Thanh vien: ";
			gotoXY(35, 14); cout << "   Le Van DINH  ";
			gotoXY(35, 15); cout << " Nguyen Nhat DUY";
			gotoXY(35, 16); cout <<  "  Tram Huu DUC  ";
			gotoXY(28, 18); cout << "Youtube: ";
			gotoXY(28, 19); cout << "Github: ";

			_getch();

			delete_menu();
		};
	}
	else
	{
		return;
	};

	textcolor(7);
};
// ---------------------------------------------------------

// ------------- HUONG DAN CHOI GAME -----------------------
void tutorial(int state = 0, int choose = 0) 
{
	if (state != 0)
	{
		if (choose == 0) 
		{
			delete_inside_table(87, 2, 16, 26);
			setTextColor(7);
			textcolor(10);
			gotoXY(87, 10); cout << "  <> CONTROL:  ";
			gotoXY(87, 12); cout << "         W     ";
			gotoXY(87, 13); cout << "    A        D ";
			gotoXY(87, 14); cout << "         S     ";
			gotoXY(87, 15); cout << "               ";
			gotoXY(87, 16); cout << "  ESC: Save game ";
			gotoXY(87, 17); cout << "  Enter: Choose ";
			textcolor(7);
		}
		else
		{
			delete_inside_table(87, 2, 16, 26);
			delete_menu();

			textcolor(10);
			/*gotoXY(33, 10); cout << "  <> CONTROL:  ";
			gotoXY(33, 12); cout << "         W     ";
			gotoXY(33, 13); cout << "    A        D ";
			gotoXY(33, 14); cout << "         S     ";
			gotoXY(33, 15); cout << "               ";
			gotoXY(33, 16); cout << "  ESC: Save game ";
			gotoXY(33, 17); cout << "  P: Pause game ";*/
			gotoXY(38, 7); cout << "CAC CHE DO CHOI";
			gotoXY(10, 9); cout << "CLASSCICAL:  Che do co dien";
			gotoXY(22, 10); cout << "- Ran co the di xuyen tuong, xuat hien o tuong ben doi dien";
			gotoXY(22, 11); cout << "- An du 5 thuc an nho se xuat hien thuc an to co thoi gian";
			gotoXY(10, 13); cout << "CHALLENGE: Che do thu thach";
			gotoXY(22, 14); cout << "- Ban phai vuot qa 5 level, tang toc do chay sau moi level";
			gotoXY(22, 15); cout << "- Chu y: cham tuong -> die";
			gotoXY(10, 17); cout << "AVANDCED: Che do nang cao";
			gotoXY(22, 18); cout << "- Coming soon!";

			_getch();
			delete_menu();
		};
	};
}
// ---------------------------------------------------------------


// ----------------------------------- MENU -------------------------------------------------------------------
string list_menu[] = { " NEW GAME  ", " CONTINUE  ","HIGH SCORE","   ABOUT     "," TUTORIAL  ","   EXIT      " };

// ------------------------- LOGO ------------------------------------------------------
void hieu_ung_chu_SNAKE(int y) 
{
	setTextColor(10);
	/*int i = x_rec + 1;

	for (; i <= x_rec + 16; i++) 
	{
		//int n = 53;
		gotoXY(i, y);
		cout << "ssssssss  nnn    nn      aaa        kk  kk   eeeeeee"; gotoXY(32 + x_rec - i, y + 1);
		cout << "ss        nnnn   nn     aa aa       kk kk   ee      "; gotoXY(i, y + 2);
		cout << "ssssssss  nn nn  nn    aa   aa      kkkk    eeeeee  "; gotoXY(32 + x_rec - i, y + 3);
		cout << "      ss  nn  nn nn   aaaaaaaaa     kk kk   eeeeee  "; gotoXY(i, y + 4);
		cout << "ss    ss  nn   nnnn  aaa     aaa    kk  kk  ee      "; gotoXY(32 + x_rec - i, y + 5);
		cout << "ssssssss  nn    nnn aaa       aaa   kk   kk  eeeeeee"; //gotoXY(i, y + 5);
		Sleep(20);
		if (i == 17) return;
		delete_menu(y - 1, y + 6);
	};*/

	char a = 219; // █
	char b = 187;// ╗
	char c = 201; // ╔
	char d = 205;//═
	char e = 188;//╝
	char f = 186;//║
	char g = 200; //╚

	int line = 5;
	int x = 23;
	textcolor(62);
	gotoxy(x, line++);
	cout << a << a << a << a << a << a << a << b << a << a << a << b << "   " << a << a << b << " " << a << a << a << a << a << b << " "
		<< a << a << b << "  " << a << a << b << a << a << a << a << a << a << a << b << std::endl;
	gotoxy(x, line++);
	cout << a << a << c << d << d << d << d << e << a << a << a << a << b << "  " << a << a << f << a << a << c << d << d << a << a << b << a << a << f
		<< " " << a << a << c << e << a << a << c << d << d << d << d << e << std::endl;
	gotoxy(x, line++);
	cout << a << a << a << a << a << a << a << b << a << a << c << a << a << b << " " << a << a << f << a << a << a << a << a << a
		<< a << f << a << a << a << a << a << c << e << " " << a << a << a << a << a << b << std::endl;
	gotoxy(x, line++);
	cout << g << d << d << d << d << a << a << f << a << a << f << g << a << a << b << a << a << f << a << a << c << d << d << a << a << f << a << a <<
		c << d << a << a << b << " " << a << a << c << d << d << e << std::endl;
	gotoxy(x, line++);
	cout << a << a << a << a << a << a << a << f << a << a << f << " " << g << a << a << a << a << f << a << a << f << "  " << a << a << f << a << a << f
		<< "  " << a << a << b << a << a << a << a << a << a << a << b << std::endl;
	gotoxy(x, line++);
	cout << g << d << d << d << d << d << d << e << g << d << e << "  " << g << d << d << d << e << g << d << e << "  " << g << d << e << g << d << e <<
		"  " << g << d << e << g << d << d << d << d << d << d << e << std::endl;
	textcolor(7);
};

//  ------------------------- HIEU UNG XUAT HIEN MENU ----------------------------------------
void hieu_ung_menu()
{
	textcolor(11);
	int f = 11;
	int k[] = { 11,11,11,11,11,11 };
	int n = sizeof(k) / sizeof(k[0]);

	for (int m = x_rec + 1; m <= 35; m += 7)
	{
		for (int j = 0; j < 6; j++)
		{
			if (j % 2 == 0)
				gotoXY(m, y_rec + f + 3*j);
			else
				gotoXY(x_rec + 68 - m, y_rec + f + 3*j);
			cout << list_menu[j];
		};

		Sleep(100);
		delete_menu(y_rec + f - 1, height);
	};
	textcolor(7);
};

// ------------------- IN MENU -------------------------------
void print_menu(int choice)
{
	int f = 11;
	int k[] = { 11,11,11,11,11,11 };
	int n = sizeof(k) / sizeof(k[0]);

	for (int option = 0; option < n; ++option)
	{
		if (option == choice)
		{
			k[option] = 12;
		};

		// Doi mau option
		setTextColor(k[option]);
		// Di chuyen con tro den vi tri option
		gotoXY(x_rec + 35 + 1, y_rec + f + 3*option);
		cout << list_menu[option];
	};
};

// ------------------------- TOAN BO MENU ----------------------------------------
void menu()
{
	int i = 0;

	noCursorType();
	hieu_ung_chu_SNAKE(y_rec + 7);
	hieu_ung_menu(); // Hieu ung xuat hien menu

	while (true)
	{
		noCursorType();
		print_menu(i);
		switch (i)
		{
		case 0: new_game(1); break;
		case 1: continue_game(1, 0); break;
		case 2: high_score(1); break;
		case 3: about_game(1); break;
		case 4: tutorial(1); break;
		case 5: exit_game(1); break;
		};

		int c = _getch();

		if (c == S)
		{
			++i;
			if (i == 6)
			{
				i = 0;
			};
		}
		else if (c == W)
		{
			if (i == 0)
			{
				i = 6;
			};

			--i;
		}
		else if (c == 13)
		{
			switch (i)
			{
			case 0: new_game(1, 1); return;
			case 1:	continue_game(1, 1); return;
			case 2: 
			{
				delete_menu();
				high_score(1, 1);
				hieu_ung_chu_SNAKE(y_rec + 7);
				break;
			};
			case 3: about_game(1, 1);
				hieu_ung_chu_SNAKE(y_rec + 7);
				break;
			case 4: tutorial(1, 1);
				hieu_ung_chu_SNAKE(y_rec + 7);
				break;
			case 5: exit_game(1, 1); return;
			};

			gotoXY(0, height + y_rec + 1);
		};

		delete_menu(15);
	};
};
// ---------------------------------------------------------
#endif // !_MENU_H
