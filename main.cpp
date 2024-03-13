#include "texture.h"
#include "const.h"
#include "commonFunc.h"

//hien thi cua so
SDL_Window * gWindow = NULL;

//window renderer
SDL_Renderer * gRenderer = NULL;
//background
Ltexture gTexture;
//character right
Ltexture Rcharacter;
//character left
Ltexture Lcharacter;
//character
Ltexture character;

SDL_Rect Src[Walking_frames];

//create window
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

                //khoi tao SDL_mixer
//                if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
//                {
//                    std::cout << "SDL_mixer ko the khoi tao" << Mix_GetError();
//                    success = 0;
//                }
//
//                //khoi tao SDL_ttf
//                if(TTF_Init() == -1)
//                {
//                    std::cout << "SDL_ttf ko the khoi tao" << TTF_GetError();
//                    success = 0;
//                }
            }
        }
    }
    return success;
}

bool loadMedia()
{
    //Loading success flag
	bool success = true;

    //open the font
//    gFont = TTF_OpenFont("lazy.ttf", 28);
//    if(gFont == NULL)
//    {
//        std::cout << "ko load duoc lazy font" << TTF_GetError();
//    }
//    else
//    {
//        //render text
//        SDL_Color textColor = {0, 0, 0};
//        if(!gTextTexture.loadFromRenderedText("the quick brown fox jumps over the lazy dog", textColor))
//        {
//            std::cout << "fail to render text texture";
//            success = 0;
//        }
//    }

    //load prompt texture
    if(!gTexture.loadFromFile("image/foo.png", gRenderer))
    {
        std::cout << "ko the tai texture" << SDL_GetError();
        success = 0;
    }
    if(!Rcharacter.loadFromFile("image/Rcharacter.png", gRenderer) || !Lcharacter.loadFromFile("image/Lcharacter.png", gRenderer) || !character.loadFromFile("image/character.png", gRenderer))
    {
        std::cout << "ko tai duoc nhan vat" << SDL_GetError();
        success = 0;
    }
    else
    {
        Src[ 0 ].x =   0;
        Src[ 0 ].y =   0;
        Src[ 0 ].w =  64;
        Src[ 0 ].h =  64;

        Src[ 1 ].x =  64;
        Src[ 1 ].y =   0;
        Src[ 1 ].w =  64;
        Src[ 1 ].h =  64;

        Src[ 2 ].x =  128;
        Src[ 2 ].y =   0;
        Src[ 2 ].w =  64;
        Src[ 2 ].h =  64;
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
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//current animation frame
			int frame = 0;

			//While application is running
			while( !quit )
			{

                //Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear( gRenderer );

				//render background

                SDL_Rect* currentClip = &Src[ frame / 10 ];

				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

                }

                const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
				if( currentKeyStates[ SDL_SCANCODE_UP ] || currentKeyStates[ SDL_SCANCODE_RIGHT ])
				{
					Rcharacter.render(( SCREEN_WIDTH - currentClip->w ) / 2, ( SCREEN_HEIGHT - currentClip->h ) / 2, gRenderer, currentClip);
				}
				else if( currentKeyStates[ SDL_SCANCODE_DOWN ] || currentKeyStates[ SDL_SCANCODE_LEFT ] )
				{
					Lcharacter.render(( SCREEN_WIDTH - currentClip->w ) / 2, ( SCREEN_HEIGHT - currentClip->h ) / 2, gRenderer, currentClip);
				}
				else
				{
					character.render(( SCREEN_WIDTH - currentClip->w ) / 2, ( SCREEN_HEIGHT - currentClip->h ) / 2, gRenderer, currentClip);
				}

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
	}

	//Free resources and close SDL
	close(gWindow, gRenderer);
    gTexture.free();
    Rcharacter.free();
    Lcharacter.free();
    character.free();
	return 0;
}

