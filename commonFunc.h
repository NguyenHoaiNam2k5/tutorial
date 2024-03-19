#ifndef COMMON_FUNC_H
#define COMMON_FUNC_H

#include "texture.h"
#include "const.h"

//bool loadMedia(Ltexture gTexture, SDL_Renderer* gRenderer);

void close(SDL_Window* gWindow, SDL_Renderer* gRenderer);

//bool init(SDL_Renderer* gRenderer, SDL_Window* gWindow);

bool checkCollision( SDL_Rect a, SDL_Rect b );



#endif // COMMON_FUNC_H
