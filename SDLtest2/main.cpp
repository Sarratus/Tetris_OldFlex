#include <algorithm>
#include <iostream>
#include <SDL.h>
#include <thread>
#include <chrono>
#include <mutex>
#include "Var.h"


void Menu(bool& start, bool& loss, SDL_Renderer* renderer, SDL_Window* window) {

	double angle = 0, angle2 = 0;
	short int change = 2;
	SDL_Rect dst;
	dst.h = 600;		dst.w = 600;
	dst.x = SCREEN_WIDTH - dst.w / 2 - 50;	dst.y = SCREEN_HEIGHT / 2 - dst.h / 2 - 200;
	
	SDL_Rect dst2;
	dst2.h = 256;		dst2.w = 256;
	dst2.x = 20 - dst2.w/2;	dst2.y = 820;

	SDL_Rect dst3;
	dst3.h = 500;		dst3.w = 500;
	dst3.x = 100;	dst3.y = -230;

	SDL_Rect dst4;
	dst4 = dst3;
	dst4.y = dst3.y+500;

	SDL_Rect dst5;
	dst5 = dst3;
	dst5.y = dst3.y+500+500;
	
	SDL_Color White = { 215, 215, 215 };
	SDL_Color Black = { 20, 20, 22 };
	SDL_Color Gray = { 90, 90, 91 };

	SDL_Texture* message = nullptr,* message_o = nullptr,* theme_message = nullptr,* theme_message_o = nullptr;
	
	message = Text_Texture("press ENTER to start", renderer, White, false, 0);
	message_o = Text_Texture("press ENTER to start", renderer, Black, false, 0);

	theme_message = Text_Texture("1 - color theme     2 - dark theme", renderer, White, false, 0);
	theme_message_o = Text_Texture("1 - color theme     2 - dark theme", renderer, Black, false, 0);

	SDL_Rect Message_rect; 
	Message_rect.w = 450;
	Message_rect.h = 30;
	Message_rect.x = (SCREEN_WIDTH+UI_WIDTH) / 2 - Message_rect.w / 2 + 2;
	Message_rect.y = 700; 

	SDL_Rect Message_rect_2;
	Message_rect_2.w = 340;
	Message_rect_2.h = 15;
	Message_rect_2.x = (SCREEN_WIDTH + UI_WIDTH) / 2 - Message_rect_2.w / 2;
	Message_rect_2.y = 775;


	SDL_Rect dst6;
	dst6.h = 160;	dst6.w = 500;
	dst6.x = 100;	dst6.y = 665;

	SDL_Rect src_back;
	src_back.h = 50;	src_back.w = 48;
	src_back.x = 1;		src_back.y = 0;

	SDL_Rect dst7;
	dst7.h = SCREEN_HEIGHT+40;	dst7.w = SCREEN_WIDTH+UI_WIDTH;
	dst7.x = 0;	dst7.y = -20;

	while (!start || angle2 < 10) {		
				
		SDL_RenderClear(renderer);	

		SDL_RenderCopy(renderer, background, &src_back, &dst7);

		SDL_RenderCopy(renderer, block, &srcGREEN, &dst3);
		SDL_RenderCopy(renderer, block, &srcBLUE, &dst4);
		SDL_RenderCopy(renderer, block, &srcMAGNT, &dst5);
				
		SDL_RenderCopy(renderer, background, &src_back, &dst6);
		
		if (block != block_color)
		{
			SDL_RenderCopyEx(renderer, message, NULL, &Message_rect, NULL, NULL, SDL_FLIP_NONE);
			SDL_RenderCopyEx(renderer, theme_message, NULL, &Message_rect_2, NULL, NULL, SDL_FLIP_NONE);
		}
		else
		{
			SDL_RenderCopyEx(renderer, message_o, NULL, &Message_rect, NULL, NULL, SDL_FLIP_NONE);
			SDL_RenderCopyEx(renderer, theme_message_o, NULL, &Message_rect_2, NULL, NULL, SDL_FLIP_NONE);
		}		
		
		if (dst3.y >= 1000)
		{
			dst3.y -= 1500;
		}
		else
		{
			dst3.y += 3;
		}
		
		if (dst4.y >= 1000)
		{
			dst4.y -= 1500;
		}
		else
		{
			dst4.y += 3;
		}
		
		if (dst5.y >= 1000)
		{
			dst5.y -= 1500;
		}
		else
		{
			dst5.y += 3;
		}

		render.lock();SDL_RenderPresent(renderer);render.unlock();

		dst.h += change;
		dst.w += change;
				
		if (dst.h == 700)
			change *= -1;
		if (dst.h == 600)
			change *= -1;			

		this_thread::sleep_for(chrono::milliseconds(25));

		if (start)
			angle2 += 1;
	}
	
	if (!loss)
	if (start)
	{		
		unsigned int opacity = 255, time_pause = 13, steps = 110;
		
		int accel = 2;
		dst.x = 500;
		SDL_SetTextureBlendMode(background_color, SDL_BLENDMODE_BLEND);
		SDL_SetTextureBlendMode(background_dark, SDL_BLENDMODE_BLEND);

		for (int i = 0; i < steps; i++)
		{			
			SDL_RenderClear(renderer);

			if (opacity > 2) 
				if (block != block_color) {
					SDL_SetTextureAlphaMod(message, ------opacity);						
				} else {
					SDL_SetTextureAlphaMod(message_o, ------opacity);														
				}			
				
			if (angle >= 360)
				angle -= 360;
			
			----dst2.x;

			Background_Renderer(renderer);

			if (block == block_color) {
				SDL_RenderCopy(renderer, background_color, &src_back, &dst7);
			} else {
				SDL_RenderCopy(renderer, background_dark, &src_back, &dst7);
			}
			

			SDL_RenderCopy(renderer, block, &srcGREEN, &dst3);
			SDL_RenderCopy(renderer, block, &srcBLUE, &dst4);
			SDL_RenderCopy(renderer, block, &srcMAGNT, &dst5);

			SDL_RenderCopy(renderer, background, &src_back, &dst6);				
			
			if (block != block_color) {

				SDL_RenderCopyEx(renderer, message, NULL, &Message_rect, NULL, NULL, SDL_FLIP_NONE);
			}
			else
			{
				SDL_RenderCopyEx(renderer, message_o, NULL, &Message_rect, NULL, NULL, SDL_FLIP_NONE);
			}	
			
			dst.x -= 3;
			dst6.w -= accel;

			if (dst3.y > 0 && dst3.y < 500) {
				dst3.x += accel;
			}
			else
			{
				dst3.x -= accel;
			}
			
			if (dst4.y > 0 && dst4.y < 500) {
				dst4.x += accel;
			}
			else
			{
				dst4.x -= accel;
			}

			if (dst5.y > 0 && dst5.y < 500) {
				dst5.x += accel;
			}
			else
			{
				dst5.x -= accel;
			}

			accel += 1;
						
			render.lock();SDL_RenderPresent(renderer);render.unlock();

			this_thread::sleep_for(chrono::milliseconds(time_pause));			
		}		
	}
}

int main(int argc, char * argv[]) {
	
	Figures_Init();
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
	SDL_Window *window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH+UI_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		//cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED/* || SDL_RENDERER_PRESENTVSYNC*/);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	if (renderer == nullptr) {
		//cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	// 193		201		209		- white 
	// 19		20		22		- black

	block_color = Image_Load("Squares3.bmp", renderer);
	block_dark = Image_Load("Squares2.bmp", renderer);
	
	block = block_color;
	
	background_color = Image_Load("backgroung3.bmp", renderer);
	background_dark = Image_Load("backgroung2.bmp", renderer);

	background = background_color;	

	bool loss = false;
	bool start = false;
	   
	thread Menu(Menu, ref(start), ref(loss), ref(renderer), ref(window));
	
	while (!start)
	{
		SDL_Event event1;
		
		while (SDL_PollEvent(&event1)) {
			
			
			

			if (event1.type == SDL_QUIT) {
				loss = true;
				start = true;				
			}				
			
			switch (event1.type) {
			case SDL_KEYDOWN:
				switch (event1.key.keysym.sym) {
					
						case SDLK_RETURN: {
						start = true;
						break;
						}

						case SDLK_1: {
							block = block_color;
							background = background_color;
							break;
						}

						case SDLK_2: {
							block = block_dark;
							background = background_dark;
							break;
						}							
				}
			}
		}
		this_thread::sleep_for(chrono::milliseconds(50));
	}

	Menu.join();
	Menu.~thread();	 
	
	SDL_Color main_color, secondary_color;

	if (block == block_color) {

		main_color = { 193, 201, 209 };
		secondary_color = { 19, 20, 22 };
		
		SDL_DestroyTexture(background_dark);
		SDL_DestroyTexture(block_dark);
		
		block_shadow = Image_Load("Squares3.bmp", renderer);

		Text_Texture_Init(renderer, secondary_color);

		SDL_SetRenderDrawColor(renderer, 193, 201, 209, 255);


	} else {

		main_color = { 19, 20, 22 };
		secondary_color = { 193, 201, 209 };

		SDL_DestroyTexture(block_color);
		SDL_DestroyTexture(background_color);

		block_shadow = Image_Load("Squares2.bmp", renderer);

		Text_Texture_Init(renderer, secondary_color);

		SDL_SetRenderDrawColor(renderer, 19, 20, 22, 255);
	}

		Figure active;
		SDL_Rect color;

		SDL_SetTextureBlendMode(block_shadow, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(block_shadow, 80);

	if (!loss) {

		Generate_New_Figure(color, active, 1);

		thread th2(The_Game, ref(loss), renderer, ref(color), ref(active));
		
		SDL_RenderClear(renderer);

		render.lock();

		Background_Renderer(renderer);
		Background_Renderer(renderer);
		Figures_Renderer(active.figure, color, x_pos_of_figure, y_pos_of_figure, renderer, 1);
		//Background_Renderer(renderer);

		SDL_RenderPresent(renderer);render.unlock();
		
		th2.detach();
	}	

	while (!loss) {
		//cout << "chityy";
		SDL_Event event;
		
		while (process_pause) {

			SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
			this_thread::sleep_for(chrono::milliseconds(20));
		}
		
		if (points > 4500 * points_modifier) {
			SLEEPING_TIME /= 2;
			points_modifier *= 2;
		}			

		if(y_pos_of_figure>=0)
		while (SDL_PollEvent(&event) && !process_pause) {
			
			/*cout << "event data:";
			cout << " " << event.type << endl;*/
			
			if (event.type == SDL_QUIT)
				return 0;

			switch (event.type) {
			case SDL_KEYDOWN:
			
			if (!pause) {

				switch (event.key.keysym.sym) {
				case SDLK_SPACE: {

					process_pause = true;
					
					bool on_floor = false;
					int inert = 45;
					SDL_Rect flag = color;

					while (!on_floor && !loss && flag.x == color.x) {

						bool flagB = true;

						unsigned short int arrayKEK[4] = { 2, 5, 6, 7 };

						for (auto i = 0; i < 4; i++)
							if (*(active.figure + arrayKEK[i]))
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
											if (shadow_sells[x_pos_of_figure / CELL_SIZE + arrayLOL[i][0]][y_pos_of_figure / CELL_SIZE + arrayLOL[i][1]].square) { flagB = false; on_floor = true; }

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
							Background_Renderer(renderer);
							Figures_Renderer(active.figure, color, x_pos_of_figure, y_pos_of_figure, renderer);
							Shadow_Render(renderer);

							render.lock();SDL_RenderPresent(renderer);render.unlock();
						}

						if (flagB)
						{
							y_pos_of_figure += CELL_SIZE;							

							SDL_RenderClear(renderer);

							Background_Renderer(renderer);
							Figures_Renderer(active.figure, color, x_pos_of_figure, y_pos_of_figure, renderer);
							Shadow_Render(renderer);
							
							render.lock();SDL_RenderPresent(renderer);render.unlock();

							

							this_thread::sleep_for(chrono::milliseconds(inert));
							if (inert >= 12) {
								inert -= 12;
							}
						};
					}
				}
								 process_pause = false;
								 this_thread::sleep_for(chrono::milliseconds(SLEEPING_TIME / 10));
								 break;
				case SDLK_p: {
									

					SDL_RenderClear(renderer);

					Background_Renderer(renderer);
					Figures_Renderer(active.figure, color, x_pos_of_figure, y_pos_of_figure, renderer);
					Shadow_Render(renderer);
					
					Pause_Render(renderer);

					render.lock();SDL_RenderPresent(renderer);render.unlock();

					pause = true;
				}
							 break;

				case SDLK_a: {
				case SDLK_LEFT: {

					process_pause = true;
					
					//cout << "Left arrow pressed";
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
						
						Background_Renderer(renderer);
						Figures_Renderer(active.figure, color, x_pos_of_figure, y_pos_of_figure, renderer);
						Shadow_Render(renderer);
						
						render.lock();SDL_RenderPresent(renderer);render.unlock();
					}
					flag = true;

					process_pause = false;

					break;
				}}								

				case SDLK_d: {
				case SDLK_RIGHT: {
					
					process_pause = true;
					
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
						
						Background_Renderer(renderer);
						Figures_Renderer(active.figure, color, x_pos_of_figure, y_pos_of_figure, renderer);
						Shadow_Render(renderer);
						
						render.lock();SDL_RenderPresent(renderer);render.unlock();
					}
					flagR = true;

					process_pause = false;

					break;
				}}
								 
				case SDLK_w: {
				case SDLK_x: {
				case SDLK_UP: {
					bool is_updated = false;

					const unsigned int figures_changes[18][2] = { { 0, 8 }, { 8, 9 }, { 9, 10 }, { 10, 0 }, { 1, 11 }, { 11, 1 }, { 3, 12 }, { 12, 3 }, { 6, 13 }, { 13, 14 }, { 14, 15 }, { 15, 6 }, { 4, 16 }, { 16, 4 }, { 2, 17 }, { 17, 18 }, { 18, 19 }, { 19, 2 } };

					for (int i = 0; i < 18; i++)
						if (equal(begin(active.figure), end(active.figure), begin((figures + figures_changes[i][0])->figure))) 
							if (x_pos_of_figure + active.figure_width == SCREEN_WIDTH && active.figure_width < (figures + figures_changes[i][1])->figure_width)
							{} else if (true) {

							active = *(figures + figures_changes[i][1]);
							is_updated = true;
							//th2.~thread();
							break;
						}

					if (is_updated) {
						SDL_RenderClear(renderer);
						
						Background_Renderer(renderer);
						Figures_Renderer(active.figure, color, x_pos_of_figure, y_pos_of_figure, renderer);
						Shadow_Render(renderer);
						
						render.lock();SDL_RenderPresent(renderer);render.unlock();
					}
					this_thread::sleep_for(chrono::milliseconds(SLEEPING_TIME / 8));
					break;
				}}}
				
				case SDLK_s: {
				case SDLK_DOWN: {

					bool flagB = true;
					unsigned short int arrayKEK[4] = { 2, 5, 6, 7 };

					for (auto i = 0; i < 4; i++)
						if (*(active.figure + arrayKEK[i]))
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
						
						Background_Renderer(renderer);
						Figures_Renderer(active.figure, color, x_pos_of_figure, y_pos_of_figure, renderer);
						Shadow_Render(renderer);
						
						render.lock();SDL_RenderPresent(renderer);render.unlock();
					}

					if (flagB && !loss)
					{
						y_pos_of_figure += CELL_SIZE;

						SDL_RenderClear(renderer);
						
						Background_Renderer(renderer);
						Figures_Renderer(active.figure, color, x_pos_of_figure, y_pos_of_figure, renderer);
						Shadow_Render(renderer);

						render.lock();SDL_RenderPresent(renderer);render.unlock();
					}

					break;
				}}						
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
		this_thread::sleep_for(chrono::milliseconds(SLEEPING_TIME / 17));
	}
	
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;	
}