#include "const.h"
#include "character.h"
#include "texture.h"
#include "commonFunc.h"


Tile::Tile(int x, int y, int tileType)
{

    //get the offsets
    mBox.x = x;
    mBox.y = y;

    //set the collision box
    mBox.w = TILE_WIDTH;
    mBox.h = TILE_HEIGHT;

    // get the tile type
    mType = tileType;

}

void Tile::render(SDL_Rect camera, Ltexture& gTileTexture, SDL_Rect gTileClips[], SDL_Renderer* gRenderer)
{

    //if the tile is on screen
    if(checkCollision(camera, mBox))
    {

        //show the  tile
        gTileTexture. render(mBox.x - camera.x, mBox.y - camera.y, gRenderer, &gTileClips[mType]);
    }
}

int Tile::getType()
{
    return mType;
}

SDL_Rect Tile::getBox()
{
    return mBox;
}


Character::Character()
{
    // khoi tao toa do
    mBox.x = SCREEN_WIDTH / 2;
    mBox.y = SCREEN_HEIGHT / 2 ;

    //set collision box dimension
    mBox.w = CHARACTER_WIDTH;
    mBox.h = CHARACTER_HEIGHT;

    //khoi tao toc do
    mVelX = 0;
    mVelY = 0;

}

void Character::handleEvent(SDL_Event& e, SDL_Renderer* gRenderer, Ltexture& gWeapon)
{
    //if a key was pressed
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch(e.key.keysym.sym)
        {
            case SDLK_UP:
                mVelY -= CHARACTER_VEL;
                break;
            case SDLK_DOWN:
                mVelY += CHARACTER_VEL;
                break;
            case SDLK_LEFT:
                mVelX -= CHARACTER_VEL;
                break;
            case SDLK_RIGHT:
                mVelX += CHARACTER_VEL;
                break;
        }
    }
    //if key was released
     if(e.type == SDL_KEYUP && e.key.repeat == 0)
    {

        //dieu chinh toc do
        switch(e.key.keysym.sym)
        {
            case SDLK_UP: mVelY += CHARACTER_VEL; break;
            case SDLK_DOWN: mVelY -= CHARACTER_VEL; break;
            case SDLK_LEFT: mVelX += CHARACTER_VEL; break;
            case SDLK_RIGHT: mVelX -= CHARACTER_VEL; break;
        }
    }

    revolver.handleEvent(e);
}

void Character::move(Tile *tiles[], SDL_Rect& camera)
{
    //move the character left or right
    mBox.x += mVelX;
//    mCollider.x = mPosX;

    //if the dot went too far
    if((mBox.x < 0) || (mBox.x + CHARACTER_WIDTH > LEVEL_WIDTH) || touchesWall(mBox, tiles) )
    {
        //move back
        mBox.x -= mVelX;
    }

    //move the dot up or down
    mBox.y += mVelY;

    //if the dot went too far
    if((mBox.y < 0) || (mBox.y + CHARACTER_HEIGHT > LEVEL_HEIGHT) || touchesWall(mBox, tiles) )
    {
        //move back
        mBox.y -= mVelY;
    }
    revolver.set_x_val(mBox.x - camera.x - 1);
    revolver.set_y_val(mBox.y - camera.y );
}
void Character::render(SDL_Renderer* gRenderer, SDL_Rect& camera, Ltexture Char[], SDL_Rect* currentClip, Ltexture& gWeapon, Ltexture& gBullet)
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    if( currentKeyStates[ SDL_SCANCODE_UP ] || currentKeyStates[ SDL_SCANCODE_RIGHT ])
    {
        Char[0].render(mBox.x - camera.x, mBox.y - camera.y, gRenderer, currentClip);
    }
    else if( currentKeyStates[ SDL_SCANCODE_DOWN ] || currentKeyStates[ SDL_SCANCODE_LEFT ] )
    {
        Char[1].render(mBox.x - camera.x, mBox.y - camera.y, gRenderer, currentClip);
    }
    else
    {
        Char[2].render(mBox.x - camera.x, mBox.y - camera.y, gRenderer, currentClip);
    }
    revolver.render(gRenderer, gWeapon);
    revolver.handleBullet(gRenderer, gBullet);
}

void Character::setCamera(SDL_Rect& camera)
{
    //Center the camera over the dot
    camera.x = ( mBox.x + CHARACTER_WIDTH / 2) - SCREEN_WIDTH / 2;
    camera.y = ( mBox.y + CHARACTER_HEIGHT / 2) - SCREEN_HEIGHT / 2;

    //keep the camera in bounds
    if(camera.x < 0)
    {
        camera.x = 0;
    }
    if( camera.y < 0 )
    {
        camera.y = 0;
    }
    if( camera.x > LEVEL_WIDTH - camera.w )
    {
        camera.x = LEVEL_WIDTH - camera.w;
    }
    if( camera.y > LEVEL_HEIGHT - camera.h )
    {
        camera.y = LEVEL_HEIGHT - camera.h;
    }
}

bool touchesWall(SDL_Rect box, Tile* tiles[])
{
    //duyet qua cac tiles
    for(int i = 0; i < TOTAL_TILES; i++)
    {
        //if the tile is a wall type tile
        if(tiles[i]->getType() == TILE_wall)
        {
            //if the collision box  touches the wall tile
            if(checkCollision(box, tiles[i]->getBox()))
            {
                return 1;
            }
        }
    }
    return 0;
}

//bool touchesTree(SDL_Rect box, Tile* tiles[])
//{
//    for(int i = 0; i < TOTAL_TILES; i++)
//    {
//        if(tiles[i]->getType() == TILE_tree1)
//        {
//            if(checkCollision(box, tiles[i]->getBox()))
//            {
//                return true;
//            }
//        }
//    }
//    return false;
//}


bool setTiles( Tile* tiles[], SDL_Rect gTileClips[] )
{
	//Success flag
	bool tilesLoaded = true;

    //The tile offsets
    int x = 0, y = 0;

    //Open the map
    std::ifstream map( "image/lazy.map" );

    //If the map couldn't be loaded
    if( map.fail() )
    {
		printf( "Unable to load map file!\n" );
		tilesLoaded = false;
    }
	else
	{
		//Initialize the tiles
		for( int i = 0; i < TOTAL_TILES; ++i )
		{
			//Determines what kind of tile will be made
			int tileType = -1;

			//Read tile from map file
			map >> tileType;

			//If the was a problem in reading the map
			if( map.fail() )
			{
				//Stop loading map
				printf( "Error loading map: Unexpected end of file!\n" );
				tilesLoaded = false;
				break;
			}

			//If the number is a valid tile number
			if( ( tileType >= 0 ) && ( tileType < TOTAL_TILE_SPRITES ) )
			{
				tiles[ i ] = new Tile( x, y, tileType );
			}
			//If we don't recognize the tile type
			else
			{
				//Stop loading map
				printf( "Error loading map: Invalid tile type at %d!\n", i );
				tilesLoaded = false;
				break;
			}

			//Move to next tile spot
			x += TILE_WIDTH;

			//If we've gone too far
			if( x >= LEVEL_WIDTH )
			{
				//Move back
				x = 0;

				//Move to the next row
				y += TILE_HEIGHT;
			}
		}

		//Clip the sprite sheet
		if( tilesLoaded )
		{
			gTileClips[ TILE_background ].x = 0;
			gTileClips[ TILE_background ].y = 0;
			gTileClips[ TILE_background ].w = TILE_WIDTH;
			gTileClips[ TILE_background ].h = TILE_HEIGHT;

			gTileClips[ TILE_wall ].x = 0;
			gTileClips[ TILE_wall ].y = 32;
			gTileClips[ TILE_wall ].w = TILE_WIDTH;
			gTileClips[ TILE_wall ].h = TILE_HEIGHT;
//
//			gTileClips[ TILE_tree1 ].x = 32;
//			gTileClips[ TILE_tree1 ].y = 32;
//			gTileClips[ TILE_tree1 ].w = TILE_WIDTH;
//			gTileClips[ TILE_tree1 ].h = TILE_HEIGHT;
//
//			gTileClips[ TILE_tree2 ].x = 32;
//			gTileClips[ TILE_tree2 ].y = 0;
//			gTileClips[ TILE_tree2 ].w = TILE_WIDTH;
//			gTileClips[ TILE_tree2 ].h = TILE_HEIGHT;

		}
	}

    //Close the file
    map.close();

    //If the map was loaded fine
    return tilesLoaded;
}
