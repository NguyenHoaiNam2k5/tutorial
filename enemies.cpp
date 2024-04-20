#include "enemies.h"
#include "const.h"
#include "texture.h"
#include "commonFunc.h"

threatsObject::threatsObject()
{
    mBox.x = 0;
    mBox.y = 0;
    mBox.h = ENEMY_HEIGHT;
    mBox.w = ENEMY_WIDTH;
    is_move_ = 0;
}

threatsObject::~threatsObject()
{

}

void threatsObject::render(SDL_Renderer* gRenderer, Ltexture& gEnemy, SDL_FRect camera)
{
    gEnemy.render(mBox.x -camera.x, mBox.y-camera.y, gRenderer);
}

void threatsObject::Free(Ltexture& gEnemy)
{
    gEnemy.free();
}

void threatsObject::move(const double& posX, const double& posY)
{
//    mBox.x += ENEMY_VEL;

    double preX = mBox.x;
    double preY = mBox.y;
    if(posX == mBox.x)
    {
        if(posY > mBox.y)
            mBox.y+=ENEMY_VEL;
        else
            mBox.y-=ENEMY_VEL;
    }
    else if(posY == mBox.y)
    {
        if(posX > mBox.x)
            mBox.x+=ENEMY_VEL;
        else
            mBox.x-=ENEMY_VEL;
    }
    else if(abs(posX - mBox.x) > abs(posY - mBox.y))
    {
        if(mBox.x < posX){
            mBox.x += ENEMY_VEL;
        }
        else{
            mBox.x -= ENEMY_VEL;
        }
        mBox.y = timY(preX, preY, posX, posY, mBox.x);
    }
    else
    {
        if(mBox.y < posY){
            mBox.y += ENEMY_VEL;
        }
        else{
            mBox.y -= ENEMY_VEL;
        }
        mBox.x = timX(preX, preY, posX, posY, mBox.y);
    }
}
