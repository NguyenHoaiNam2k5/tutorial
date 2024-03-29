#include "const.h"
#include "texture.h"

class threatsObject
{
public:
    const int ENEMY_WIDTH = 32;
    const int ENEMY_HEIGHT = 32;

    const float ENEMY_VEL = 0.5;

    threatsObject();
    ~threatsObject();
//    void set_x_val(const float& xVal){x_val_ = xVal;}
//    void set_x_val(const float& yVal){y_val_ = yVal;}

    void set_x_pos(const float& xp){mBox.x = xp;}
    void set_y_pos(const float& yp){mBox.y = yp;}
    float get_x_pos()const {return mBox.x;}
    float get_y_pos()const {return mBox.y;}
    void set_is_move(const bool& isMove){is_move_ = isMove;}
    bool get_is_move() const{return is_move_;}
    void SetMapXY(const int&mp_x, const int&mp_y) {map_x_ = mp_x;map_y_ = mp_y;}
    void render(SDL_Renderer* gRenderer, Ltexture& gEnemy);
//    void DoPlayer();
//    void CheckToMap();
    void move(const double& posX, const double& posY);

    int get_height_frame()const {return mBox.h;}
    int get_width_frame()const {return mBox.w;}

    SDL_FRect getBox()const{return mBox;}

private:
//    int height_frame_;
//    int width_frame_;
    SDL_FRect mBox;
//    float x_val_;
//    float y_val_;
    int map_x_;
    int map_y_;
    bool is_move_;
};
