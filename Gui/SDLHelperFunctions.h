#ifndef SDLHELPERFUNCTION_H_
#define SDLHELPERFUNCTION_H_
#include <SDL.h>
#include <stdio.h>

/*!
 * Given a x, y, and a rectangle[minX,maxX,minY,maxY]
 * @return
 *      is the x,y point inside the rectangle.
 */
int PointInsideRectangle(int, int, int[]);

/*!
 * Given a rectangle[minX,maxX,minY,maxY]
 * @return the rectangle converted to SDL_Rect[angle]
 */
SDL_Rect CreateSDLRectFromIntArray(int*);

/*!
 * given an SDL_Event
 * @return whether the event is an Exit event.
 */
int EventIsExitEvent(SDL_Event*);

/*!
 * Load texture into SDL_Texture pointer.
 * Also make (FF,00,FF) color transparent.
 * @return 1 on success, 0 on failure.
 */
int LoadTexture(SDL_Texture**, SDL_Renderer*, char*);

/*!
 * Load surface into SDL_Surface pointer.
 * Also make (FF,00,FF) color transparent.
 * @return 1 on success, 0 on failure.
 */
int LoadSurface(SDL_Surface**, char*);

#endif
