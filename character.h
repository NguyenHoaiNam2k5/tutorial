#pragma once
#include "const.h"
#include "texture.h"
#include "weapon.h"
#include "imgTimer.h"


class Tile
{
public:
    //khoi tao position and type
    Tile(int x, int y, int tileType);

    //Show the tile
    void render( SDL_FRect camera, Ltexture& gTileTexture, SDL_Rect gTileClips[], SDL_Renderer* gRenderer);

    //get the tiletype
    int getType();

    //get the collision box;
    SDL_FRect getBox();

private:

    //the attributes of the tile
    SDL_FRect mBox;

    //the tile type;
    int mType;
};


class Character
{
public:


    //toc do toi da
    const float CHARACTER_VEL = 0.5;

    //ham khoi tao
    Character();

    //dat nhan vat ve trang thai ban dau
    void set_character();

    //takes key presses and adjusts the character's velocity
    void handleEvent(SDL_Event& e, SDL_Renderer* gRenderer, Ltexture& gWeapon, SDL_FRect camera, Mix_Chunk* gShoot);

    //move the character and checks collision
    void move(Tile *tiles[], SDL_FRect& camera);

    //camera
    void setCamera(SDL_FRect& camera);

    //Shows the character on the screen
    void render(SDL_Renderer* gRenderer, SDL_FRect& camera, Ltexture Char[], SDL_Rect* currentClip, Ltexture& gWeapon, Ltexture& gBullet);

    float get_x_pos()const {return mBox.x;}
    float get_y_pos()const {return mBox.y;}

    float get_vel_x(){return mVelX;}
    float get_vel_y(){return mVelY;}

    void set_x_pos(float x){mBox.x = x;}
    void set_y_pos(float y){mBox.y = y;}
    void set_x_vel(float x){mVelX = x;}
    void set_y_vel(float y){mVelY = y;}

    SDL_FRect get_rect() const {return mBox;}

    void set_shoot();
    void set_bullet();
    int get_bullet_left(){return bullet_left;}
    void set_level_up(bool lv){is_level_up = lv;}
    bool get_level_up(){return is_level_up;}
    int get_health(){return health;}
    void set_health(int hp){health = hp;}
    void handleLevelUp(SDL_Event e, ImpTimer& fps_timer);

//    std::vector<bulletObject*> get_bullet_list()const{return revolver.get_bullet_list();}
    void set_bullet_list(std::vector<bulletObject*> bullet_list)
    {
        p_bullet_list_ = bullet_list;
    }

    void removeBullet(const int& idx);

    void set_undead_time(int t){undeadTime = t;}
    int get_undead_time(){return undeadTime;}

    std::vector<bulletObject*> get_bullet_list()const{return p_bullet_list_;}
    void handleBullet(SDL_Renderer* gRenderer, Ltexture& gBullet, SDL_FRect camera);

private:
    std::vector <bulletObject*> p_bullet_list_;
    //weapon
    weapon revolver;

    //shoot
    bool shoot;
    //max bullet
    int max_bullet;
    //so dan da ban
    int shooted_bullet;
    //so dan con lai
    int bullet_left;
    //level up
    bool is_level_up;
    //chi so sinh menh
    int health;

    int StartTime;

    int undeadTime;

    //collision box of the character
    SDL_FRect mBox;

    //toc do nhan vat
    float mVelX, mVelY;

//    //Character's collision box
//    SDL_Rect mCollider;
};

bool touchesWall(SDL_FRect box, Tile* tiles[]);

//bool touchesTree(SDL_Rect, Tile* tiles[]);

bool setTiles( Tile* tiles[], SDL_Rect gTileClips[] );
