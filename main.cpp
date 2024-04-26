#include "texture.h"
#include "const.h"
#include "commonFunc.h"
#include "character.h"
#include "imgTimer.h"
#include "enemies.h"
#include "load_image.h"

int main(int argc, char* argv[])
{
    ImpTimer fps_timer;
    //Start up SDL and create window
	if( !init(gRenderer, gWindow) )
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
            Mix_PlayMusic(gTitleMusic, -1);
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
                        Mix_HaltMusic();
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

            Mix_PlayMusic(gOstMusic, -1);

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
                        Char1.handleEvent(e, gRenderer, gWeapon, camera, gShoot);
                    }
                }
                //move character
                Char1.move(tileSet, camera);
                Char1.setCamera(camera);
                Char1.set_shoot();
                Char1.set_bullet();
                if(defeated_enemy >= LEVEL_UP)
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

                if(SDL_GetTicks() % 400 == 0){
                    threatsObject* p_enemy1 = new threatsObject();
                    threatsObject* p_enemy2 = new threatsObject();
                    threatsObject* p_enemy3 = new threatsObject();
                    threatsObject* p_enemy4 = new threatsObject();
                    p_enemy1->set_x_pos(0);
                    p_enemy1->set_y_pos(LEVEL_HEIGHT/2);
                    p_enemy1->set_is_move(1);
                    p_enemy2->set_x_pos(LEVEL_WIDTH/2);
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
                            Mix_PlayChannel(-1, gPlayerCol, 0);
                            Char1.set_health(Char1.get_health()-1);
                            gRed.render(0, 0, gRenderer);
//                            Char1.set_x_pos(Char1.get_x_pos() + 20);
                            SDL_Delay(10);
                            if(Char1.get_health() <= 0)
                            {
                                quit = 1;
                            }
                            Char1.set_undead_time(SDL_GetTicks());
                            int bCol2 = checkCollision2(rect_enemy, rect_player);
                            if(bCol2 == right)
                            {
                                Char1.set_x_pos(Char1.get_x_pos() + 30);
                                if(touchesWall(Char1.get_rect(), tileSet))
                                {
                                    Char1.set_x_pos(Char1.get_x_pos() - 30);
                                }
                            }
                            if(bCol2 == left)
                            {
                                Char1.set_x_pos(Char1.get_x_pos() - 30);
                                if(touchesWall(Char1.get_rect(), tileSet))
                                {
                                    Char1.set_x_pos(Char1.get_x_pos() + 30);
                                }
                            }
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
                                    Mix_PlayChannel(-1, gBulletCol, 0);
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
				if(((fps_timer.get_ticks())/60000) >= 10)
                {
                    timeText << "Time: " << (fps_timer.get_ticks())/60000 << ":";
                    if(((fps_timer.get_ticks())/1000)%60 >= 10)
                    {
                        timeText << (((fps_timer.get_ticks())/1000)%60);
                    }
                    else
                    {
                        timeText << "0" << ((fps_timer.get_ticks())/1000)%60;
                    }
                }
                else
                {
                    timeText << "Time: " << "0" << (fps_timer.get_ticks())/60000 << ":";
                    if(((fps_timer.get_ticks())/1000)%60 >= 10)
                    {
                        timeText << ((fps_timer.get_ticks())/1000)%60;
                    }
                    else
                    {
                        timeText << "0" << ((fps_timer.get_ticks())/1000)%60;
                    }
                }

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
				gTimeTextTexture.render( 691, 33, gRenderer );
				gHealthTextTexture.render( 0, 33, gRenderer );
				gBulletTextTexture.render( 0, 62, gRenderer );



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

                gLevel.render(20, 0, gRenderer);
                SDL_Rect clip;
                clip.h = 32;
                clip.w = (800/LEVEL_UP)*defeated_enemy;
                gLevel1.render(20, 0, gRenderer, &clip);
                if(fps_timer.get_ticks() >= survive_time)
                {
                    quit = 1;
                }
                while(quit == 1)
                {
                    Mix_HaltMusic();
                    if(fps_timer.get_ticks() < survive_time)
                    {
                        gDefeat.render(0,0, gRenderer);
                        SDL_RenderPresent(gRenderer);
                    }
                    else
                    {
                        gWin.render(0,0, gRenderer);
                        SDL_RenderPresent(gRenderer);
                    }
                    if(SDL_PollEvent( &e ) != 0 && e.button.button == SDL_BUTTON_LEFT && e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        int x, y;
                        SDL_GetMouseState(&x, &y);
                        if(x > 330 && x < 510 && y > 410 && y < 490 )
                        {
                            quit = 0;
                            Char1.set_character();
                            fps_timer.start();
                            defeated_enemy = 0;
                            enemies.clear();
                            Mix_PlayMusic(gOstMusic, -1);
                            break;
                        }
                        else if(x > 330 && x < 510 && y > 280 && y < 370)
                        {
                            break;
                        }
                    }
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
        //Free resources and close SDL
        close(gWindow, gRenderer, gFont);
        Free();

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

