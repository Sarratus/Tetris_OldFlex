#include <algorithm>
#include <iostream>
#include <SDL.h>
#include <thread>
#include <chrono>
//#include <mutex>
#include "Var.h"


void Menu(bool& start, SDL_Renderer* renderer, SDL_Rect color, Figure active, SDL_Window* window) {

	double angle = 0, angle2 = 0;
	short int change = 2;
	SDL_Rect dst;
	dst.h = 600;		dst.w = 600;
	dst.x = SCREEN_WIDTH - dst.w / 2 - 50;	dst.y = SCREEN_HEIGHT / 2 - dst.h / 2 - 200;
	
	SDL_Rect dst2;
	dst2.h = 256;		dst2.w = 256;
	dst2.x = 20 - dst2.w/2;	dst2.y = 820;

	SDL_Color White = { 150, 200, 255 };
	SDL_Texture* message = nullptr;
	
	message = Text_Texture("Press Enter to start", renderer, White);
	
	SDL_Rect Message_rect; 
	Message_rect.w = 390;
	Message_rect.h = 26;
	Message_rect.x = SCREEN_WIDTH / 2 - Message_rect.w / 2 + 3;
	Message_rect.y = 700; 

	while (!start) {		
				
		SDL_RenderClear(renderer);
		
		SDL_RenderCopyEx(renderer, block, &srcBLUE, &dst, angle++, NULL, SDL_FLIP_NONE);
		SDL_RenderCopyEx(renderer, block, &srcGREEN, &dst2, ++++++angle2, NULL, SDL_FLIP_NONE);
		SDL_RenderCopyEx(renderer, message, NULL, &Message_rect, NULL, NULL, SDL_FLIP_NONE);		
		SDL_RenderPresent(renderer);

		dst.h += change;
		dst.w += change;
				
		if (dst.h == 700)
			change *= -1;
		if (dst.h == 600)
			change *= -1;			

		this_thread::sleep_for(chrono::milliseconds(40));
	}
	if (start)
	{		
		unsigned int opacity = 255, time_pause = 40, steps = 130;
		double rotation = 1;

		for (int i = 0; i < steps; i++)
		{
			SDL_RenderClear(renderer);

			if (opacity > 1)
				SDL_SetTextureAlphaMod(message, --(--opacity));			

			angle += rotation;
			rotation += 0.03;

			SDL_RenderCopyEx(renderer, block, &srcBLUE, &dst, angle, NULL, SDL_FLIP_NONE);
			SDL_RenderCopyEx(renderer, message, NULL, &Message_rect, NULL, NULL, SDL_FLIP_NONE);
			
			SDL_RenderPresent(renderer);

			this_thread::sleep_for(chrono::milliseconds(time_pause));
			if (time_pause > 16)
				--time_pause;
		}
		steps = 130;
		
		int del_x = ((dst.x + dst.w / 2) - (SCREEN_WIDTH / 2)) / steps;
		int del_y = ((dst.y + dst.h / 2) - (SCREEN_HEIGHT / 2)) / steps;

		cout << " " << dst.x << " " << SCREEN_WIDTH;
		steps += 100;
		
		for (int i = 0; i < steps; i++)
		{
			//cout << "step" << del_x;
			SDL_RenderClear(renderer);

			angle += rotation;
			rotation += 0.07;

			if (dst.x + dst.w / 2 != SCREEN_WIDTH / 2)
				--dst.x;
			if (dst.y + dst.h / 2 != SCREEN_HEIGHT / 2)
				++dst.y;

			SDL_RenderCopyEx(renderer, block, &srcBLUE, &dst, angle, NULL, SDL_FLIP_NONE);
		
			SDL_RenderPresent(renderer);

			this_thread::sleep_for(chrono::milliseconds(time_pause));
		}	

		steps = 130;

		for (int i = 0; i < steps; i++)
		{
			SDL_RenderClear(renderer);

			angle += rotation;
			rotation += 0.09;

			----dst.y;
			++++++++dst.h;
			----dst.x;
			++++++++dst.w;
			
			SDL_RenderCopyEx(renderer, block, &srcBLUE, &dst, angle, NULL, SDL_FLIP_NONE);

			SDL_RenderPresent(renderer);

			this_thread::sleep_for(chrono::milliseconds(time_pause));
			if (time_pause  > 10)
				--time_pause;
		}
		
		steps = 85;
		opacity = 0;

		SDL_Surface* Fog = NULL;
		SDL_Texture* white_background = NULL;

		Fog = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);

		white_background = SDL_CreateTextureFromSurface(renderer, Fog);

		SDL_SetTextureBlendMode(white_background, SDL_BLENDMODE_BLEND);

		for (int i = 0; i < steps; i++)
		{
			SDL_RenderClear(renderer);

			angle += rotation;
			rotation += 0.13;

			----dst.y;
			++++++++dst.h;
			----dst.x;
			++++++++dst.w;
						
			if (opacity < 255)
			SDL_SetTextureAlphaMod(white_background, ++++++opacity);
			//cout << opacity << " ";
			
			SDL_RenderCopyEx(renderer, block, &srcBLUE, &dst, angle, NULL, SDL_FLIP_NONE);
			SDL_RenderCopyEx(renderer, white_background, NULL, NULL, NULL, NULL, SDL_FLIP_NONE);

			SDL_RenderPresent(renderer);

			this_thread::sleep_for(chrono::milliseconds(time_pause));
		}		
	}
}

int main(int argc, char * argv[]) {
	
	*(figures + 0) = { { 1,1,1,1,0,0,0,0,0,0 }, {100} };	*(figures + 8) = { { 0,1,0,0,1,0,1,0,1,0 }, {150} };	*(figures + 9) = { { 0,0,1,1,1,1,0,0,0,0 }, {100} };	*(figures + 10) = { { 0,1,1,0,0,1,1,0,0,0 }, {150} };
	*(figures + 1) = { { 0,1,1,1,1,0,0,0,0,0 }, {100} };	*(figures + 11) = { { 0,1,0,0,1,1,1,0,0,0 }, {150} };
	*(figures + 2) = { { 1,0,0,1,1,1,0,0,0,0 }, {100} };	*(figures + 17) = { { 0,0,1,0,0,1,1,0,1,0 }, {150} };	*(figures + 18) = { { 1,1,1,0,0,1,0,0,0,0 }, {100} };	*(figures + 19) = { { 0,1,1,0,1,0,0,0,1,0 }, {150} };
	*(figures + 3) = { { 1,1,0,0,1,1,0,0,0,0 }, {100} };	*(figures + 12) = { { 0,0,1,0,1,1,0,0,1,0 }, {150} };
	*(figures + 4) = { { 0,0,1,0,0,1,1,1,0,0 }, {200} };	*(figures + 16) = { { 1,1,1,0,0,0,0,0,0,1 }, {50} };
	*(figures + 5) = { { 0,1,1,0,1,1,0,0,0,0 }, {100} };
	*(figures + 6) = { { 0,0,1,0,1,1,1,0,0,0 }, {150} };	*(figures + 13) = { { 1,1,1,0,1,0,0,0 }, {100} };		*(figures + 14) = { { 0,1,0,0,1,1,0,0,1,0 }, {150} };	*(figures + 15) = { { 0,1,0,1,1,1,0,0,0,0 }, {100} };

	*(figures + 7) = { { 0,0,0,0,0,0,0,0 }, {0} };
	
	Color_Init();

	shadow_sells = new Shadow_Cell*[WIDTH_OF_PLAYING_FIELD];

	for (int i1 = 0; i1 < WIDTH_OF_PLAYING_FIELD; i1++)
	{
		*(shadow_sells + i1) = new Shadow_Cell[HEIGHT_OF_PLAYING_FIELD];
	}		
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		//cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
	}
	else
	{
		//cout << "SDL initialization succeeded!";
	}
	SDL_Window *window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		//cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		//cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	
	block = Image_Load("Squares.bmp", renderer);
		
	Figure active;
	
	SDL_Rect color = srcYELL;
	figure_color_next = 1;

	bool start = false;
	thread Menu(Menu, ref(start), ref(renderer), color, active, ref(window));
	
	while (!start)
	{
		SDL_Event event1;
		
		while (SDL_PollEvent(&event1)) {
			switch (event1.type) {
			case SDL_KEYDOWN:
				switch (event1.key.keysym.sym) {
					
						case SDLK_RETURN: {
						start = true;
						break;
					}				
				}
			}
		}
		this_thread::sleep_for(chrono::milliseconds(100));
	}

	Menu.join();
		
	Generate_New_Figure(color, active);
	
	bool loss = false;

	thread th2(The_Game, ref(loss), renderer, ref(color), ref(active));
	th2.detach();

	while (!loss) {
//		cout << "chityy";
		SDL_Event event;
		while (SDL_PollEvent(&event) && !process_pause) {
			
			switch (event.type) {
			case SDL_KEYDOWN:
			
			if (!pause) {

				switch (event.key.keysym.sym) {
				case SDLK_SPACE: {

					bool on_floor = false;
					int inert = 45;
					SDL_Rect flag = color;

					while (!on_floor && !loss && flag.x == color.x) {

						bool flagB = true;
												
						if (y_pos_of_figure >= CELL_SIZE * 17) {

							on_floor = true;
							
							Rewrite_of_shadow_cells(active, x_pos_of_figure, y_pos_of_figure, color);
							active = *(figures + 7);

							flagB = false;

						}
						else {

							int arrayLOL[10][2] = { { 0, 1 }, { 0, 2 }, { 0, 3 }, { 1, 1 }, { 1, 2 }, { 1, 3 }, { 2, 3 }, { 3, 3 }, { 2, 2 }, { 0, 0 } };

							for (int i = 0; i < 10; i++)
								if (*(active.figure + i))
									if (shadow_sells[x_pos_of_figure / CELL_SIZE + arrayLOL[i][0]][y_pos_of_figure / CELL_SIZE + arrayLOL[i][1]].square) { flagB = false; on_floor = true;  }

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
						
						if (flagB)
						{
							y_pos_of_figure += CELL_SIZE;

							SDL_RenderClear(renderer);

							Figures_Renderer(active.figure, color, x_pos_of_figure, y_pos_of_figure, renderer);
							Shadow_Render(renderer);

							SDL_RenderPresent(renderer);

							this_thread::sleep_for(chrono::milliseconds(inert));
							if (inert >= 12) {
								inert -= 12;
							}
						};
					}
				}
								 this_thread::sleep_for(chrono::milliseconds(SLEEPING_TIME / 10));
								 break;
				case SDLK_p: {

					pause = true;
				}
							 break;

				case SDLK_LEFT: {
					cout << "Left arrow pressed";
					bool flag = true;

					int arrayLOL[10][2] = {
							{1, 0}, {1, 1}, {1, 2}, {0, 0}, {0, 1}, {0, 2}, {-1, 2}, {-2, 2}, {-1, 1}, {1, -1} };

					if (x_pos_of_figure == 0) {
						flag = false;
						//cout << "LOL2!";
					}
					else {
						if (x_pos_of_figure != 0)
						{
							for (int i = 0; i < 10; i++)
								if (*(active.figure + i))
									if (shadow_sells[x_pos_of_figure / CELL_SIZE - arrayLOL[i][0]][y_pos_of_figure / CELL_SIZE + arrayLOL[i][1]].square) {
										flag = false;
										//cout << "\nLOL! - " << flag;
									}
						}
					}
					if (flag) {
						x_pos_of_figure -= CELL_SIZE;
						SDL_RenderClear(renderer);
						Figures_Renderer(active.figure, color, x_pos_of_figure, y_pos_of_figure, renderer);
						Shadow_Render(renderer);
						SDL_RenderPresent(renderer);
					}
					flag = true;
				}
								break;
				case SDLK_RIGHT: {
					if (x_pos_of_figure + active.figure_width == SCREEN_WIDTH) {}


					bool flagR = true;

					int arrayLOL[10][2] = {
							{1, 0}, {1, 1}, {1, 2}, {2, 0}, {2, 1}, {2, 2}, {3, 3}, {4, 3}, {3, 2}, {1, -1} };

					if (x_pos_of_figure + active.figure_width == SCREEN_WIDTH) {
						flagR = false;
						//cout << "LOL2!";
					}
					else {
						if (x_pos_of_figure != SCREEN_WIDTH - active.figure_width)
						{
							for (int i = 0; i < 10; i++)
								if (*(active.figure + i))
									if (shadow_sells[x_pos_of_figure / CELL_SIZE + arrayLOL[i][0]][y_pos_of_figure / CELL_SIZE + arrayLOL[i][1]].square) {
										flagR = false;
										//cout << "\nLOL! - " << flagR;
									}
						}
					}
					if (flagR) {
						x_pos_of_figure += CELL_SIZE;
						SDL_RenderClear(renderer);
						Figures_Renderer(active.figure, color, x_pos_of_figure, y_pos_of_figure, renderer);
						Shadow_Render(renderer);
						SDL_RenderPresent(renderer);
					}
					flagR = true;
				}
								 break;
				case SDLK_x: {
				case SDLK_UP: {
					bool is_updated = false;

					const unsigned int figures_changes[18][2] = { { 0, 8 }, { 8, 9 }, { 9, 10 }, { 10, 0 }, { 1, 11 }, { 11, 1 }, { 3, 12 }, { 12, 3 }, { 6, 13 }, { 13, 14 }, { 14, 15 }, { 15, 6 }, { 4, 16 }, { 16, 4 }, { 2, 17 }, { 17, 18 }, { 18, 19 }, { 19, 2 } };

					for (int i = 0; i < 18; i++)
						if (equal(begin(active.figure), end(active.figure), begin((figures + figures_changes[i][0])->figure))) {
							active = *(figures + figures_changes[i][1]);
							is_updated = true;
							th2.~thread();
							break;
						}

					if (is_updated) {
						SDL_RenderClear(renderer);
						Figures_Renderer(active.figure, color, x_pos_of_figure, y_pos_of_figure, renderer);
						Shadow_Render(renderer);
						SDL_RenderPresent(renderer);
					}
					this_thread::sleep_for(chrono::milliseconds(SLEEPING_TIME / 8));
					break;
				}}
				case SDLK_DOWN: {

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

					if (flagB && !loss)
					{
						y_pos_of_figure += CELL_SIZE;

						SDL_RenderClear(renderer);

						Figures_Renderer(active.figure, color, x_pos_of_figure, y_pos_of_figure, renderer);
						Shadow_Render(renderer);

						SDL_RenderPresent(renderer);
					}
				}

						break;
				}
			}
			else
			{				
				switch (event.key.keysym.sym) {
				case SDLK_p: {

					pause = false;
				}
							 break;
				}
			}				
			}
		}
		this_thread::sleep_for(chrono::milliseconds(SLEEPING_TIME / 20));
	}
	cout << "End of the cycle - " << loss;
		
	if (loss)
	{
		cout << "You are loss. NOOB! (Hahahahahahahah)";
		this_thread::sleep_for(chrono::milliseconds(SLEEPING_TIME * 20));
	}
	return 0;	
}