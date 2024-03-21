#include "texture.h"
#include "const.h"
#include "commonFunc.h"
#include "character.h"


//hien thi cua so
SDL_Window * gWindow = NULL;

//window renderer
SDL_Renderer * gRenderer = NULL;

//character
Ltexture Char[NUM_CHAR];
//Ltexture gDotTexture;

//tile map
Ltexture gTileTexture;
SDL_Rect gTileClips[ TOTAL_TILE_SPRITES ];

//weapon
Ltexture gWeapon;

SDL_Rect Src[Walking_frames];



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
    return success;
}

bool init()
{
    bool success = 1;
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        success = 0;
        std::cout << "ko the khoi tao SDL" << SDL_GetError() << std::endl;
    }
    else
    {
        gWindow = SDL_CreateWindow("texture tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL)
        {
            std::cout << "ko the khoi tao cua so" << SDL_GetError() << std::endl;
            success = 0;
        }
        else
        {
            //create renderer
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(gRenderer == NULL)
            {
                std::cout << "ko the khoi tao renderer" << SDL_GetError() << std::endl;
                success = 0;
            }
            else
            {
                //tao mau cho renderer
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                //khoi tao PNG loading
                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags) & imgFlags))
                {
                    std::cout << "ko the khoi tao SDL_image" << IMG_GetError() << std::endl;
                    success = 0;
                }
            }
        }
    }
    return success;
}



int main(int argc, char* argv[])
{
    //Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
	    Tile* tileSet[TOTAL_TILES];
		//Load media
		if( !loadMedia(tileSet) )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			Character Char1;

            SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

			//current animation frame
			int frame = 0;

			//While application is running
			while( !quit )
			{

                //Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear( gRenderer );

                SDL_Rect* currentClip = &Src[ frame / 10 ];

				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					else
                    {
                        Char1.handleEvent(e, gRenderer, gWeapon);
                    }
                }
                //move character
                Char1.move(tileSet, camera);
                Char1.setCamera(camera);

                //render level
                for(int i = 0; i < TOTAL_TILES; i++)
                {
                    tileSet[i]->render(camera, gTileTexture, gTileClips, gRenderer);
                }

                Char1.render(gRenderer, camera, Char, currentClip, gWeapon);

                //update screen
				SDL_RenderPresent(gRenderer);

				//Go to next frame
				++frame;

				//cycle animation
				if(frame / 10 >= Walking_frames)
                {
                    frame = 0;
                }
			}
        }
        //Free resources and close SDL
        close(gWindow, gRenderer);
        gTileTexture.free();
        gWeapon.free();
        for(int i = 0; i < NUM_CHAR; i++)
        {
            Char[i].free();
        }
        for( int i = 0; i < TOTAL_TILES; ++i )
        {
            if( tileSet[ i ] != NULL )
            {
                delete tileSet[ i ];
                tileSet[ i ] = NULL;
            }
        }
	}
	return 0;
}

