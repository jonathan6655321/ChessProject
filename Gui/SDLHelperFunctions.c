#include "SDLHelperFunctions.h"

int PointInsideRectangle(int x, int y, int *Rectangle) {
    int minX = Rectangle[0], maxX = Rectangle[1], minY = Rectangle[2], maxY =
            Rectangle[3];
    if ((x >= minX && x <= maxX) && (y >= minY && y <= maxY)) {
        return 1;
    }
    return 0;
}

SDL_Rect CreateSDLRectFromIntArray(int *Rectangle) {
    SDL_Rect ret;
    ret.x = Rectangle[0];
    ret.y = Rectangle[2];
    ret.w = Rectangle[1] - Rectangle[0];
    ret.h = Rectangle[3] - Rectangle[2];
    return ret;
}

int EventIsExitEvent(SDL_Event *event) {
    if (event != NULL && event->type == SDL_WINDOWEVENT && event->window.event
                                                           == SDL_WINDOWEVENT_CLOSE) {
        return 1;
    }
    return 0;
}

int LoadSurface(SDL_Surface **surface, char *filePath) {
    *surface = SDL_LoadBMP(filePath);

    if (*surface == NULL) {
        printf("couldn't create %s surface\n", filePath);
        return 0;
    }
    SDL_PixelFormat *fmt = (*surface)->format;
    Uint32 transperantColorKey = SDL_MapRGB(fmt, 0xFF, 0, 0xFF);
    if (SDL_SetColorKey(*surface, SDL_TRUE, transperantColorKey)) {
        printf("couldn't create %s texture\n", filePath);
        return 0;
    }

    return 1;
}

