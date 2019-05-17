#include <SDL.h>
#include <thread>
#include <iostream>
#include <random>
#include "Var.h"

int number_of_figure_next, previous_figure = 0;

void Delete_line(SDL_Renderer* renderer) {

	process_pause = true;
	
	for (int i = 0; i < HEIGHT_OF_PLAYING_FIELD; i++)
		if (shadow_sells[0][i].square && shadow_sells[1][i].square && shadow_sells[2][i].square && shadow_sells[3][i].square && shadow_sells[4][i].square && shadow_sells[5][i].square && shadow_sells[6][i].square && shadow_sells[7][i].square && shadow_sells[8][i].square && shadow_sells[9][i].square) {

			//cout << "\nLine cheked!\n";
			for (int j = 0; j < WIDTH_OF_PLAYING_FIELD; j++)
			{
				this_thread::sleep_for(chrono::milliseconds(SLEEPING_TIME / 20));
				SDL_RenderClear(renderer);
				shadow_sells[j][i].square = false;
				Shadow_Render(renderer);
				SDL_RenderPresent(renderer);
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
			Shadow_Render(renderer);
			SDL_RenderPresent(renderer);
		}

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
	
	bool flagB = true;
	int number_of_figure = 0, previous_figure = 0;

	while (!loss) {
		
		cout << "y_pos = " << y_pos_of_figure;

		SDL_RenderClear(renderer);																// RENDER CLEAR

		this_thread::sleep_for(chrono::milliseconds(SLEEPING_TIME));

		if (pause)
		{
			SDL_RenderClear(renderer);
			Figures_Renderer(active.figure, color, x_pos_of_figure, y_pos_of_figure, renderer);
			Shadow_Render(renderer);

			SDL_Color white = { 255, 255, 255 };
			SDL_Rect Message_rect;
			Message_rect.w = 250;
			Message_rect.h = 55;
			Message_rect.x = SCREEN_WIDTH / 2 - Message_rect.w / 2 + 3;
			Message_rect.y = 300;

			SDL_RenderCopyEx(renderer, Text_Texture("pause", renderer, white), NULL, &Message_rect, NULL, NULL, SDL_FLIP_NONE);

			SDL_RenderPresent(renderer);

			while (pause) {

				if (!pause)
					break;

				this_thread::sleep_for(chrono::milliseconds(300));
			}
		}


		bool flagB = true;

		if (y_pos_of_figure >= CELL_SIZE * 17) {
			
			Rewrite_of_shadow_cells(active, x_pos_of_figure, y_pos_of_figure, color);
			active = *(figures + 7);

			flagB = false;

		}
		else {

			int arrayLOL[10][2] = { { 0, 1 }, { 0, 2 }, { 0, 3 }, { 1, 1 }, { 1, 2 }, { 1, 3 }, { 2, 3 }, { 3, 3 }, { 2, 2 }, { 0, 0 } };

			for (int i = 0; i < 10; i++)
				if (*(active.figure + i))
					if (shadow_sells[x_pos_of_figure / CELL_SIZE + arrayLOL[i][0]][y_pos_of_figure / CELL_SIZE + arrayLOL[i][1]].square) { flagB = false; }

			if (!flagB) {
				if (y_pos_of_figure == 0) {

					loss = true;
				}

				Rewrite_of_shadow_cells(active, x_pos_of_figure, y_pos_of_figure, color);
				active = *(figures + 7);
			}
		}

		if (!flagB && !loss) {

			Delete_line(renderer);

			Generate_New_Figure(color, active);

			SDL_RenderClear(renderer);
			Figures_Renderer(active.figure, color, x_pos_of_figure, y_pos_of_figure, renderer);
			Shadow_Render(renderer);
			SDL_RenderPresent(renderer);
		}

		//		cout << "\nPADAU! -\t";
		SDL_RenderClear(renderer);

		if (!process_pause)
			y_pos_of_figure += CELL_SIZE;

		Figures_Renderer(active.figure, color, x_pos_of_figure, y_pos_of_figure, renderer);
		Shadow_Render(renderer);
		SDL_RenderPresent(renderer);															// RENDER PRESENT
	}
	return 0;
}