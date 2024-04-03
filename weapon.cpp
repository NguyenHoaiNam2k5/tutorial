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
    if(e.button.button == SDL_BUTTON_LEFT && e.type == SDL_MOUSEBUTTONDOWN)
    {
        bulletObject* p_bullet = new bulletObject();
//        p_bullet->render(gRenderer, gBullet);

        p_bullet->set_x_val(mBox.x+CHARACTER_WIDTH/2);
        p_bullet->set_y_val(mBox.y+CHARACTER_HEIGHT/2);
        p_bullet->set_is_move(1);

        p_bullet_list_.push_back(p_bullet);
    }
}

void weapon :: removeBullet(const int& idx)
{
    int size = p_bullet_list_.size();
    if(size > 0 && idx < size)
    {
        bulletObject* p_bullet = p_bullet_list_.at(idx);
        p_bullet_list_.erase(p_bullet_list_.begin() + idx);
        if(p_bullet)
        {
            delete p_bullet;
            p_bullet = NULL;
        }
    }
}

void weapon::handleBullet(SDL_Renderer* gRenderer, Ltexture& gBullet, SDL_FRect camera)
{
    for(int i = 0; i <int(p_bullet_list_.size()); i++)
    {
        bulletObject* p_bullet = p_bullet_list_.at(i);
        if(p_bullet != NULL)
        {
            if(p_bullet->get_is_move() == 1)
            {
                if(p_bullet->get_posX() == 0 && p_bullet->get_posY() == 0)
                {
                    p_bullet->set_posX(mBox.x+CHARACTER_WIDTH/2);
                    p_bullet->set_posY(mBox.y+CHARACTER_HEIGHT/2);
                }
                p_bullet->Move();
                p_bullet->render(gRenderer, gBullet, camera);
            }
            else
            {
                p_bullet_list_.erase(p_bullet_list_.begin()+i);
                if(p_bullet != NULL)
                {
                    delete p_bullet;
                    p_bullet = NULL;
                }
            }
        }
    }
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

