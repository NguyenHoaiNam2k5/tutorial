#include "texture.h"
#include "const.h"
#include "weapon.h"

weapon::weapon()
{
    mBox.x = 0;
    mBox.y = 0;
    mBox.h = WEAPON_HEIGHT;
    mBox.w = WEAPON_WIDTH;
}


void weapon::handleEvent(SDL_Event& e, SDL_Renderer* gRenderer, Ltexture& gWeapon)
{
    int x, y;
    if(e.type == SDL_MOUSEMOTION)
    {

        SDL_GetMouseState(&x, &y);
    }
    if(x < mBox.x+WEAPON_WIDTH/2)
    {
//        SDL_Point* center;
//        //đặt tâm quay
//        center->x = mBox.x+6;
//        center->y = mBox.y+12;
        double angle;
        angle = atan((y-mBox.y+12) / (mBox.x+6 - x));
        //Đổi sang độ
        angle = angle * M_PI / 180;
        gWeapon.render(mBox.x, mBox.y, gRenderer, NULL, angle);
    }
    else
    {
//        SDL_Point* center;
//        //đặt tâm quay
//        center->x = mBox.x+16;
//        center->y = mBox.y+12;
        double angle;
        angle = atan((mBox.y+12 - y) / (x - mBox.x+16));
        //Đổi sang độ
        angle = angle * M_PI / 180;
        gWeapon.render(mBox.x, mBox.y, gRenderer, NULL, angle, NULL, SDL_FLIP_VERTICAL);
    }
}
