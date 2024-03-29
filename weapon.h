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

    void set_bullet_list(std::vector<bulletObject*> bullet_list)
    {
        p_bullet_list_ = bullet_list;
    }

    std::vector<bulletObject*> get_bullet_list()const{return p_bullet_list_;}
    void handleBullet(SDL_Renderer* gRenderer, Ltexture& gBullet);
private:
    std::vector <bulletObject*> p_bullet_list_;
    SDL_FRect mBox;
    SDL_Point mouse;
    double angle;
};
