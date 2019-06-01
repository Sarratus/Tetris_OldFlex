




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