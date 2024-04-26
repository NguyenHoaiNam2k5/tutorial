#pragma once
#include "texture.h"
#include "const.h"

class bulletObject
{
public:
    const float BULLET_WIDTH = 16;
    const float BULLET_HEIGHT = 16;

    const int BULLET_VEL = 4;

    bulletObject();
    ~bulletObject();

//    void set_x_val(const int& xVal){x_val_ = xVal;}
//    void set_y_val(const int& yVal){y_val_ = yVal;}
    float get_x_val() const {return Box.x;}
    float get_y_val() const {return Box.y;}

    void set_is_move(const bool& isMove){is_move_ = isMove;}
    bool get_is_move()const {return is_move_;}

//    void handleEvent(SDL_Event& e
    void set_x_val(const int& x){Box.x = x;}
    void set_y_val(const int& y){Box.y = y;}

    void set_posX(const int& x){posX = x;}
    void set_posY(const int& y){posY = y;}

    float get_posX() const {return posX;}
    float get_posY() const {return posY;}

    SDL_FRect get_box(){return Box;}

    void setCamera(SDL_FRect cameraRect){camera = cameraRect;}

    void set_mouseX_val(){mouseX+=camera.x;}
    void set_mouseY_val(){mouseY+=camera.y;}

    void render(SDL_Renderer* gRenderer, Ltexture& gBullet, SDL_FRect camera);

    void Move(SDL_FRect camera);
private:

    bool is_move_;

    SDL_FRect Box;

    SDL_FRect camera;

    float posX, posY;

    int mouseX, mouseY;
};
