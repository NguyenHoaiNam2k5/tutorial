#pragma once

#include "const.h"
#include "texture.h"

class weapon
{
public:
    int const WEAPON_WIDTH = 19;
    int const WEAPON_HEIGHT = 16;
    weapon();
    void handleEvent(SDL_Event& e);
    void render(SDL_Renderer* gRenderer, Ltexture& gWeapon);
    void set_x_val(const int& x){mBox.x = x;}
    void set_y_val(const int& y){mBox.y = y;}
private:
    SDL_Rect mBox;
    SDL_Point mouse;
    double angle;
};
