#ifndef COMMON_FUNC_H
#define COMMON_FUNC_H

#include "texture.h"
#include "const.h"

//bool loadMedia(Ltexture gTexture, SDL_Renderer* gRenderer);

void close(SDL_Window* gWindow, SDL_Renderer* gRenderer);

//bool init(SDL_Renderer* gRenderer, SDL_Window* gWindow);

bool checkCollision( SDL_Rect a, SDL_Rect b );

//ttim y khi biet x va duong thang di qua diem do
double timY(const int& x1, const int& y1, const int& x2, const int& y2, const int& x);

#endif // COMMON_FUNC_H
