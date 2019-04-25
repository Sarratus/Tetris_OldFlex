#include <algorithm> 
#include <iterator>
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <thread>
#include <chrono>
#include <random>

using namespace std;

const unsigned int width = 500;
const unsigned int height = 1000;
const int number_of_figures = 8;
const int width_of_playing_field = 10;
const int HEIGHT_OF_PLAYING_FIELD = 20;
const int CELL_SIZE = 50;
int sleeping_time = 1000;
int x_pos_of_figure = 150;
int y_pos_of_figure = 0;
int number_of_figure_next, previous_figure;
int figure_color_next = 0, figure_color_prev = 0;

SDL_Rect srcRED, srcYELL, srcBLUE, srcGREEN, srcMAGNT, srcCYAN;
SDL_Texture *block = nullptr;
enum Color { Red = 1, Yellow, Blue };
struct Figure { bool figure[10] = { 0,0,0,0,0,0,0,0,0,0 }; int figure_width = 0; };
Figure figures[20];
struct Shadow_Cell { bool square = 0; SDL_Rect color = srcRED; };
Shadow_Cell **shadow_sells;
struct Figure2 { bool **active_sells; };
Figure2 figures2[number_of_figures];

int Generate_Random_Number(int a, int b) {
	random_device rd;
	mt19937 rng(rd());
	uniform_int_distribution<int> rand(a, b);
	return rand(rd);
}
void Generate_New_Figure(SDL_Rect &color, Figure &active) {
	
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
}
SDL_Texture *Image_Load(string image, SDL_Renderer *renderer) {
	SDL_Surface *load_image = nullptr;
	SDL_Texture *texture = nullptr;

	load_image = SDL_LoadBMP(image.c_str());
	if (load_image != nullptr)
	{
		texture = SDL_CreateTextureFromSurface(renderer, load_image);
		SDL_FreeSurface(load_image);
	}
	return texture;
}
void Render(int x, int y, SDL_Texture *image, SDL_Renderer *renderer, SDL_Rect *srcrect)
{
	SDL_Rect pos;
	pos.x = x;
	pos.y = y;
	pos.h = CELL_SIZE;
	pos.w = CELL_SIZE;

	SDL_RenderCopy(renderer, image, srcrect, &pos);
}
void Figures_Renderer(bool figure[10], SDL_Rect color_of_figure, int x, int y, SDL_Renderer *renderer) {
	
	if (*(figure + 0))
		Render(x, y, block, renderer, &color_of_figure);
	if (*(figure + 1))
		Render(x, y + CELL_SIZE, block, renderer, &color_of_figure);
	if (*(figure + 2))
		Render(x, y + 2 * CELL_SIZE, block, renderer, &color_of_figure);
	if (*(figure + 3))
		Render(x + CELL_SIZE, y, block, renderer, &color_of_figure);
	if (*(figure + 4))
		Render(x + CELL_SIZE, y + CELL_SIZE, block, renderer, &color_of_figure);
	if (*(figure + 5))
		Render(x + CELL_SIZE, y + 2 * CELL_SIZE, block, renderer, &color_of_figure);
	if (*(figure + 6))
		Render(x + 2 * CELL_SIZE, y + 2 * CELL_SIZE, block, renderer, &color_of_figure);
	if (*(figure + 7))
		Render(x + 3 * CELL_SIZE, y + 2 * CELL_SIZE, block, renderer, &color_of_figure);
	if (*(figure + 8))
		Render(x + 2 * CELL_SIZE, y + CELL_SIZE, block, renderer, &color_of_figure);
	if (*(figure + 9))
		Render(x, y - 1 * CELL_SIZE, block, renderer, &color_of_figure);
	
}
void Rewrite_of_shadow_cells(Figure active, int x_pos_of_figure, int y_pos_of_figure, SDL_Rect color) {

	int arrayLOL[10][2] = { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 1, 0 }, { 1, 1 }, { 1, 2 }, { 2, 2 }, { 3, 2 }, { 2, 1 }, { 0, -1 } };

	for (int i = 0; i < 10; i++)
		if (*(active.figure + i)) {
			shadow_sells[x_pos_of_figure / CELL_SIZE + arrayLOL[i][0]][y_pos_of_figure / CELL_SIZE + arrayLOL[i][1]].square = true;
			shadow_sells[x_pos_of_figure / CELL_SIZE + arrayLOL[i][0]][y_pos_of_figure / CELL_SIZE + arrayLOL[i][1]].color = color;
		}
}
void Shadow_Render(SDL_Renderer *renderer) {
	for (int i = 0; i < width_of_playing_field; i++)
		for (int j = 0; j < HEIGHT_OF_PLAYING_FIELD; j++) {
			if (shadow_sells[i][j].square)
			{
				Render(i * CELL_SIZE, j * CELL_SIZE, block, renderer, &shadow_sells[i][j].color);
			}
		}
}
bool The_Game(bool &loss, SDL_Renderer *renderer, SDL_Rect &color, Figure &active) {
	bool flagB = true;
	int number_of_figure = 0, previous_figure = 0;

	while (!loss) {
		SDL_RenderClear(renderer);																// RENDER CLEAR
		
		this_thread::sleep_for(chrono::milliseconds(sleeping_time));

		if (y_pos_of_figure >= CELL_SIZE * 17) {

			Rewrite_of_shadow_cells(active, x_pos_of_figure, y_pos_of_figure, color);
			active = *(figures + 7);

			x_pos_of_figure = 150;
			y_pos_of_figure = -CELL_SIZE;

			Generate_New_Figure(color, active);

			SDL_RenderClear(renderer);
			Figures_Renderer(active.figure, color, x_pos_of_figure, y_pos_of_figure, renderer);
			Shadow_Render(renderer);
			SDL_RenderPresent(renderer);
		}
		else {
			flagB = true;

			int arrayLOL[10][2] = { { 0, 1 }, { 0, 2 }, { 0, 3 }, { 1, 1 }, { 1, 2 }, { 1, 3 }, { 2, 3 }, { 3, 3 }, { 2, 2 }, { 0, 0 } };

			for (int i = 0; i < 10; i++)
				if (*(active.figure + i))
					if (shadow_sells[x_pos_of_figure / CELL_SIZE + arrayLOL[i][0]][y_pos_of_figure / CELL_SIZE + arrayLOL[i][1]].square) { flagB = false; }

			if (!flagB) {
				if (y_pos_of_figure == 0)
					loss = true;

				Rewrite_of_shadow_cells(active, x_pos_of_figure, y_pos_of_figure, color);
				active = *(figures + 7);

				for (int i = 0; i < HEIGHT_OF_PLAYING_FIELD; i++)
					if (shadow_sells[0][i].square && shadow_sells[1][i].square && shadow_sells[2][i].square && shadow_sells[3][i].square && shadow_sells[4][i].square && shadow_sells[5][i].square && shadow_sells[6][i].square && shadow_sells[7][i].square && shadow_sells[8][i].square && shadow_sells[9][i].square) {

						//cout << "\nLine cheked!\n";
						for (int j = 0; j < width_of_playing_field; j++)
						{
							this_thread::sleep_for(chrono::milliseconds(sleeping_time / 20));
							SDL_RenderClear(renderer);
							shadow_sells[j][i].square = false;
							Shadow_Render(renderer);
							SDL_RenderPresent(renderer);
						}
						//cout << "\nLine deleted!\n";
						SDL_RenderClear(renderer);
						
						for (int j = 0; j < width_of_playing_field; j++)
							for (int k = HEIGHT_OF_PLAYING_FIELD - i - 1; k >= 0; k--)
							{
								cout << "Flexing";
								if (shadow_sells[j][k].square) {
									shadow_sells[j][k + 1].square = shadow_sells[j][k].square;
									shadow_sells[j][k].square = false;
									shadow_sells[j][k + 1].color = shadow_sells[j][k].color;
								}
							}
						
						this_thread::sleep_for(chrono::milliseconds(sleeping_time / 5));
						Shadow_Render(renderer);
						SDL_RenderPresent(renderer);
					}

				if (!loss) {
					x_pos_of_figure = 150;
					y_pos_of_figure = -CELL_SIZE;
										
					Generate_New_Figure(color, active);

					SDL_RenderClear(renderer);
					Figures_Renderer(active.figure, color, x_pos_of_figure, y_pos_of_figure, renderer);
					Shadow_Render(renderer);
					SDL_RenderPresent(renderer);
				}
			}
		}
//		cout << "\nPADAU! -\t";
		SDL_RenderClear(renderer);
		
		y_pos_of_figure += CELL_SIZE;
		Figures_Renderer(active.figure, color, x_pos_of_figure, y_pos_of_figure, renderer);
		Shadow_Render(renderer);
		SDL_RenderPresent(renderer);															// RENDER PRESENT
	}
	return 0;
}
void Menu(bool &start, SDL_Renderer *renderer, SDL_Rect color, Figure active) {

	unsigned short int angle = 0;
	short int change = 2;
	SDL_Rect dst;
	dst.h = 600;		dst.w = 600;
	dst.x = width - dst.w / 2 - 50;	dst.y = height / 2 - dst.h / 2 - 200;
		
	TTF_Font* Sans = nullptr;
	Sans = TTF_OpenFont("C:\\Users\\User\\source\\repos\\SDLtest2\\Debug\\Pixelnaya_Zalupa.ttf", 24);
	SDL_Color White = { 255, 255, 255 };
	
	SDL_Surface* message_surface = nullptr;
	SDL_Texture* message = nullptr;
	
	if(Sans != nullptr)
		message_surface = TTF_RenderText_Blended(Sans, "Press Enter to start", White);
	
	if (message_surface != nullptr)
	{
		message = SDL_CreateTextureFromSurface(renderer, message_surface);
		SDL_FreeSurface(message_surface);
	}
	TTF_CloseFont(Sans);	

	SDL_Rect Message_rect; 
	Message_rect.w = 410;
	Message_rect.h = 33;
	Message_rect.x = width / 2 - Message_rect.w / 2 + 3;
	Message_rect.y = 700; 

	while (!start) {		

		SDL_RenderClear(renderer);
		
		SDL_RenderCopyEx(renderer, block, &srcBLUE, &dst, angle++, NULL, SDL_FLIP_NONE);

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
		/*for (int i = 0; i < length; i++)
		{

		}
		SDL_RenderClear(renderer);

		SDL_RenderCopyEx(renderer, block, &srcBLUE, &dst, angle++, NULL, SDL_FLIP_NONE);

		SDL_RenderCopyEx(renderer, message, NULL, &Message_rect, NULL, NULL, SDL_FLIP_NONE);

		SDL_RenderPresent(renderer);*/
	}
}

int main(int argc, char * argv[]) {
	//curr_time = time(NULL);

	*(figures + 0) = { { 1,1,1,1,0,0,0,0,0,0 }, {100} };	*(figures + 8) = { { 0,1,0,0,1,0,1,0,1,0 }, {150} };	*(figures + 9) = { { 0,0,1,1,1,1,0,0,0,0 }, {100} };	*(figures + 10) = { { 0,1,1,0,0,1,1,0,0,0 }, {150} };
	*(figures + 1) = { { 0,1,1,1,1,0,0,0,0,0 }, {100} };	*(figures + 11) = { { 0,1,0,0,1,1,1,0,0,0 }, {150} };
	*(figures + 2) = { { 1,0,0,1,1,1,0,0,0,0 }, {100} };	*(figures + 17) = { { 0,0,1,0,0,1,1,0,1,0 }, {150} };	*(figures + 18) = { { 1,1,1,0,0,1,0,0,0,0 }, {100} };	*(figures + 19) = { { 0,1,1,0,1,0,0,0,1,0 }, {150} };
	*(figures + 3) = { { 1,1,0,0,1,1,0,0,0,0 }, {100} };	*(figures + 12) = { { 0,0,1,0,1,1,0,0,1,0 }, {150} };
	*(figures + 4) = { { 0,0,1,0,0,1,1,1,0,0 }, {200} };	*(figures + 16) = { { 1,1,1,0,0,0,0,0,0,1 }, {50} };
	*(figures + 5) = { { 0,1,1,0,1,1,0,0,0,0 }, {100} };
	*(figures + 6) = { { 0,0,1,0,1,1,1,0,0,0 }, {150} };	*(figures + 13) = { { 1,1,1,0,1,0,0,0 }, {100} };		*(figures + 14) = { { 0,1,0,0,1,1,0,0,1,0 }, {150} };	*(figures + 15) = { { 0,1,0,1,1,1,0,0,0,0 }, {100} };

	*(figures + 7) = { { 0,0,0,0,0,0,0,0 }, {0} };

	srcRED.h = CELL_SIZE;		srcYELL.h = CELL_SIZE;		srcBLUE.h = CELL_SIZE;		srcGREEN.h = CELL_SIZE;		srcMAGNT.h = CELL_SIZE;		srcCYAN.h = CELL_SIZE;
	srcRED.w = CELL_SIZE;		srcYELL.w = CELL_SIZE;		srcBLUE.w = CELL_SIZE;		srcGREEN.w = CELL_SIZE;		srcMAGNT.w = CELL_SIZE;		srcCYAN.w = CELL_SIZE;
	srcRED.x = 0;				srcYELL.x = 50;				srcBLUE.x = 100;			srcGREEN.x = 150;			srcMAGNT.x = 200;			srcCYAN.x = 250;
	srcRED.y = 0;				srcYELL.y = 0;				srcBLUE.y = 0;				srcGREEN.y = 0;				srcMAGNT.y = 0;				srcCYAN.y = 0;

	shadow_sells = new Shadow_Cell*[width_of_playing_field];
	for (int i1 = 0; i1 < width_of_playing_field; i1++)
	{
		*(shadow_sells + i1) = new Shadow_Cell[HEIGHT_OF_PLAYING_FIELD];
	}

	if (TTF_Init() == -1)
	{
		//cout << "SDL_ttf initialization failed.";
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		//cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
	}
	else
	{
		//cout << "SDL initialization succeeded!";
	}
	SDL_Window *window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
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

	bool loss = false;

	Figure active;
	

	
	SDL_Rect color = srcYELL;
	figure_color_next = 1;
	
	previous_figure = 0;

	bool start = false;
	thread Menu(Menu, ref(start), ref(renderer), color, active);
	
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
				case SDLK_UP: {
					cout << "Druguyu zhmi";
					break;
				}
				case SDLK_SPACE: {
					cout << "space";
					break;
				}
				}
			}
		}
		this_thread::sleep_for(chrono::milliseconds(16));
	}

	Menu.join();

	TTF_Quit();
		
	Generate_New_Figure(color, active);
		
	thread th2(The_Game, ref(loss), renderer, ref(color), ref(active));
	th2.detach();
	
	//cout << "Event tracker will started";
	while (!loss) {
//		cout << "chityy";
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
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

							x_pos_of_figure = 150;
							y_pos_of_figure = -CELL_SIZE;
							
							Generate_New_Figure(color, active);

							SDL_RenderClear(renderer);
							Figures_Renderer(active.figure, color, x_pos_of_figure, y_pos_of_figure, renderer);
							Shadow_Render(renderer);
							SDL_RenderPresent(renderer);
						}
						else {


							int arrayLOL[10][2] = { { 0, 1 }, { 0, 2 }, { 0, 3 }, { 1, 1 }, { 1, 2 }, { 1, 3 }, { 2, 3 }, { 3, 3 }, { 2, 2 }, { 0, 0 } };

							for (int i = 0; i < 10; i++)
								if (*(active.figure + i))
									if (shadow_sells[x_pos_of_figure / CELL_SIZE + arrayLOL[i][0]][y_pos_of_figure / CELL_SIZE + arrayLOL[i][1]].square) { flagB = false; on_floor = true; }

							if (!flagB) {
								if (y_pos_of_figure == 0) {
									loss = true;
									break;
									break;

								}


								Rewrite_of_shadow_cells(active, x_pos_of_figure, y_pos_of_figure, color);
								active = *(figures + 7);

								for (int i = 0; i < HEIGHT_OF_PLAYING_FIELD; i++)
									if (shadow_sells[0][i].square && shadow_sells[1][i].square && shadow_sells[2][i].square && shadow_sells[3][i].square && shadow_sells[4][i].square && shadow_sells[5][i].square && shadow_sells[6][i].square && shadow_sells[7][i].square && shadow_sells[8][i].square && shadow_sells[9][i].square) {

										//cout << "\nLine cheked!\n";
										for (int j = 0; j < width_of_playing_field; j++)
										{
											this_thread::sleep_for(chrono::milliseconds(sleeping_time / 20));
											SDL_RenderClear(renderer);
											shadow_sells[j][i].square = false;
											Shadow_Render(renderer);
											SDL_RenderPresent(renderer);
										}
										//cout << "\nLine deleted!\n";
										SDL_RenderClear(renderer);

										for (int j = 0; j < width_of_playing_field; j++)
											for (int k = i - 1; k >= 0; k--)
											{
												//cout << "Flexing";
												if (shadow_sells[j][k].square) {
													shadow_sells[j][k + 1].square = shadow_sells[j][k].square;
													shadow_sells[j][k].square = false;
													shadow_sells[j][k + 1].color = shadow_sells[j][k].color;
												}
											}

										this_thread::sleep_for(chrono::milliseconds(sleeping_time / 8));
										Shadow_Render(renderer);
										SDL_RenderPresent(renderer);
									}

								if (!loss) {
									
									on_floor = true;
																		
									x_pos_of_figure = 150;
									y_pos_of_figure = -CELL_SIZE;

									Generate_New_Figure(color, active);

									SDL_RenderClear(renderer);
									Figures_Renderer(active.figure, color, x_pos_of_figure, y_pos_of_figure, renderer);
									Shadow_Render(renderer);
									SDL_RenderPresent(renderer);
								}
							}
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
					this_thread::sleep_for(chrono::milliseconds(sleeping_time / 10));
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
					if (x_pos_of_figure + active.figure_width == width) {}


					bool flagR = true;

					int arrayLOL[10][2] = {
							{1, 0}, {1, 1}, {1, 2}, {2, 0}, {2, 1}, {2, 2}, {3, 3}, {4, 3}, {3, 2}, {1, -1} };

					if (x_pos_of_figure + active.figure_width == width) {
						flagR = false;
						//cout << "LOL2!";
					}
					else {
						if (x_pos_of_figure != width - active.figure_width)
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
					this_thread::sleep_for(chrono::milliseconds(sleeping_time / 8));
					break;
				}}
				case SDLK_DOWN:

					bool flagB = true;
					if (y_pos_of_figure >= CELL_SIZE * 17) {

						Rewrite_of_shadow_cells(active, x_pos_of_figure, y_pos_of_figure, color);
						active = *(figures + 7);

						x_pos_of_figure = 150;
						y_pos_of_figure = -CELL_SIZE;
												
						Generate_New_Figure(color, active);

						SDL_RenderClear(renderer);
						Figures_Renderer(active.figure, color, x_pos_of_figure, y_pos_of_figure, renderer);
						Shadow_Render(renderer);
						SDL_RenderPresent(renderer);
					}
					else {


						int arrayLOL[10][2] = { { 0, 1 }, { 0, 2 }, { 0, 3 }, { 1, 1 }, { 1, 2 }, { 1, 3 }, { 2, 3 }, { 3, 3 }, { 2, 2 }, { 0, 0 } };

						for (int i = 0; i < 10; i++)
							if (*(active.figure + i))
								if (shadow_sells[x_pos_of_figure / CELL_SIZE + arrayLOL[i][0]][y_pos_of_figure / CELL_SIZE + arrayLOL[i][1]].square) { flagB = false; }

						if (!flagB) {
							if (y_pos_of_figure == 0) {
								loss = true;
								break;
								break;
								
							}
								

							Rewrite_of_shadow_cells(active, x_pos_of_figure, y_pos_of_figure, color);
							active = *(figures + 7);

							for (int i = 0; i < HEIGHT_OF_PLAYING_FIELD; i++)
								if (shadow_sells[0][i].square && shadow_sells[1][i].square && shadow_sells[2][i].square && shadow_sells[3][i].square && shadow_sells[4][i].square && shadow_sells[5][i].square && shadow_sells[6][i].square && shadow_sells[7][i].square && shadow_sells[8][i].square && shadow_sells[9][i].square) {

									//cout << "\nLine cheked!\n";
									for (int j = 0; j < width_of_playing_field; j++)
									{
										this_thread::sleep_for(chrono::milliseconds(sleeping_time / 20));
										SDL_RenderClear(renderer);
										shadow_sells[j][i].square = false;
										Shadow_Render(renderer);
										SDL_RenderPresent(renderer);
									}
									//cout << "\nLine deleted!\n";
									SDL_RenderClear(renderer);
									
									for (int j = 0; j < width_of_playing_field; j++)
										for (int k = i - 1; k >= 0; k--)
										{
											//cout << "Flexing";
											if (shadow_sells[j][k].square) {
												shadow_sells[j][k + 1].square = shadow_sells[j][k].square;
												shadow_sells[j][k].square = false;
												shadow_sells[j][k + 1].color = shadow_sells[j][k].color;
											}
										}
									
									this_thread::sleep_for(chrono::milliseconds(sleeping_time / 8));
									Shadow_Render(renderer);
									SDL_RenderPresent(renderer);
								}

							if (!loss) {
								x_pos_of_figure = 150;
								y_pos_of_figure = -CELL_SIZE;
																
								Generate_New_Figure(color, active);

								SDL_RenderClear(renderer);
								Figures_Renderer(active.figure, color, x_pos_of_figure, y_pos_of_figure, renderer);
								Shadow_Render(renderer);
								SDL_RenderPresent(renderer);
							}
						}
					}
					if (flagB)
					{
						y_pos_of_figure += CELL_SIZE;

						SDL_RenderClear(renderer);

						Figures_Renderer(active.figure, color, x_pos_of_figure, y_pos_of_figure, renderer);
						Shadow_Render(renderer);

						SDL_RenderPresent(renderer);
					};
				}
				break;
			}
		}
		this_thread::sleep_for(chrono::milliseconds(sleeping_time / 25));
	}
	cout << "End of the cycle - " << loss;
	
	if (loss)
	{
		cout << "You are loss. NOOB! (Hahahahahahahah)";
		this_thread::sleep_for(chrono::milliseconds(sleeping_time * 20));
	}

	return 0;

	
}