#include "texture.h"
#include "const.h"
#include "commonFunc.h"

//bool loadMedia(Ltexture gTexture, SDL_Renderer* gRenderer)
//{
//    //Loading success flag
//	bool success = true;
//
//    //open the font
////    gFont = TTF_OpenFont("lazy.ttf", 28);
////    if(gFont == NULL)
////    {
////        std::cout << "ko load duoc lazy font" << TTF_GetError();
////    }
////    else
////    {
////        //render text
////        SDL_Color textColor = {0, 0, 0};
////        if(!gTextTexture.loadFromRenderedText("the quick brown fox jumps over the lazy dog", textColor))
////        {
////            std::cout << "fail to render text texture";
////            success = 0;
////        }
////    }
//
//    //load prompt texture
//    if(!gTexture.loadFromFile("foo.png", gRenderer))
//    {
//        std::cout << "ko the tai texture" << SDL_GetError();
//        success = 0;
//    }
//
//    return success;
//}

void close(SDL_Window* gWindow, SDL_Renderer* gRenderer)
{
//	//Free loaded image
//	gTexture.free();

//	//free global font
//	TTF_CloseFont(gFont);
//	gFont = NULL;

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

//create window
//bool init(SDL_Renderer* gRenderer, SDL_Window* gWindow)
//{
//    bool success = 1;
//    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
//    {
//        success = 0;
//        std::cout << "ko the khoi tao SDL" << SDL_GetError() << std::endl;
//    }
//    else
//    {
//        gWindow = SDL_CreateWindow("texture tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//        if(gWindow == NULL)
//        {
//            std::cout << "ko the khoi tao cua so" << SDL_GetError() << std::endl;
//            success = 0;
//        }
//        else
//        {
//            //create renderer
//            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//            if(gRenderer == NULL)
//            {
//                std::cout << "ko the khoi tao renderer" << SDL_GetError() << std::endl;
//                success = 0;
//            }
//            else
//            {
//                //tao mau cho renderer
//                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
//                //khoi tao PNG loading
//                int imgFlags = IMG_INIT_PNG;
//                if(!(IMG_Init(imgFlags) & imgFlags))
//                {
//                    std::cout << "ko the khoi tao SDL_image" << IMG_GetError() << std::endl;
//                    success = 0;
//                }
//            }
//        }
//    }
//    return success;
//}

bool checkCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}


