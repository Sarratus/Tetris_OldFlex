#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>
#include <vector>
#include "Var.h"

SDL_Texture* pause_text_texture,* numbers_texture,* next_figure_text_texture;
SDL_Rect numbers_text[10];

SDL_Texture* Image_Load(string image, SDL_Renderer* renderer) {
	
	SDL_Surface* load_image = nullptr;
	SDL_Texture* texture = nullptr;

	load_image = SDL_LoadBMP(image.c_str());
	if (load_image != nullptr)
	{
		texture = SDL_CreateTextureFromSurface(renderer, load_image);
		SDL_FreeSurface(load_image);
	}
	return texture;
}
void Render(int x, int y, SDL_Texture* image, SDL_Renderer* renderer, SDL_Rect* srcrect, int block_size)
{
	SDL_Rect pos;
	pos.x = x;
	pos.y = y;
	pos.h = block_size;
	pos.w = block_size;

	SDL_RenderCopy(renderer, image, srcrect, &pos);
}

int Figure_Shadow_Renderer(bool figure[10], int x, int y, int& min) {

		int arrayLOL[10][2] = { { 0, 1 }, { 0, 2 }, { 0, 3 }, { 1, 1 }, { 1, 2 }, { 1, 3 }, { 2, 3 }, { 3, 3 }, { 2, 2 }, { 0, 0 } };
		int y_del[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
		int y_del_floor = NULL;
				
		for (int i = 0; i < 10; i++)
			if (*(figure + i))
				for (int j = 0; j < HEIGHT_OF_PLAYING_FIELD + 4; j++)
				{
					if (x / CELL_SIZE + arrayLOL[i][0] < 10)
					if ((y / CELL_SIZE + arrayLOL[i][1] + j) <= 19)
						if (shadow_sells[x / CELL_SIZE + arrayLOL[i][0]][y / CELL_SIZE + arrayLOL[i][1] + j].square) {

							y_del[i] = j * CELL_SIZE;

							break;
						}
					if (y + j * CELL_SIZE == 1000 && y_del_floor == NULL) {
						y_del_floor = j * 50 - 150;
					}
				}

		for (int j = 0; j < 10; j++) {
			if (y_del[j] < min && y_del[j] != 1) {
				min = y_del[j];
			}
		}
		if (y_del_floor < min && y_del_floor != 0 && y_del_floor != NULL)
			min = y_del_floor;
		
	return min;
}

void Figures_Preview_Renderer(bool figure[10], int color_of_figure, int x, int y, SDL_Renderer* renderer) {

	int arrayLOL[10][2] = { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 1, 0 }, { 1, 1 }, { 1, 2 }, { 2, 2 }, { 3, 2 }, { 2, 1 }, { 0, -1 } };

	SDL_Rect color;

	switch (color_of_figure)
	{
	case(0):
		color = srcRED;
		break;
	case(1):
		color = srcYELL;
		break;
	case(2):
		color = srcBLUE;
		break;
	case(3):
		color = srcGREEN;
		break;
	case(4):
		color = srcMAGNT;
		break;
	case(5):
		color = srcCYAN;
		break;
	default:
		color = srcYELL;		
		break;
	}

	for (int i = 0; i < 10; i++)
		if (*(figure + i))
			Render(x + arrayLOL[i][0] * 30, y + arrayLOL[i][1] * 30, block, renderer, &color, 30);

}

void Points_renderer(SDL_Renderer* renderer, int x, int y, int h, int w) {

	string points_text = to_string(points);
	SDL_Rect text = { x - points_text.length() * h / 2 + w / 2, y, h, h };
	
	for (int i = 0; i < points_text.length(); i++)
	{
		SDL_RenderCopy(renderer, numbers_texture, &numbers_text[int(points_text[i]) - 48], &text);
		text.x += h;
	}
}

void Background_Renderer(SDL_Renderer* renderer) {

		
	SDL_Rect back;
	back.h = SCREEN_HEIGHT;	back.w = SCREEN_WIDTH;
	back.x = 0;				back.y = 0;

	SDL_RenderCopy(renderer, background, NULL, &back);	

	SDL_Rect preview_src2;
	preview_src2.h = 48;	preview_src2.w = 48;
	preview_src2.x = 1;	preview_src2.y = 1;

	SDL_Rect preview_dst2;
	preview_dst2.h = SCREEN_HEIGHT;	preview_dst2.w = UI_WIDTH;
	preview_dst2.x = SCREEN_WIDTH;	preview_dst2.y = 0;

	SDL_RenderCopy(renderer, background, &preview_src2, &preview_dst2);

	SDL_Rect preview_src;
	preview_src.h = 50 * 3;	preview_src.w = 50 * 4;
	preview_src.x = 0;	preview_src.y = 0;

	SDL_Rect preview_dst = { 540, 80, 30*4, 30*3 };
	SDL_RenderCopy(renderer, background, &preview_src, &preview_dst);		
		
	int x = 540;

	if ((figures + number_of_figure_next)->figure_width < 150)
		x = 570;

	thread preview(Figures_Preview_Renderer, (figures + number_of_figure_next)->figure, figure_color_next, x, 80, renderer);

	Points_renderer(renderer, SCREEN_WIDTH, 204, 16, 200);
	
	SDL_Rect text1 = { SCREEN_WIDTH + 28, 42, 150, 16 };
	SDL_RenderCopy(renderer, next_figure_text_texture, NULL, &text1);
		

		preview.join();
		preview.~thread();	

}

void Figures_Renderer(bool figure[10], SDL_Rect color_of_figure, int x, int y, SDL_Renderer* renderer) {
	
	int min = 1150;		
	
	thread sh(Figure_Shadow_Renderer, figure, x, y, ref(min));		

	int arrayLOL[10][2] = { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 1, 0 }, { 1, 1 }, { 1, 2 }, { 2, 2 }, { 3, 2 }, { 2, 1 }, { 0, -1 } };

	for (int i = 0; i < 10; i++)
		if (*(figure + i))
			if (x + arrayLOL[i][0] * CELL_SIZE < 10*50)
			if (y + arrayLOL[i][1] * CELL_SIZE >= 0)
				Render(x + arrayLOL[i][0] * CELL_SIZE, y + arrayLOL[i][1] * CELL_SIZE, block, renderer, &color_of_figure, CELL_SIZE);
	
	sh.join();	
	sh.~thread();
	
	if (min != 1150)
		for (int i = 0; i < 10; i++)
			if (*(figure + i))
				if (y + min + arrayLOL[i][1] * CELL_SIZE >= 0)
					if (min!=0)
					Render(x + arrayLOL[i][0] * CELL_SIZE, y + min + arrayLOL[i][1] * CELL_SIZE, block_shadow, renderer, &color_of_figure, CELL_SIZE);		
}

void Figures_Renderer(bool figure[10], SDL_Rect color_of_figure, int x, int y, SDL_Renderer* renderer, int a) {
	
	int arrayLOL[10][2] = { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 1, 0 }, { 1, 1 }, { 1, 2 }, { 2, 2 }, { 3, 2 }, { 2, 1 }, { 0, -1 } };

	for (int i = 0; i < 10; i++)
		if (*(figure + i))
			if (y + arrayLOL[i][1] * CELL_SIZE >= 0)
				Render(x + arrayLOL[i][0] * CELL_SIZE, y + arrayLOL[i][1] * CELL_SIZE, block, renderer, &color_of_figure, CELL_SIZE);
}

void Shadow_Render(SDL_Renderer* renderer) {
	for (int i = 0; i < WIDTH_OF_PLAYING_FIELD; i++)
		for (int j = 0; j < HEIGHT_OF_PLAYING_FIELD; j++) {
			if (shadow_sells[i][j].square)
			{
				Render(i * CELL_SIZE, j * CELL_SIZE, block, renderer, &shadow_sells[i][j].color, CELL_SIZE);
			}
		}
}

void Text_Texture_Init(SDL_Renderer* renderer, SDL_Color text_color) {

	pause_text_texture = Text_Texture("pause", renderer, text_color, 0, 0);
	numbers_texture = Text_Texture("0123456789", renderer, text_color, 0, 0);
	for (int i = 0; i < 10; i++)
		*(numbers_text + i) = { 26*i,0,26,26 };
		
	next_figure_text_texture = Text_Texture("next figure:", renderer, text_color, 0, 0);
}

void Pause_Render(SDL_Renderer* renderer) {

	SDL_Color color;

	if (block != block_color) {
		color = { 240, 240, 242 };
	}
	else
	{
		color = { 30, 30, 31 };
	}

	SDL_Rect Message_rect;
	Message_rect.w = 250;
	Message_rect.h = 57;
	Message_rect.x = SCREEN_WIDTH / 2 - Message_rect.w / 2 + 4;
	Message_rect.y = 300 - 1;

	SDL_RenderCopy(renderer, pause_text_texture, NULL, &Message_rect);
}

SDL_Texture* Text_Texture(const char* Text, SDL_Renderer* renderer, SDL_Color Color, bool is_outline, int outline_size) {

	TTF_Init();
	

		TTF_Font* Sans = nullptr;
				
		Sans = TTF_OpenFont("Pixelnaya_Zalupa.ttf", 26);
		
		SDL_Surface* message_surface = nullptr;
		SDL_Texture* message = nullptr;

		if (Sans != nullptr) {
					
			message_surface = TTF_RenderText_Blended(Sans, Text, Color);
		}

		if (message_surface != nullptr)
		{
			message = SDL_CreateTextureFromSurface(renderer, message_surface);
			SDL_FreeSurface(message_surface);
		}
		
		TTF_CloseFont(Sans);
		
		
		TTF_Quit();

		return message;		
}

