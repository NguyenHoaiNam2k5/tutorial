#pragma once

#include "const.h"
#include "texture.h"

class threatsObject
{
public:
    const float ENEMY_WIDTH = 32;
    const float ENEMY_HEIGHT = 32;

    const float ENEMY_VEL = 0.2;

    threatsObject();
    ~threatsObject();

    void set_x_pos(const float& xp){mBox.x = xp;}
    void set_y_pos(const float& yp){mBox.y = yp;}
    void set_is_move(const bool& isMove){is_move_ = isMove;}
    bool get_is_move() const{return is_move_;}
    void render(SDL_Renderer* gRenderer, Ltexture& gEnemy, SDL_FRect camera);
    void move(const double& posX, const double& posY);

    SDL_FRect getBox()const{return mBox;}

    void Free(Ltexture& gEnemy);


private:

    SDL_FRect mBox;

    bool is_move_;
};
