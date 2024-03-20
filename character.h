#pragma once
#include "const.h"
#include "texture.h"

class Tile
{
public:
    //khoi tao position and type
    Tile(int x, int y, int tileType);

    //Show the tile
    void render( SDL_Rect camera, Ltexture& gTileTexture, SDL_Rect gTileClips[], SDL_Renderer* gRenderer);

    //get the tiletype
    int getType();

    //get the collision box;
    SDL_Rect getBox();

private:
    //the attributes of the tile
    SDL_Rect mBox;

    //the tile type;
    int mType;
};


class Character
{
public:
    //kich thuoc nhan vat
    static const int CHARACTER_WIDTH = 16;
    static const int CHARACTER_HEIGHT = 26;

    //toc do toi da
    static const int CHARACTER_VEL = 1;

    //ham khoi tao
    Character();

    //takes key presses and adjusts the character's velocity
    void handleEvent(SDL_Event& e);

    //move the character and checks collision
    void move(Tile *tiles[]);

    //camera
    void setCamera(SDL_Rect& camera);

    //Shows the character on the screen
    void render(SDL_Renderer* gRenderer, SDL_Rect& camera, Ltexture Char[], SDL_Rect* currentClip);



private:
    //collision box of the character
    SDL_Rect mBox;

    //toc do nhan vat
    int mVelX, mVelY;

//    //Character's collision box
//    SDL_Rect mCollider;
};

bool touchesWall(SDL_Rect box, Tile* tiles[]);

bool touchesTree(SDL_Rect, Tile* tiles[]);

bool setTiles( Tile* tiles[], SDL_Rect gTileClips[] );
