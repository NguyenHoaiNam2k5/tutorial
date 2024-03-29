#pragma once
#include "const.h"
#include "texture.h"
#include "weapon.h"


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
    static const int CHARACTER_VEL = 1;

    //ham khoi tao
    Character();

    //takes key presses and adjusts the character's velocity
    void handleEvent(SDL_Event& e, SDL_Renderer* gRenderer, Ltexture& gWeapon);

    //move the character and checks collision
    void move(Tile *tiles[], SDL_FRect& camera);

    //camera
    void setCamera(SDL_FRect& camera);

    //Shows the character on the screen
    void render(SDL_Renderer* gRenderer, SDL_FRect& camera, Ltexture Char[], SDL_Rect* currentClip, Ltexture& gWeapon, Ltexture& gBullet);

//    void setWeapon();

private:
    //weapon
    weapon revolver;

    //collision box of the character
    SDL_FRect mBox;

    //toc do nhan vat
    double mVelX, mVelY;

//    //Character's collision box
//    SDL_Rect mCollider;
};

bool touchesWall(SDL_FRect box, Tile* tiles[]);

//bool touchesTree(SDL_Rect, Tile* tiles[]);

bool setTiles( Tile* tiles[], SDL_Rect gTileClips[] );
