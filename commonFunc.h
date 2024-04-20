#ifndef COMMON_FUNC_H
#define COMMON_FUNC_H

#include "texture.h"
#include "const.h"

//bool loadMedia(Ltexture gTexture, SDL_Renderer* gRenderer);

void close(SDL_Window* gWindow, SDL_Renderer* gRenderer, TTF_Font* gFont);

//bool init(SDL_Renderer* gRenderer, SDL_Window* gWindow);

//bool checkCollision( SDL_FRect a, SDL_FRect b );

bool checkCollision(const SDL_FRect& object1, const SDL_FRect& object2);
int checkCollision2(const SDL_FRect& object1, const SDL_FRect& object2);

//tim y khi biet x va duong thang di qua diem do
float timY(const float& x1, const float& y1, const int& x2, const int& y2, const float& x);

//tim x khi biet y va duong thang di qua diem do
float timX(const float& x1, const float& y1, const int& x2, const int& y2, const float& y);

#endif // COMMON_FUNC_H
