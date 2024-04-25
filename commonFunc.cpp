#include "texture.h"
#include "const.h"
#include "commonFunc.h"



void close(SDL_Window* gWindow, SDL_Renderer* gRenderer, TTF_Font* gFont)
{

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
	Mix_Quit();
}


int checkCollision2(const SDL_FRect& object1, const SDL_FRect& object2)
{
    float left_a = object1.x;
    float right_a = object1.x + object1.w;
    float top_a = object1.y;
    float bottom_a = object1.y + object1.h;

    float left_b = object2.x;
    float right_b = object2.x + object2.w;
    float top_b = object2.y;
    float bottom_b = object2.y + object2.h;

    if(left_a <= right_b && left_a >= left_b)
    {
        return right;
    }
    else if(left_b <= right_a && left_b>= left_a)
    {
        return left;
    }
    else if(top_a <= bottom_b && top_a >= top_b)
    {
        return bottom;
    }
    else if(top_b <= bottom_a && top_b >= top_a)
    {
        return top;
    }
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

bool init(SDL_Renderer*&gRenderer, SDL_Window*&gWindow)
{
    bool success = 1;
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        success = 0;
        std::cout << "ko the khoi tao SDL" << SDL_GetError() << std::endl;
    }
    else
    {
        gWindow = SDL_CreateWindow("20 min till dawn", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
                //Initialize SDL_ttf
                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    success = false;
                }
                 //Initialize SDL_mixer
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
            }
        }
    }
    return success;
}

void create_enemies(std::vector<threatsObject*> &enemies)
{
    threatsObject* p_enemy1 = new threatsObject();
    threatsObject* p_enemy2 = new threatsObject();
    threatsObject* p_enemy3 = new threatsObject();
    threatsObject* p_enemy4 = new threatsObject();
    p_enemy1->set_x_pos(0);
    p_enemy1->set_y_pos(SCREEN_HEIGHT/2);
    p_enemy1->set_is_move(1);
    p_enemy2->set_x_pos(SCREEN_WIDTH/2);
    p_enemy2->set_y_pos(0);
    p_enemy2->set_is_move(1);
    p_enemy3->set_x_pos(LEVEL_WIDTH);
    p_enemy3->set_y_pos(LEVEL_HEIGHT/2);
    p_enemy3->set_is_move(1);
    p_enemy4->set_x_pos(SCREEN_WIDTH/2);
    p_enemy4->set_y_pos(LEVEL_HEIGHT);
    p_enemy4->set_is_move(1);

    enemies.push_back(p_enemy1);
    enemies.push_back(p_enemy2);
    enemies.push_back(p_enemy3);
    enemies.push_back(p_enemy4);
}


