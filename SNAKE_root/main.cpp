#include "snake.h"
#include "menu.h"

int main() 
{
	// ----- KHOI DONG ---------------------
	noCursorType(); 
	setTextColor(15);
	fix_console_window();
	resizeConsole(WIDTH, HEIGHT);
	SNAKE = NULL;
	//show_coord();
	//---------------------------------------
	
	//---------------------------------------
	while (true) 
	{
		draw_rectangle(x_rec, y_rec, width, height, 11);
		draw_rectangle(x_rec + width + 1, y_rec, 18, height, 14);
		menu();
		delete_menu();
	};
	//---------------------------------------


	gotoXY(0, height + y_rec + 1);

	delete[] SNAKE;

	return 0;
}