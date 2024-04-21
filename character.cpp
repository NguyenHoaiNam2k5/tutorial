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

void Tile::render(SDL_FRect camera, Ltexture& gTileTexture, SDL_Rect gTileClips[], SDL_Renderer* gRenderer)
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

SDL_FRect Tile::getBox()
{
    return mBox;
}


Character::Character()
{
    // khoi tao toa do
    mBox.x = SCREEN_WIDTH / 2;
    mBox.y = SCREEN_HEIGHT / 2 ;

    //shoot
    shoot = 1;

    shooted_bullet = 0;

    //max bullet
    max_bullet = 11;

    StartTime = 0;

    is_level_up = 0;

    health = 3;

    //set collision box dimension
    mBox.w = CHARACTER_WIDTH;
    mBox.h = CHARACTER_HEIGHT;

    //khoi tao toc do
    mVelX = 0;
    mVelY = 0;

}

void Character::handleEvent(SDL_Event& e, SDL_Renderer* gRenderer, Ltexture& gWeapon, SDL_FRect camera)
{
    //if a key was pressed
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch(e.key.keysym.sym)
        {
            case SDLK_UP: case SDLK_w:
                mVelY -= CHARACTER_VEL;
                break;
            case SDLK_DOWN: case SDLK_s:
                mVelY += CHARACTER_VEL;
                break;
            case SDLK_LEFT: case SDLK_a:
                mVelX -= CHARACTER_VEL;
                break;
            case SDLK_RIGHT: case SDLK_d:
                mVelX += CHARACTER_VEL;
                break;
        }
//        //di chuyen cheo
//        if(mVelX != 0 && mVelY != 0)
//        {
//            mVelX /= sqrt(2);
//            mVelY /= sqrt(2);
//        }

    }
    //if key was released
     if(e.type == SDL_KEYUP && e.key.repeat == 0)
    {

//        if(mVelX != 0 && mVelY != 0)
//        {
//            mVelX *= sqrt(2);
//            mVelY *= sqrt(2);
//        }

        //dieu chinh toc do
        switch(e.key.keysym.sym)
        {
            case SDLK_UP: case SDLK_w:
                mVelY += CHARACTER_VEL;
                break;
            case SDLK_DOWN: case SDLK_s:
                mVelY -= CHARACTER_VEL;
                break;
            case SDLK_LEFT: case SDLK_a:
                mVelX += CHARACTER_VEL;
                break;
            case SDLK_RIGHT: case SDLK_d:
                mVelX -= CHARACTER_VEL;
                break;
        }
    }
     if(e.button.button == SDL_BUTTON_LEFT && e.type == SDL_MOUSEBUTTONDOWN && shoot)
    {
        bulletObject* p_bullet = new bulletObject();
//        p_bullet->render(gRenderer, gBullet);

        p_bullet->set_posX(mBox.x+CHARACTER_WIDTH/2);
        p_bullet->set_posY(mBox.y+CHARACTER_HEIGHT/2);
        p_bullet->set_is_move(1);
        p_bullet->setCamera(camera);
        p_bullet->setCamera(camera);
        p_bullet->set_mouseX_val();
        p_bullet->set_mouseY_val();
        shooted_bullet++;


        p_bullet_list_.push_back(p_bullet);
    }



    revolver.handleEvent(e);
}

void Character::handleLevelUp(SDL_Event& e, ImpTimer fps_timer)
{
//    gLevelUp.render(105,167, gRenderer);
//    SDL_RenderPresent(gRenderer);
    while(1)
    {
        if(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_KEYDOWN)
            {
                if(e.key.keysym.sym == SDLK_1)
            {
                    fps_timer.set_level_up();
                    is_level_up = 0;
                    break;
                }
                else if(e.key.keysym.sym == SDLK_2)
                {
                    max_bullet+=2;
                    is_level_up = 0;
                    break;
                }
                else if(e.key.keysym.sym == SDLK_3)
                {
                    health++;
                    is_level_up = 0;
                    break;
                }
            }
        }
    }
}

void Character::move(Tile *tiles[], SDL_FRect& camera)
{
    //move the character left or right
    mBox.x += mVelX;
//    mCollider.x = mPosX;

    //if the character went too far
    if((mBox.x < 0) || (mBox.x + CHARACTER_WIDTH > LEVEL_WIDTH) || touchesWall(mBox, tiles) )
    {
        //move back
        mBox.x -= mVelX;
    }

    //move the character up or down
    mBox.y += mVelY;

    //if the character went too far
    if((mBox.y < 0) || (mBox.y + CHARACTER_HEIGHT > LEVEL_HEIGHT) || touchesWall(mBox, tiles) )
    {
        //move back
        mBox.y -= mVelY;
    }
    revolver.set_x_val(mBox.x - camera.x );
    revolver.set_y_val(mBox.y - camera.y );
}
void Character::render(SDL_Renderer* gRenderer, SDL_FRect& camera, Ltexture Char[], SDL_Rect* currentClip, Ltexture& gWeapon, Ltexture& gBullet)
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    if( currentKeyStates[ SDL_SCANCODE_RIGHT ] || currentKeyStates[ SDL_SCANCODE_D ])
    {
        Char[0].render(mBox.x - camera.x, mBox.y - camera.y, gRenderer, currentClip);
    }
    else if( currentKeyStates[ SDL_SCANCODE_LEFT ] || currentKeyStates[ SDL_SCANCODE_A ])
    {
        Char[1].render(mBox.x - camera.x, mBox.y - camera.y, gRenderer, currentClip);
    }
    else if(currentKeyStates[ SDL_SCANCODE_UP ] || currentKeyStates[ SDL_SCANCODE_W ])
    {
        Char[0].render(mBox.x - camera.x, mBox.y - camera.y, gRenderer, currentClip);
    }
    else if(currentKeyStates[ SDL_SCANCODE_DOWN ] || currentKeyStates[ SDL_SCANCODE_S ])
    {
        Char[1].render(mBox.x - camera.x, mBox.y - camera.y, gRenderer, currentClip);
    }
    else
    {
        Char[2].render(mBox.x - camera.x, mBox.y - camera.y, gRenderer, currentClip);
    }
    revolver.render(gRenderer, gWeapon);
//    revolver.handleBullet(gRenderer, gBullet, camera);

}

void Character::setCamera(SDL_FRect& camera)
{
    //Center the camera over the dot
    camera.x = ( mBox.x + CHARACTER_WIDTH / 2) - SCREEN_WIDTH / 2;
    camera.y = ( mBox.y + CHARACTER_HEIGHT / 2) - SCREEN_HEIGHT / 2;

    //keep the camera in bounds
    if(camera.x < 0)
    {
        camera.x = 0;
    }
    if( camera.y < 0)
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

void Character::set_shoot(int startTime)
{
    if(shooted_bullet == max_bullet)
    {
        shoot = 0;
        shooted_bullet++;
        StartTime = startTime;
    }
    else if(SDL_GetTicks() - StartTime >= 5000 && shooted_bullet > max_bullet)
    {
        shooted_bullet = 0;
        shoot = 1;
    }
}

void Character::set_bullet()
{
    if(max_bullet - shooted_bullet <= 0) bullet_left = 0;
    else bullet_left = max_bullet - shooted_bullet;
}

void Character:: removeBullet(const int& idx)
{
    int size = p_bullet_list_.size();
    if(size > 0 && idx < size)
    {
        bulletObject* p_bullet = p_bullet_list_.at(idx);
        p_bullet_list_.erase(p_bullet_list_.begin() + idx);
        if(p_bullet)
        {
            delete p_bullet;
            p_bullet = NULL;
        }
    }
}

void Character::handleBullet(SDL_Renderer* gRenderer, Ltexture& gBullet, SDL_FRect camera)
{
    for(int i = 0; i <int(p_bullet_list_.size()); i++)
    {
        bulletObject* p_bullet = p_bullet_list_.at(i);
        if(p_bullet != NULL)
        {
            if(p_bullet->get_is_move() == 1)
            {
//                p_bullet->setCamera(camera);
//                p_bullet->set_mouseX_val();
//                p_bullet->set_mouseY_val();
                if(p_bullet->get_x_val() == 0 && p_bullet->get_y_val() == 0)
                {
                    p_bullet->set_x_val(mBox.x+CHARACTER_HEIGHT/2);
                    p_bullet->set_y_val(mBox.y+CHARACTER_WIDTH/2);
//                    p_bullet->set_posX(mBox.x+CHARACTER_HEIGHT/2);
//                    p_bullet->set_posY(mBox.y+CHARACTER_WIDTH/2);
                }
                p_bullet->render(gRenderer, gBullet, camera);
                p_bullet->Move(camera);
            }
            else
            {
                p_bullet_list_.erase(p_bullet_list_.begin()+i);
                if(p_bullet != NULL)
                {
                    delete p_bullet;
                    p_bullet = NULL;
                }
            }
        }
    }
}

bool touchesWall(SDL_FRect box, Tile* tiles[])
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
