#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include "mylib.h"
#include <iostream>
#include <sstream>
#include <time.h>
using namespace std;


int main( int argc, char* args[] )
{
    srand(time(NULL));

    if(!init()){
        cout<<"SDL has a problem";
    }
    else{

        if(createrenderwindow("knight and zoombies")){
            clearscreen();
            bgtexture.loadimage("background/background.png");

            gamemap.getmap("map/defaultmap.txt");
            gamemap.loadmap();

            knight.setframe(10);
            knight.loadrunframe("characterimage/main/foo0.png");
            knight.loadattackframe();
            knight.loadjumpframe();
            knight.loadskillframe();

            bgtexture.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,0);

            knight.mytexture.loadimage("characterimage/main/foo0.png");

            mymonster.loadmonster_frame(monster_frame);
            mymonster.loadmonster_fire_frame(monster_fire_frame);
            mymonster.loadmonster_attack_frame(monster_attack_frame);
            mymonster.loadmonster_dead_frame(monster_dead_frame);

            loadmonster_image("characterimage/monster/foo0.png", monster_arr);
            loadmonsterpos(&blockw,&blockh,(knight.mytexture.getwidth()+40)/2+50,monster_arr);

            knight.mytexture.setpos(0,300);

            emptybartexture.loadimage("characterimage/heathandmana/emptybar.png");
            heathtexture.loadimage("characterimage/heathandmana/heath.jpg");
            manatexture.loadimage("characterimage/heathandmana/mana.jpg");

            starttexture1.loadimage("start/knight.png");
            starttexture2.loadimage("start/zoombie.png");
            musicontexture.loadimage("musicimage/on.png");
            musicofftexture.loadimage("musicimage/off.png");
            musictexture.loadimage("musicimage/off.png");
            endtexture.loadimage("end/end.png");

            myboss.mytexture.loadimage("characterimage/boss/boss0.png");
            myboss.load_boss_frame(boss_frame);
            myboss.load_boss_attack_frame(boss_attack_frame);
            myboss.load_boss_dead_frame(boss_dead_frame);
            myboss.loadboss();


//            g_str="Hello world";
            texttexture.setfont("lazy.ttf",SCREEN_HEIGHT/12);
//            texttexture.rendertext(7*SCREEN_WIDTH/10,0);
//            SDL_StartTextInput();

            bool quit=false;
            SDL_Event e;
            while(!quit ){
                if(start_flag) start(&e, &bgtexture, &starttexture1, &starttexture2, &texttexture, &musicontexture, &musicofftexture, &musictexture, &start_flag, &mymix);

                while( SDL_PollEvent( &e ) != 0 && e.type != SDL_MOUSEMOTION)
                {
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;

                    }
//                    inputtext(&e,&g_str,11);

                    knight.mytexture.handle(&e);
                    mixinput(&e);

                    windowhandle(&e, &SCREEN_WIDTH, &SCREEN_HEIGHT ,&blockw, &blockh);

                }
                if(!start_flag){
                    if(!knight.dead_flag){
                        clearscreen();
                        knight.mymove(&e, &SCREEN_WIDTH, &SCREEN_HEIGHT, gamemap.getground(knight.mytexture.getpos().x, &blockw, &blockh, (knight.mytexture.getwidth()+40)/2+50));
                        bgtexture.render(0,0,SCREEN_WIDTH, SCREEN_HEIGHT,0);

                        gamemap.changemap(&knight.mytexture, SCREEN_WIDTH, &blockw, &blockh, monster_arr, &myboss);
                        gamemap.rendermap(&SCREEN_WIDTH, &SCREEN_HEIGHT);

    //                    texttexture.loadtext(g_str.c_str(),textColor);
    //                    texttexture.rendertext(7*SCREEN_WIDTH/10,0);
                        get_main_posx(knight.mytexture.pos.x);

                        check_dead_condition(&myboss, monster_arr, &knight);
                        rendermonster(monster_arr, SCREEN_WIDTH/12, SCREEN_HEIGHT/12);

                        knight.mytexture.render(knight.mytexture.getpos().x, knight.mytexture.getpos().y, SCREEN_WIDTH/12, SCREEN_HEIGHT/12, 0);
                        check_main_hp(&knight, monster_arr, &myboss);

                        fixmonsterbullet(monster_arr, &e, &knight);
                        monsters_falldown(monster_arr, monster_frame, monster_fire_frame, monster_attack_frame, monster_dead_frame);
                        display_heath_and_mana(&knight, &myboss, monster_arr, &heathtexture, &manatexture, &emptybartexture);


                        myboss.boss_falldown(boss_frame, boss_dead_frame);
                        myboss.boss_fire(boss_attack_frame, monster_fire_frame);
                        myboss.special_skill();
                        myboss.boss_render();




                        knight.run(&e);
                        knight.mytexture.frame_flip(&e);
                        knight.attack(&e, &mymix);
                        knight.skill(&e, &SCREEN_WIDTH);
                        knight.boss_effect(myboss.send_fall_down_sign(), myboss.first_fall_down_key);
                        knight.dead();

                    }
                        else {
                            gameover(&myboss, &gamemap, monster_arr, &knight, &e, &endtexture, &bgtexture, &texttexture, &start_flag);
                        }
                }
                updatescreen();

            }
//            SDL_StopTextInput();
//            getquit();
        }
    }
    close();
	return 0;
}

