int PointInsideRentangle(int x, int y. int[] rentangle){
	int minX =  rentangle[0], maxX = rentangle[1], minY = rentangle[2], maxY = rentangle[3];
	if ((x >= minX && x <= maxX) && (y >= minY && y <= maxY)) {
		return 1;
	}
	return 0;
}

SDL_Rect CreateSDLRectFromIntArray(int[] rentangle){
	SDL_Rect ret = { .x = rentangle[0], .y = rentangle[2], .h = rentangle[1]-rentangle[0], .w = rentangle[3]-rentangle[2] };
	return ret;
}

int EventIsExitEvent(SDL_Event event){
	if(event != NULL && event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_CLOSE){
		return 1;
	}
	return 0;
}

int LoadTexture(**SDL_Texture texture,  SDL_Renderer* renderer, char* filePath){
	SDL_Surface* loadingSurface = SDL_LoadBMP(filePath);
	*texture = NULL;
	
	if (loadingSurface == NULL ) {
		printf("couldn't create %s surface\n", filePath);
		return 0;
	}
	
	*texture = SDL_CreateTextureFromSurface(renderer,
			loadingSurface);
	
	SDL_FreeSurface(loadingSurface);
	
	if (*texture == NULL ) {
		printf("couldn't create %s texture\n", filePath);
		return 0;
	}
	return 1;
}

