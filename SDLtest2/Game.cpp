#include <SDL.h>
#include <thread>
#include <iostream>
#include <random>
#include "Var.h"

int previous_figure, previous_figure2;
int figure_color_prev, figure_color_prev2;

void Delete_line(SDL_Renderer* renderer) {

	process_pause = true;
	
	int a = 0;

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
								
			if (a == 0)
				this_thread::sleep_for(chrono::milliseconds(SLEEPING_TIME / 12));
			
			++a;
					   
			//cout << "\nLine cheked!\n";
			
			//SDL_Rect viewport = { 0, i * CELL_SIZE, SCREEN_WIDTH, CELL_SIZE };
			//SDL_RenderSetViewport(renderer, &viewport);

			for (int j = 0; j < WIDTH_OF_PLAYING_FIELD; j++)
			{
				this_thread::sleep_for(chrono::milliseconds(SLEEPING_TIME / 20));
				
				SDL_RenderClear(renderer);
				
				Background_Renderer(renderer);
				shadow_sells[j][i].square = false;
				Shadow_Render(renderer);
				
				render.lock();SDL_RenderPresent(renderer);render.unlock();

			}

			//SDL_RenderSetViewport(renderer, NULL);

			SDL_RenderClear(renderer);

			for (int j = 0; j < WIDTH_OF_PLAYING_FIELD; j++)
				for (int k = i - 1; k >= 0; k--)
				{
					if (shadow_sells[j][k].square) {
						shadow_sells[j][k + 1].square = shadow_sells[j][k].square;
						shadow_sells[j][k].square = false;
						shadow_sells[j][k + 1].color = shadow_sells[j][k].color;
					}
				}

			switch (a)
			{
			case 1:
				points += 100;
				break;
			case 2:
				points += 200;
				break;
			case 3:
				points += 400;
				break;
			case 4:
				points += 800;
				break;
			}
			//cout << endl << points << endl;

			this_thread::sleep_for(chrono::milliseconds(SLEEPING_TIME / 8));
			
			Background_Renderer(renderer);
			Shadow_Render(renderer);
			render.lock();SDL_RenderPresent(renderer);render.unlock();
						
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

void Figures_Init() {

	*(figures + 0) = { { 1,1,1,1,0,0,0,0,0,0 }, {100} };	*(figures + 8) = { { 0,1,0,0,1,0,1,0,1,0 }, {150} };	*(figures + 9) = { { 0,0,1,1,1,1,0,0,0,0 }, {100} };	*(figures + 10) = { { 0,1,1,0,0,1,1,0,0,0 }, {150} };
	*(figures + 1) = { { 0,1,1,1,1,0,0,0,0,0 }, {100} };	*(figures + 11) = { { 0,1,0,0,1,1,1,0,0,0 }, {150} };
	*(figures + 2) = { { 1,0,0,1,1,1,0,0,0,0 }, {100} };	*(figures + 17) = { { 0,0,1,0,0,1,1,0,1,0 }, {150} };	*(figures + 18) = { { 1,1,1,0,0,1,0,0,0,0 }, {100} };	*(figures + 19) = { { 0,1,1,0,1,0,0,0,1,0 }, {150} };
	*(figures + 3) = { { 1,1,0,0,1,1,0,0,0,0 }, {100} };	*(figures + 12) = { { 0,0,1,0,1,1,0,0,1,0 }, {150} };
	*(figures + 4) = { { 0,0,1,0,0,1,1,1,0,0 }, {200} };	*(figures + 16) = { { 1,1,1,0,0,0,0,0,0,1 }, {50} };
	*(figures + 5) = { { 0,1,1,0,1,1,0,0,0,0 }, {100} };
	*(figures + 6) = { { 0,0,1,0,1,1,1,0,0,0 }, {150} };	*(figures + 13) = { { 1,1,1,0,1,0,0,0 }, {100} };		*(figures + 14) = { { 0,1,0,0,1,1,0,0,1,0 }, {150} };	*(figures + 15) = { { 0,1,0,1,1,1,0,0,0,0 }, {100} };

	*(figures + 7) = { { 0,0,0,0,0,0,0,0 }, {0} };
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
	previous_figure = number_of_figure_next;

	number_of_figure_next = Generate_Random_Number(0, 6);
	previous_figure2 = previous_figure;
	previous_figure = number_of_figure_next;

	active = *(figures + number_of_figure_next);	

regen:
	number_of_figure_next = Generate_Random_Number(0, 6);
	if (number_of_figure_next == previous_figure || number_of_figure_next == previous_figure2)
		goto regen;

	figure_color_next = Generate_Random_Number(0, 5);
	figure_color_prev = figure_color_next;

	figure_color_next = Generate_Random_Number(0, 5);
	figure_color_prev2 = figure_color_prev;
	figure_color_prev = figure_color_next;

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

REcolor:
	figure_color_next = Generate_Random_Number(0, 5);
	if ( figure_color_next == figure_color_prev || figure_color_next == figure_color_prev2 )
		goto REcolor;

	x_pos_of_figure = 150;
	y_pos_of_figure = -100;
}

void Generate_New_Figure(SDL_Rect& color, Figure& active) {

	cout << "new figure! =)";

	active = *(figures + number_of_figure_next);

	previous_figure2 = previous_figure;
	previous_figure = number_of_figure_next;

regen:
	number_of_figure_next = Generate_Random_Number(0, 6);
	if (number_of_figure_next == previous_figure || number_of_figure_next == previous_figure2)
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

	figure_color_prev2 = figure_color_prev;
	figure_color_prev = figure_color_next;

REcolor:
	figure_color_next = Generate_Random_Number(0, 5);
	if (figure_color_next == figure_color_prev || figure_color_next == figure_color_prev2)
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
			this_thread::sleep_for(chrono::milliseconds(SLEEPING_TIME / 20));

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

		if (y_pos_of_figure >= 0)
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
					if (x_pos_of_figure / CELL_SIZE + arrayLOL[i][0] < 10)
					if (shadow_sells[x_pos_of_figure / CELL_SIZE + arrayLOL[i][0]][y_pos_of_figure / CELL_SIZE + arrayLOL[i][1]].square) { is_falling = false; }

			if (!is_falling) {
				if (y_pos_of_figure == 0) {

					loss = true;
				}

				Rewrite_of_shadow_cells(active, x_pos_of_figure, y_pos_of_figure, color);
				active = *(figures + 7);
			}
		}

		if (!is_falling && !loss && !process_pause) {

			Delete_line(renderer);

			Generate_New_Figure(color, active);
						
			SDL_RenderClear(renderer);
			
			Background_Renderer(renderer);
			Figures_Renderer(active.figure, color, x_pos_of_figure, y_pos_of_figure, renderer);
			Shadow_Render(renderer);

			render.lock();SDL_RenderPresent(renderer);render.unlock();
		}
		else if (!process_pause)
		{
			y_pos_of_figure += CELL_SIZE;
			
			SDL_RenderClear(renderer);

			Background_Renderer(renderer);
			Figures_Renderer(active.figure, color, x_pos_of_figure, y_pos_of_figure, renderer);
			Shadow_Render(renderer);
			
			render.lock();SDL_RenderPresent(renderer);render.unlock();
		}		
		}		
	}
	return 0;
}