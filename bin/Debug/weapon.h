#pragma once

#include "const.h"
#include "texture.h"
#include "bullet.h"

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
    int get_mouseX(){return mouse.x;}
    int get_mouseY(){return mouse.y;}

private:

    SDL_FRect mBox;
    SDL_Point mouse;
    double angle;
};
