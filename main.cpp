#include "texture.h"
#include "const.h"
#include "commonFunc.h"
#include "character.h"
#include "imgTimer.h"
#include "enemies.h"


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
    //Open the font
    gFont = TTF_OpenFont( "image/text.ttf", 28 );
    if( gFont == NULL )
    {
        std::cout << "Failed to load lazy font! SDL_ttf Error: %s\n" << TTF_GetError() << std::endl ;
        success = false;
    }
//    else
//    {
//        //Render text
//        SDL_Color textColor = { 0, 100, 0 };
//        //Load prompt texture
//		if( !gPromptTextTexture.loadFromRenderedText( "Press Enter to Reset Start Time.", textColor, gRenderer, gFont ) )
//		{
//			printf( "Unable to render prompt texture!\n" );
//			success = false;
//		}
//    }
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
            }
        }
    }
    return success;
}



int main(int argc, char* argv[])
{
    ImpTimer fps_timer;
    ImpTimer fps_timer1;
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
			bool quit = 1;

			//Event handler
			SDL_Event e;

			Character Char1;

            SDL_FRect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

            std::vector<threatsObject*> enemies;
            //render main menu
            gStart.render(0, 0, gRenderer);
            SDL_RenderPresent(gRenderer);
            while(1)
            {
                if(SDL_PollEvent( &e ) != 0 && e.button.button == SDL_BUTTON_LEFT && e.type == SDL_MOUSEBUTTONDOWN)
                {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if(x > 310 && x < 525 && y > 270 && y < 325 )
                    {
                        gStart.free();
                        quit = 0;
                        break;
                    }
                    else if(x > 310 && x < 525 && y > 345 && y < 395 )
                    {
                        break;
                    }
                }
            }
			//current animation frame
            int frame = 0;
            //so ke dich bi tieu diet
            int defeated_enemy = 0;

			//In memory text stream
			std::stringstream timeText;
			std::stringstream healthText;
			std::stringstream bulletText;

			fps_timer.start();

			//While application is running
			while( !quit )
			{

			    fps_timer1.start();

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
//                        if(Char1.get_level_up() == 1)
//                        {
//                            gLevelUp.render(105, 167, gRenderer);
//                            SDL_RenderPresent(gRenderer);
//                        }
//                        while(Char1.get_level_up() == 1)
//                        {
//
//                            Char1.handleLevelUp(e, fps_timer, gLevelUp);
//                        }
//                        if(Char1.get_level_up() == 1)
//                        {
//
//                            gLevelUp.render(105, 167, gRenderer);
//                            SDL_RenderPresent(gRenderer);
//                            fps_timer.paused();
//                            Char1.handleLevelUp(e, fps_timer);
//                            fps_timer.unpaused();
//                        }
                        Char1.handleEvent(e, gRenderer, gWeapon, camera);
//                        gLevelUp.free();
                    }
                }
                //move character
                Char1.move(tileSet, camera);
                Char1.setCamera(camera);
                Char1.set_shoot();
                Char1.set_bullet();
                if(defeated_enemy == LEVEL_UP)
                {
                    Char1.set_level_up(1);
                    defeated_enemy = 0;
                }
                //render level
                for(int i = 0; i < TOTAL_TILES; i++)
                {
                    tileSet[i]->render(camera, gTileTexture, gTileClips, gRenderer);
                }

                Char1.render(gRenderer, camera, Char, currentClip, gWeapon, gBullet);
                Char1.handleBullet(gRenderer, gBullet, camera);

                if(SDL_GetTicks() % 200 == 0){
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
//                std::cout << enemies.size() << std::endl;
                for(int i = 0; i <int(enemies.size()); i++)
                {
                    threatsObject* p_enemy = enemies.at(i);
                    if(p_enemy != NULL)
                    {
                        if(p_enemy->get_is_move() == 1)
                        {
                            p_enemy->render(gRenderer, gEnemy, camera);
                            p_enemy->move(Char1.get_x_pos(), Char1.get_y_pos());

                        }
                        else
                        {
                            enemies.erase(enemies.begin()+i);
                            if(p_enemy != NULL)
                            {
                                delete p_enemy;
                                p_enemy = NULL;
                            }
                        }

                        //kt va chạm giữa nhân vật và kẻ địch
                        SDL_FRect rect_player = Char1.get_rect();
                        SDL_FRect rect_enemy = p_enemy->getBox();
                        bool bCol1 = false;
                        bCol1 = checkCollision(rect_enemy, rect_player);
                        if(bCol1 && (SDL_GetTicks() - Char1.get_undead_time()) > 1000)
                        {
                            Char1.set_health(Char1.get_health()-1);
                            gRed.render(0, 0, gRenderer);
                            Char1.set_x_pos(Char1.get_x_pos() + 20);
                            SDL_Delay(10);
                            if(Char1.get_health() <= 0)
                            {
                                quit = 1;
                            }
                            Char1.set_undead_time(SDL_GetTicks());
                        }
                    }
                }

                std::vector<bulletObject*> bullet_arr = Char1.get_bullet_list();
                for(int r = 0; r < int(bullet_arr.size()); r++)
                {
                    bulletObject* p_bullet = bullet_arr.at(r);
                    if(p_bullet != NULL)
                    {
                        for(int t = 0; t < int(enemies.size()); t++)
                        {
                            threatsObject* obj_threat = enemies.at(t);
                            if(obj_threat != NULL)
                            {
                                SDL_FRect tRect= obj_threat->getBox();
                                SDL_FRect bRect = p_bullet->get_box();

                                bool bCol = checkCollision(tRect, bRect);
                                if(bCol)
                                {
                                    defeated_enemy++;
                                    for(int ex = 0; ex < explosion_frames; ex++)
                                    {
                                        gExplosion.render(obj_threat->getBox().x-camera.x, obj_threat->getBox().y-camera.y, gRenderer, &Exf[ex]);
                                    }
                                    Char1.removeBullet(r);
                                    enemies.erase(enemies.begin()+t);
                                    if(obj_threat != NULL)
                                    {
                                        delete obj_threat;
                                        obj_threat = NULL;
                                    }

                                }
                            }
                        }
                    }
                }

                //Set text to be rendered
				timeText.str( "" );
				healthText.str("");
				bulletText.str("");
				timeText << "Time: " << (fps_timer.get_ticks())/60000 << ":" << ((fps_timer.get_ticks())/1000)%60;
				healthText << "Health: " << Char1.get_health();
				bulletText << "bullet: " << Char1.get_bullet_left();
				SDL_Color textColor = { 0, 100, 0 };

				//Render text
				if( !gTimeTextTexture.loadFromRenderedText( timeText.str().c_str(), textColor, gRenderer, gFont ) )
				{
					printf( "Unable to render time texture!\n" );
				}
				if( !gHealthTextTexture.loadFromRenderedText( healthText.str().c_str(), textColor, gRenderer, gFont ) )
				{
					printf( "Unable to render health texture!\n" );
				}
				if( !gBulletTextTexture.loadFromRenderedText( bulletText.str().c_str(), textColor, gRenderer, gFont ) )
				{
					printf( "Unable to render bullet texture!\n" );
				}

				//Render textures


				gTimeTextTexture.render( 0, 0, gRenderer );
				gHealthTextTexture.render( 0, 29, gRenderer );
				gBulletTextTexture.render( 0, 58, gRenderer );



                if(Char1.get_level_up() == 1)
                {
                    gLevelUp.render(105, 167, gRenderer);
                    SDL_RenderPresent(gRenderer);
                    fps_timer.paused();
                    Char1.handleLevelUp(e, fps_timer);
                    fps_timer.unpaused();
                    Char1.set_x_vel(0);
                    Char1.set_y_vel(0);
                }

                //update screen
				SDL_RenderPresent(gRenderer);
//				int real_imp_time = fps_timer1.get_ticks();
//				std::cout << real_imp_time << std::endl;
//				int time_one_frame= 1000/FRAME_PER_SECOND;
//
//				if(real_imp_time < time_one_frame)
//                {
//                    int delay_time = time_one_frame - real_imp_time;
//                    if(delay_time >= 0)
//                    {
//                        SDL_Delay(delay_time);
//                    }
//                }
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
        close(gWindow, gRenderer, gFont);
        gTileTexture.free();
        gWeapon.free();
        gBullet.free();
        gRed.free();
        gExplosion.free();
        gTimeTextTexture.free();
        gHealthTextTexture.free();
        gLevelUp.free();
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
        gStart.free();
	}
	return 0;
}

