#pragma once
#include "texture.h"
#include "const.h"

class bulletObject
{
public:
    const int BULLET_WIDTH = 5;
    const int BULLET_HEIGHT = 5;

    const int BULLET_VEL = 2;

    bulletObject();
    ~bulletObject();

//    void set_x_val(const int& xVal){x_val_ = xVal;}
//    void set_y_val(const int& yVal){y_val_ = yVal;}
    int get_x_val() const {return Box.x;}
    int get_y_val() const {return Box.y;}

    void set_is_move(const bool& isMove){is_move_ = isMove;}
    bool get_is_move()const {return is_move_;}

//    void handleEvent(SDL_Event& e
    void set_x_val(const int& x){Box.x = x;}
    void set_y_val(const int& y){Box.y = y;}

//    void set_mouseX_val(const int& x){mouseX = x;}
//    void set_mouseY_val(const int& y){mouseY = y;}

    void render(SDL_Renderer* gRenderer, Ltexture& gBullet, SDL_FRect camera);

    void Move( const double& posX, const double& posY);
private:
//    int x_val_;
//    int y_val_;
    bool is_move_;

    SDL_FRect Box;

    int mouseX, mouseY;
};
