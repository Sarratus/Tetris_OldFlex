#include <SDL.h>
#include <thread>
#include <iostream>
#include <random>
#include "Var.h"

int number_of_figure_next, previous_figure = 0;
int figure_color_next, figure_color_prev;

void Delete_line(SDL_Renderer* renderer) {

	process_pause = true;
	
	bool a = false;

	for (int i = 0; i < HEIGHT_OF_PLAYING_FIELD; i++)
		if (
			shadow_sells[0][i].square &&
			shadow_sells[1][i].square &&
			shadow_sells[2][i].square &&
			shadow_sells[3][i].square &&
			shadow_sells[4][i].square &&
			shadow_sells[5][i].square &&
			shadow_sells[6][i].square &&
			shadow_sells[7][i].square &&
			shadow_sells[8][i].square &&
			shadow_sells[9][i].square
		) {
								
			if (!a)
				this_thread::sleep_for(chrono::milliseconds(SLEEPING_TIME / 12));
			
			a = true;

			//cout << "\nLine cheked!\n";
			for (int j = 0; j < WIDTH_OF_PLAYING_FIELD; j++)
			{
				this_thread::sleep_for(chrono::milliseconds(SLEEPING_TIME / 20));
				
				render.lock();

				SDL_RenderClear(renderer);
				
				SDL_RenderCopy(renderer, background, NULL, NULL);
				shadow_sells[j][i].square = false;
				Shadow_Render(renderer);
				
				SDL_RenderPresent(renderer);

				render.unlock();
			}
			//cout << "\nLine deleted!\n";
			SDL_RenderClear(renderer);

			for (int j = 0; j < WIDTH_OF_PLAYING_FIELD; j++)
				for (int k = i - 1; k >= 0; k--)
				{
					//cout << "Flexing";
					if (shadow_sells[j][k].square) {
						shadow_sells[j][k + 1].square = shadow_sells[j][k].square;
						shadow_sells[j][k].square = false;
						shadow_sells[j][k + 1].color = shadow_sells[j][k].color;
					}
				}

			this_thread::sleep_for(chrono::milliseconds(SLEEPING_TIME / 8));
			
			render.lock();

			SDL_RenderCopy(renderer, background, NULL, NULL);
			Shadow_Render(renderer);
			SDL_RenderPresent(renderer);

			render.unlock();
		}

	this_thread::sleep_for(chrono::milliseconds(SLEEPING_TIME / 3));

	process_pause = false;
}

void Color_Init() {

	srcRED.h = CELL_SIZE;		srcYELL.h = CELL_SIZE;		srcBLUE.h = CELL_SIZE;		srcGREEN.h = CELL_SIZE;		srcMAGNT.h = CELL_SIZE;		srcCYAN.h = CELL_SIZE;
	srcRED.w = CELL_SIZE;		srcYELL.w = CELL_SIZE;		srcBLUE.w = CELL_SIZE;		srcGREEN.w = CELL_SIZE;		srcMAGNT.w = CELL_SIZE;		srcCYAN.w = CELL_SIZE;
	srcRED.x = 0;				srcYELL.x = 50;				srcBLUE.x = 100;			srcGREEN.x = 150;			srcMAGNT.x = 200;			srcCYAN.x = 250;
	srcRED.y = 0;				srcYELL.y = 0;				srcBLUE.y = 0;				srcGREEN.y = 0;				srcMAGNT.y = 0;				srcCYAN.y = 0;
}

int Generate_Random_Number(int a, int b) {
	random_device rd;
	mt19937 rng(rd());
	uniform_int_distribution<int> rand(a, b);
	return rand(rd);
}

void Generate_New_Figure(SDL_Rect& color, Figure& active, int a) {

	cout << "first figure! =)";

	number_of_figure_next = Generate_Random_Number(0, 6);

	active = *(figures + number_of_figure_next);

	previous_figure = number_of_figure_next;

regen:
	number_of_figure_next = Generate_Random_Number(0, 6);
	if (number_of_figure_next == previous_figure)
		goto regen;

	figure_color_next = Generate_Random_Number(0, 5);
	
	switch (figure_color_next)
	{
	case(0):
		color = srcRED;
		cout << "\nRed";
		break;
	case(1):
		color = srcYELL;
		cout << "\nYellow";
		break;
	case(2):
		color = srcBLUE;
		cout << "\nBlue";
		break;
	case(3):
		color = srcGREEN;
		cout << "\nGreen";
		break;
	case(4):
		color = srcMAGNT;
		cout << "\nMagenta";
		break;
	case(5):
		color = srcCYAN;
		cout << "\nCyan";
		break;
	default:
		color = srcYELL;
		cout << "\nYellow";
		break;
	}

	figure_color_prev = figure_color_next;

REcolor:
	figure_color_next = Generate_Random_Number(0, 5);
	if (figure_color_next == figure_color_prev)
		goto REcolor;

	x_pos_of_figure = 150;
	y_pos_of_figure = -100;
}

void Generate_New_Figure(SDL_Rect& color, Figure& active) {

	cout << "new figure! =)";

	active = *(figures + number_of_figure_next);

	previous_figure = number_of_figure_next;

regen:
	number_of_figure_next = Generate_Random_Number(0, 6);
	if (number_of_figure_next == previous_figure)
		goto regen;

	switch (figure_color_next)
	{
	case(0):
		color = srcRED;
		cout << "\nRed";
		break;
	case(1):
		color = srcYELL;
		cout << "\nYellow";
		break;
	case(2):
		color = srcBLUE;
		cout << "\nBlue";
		break;
	case(3):
		color = srcGREEN;
		cout << "\nGreen";
		break;
	case(4):
		color = srcMAGNT;
		cout << "\nMagenta";
		break;
	case(5):
		color = srcCYAN;
		cout << "\nCyan";
		break;
	default:
		color = srcYELL;
		cout << "\nYellow";
		break;
	}

	figure_color_prev = figure_color_next;

REcolor:
	figure_color_next = Generate_Random_Number(0, 5);
	if (figure_color_next == figure_color_prev)
		goto REcolor;

	x_pos_of_figure = 150;
	y_pos_of_figure = 0;
}

void Rewrite_of_shadow_cells(Figure active, int x_pos_of_figure, int y_pos_of_figure, SDL_Rect color) {

	int arrayLOL[10][2] = { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 1, 0 }, { 1, 1 }, { 1, 2 }, { 2, 2 }, { 3, 2 }, { 2, 1 }, { 0, -1 } };

	for (int i = 0; i < 10; i++)
		if (*(active.figure + i)) {
			shadow_sells[x_pos_of_figure / CELL_SIZE + arrayLOL[i][0]][y_pos_of_figure / CELL_SIZE + arrayLOL[i][1]].square = true;
			shadow_sells[x_pos_of_figure / CELL_SIZE + arrayLOL[i][0]][y_pos_of_figure / CELL_SIZE + arrayLOL[i][1]].color = color;
		}
}

bool The_Game(bool& loss, SDL_Renderer* renderer, SDL_Rect& color, Figure& active) {
	
	bool is_falling = true;
	int number_of_figure = 0, previous_figure = 0;

	while (!loss) {
		
		if (process_pause) 
			this_thread::sleep_for(chrono::milliseconds(SLEEPING_TIME / 10));

		if (!process_pause) {
		
		//cout << "y_pos = " << y_pos_of_figure;

		SDL_RenderClear(renderer);																// RENDER CLEAR

		this_thread::sleep_for(chrono::milliseconds(SLEEPING_TIME));

		if (pause)
		{
			
			while (pause) {

				if (!pause)
					break;

				this_thread::sleep_for(chrono::milliseconds(50));
			}
		}

		bool is_falling = true;

		unsigned short int arrayKEK[4] = { 2, 5, 6, 7 };

		for (auto i = 0; i < 4; i++)
			if (*(active.figure + arrayKEK[i]))
				if (y_pos_of_figure >= CELL_SIZE * 17) {
					
					Rewrite_of_shadow_cells(active, x_pos_of_figure, y_pos_of_figure, color);
					active = *(figures + 7);

					is_falling = false;

				} else {

			int arrayLOL[10][2] = { { 0, 1 }, { 0, 2 }, { 0, 3 }, { 1, 1 }, { 1, 2 }, { 1, 3 }, { 2, 3 }, { 3, 3 }, { 2, 2 }, { 0, 0 } };

			for (int i = 0; i < 10; i++)
				if (*(active.figure + i))
					if (shadow_sells[x_pos_of_figure / CELL_SIZE + arrayLOL[i][0]][y_pos_of_figure / CELL_SIZE + arrayLOL[i][1]].square) { is_falling = false; }

			if (!is_falling) {
				if (y_pos_of_figure == 50) {

					loss = true;
				}

				Rewrite_of_shadow_cells(active, x_pos_of_figure, y_pos_of_figure, color);
				active = *(figures + 7);
			}
		}

		if (!is_falling && !loss) {

			Delete_line(renderer);

			Generate_New_Figure(color, active);
						
			SDL_RenderClear(renderer);
			
			SDL_RenderCopy(renderer, background, NULL, NULL);
			Figures_Renderer(active.figure, color, x_pos_of_figure, y_pos_of_figure, renderer);
			Shadow_Render(renderer);

			SDL_RenderPresent(renderer);
		}
		else
		{
			y_pos_of_figure += CELL_SIZE;

			//		cout << "\nPADAU! -\t";					

			SDL_RenderClear(renderer);

			SDL_RenderCopy(renderer, background, NULL, NULL);
			Figures_Renderer(active.figure, color, x_pos_of_figure, y_pos_of_figure, renderer);
			Shadow_Render(renderer);

			render.lock();

			SDL_RenderPresent(renderer);

			render.unlock();
		}		
		}		
	}
	return 0;
}