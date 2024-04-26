#include "const.h"
#include "texture.h"
#include "weapon.h"

weapon::weapon()
{
    mBox.x = 0;
    mBox.y = 0;
    mBox.h = WEAPON_HEIGHT;
    mBox.w = WEAPON_WIDTH;
    mouse.x = 0;
    mouse.y = 0;
    angle = 0;
}

void weapon::handleEvent(SDL_Event& e)
{

    SDL_GetMouseState(&mouse.x, &mouse.y);
}



void weapon::render(SDL_Renderer* gRenderer, Ltexture& gWeapon)
{
    double dx = mouse.x - mBox.x - WEAPON_WIDTH/2;
    double dy = mouse.y - mBox.y - WEAPON_HEIGHT /2;

    //tinh goc va chuyen sang do
    angle = atan(dy / dx);
    double angle_degrees = angle * 180 / M_PI;

    // Kiểm tra nếu chuột nằm ở bên trái hay bên phải của vũ khí
    if(dx > 0) {
        gWeapon.render(mBox.x, mBox.y, gRenderer, NULL, angle_degrees);
    }
    else {
        gWeapon.render(mBox.x, mBox.y, gRenderer, NULL, angle_degrees, NULL, SDL_FLIP_HORIZONTAL);

    }

}

