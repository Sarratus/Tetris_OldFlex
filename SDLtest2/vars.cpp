#include "Var.h"

int x_pos_of_figure = 150;
int y_pos_of_figure = 0;

bool pause = false;
bool process_pause = false;

SDL_Texture* block = nullptr, * block_color = nullptr, * block_dark = nullptr;
SDL_Texture* background = nullptr, * background_color = nullptr, * background_dark = nullptr;

Shadow_Cell** shadow_sells = nullptr;

Figure figures[20];

SDL_Rect srcRED, srcYELL, srcBLUE, srcGREEN, srcMAGNT, srcCYAN;

mutex render;