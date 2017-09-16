#ifndef SDLHELPERFUNCTION_H_
#define SDLHELPERFUNCTION_H_
#include <SDL.h>

int PointInsideRentangle(int x, int y. int[] rentangle);

SDL_Rect CreateSDLRectFromIntArray(int[] rentangle);

int EventIsExitEvent(SDL_Event event);

int LoadTexture(**SDL_Texture texture,  SDL_Renderer* renderer, char* filePath);

#endif
