




//////////// ANIMATIONS //////////////////////////////////////////////////////

		//steps = 130;
		//	
		//
		//int del_x = ((dst.x + dst.w / 2) - (SCREEN_WIDTH / 2)) / steps;
		//int del_y = ((dst.y + dst.h / 2) - (SCREEN_HEIGHT / 2)) / steps;

		////cout << " " << dst.x << " " << SCREEN_WIDTH;
		//steps += 100;
		//
		//for (int i = 0; i < steps; i++)
		//{
		//	//cout << "step" << del_x;
		//	SDL_RenderClear(renderer);

		//	angle += rotation;
		//	rotation += 0.07;

		//	if (dst.x + dst.w / 2 != SCREEN_WIDTH / 2)
		//		--dst.x;
		//	if (dst.y + dst.h / 2 != SCREEN_HEIGHT / 2)
		//		++dst.y;

		//	SDL_RenderCopyEx(renderer, block, &srcBLUE, &dst, angle, NULL, SDL_FLIP_NONE);
		//
		//	SDL_RenderPresent(renderer);

		//	this_thread::sleep_for(chrono::milliseconds(time_pause));
		//}	

		//steps = 130;

		//for (int i = 0; i < steps; i++)
		//{
		//	SDL_RenderClear(renderer);

		//	if (angle >= 360)
		//		angle -= 360;
		//	
		//	angle += rotation;
		//	rotation += 0.09;

		//	----dst.y;
		//	++++++++dst.h;
		//	----dst.x;
		//	++++++++dst.w;
		//	
		//	SDL_RenderCopyEx(renderer, block, &srcBLUE, &dst, angle, NULL, SDL_FLIP_NONE);

		//	SDL_RenderPresent(renderer);

		//	this_thread::sleep_for(chrono::milliseconds(time_pause));
		//	if (time_pause  > 10)
		//		--time_pause;
		//}
		//
		//steps = 85;
		//opacity = 0;

		//SDL_Surface* Fog = NULL;
		//SDL_Texture* white_background = NULL;

		//Fog = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);

		//white_background = SDL_CreateTextureFromSurface(renderer, Fog);

		//SDL_SetTextureBlendMode(white_background, SDL_BLENDMODE_BLEND);

		//for (int i = 0; i < steps; i++)
		//{
		//	SDL_RenderClear(renderer);

		//	/*if (angle >= 360)
		//		angle -= 360;
		//	
		//	angle += rotation;
		//	rotation += 0.13;

		//	----dst.y;
		//	++++++++dst.h;
		//	----dst.x;
		//	++++++++dst.w;*/
		//				
		//	if (opacity < 255)
		//	SDL_SetTextureAlphaMod(white_background, ++++++opacity);
		//	//cout << opacity << " ";
		//	
		//	/*SDL_RenderCopyEx(renderer, block, &srcBLUE, &dst, angle, NULL, SDL_FLIP_NONE);*/
		//	SDL_RenderCopyEx(renderer, white_background, NULL, NULL, NULL, NULL, SDL_FLIP_NONE);

		//	SDL_RenderPresent(renderer);

		//	this_thread::sleep_for(chrono::milliseconds(time_pause));
		//}		

////////////// ANIMATIONS /////////////////////////////////////////////////////////////////////

////////////// OLD SPACE //////////////////////////////////////////////////////////////////////

/*

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
					*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////