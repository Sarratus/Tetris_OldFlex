#include "Var.h"

int x_pos_of_figure = 150;
int y_pos_of_figure = 0;

int number_of_figure_next;
int figure_color_next;

bool pause = false;
bool process_pause = false;

long unsigned int points = 0, points_modifier = 1;

unsigned int SLEEPING_TIME = 1000;

SDL_Texture* block = nullptr, * block_color = nullptr, * block_dark = nullptr,* block_shadow;
SDL_Texture* background = nullptr, * background_color = nullptr, * background_dark = nullptr;

Shadow_Cell** shadow_sells = nullptr;

Figure figures[20];

SDL_Rect srcRED, srcYELL, srcBLUE, srcGREEN, srcMAGNT, srcCYAN;

mutex render;