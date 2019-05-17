#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>
#include "Var.h"

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
void Render(int x, int y, SDL_Texture* image, SDL_Renderer* renderer, SDL_Rect* srcrect)
{
	SDL_Rect pos;
	pos.x = x;
	pos.y = y;
	pos.h = CELL_SIZE;
	pos.w = CELL_SIZE;

	SDL_RenderCopy(renderer, image, srcrect, &pos);
}
void Figures_Renderer(bool figure[10], SDL_Rect color_of_figure, int x, int y, SDL_Renderer* renderer) {

	int arrayLOL[10][2] = { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 1, 0 }, { 1, 1 }, { 1, 2 }, { 2, 2 }, { 3, 2 }, { 2, 1 }, { 0, -1 } };

	for (int i = 0; i < 10; i++)
		if (*(figure + i))
			Render(x + arrayLOL[i][0] * CELL_SIZE, y + arrayLOL[i][1] * CELL_SIZE, block, renderer, &color_of_figure);

}
void Shadow_Render(SDL_Renderer* renderer) {
	for (int i = 0; i < WIDTH_OF_PLAYING_FIELD; i++)
		for (int j = 0; j < HEIGHT_OF_PLAYING_FIELD; j++) {
			if (shadow_sells[i][j].square)
			{
				Render(i * CELL_SIZE, j * CELL_SIZE, block, renderer, &shadow_sells[i][j].color);
			}
		}
}
SDL_Texture* Text_Texture(const char* Text, SDL_Renderer* renderer, SDL_Color Color) {

	TTF_Init();

		TTF_Font* Sans = nullptr;
		Sans = TTF_OpenFont("C:\\Users\\User\\source\\repos\\SDLtest2\\Debug\\Pixelnaya_Zalupa.ttf", 24);

		SDL_Surface* message_surface = nullptr;
		SDL_Texture* message = nullptr;

		if (Sans != nullptr) {

			cout << "surf";
			message_surface = TTF_RenderText_Blended(Sans, Text, Color);
		}

		if (message_surface != nullptr)
		{
			cout << "texture";
			message = SDL_CreateTextureFromSurface(renderer, message_surface);
			SDL_FreeSurface(message_surface);
		}
		TTF_CloseFont(Sans);

		TTF_Quit();

		return message;		
}