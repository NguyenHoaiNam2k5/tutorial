#pragma once

#include "const.h"
#include "texture.h"

class threatsObject
{
public:
    const float ENEMY_WIDTH = 32;
    const float ENEMY_HEIGHT = 32;

    const float ENEMY_VEL = 0.1;

    threatsObject();
    ~threatsObject();

    void set_x_pos(const float& xp){mBox.x = xp;}
    void set_y_pos(const float& yp){mBox.y = yp;}
//    float get_x_pos()const {return mBox.x;}
//    float get_y_pos()const {return mBox.y;}
    void set_is_move(const bool& isMove){is_move_ = isMove;}
    bool get_is_move() const{return is_move_;}
    void render(SDL_Renderer* gRenderer, Ltexture& gEnemy, SDL_FRect camera);
    void move(const double& posX, const double& posY);

    SDL_FRect getBox()const{return mBox;}

    void Free(Ltexture& gEnemy);


private:
//    int height_frame_;
//    int width_frame_;
    SDL_FRect mBox;
//    float x_val_;
//    float y_val_;
    bool is_move_;
};
