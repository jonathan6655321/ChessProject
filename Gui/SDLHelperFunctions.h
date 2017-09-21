#ifndef SDLHELPERFUNCTION_H_
#define SDLHELPERFUNCTION_H_
#include <SDL.h>

int PointInsideRectangle(int, int, int*);

SDL_Rect CreateSDLRectFromIntArray(int*);

int EventIsExitEvent(SDL_Event*);

int LoadTexture(SDL_Texture**,  SDL_Renderer*, char*);

#endif
