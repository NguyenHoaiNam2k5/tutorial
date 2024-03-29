#ifndef COMMON_FUNC_H
#define COMMON_FUNC_H

#include "texture.h"
#include "const.h"

//bool loadMedia(Ltexture gTexture, SDL_Renderer* gRenderer);

void close(SDL_Window* gWindow, SDL_Renderer* gRenderer);

//bool init(SDL_Renderer* gRenderer, SDL_Window* gWindow);

bool checkCollision( SDL_FRect a, SDL_FRect b );

//tim y khi biet x va duong thang di qua diem do
double timY(const double& x1, const double& y1, const int& x2, const int& y2, const double& x);

//tim x khi biet y va duong thang di qua diem do
double timX(const double& x1, const double& y1, const int& x2, const int& y2, const double& y);

#endif // COMMON_FUNC_H
