#include "texture.h"
#include "const.h"
#include "commonFunc.h"



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


bool checkCollision( SDL_FRect a, SDL_FRect b )
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

double timY(const double& x1, const double& y1, const int& x2, const int& y2, const int& x)
{
    double y;
    double a=(y1-y2)/(x1-x2)*1.0;
    double b = y1 - a*x1;
    y = a*x+b;
    return y;
}


