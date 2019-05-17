#include "Var.h"

int x_pos_of_figure = 150;
int y_pos_of_figure = 0;

int figure_color_next = 0;
int figure_color_prev = 0;

bool pause = false;
bool process_pause = false;

SDL_Texture* block = nullptr;

Shadow_Cell** shadow_sells = nullptr;

Figure figures[20];

SDL_Rect srcRED, srcYELL, srcBLUE, srcGREEN, srcMAGNT, srcCYAN;