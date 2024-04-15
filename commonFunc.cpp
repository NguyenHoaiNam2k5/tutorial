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


//bool checkCollision( SDL_FRect a, SDL_FRect b )
//{
//    //The sides of the rectangles
//    float leftA, leftB;
//    float rightA, rightB;
//    float topA, topB;
//    float bottomA, bottomB;
//
//    //Calculate the sides of rect A
//    leftA = a.x;
//    rightA = a.x + a.w;
//    topA = a.y;
//    bottomA = a.y + a.h;
//
//    //Calculate the sides of rect B
//    leftB = b.x;
//    rightB = b.x + b.w;
//    topB = b.y;
//    bottomB = b.y + b.h;
//
//    //If any of the sides from A are outside of B
//    if( bottomA <= topB )
//    {
//        return false;
//    }
//
//    if( topA >= bottomB )
//    {
//        return false;
//    }
//
//    if( rightA <= leftB )
//    {
//
//        return false;
//    }
//
//    if( leftA >= rightB )
//    {
//        return false;
//    }
//
//    //If none of the sides from A are outside B
//    return true;
//}

float timY(const float& x1, const float& y1, const int& x2, const int& y2, const float& x)
{
    float y;
    float a=(y1-y2)/(x1-x2)*1.0;
    float b = y1 - a*x1;
    y = a*x+b;
    return y;
}

float timX(const float& x1, const float& y1, const int& x2, const int& y2, const float& y)
{
    float x;
    float a=(y1-y2)/(x1-x2)*1.0;
    float b = y1 - a*x1;
    x = (y-b)/a;
    return x;
}

bool checkCollision(const SDL_FRect& object1, const SDL_FRect& object2)
{
  float left_a = object1.x;
  float right_a = object1.x + object1.w;
  float top_a = object1.y;
  float bottom_a = object1.y + object1.h;

  float left_b = object2.x;
  float right_b = object2.x + object2.w;
  float top_b = object2.y;
  float bottom_b = object2.y + object2.h;

  // Case 1: size object 1 < size object 2
  if (left_a > left_b && left_a < right_b)
  {
    if (top_a > top_b && top_a < bottom_b)
    {
      return true;
    }
  }

  if (left_a > left_b && left_a < right_b)
  {
    if (bottom_a > top_b && bottom_a < bottom_b)
    {
      return true;
    }
  }

  if (right_a > left_b && right_a < right_b)
  {
    if (top_a > top_b && top_a < bottom_b)
    {
      return true;
    }
  }

  if (right_a > left_b && right_a < right_b)
  {
    if (bottom_a > top_b && bottom_a < bottom_b)
    {
      return true;
    }
  }

  // Case 2: size object 1 < size object 2
  if (left_b > left_a && left_b < right_a)
  {
    if (top_b > top_a && top_b < bottom_a)
    {
      return true;
    }
  }

  if (left_b > left_a && left_b < right_a)
  {
    if (bottom_b > top_a && bottom_b < bottom_a)
    {
      return true;
    }
  }

  if (right_b > left_a && right_b < right_a)
  {
    if (top_b > top_a && top_b < bottom_a)
    {
      return true;
    }
  }

  if (right_b > left_a && right_b < right_a)
  {
    if (bottom_b > top_a && bottom_b < bottom_a)
    {
      return true;
    }
  }

   // Case 3: size object 1 = size object 2
  if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
  {
    return true;
  }

  return false;
}


