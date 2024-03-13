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
