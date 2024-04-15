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
    SDL_GetMouseState(&mouseX, &mouseY);
//    mouseX+=camera.x;
//    mouseY+=camera.y;
//    camera.x = 0;
//    camera.y = 0;
//    camera.h = 0;
//    camera.w = 0;
//    mouseX-=camera.x;
//    mouseY-=camera.y;
    posX = 0;
    posY = 0;
}

bulletObject::~bulletObject()
{

}


void bulletObject::Move(SDL_FRect camera)
{

    std::cout << mouseX << " " << mouseY << std::endl;
    if(posX == float(mouseX))
    {
        if(mouseY > posY)
            Box.y+=BULLET_VEL;
        else
            Box.y-=BULLET_VEL;
    }
    if(posY == float(mouseY))
    {
        if(mouseX > posX)
            Box.x+=BULLET_VEL;
        else
            Box.x-=BULLET_VEL;
    }
    else if(abs(posX - mouseX) > abs(posY - mouseY))
    {
        if(mouseX > posX){
            Box.x += BULLET_VEL;
        }
        else{
            Box.x -= BULLET_VEL;
        }
        Box.y = timY(posX, posY, mouseX, mouseY, Box.x);
    }
    else
    {
        if(mouseY > posY){
            Box.y += BULLET_VEL;
        }
        else{
            Box.y -= BULLET_VEL;
        }
        Box.x = timX(posX, posY, mouseX, mouseY, Box.y);
    }
    if(Box.x > LEVEL_WIDTH || Box.y > LEVEL_HEIGHT || Box.x < 0 || Box.y < 0) is_move_ = 0;
//    Box.x -= BULLET_VEL;
//    Box.y -= BULLET_VEL;
//    Box.x -= BULLET_VEL;
}

void bulletObject::render(SDL_Renderer* gRenderer, Ltexture& gBullet, SDL_FRect camera)
{
    gBullet.render(Box.x - camera.x, Box.y - camera.y, gRenderer);
//    gBullet.render(Box.x, Box.y, gRenderer);
}
