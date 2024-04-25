#pragma once

#include "const.h"
#include "texture.h"
#include "character.h"

//hien thi cua so
SDL_Window * gWindow = NULL;

//window renderer
SDL_Renderer * gRenderer = NULL;

//character
Ltexture Char[NUM_CHAR];
//weapon
Ltexture gWeapon;
//bullet
Ltexture gBullet;
//enemy
Ltexture gEnemy;
//start screen
Ltexture gStart;
//red frame
Ltexture gRed;
//explosion
Ltexture gExplosion;
//text
Ltexture gTimeTextTexture;
Ltexture gHealthTextTexture;
Ltexture gBulletTextTexture;

//level up
Ltexture gLevelUp;
Ltexture gLevel;
Ltexture gLevel1;
//defeat
Ltexture gDefeat;
//victory
Ltexture gWin;
//the music that will be played
Mix_Music* gMusic = NULL;

//the sound effect that will be used
Mix_Chunk* gShoot = NULL;
Mix_Chunk* gPlayerCol = NULL;
Mix_Chunk* gBulletCol = NULL;


//tile map
Ltexture gTileTexture;
SDL_Rect gTileClips[ TOTAL_TILE_SPRITES ];


//walking_frames
SDL_Rect Src[Walking_frames];
//explosion frames
SDL_Rect Exf[explosion_frames];
//font
TTF_Font* gFont;

bool loadMedia(Tile* tiles[])
{
    //Loading success flag
	bool success = true;
    if(!Char[0].loadFromFile("image/Rcharacter.png", gRenderer) || !Char[1].loadFromFile("image/Lcharacter.png", gRenderer) || !Char[2].loadFromFile("image/character.png", gRenderer))
    {
        std::cout << "ko tai duoc nhan vat" << SDL_GetError();
        success = 0;
    }
    else
    {
        Src[ 0 ].x =   0;
        Src[ 0 ].y =   0;
        Src[ 0 ].w =  32;
        Src[ 0 ].h =  32;

        Src[ 1 ].x =  32;
        Src[ 1 ].y =   0;
        Src[ 1 ].w =  32;
        Src[ 1 ].h =  32;

        Src[ 2 ].x =  64;
        Src[ 2 ].y =   0;
        Src[ 2 ].w =  32;
        Src[ 2 ].h =  32;
    }

    //load explosion texture
    if(!gExplosion.loadFromFile("image/explosion.png", gRenderer))
    {
        std::cout << "ko tai duoc explosion texture";
        success = 0;
    }
    else
    {
        for(int i = 0; i <= 96; i+= 32)
        {
            Exf[i].x = i;
            Exf[i].y = 0;
            Exf[i].w = 32;
            Exf[i].h = 32;
        }
    }

    //load tile texture
    if(!gTileTexture.loadFromFile("image/tileMap.png", gRenderer))
    {
        std::cout << "ko tai duoc tile set texture";
        success = 0;
    }

    //load tile map
    if(!setTiles(tiles, gTileClips))
    {
        std::cout << "ko tai duoc tile set";
        success = 0;
    }

    //load weapon
    if(!gWeapon.loadFromFile("image/Rweapon.png", gRenderer))
    {
        std::cout << "ko tai duoc weapon";
        success = 0;
    }
    if(!gBullet.loadFromFile("image/dot.png", gRenderer))
    {
        std::cout << "ko tai duoc bullet";
        success = 0;
    }
    if(!gEnemy.loadFromFile("image/enemies.png", gRenderer))
    {
        std::cout << "ko tai duoc enemy";
        success = 0;
    }
    if(!gStart.loadFromFile("image/start.png", gRenderer))
    {
        std::cout << "ko tai duoc start";
        success = 0;
    }
    if(!gRed.loadFromFile("image/redFrame.png", gRenderer))
    {
        std::cout << "ko tai duoc red frame";
        success = 0;
    }
    if(!gLevelUp.loadFromFile("image/levelUp.png", gRenderer))
    {
        std::cout << "ko tai duoc level up";
        success = 0;
    }
    if(!gLevel.loadFromFile("image/level_up.png", gRenderer))
    {
        std::cout << "ko tai duoc level up";
        success = 0;
    }
    if(!gLevel1.loadFromFile("image/level_up1.png", gRenderer))
    {
        std::cout << "ko tai duoc level up";
        success = 0;
    }
    if(!gDefeat.loadFromFile("image/defeat.png", gRenderer))
    {
        std::cout << "ko tai duoc defeat";
        success = 0;
    }
    if(!gWin.loadFromFile("image/win.png", gRenderer))
    {
        std::cout << "ko tai duoc win";
        success = 0;
    }
    //Open the font
    gFont = TTF_OpenFont( "image/text.ttf", 28 );
    if( gFont == NULL )
    {
        std::cout << "Failed to load lazy font! SDL_ttf Error: %s\n" << TTF_GetError() << std::endl ;
        success = false;
    }

    //load music
    gMusic = Mix_LoadMUS("image/beat.wav");
    if( gMusic == NULL )
    {
        std::cout << "failed to load music" << Mix_GetError() << std::endl ;
        success = false;
    }

    //load sound effects
    gShoot = Mix_LoadWAV("image/high.wav");
    if(gShoot == NULL)
    {
        std::cout << "failed to load shoot sound effect" << Mix_GetError() << std::endl;
        success = 0;
    }

    return success;
}

void Free()
{
    gTileTexture.free();
    gWeapon.free();
    gBullet.free();
    gRed.free();
    gExplosion.free();
    gTimeTextTexture.free();
    gHealthTextTexture.free();
    gLevelUp.free();
    gDefeat.free();
    Mix_FreeChunk(gShoot);
    Mix_FreeChunk(gPlayerCol);
    Mix_FreeChunk(gBulletCol);
    Mix_FreeMusic(gMusic);
    gMusic = NULL;
    gShoot = NULL;
    gPlayerCol = NULL;
    gBulletCol = NULL;
}
