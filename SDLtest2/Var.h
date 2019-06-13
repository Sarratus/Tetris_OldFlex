#pragma once

#ifndef SDL.h
#include <SDL.h>
#endif // !SDL.h

#ifndef string
#include <string>
#endif // !string

#ifndef mutex
#include <mutex>
#endif // !mutex

using namespace std;

const unsigned short int SCREEN_WIDTH = 500;
const unsigned short int UI_WIDTH = 200;
const unsigned short int SCREEN_HEIGHT = 1000;

const unsigned short int NUMBER_OF_FIGURES = 8;

const unsigned short int WIDTH_OF_PLAYING_FIELD = 10;
const unsigned short int HEIGHT_OF_PLAYING_FIELD = 20;
const unsigned short int CELL_SIZE = 50;

extern unsigned int SLEEPING_TIME;

extern int x_pos_of_figure;
extern int y_pos_of_figure;

extern long unsigned int points, points_modifier;

extern int number_of_figure_next, previous_figure, previous_figure2;
extern int figure_color_next, figure_color_prev, figure_color_prev2;

extern bool pause, process_pause;

extern SDL_Rect srcRED, srcYELL, srcBLUE, srcGREEN, srcMAGNT, srcCYAN;

extern SDL_Texture *block, * block_color, * block_dark,* block_shadow;
extern SDL_Texture* background,* background_color,* background_dark;

struct Figure { bool figure[10] = { 0,0,0,0,0,0,0,0,0,0 }; int figure_width = 0; };
extern Figure figures[20];

struct Shadow_Cell { bool square = false; SDL_Rect color = srcBLUE; };
extern Shadow_Cell** shadow_sells;

extern mutex render;

//struct Figure2 { bool** active_sells; };
//extern Figure2 figures2[NUMBER_OF_FIGURES];


/////////////////////////////////////////// FUNCTIONS //////////////////////////////////////////////


void Figures_Renderer(bool figure[10], SDL_Rect color_of_figure, int x, int y, SDL_Renderer* renderer);
void Figures_Renderer(bool figure[10], SDL_Rect color_of_figure, int x, int y, SDL_Renderer* renderer, int a);

void Shadow_Render(SDL_Renderer* renderer);
void Shadow_Render(SDL_Renderer* renderer, int del_x);

SDL_Texture* Image_Load(string image, SDL_Renderer* renderer);

bool The_Game(bool& loss, SDL_Renderer* renderer, SDL_Rect& color, Figure& active);

SDL_Texture* Text_Texture(const char* Text, SDL_Renderer* renderer, SDL_Color Color, bool, int);

void Rewrite_of_shadow_cells(Figure active, int x_pos_of_figure, int y_pos_of_figure, SDL_Rect color);

void Generate_New_Figure(SDL_Rect&, Figure&);
void Generate_New_Figure(SDL_Rect&, Figure&, int);

int Generate_Random_Number(int, int);

void Color_Init();
void Figures_Init();

void Delete_line(SDL_Renderer* renderer);

void Background_Renderer(SDL_Renderer*);

void Pause_Render(SDL_Renderer* renderer);

void Text_Texture_Init(SDL_Renderer* renderer, SDL_Color text_color);

int Figure_Shadow_Renderer(bool figure[10], int x, int y, int& min);