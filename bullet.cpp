#include "const.h"
#include "texture.h"
#include "bullet.h"
#include "commonFunc.h"

bulletObject::bulletObject()
{
    Box.x = 0;
    Box.y = 0;
    Box.h = BULLET_HEIGHT;
    Box.w = BULLET_WIDTH;
    is_move_ = 0;
//    x_val_ = 0;
//    y_val_ = 0;
}

bulletObject::~bulletObject()
{

}


void bulletObject::Move( const int& posX, const int& posY)
{
    if(posX == mouseX)
    {
        if(mouseY > posY)
            Box.y+=BULLET_VEL;
        else
            Box.y-=BULLET_VEL;
    }
    else
    {
        if(mouseX > posX){
            Box.x += BULLET_VEL;
        }
        else{
            Box.x -= BULLET_VEL;
        }
        Box.y = timY(posX, posY, mouseX, mouseY, Box.x);
    }
    if(Box.x > SCREEN_WIDTH || Box.y > SCREEN_HEIGHT) is_move_ = 0;

}

void bulletObject::render(SDL_Renderer* gRenderer, Ltexture& gBullet)
{
    gBullet.render(Box.x, Box.y, gRenderer);
}
