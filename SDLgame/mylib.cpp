#include "mylib.h"
#include <iostream>
#include <sstream>
#include <time.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

using namespace std;

bool init(){
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        success = false;
    }
    if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    return success;
}
bool createsurfacewindow(string title){
    bool success=true;
    window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if(!window){
        cout<<"could not create window";
        success = false;
    }
    else {
        surface = SDL_GetWindowSurface( window );
    }
    return success;
}

bool createrenderwindow(string title){
        bool success=true;
        window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        if(!window){
            cout<<"could not create window";
            success = false;
        }
        else {
            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(!renderer) cout<<"could not create renerer";
            else{
                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
        return success;
}

void clearscreen(){
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( renderer );
}

void close(){
//    SDL_FreeSurface( background );
//    background = NULL;

    SDL_DestroyWindow( window );
    window = NULL;

    SDL_FreeSurface(surface);
    surface=NULL;

    SDL_DestroyRenderer(renderer);
    renderer=NULL;

    SDL_Quit();
    TTF_Quit();
    Mix_Quit();
}

void updatescreen(){
    SDL_RenderPresent( renderer );
 }

void myTexture::loadimage(string path){
    this->thissurface = IMG_Load(path.c_str());
    if( this->thissurface != NULL ){
        SDL_SetColorKey( this->thissurface, SDL_TRUE, SDL_MapRGB( this->thissurface->format, 0, 0xFF, 0xFF ) );
        this->thistexture = SDL_CreateTextureFromSurface( renderer, this->thissurface );
        this->height=this->thissurface->h;
        this->width=this->thissurface->w;
        if( this->thistexture == NULL ){
            cout<<"could not create textture from this surface";
        }
    }
    else{
        cout<<"loading image has problem";
    }
}


SDL_Point myTexture::getpos(){
    return this->pos;
 }

void myTexture::render(int x, int y, int w, int h, bool mode){
        if(!mode){
            this->textturepart.h=this->height;
            this->textturepart.w=this->width;
        }

        this->textturepos.x=x;
        this->textturepos.y=y;
        this->textturepos.w=w;
        this->textturepos.h=h;
        SDL_RenderCopyEx( renderer, this->thistexture, &(this->textturepart), &this->textturepos , this->angle, &this->center, this->flip);
}

void getquit(){
    bool quit=false;
    SDL_Event e;
         /*
            loop bat su kien close  window dang mo
            kieu SDL_event nhan input
            ham SDL_PollEvent bat SDL_Event
            danh dau de out khoi loop
        */
    while(!quit ){
        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
        }
    }
}

void setviewport(int x, int y, int w, int h){
    SDL_Rect viewport;
    viewport.x = x;
    viewport.y = y;
    viewport.w = w;
    viewport.h = h;
    SDL_RenderSetViewport( renderer, &viewport );
}

int myTexture::getwidth(){
    return 3*this->textturepos.w/10;
}
int myTexture::getheight(){
    return this->textturepos.h;
}

myTexture::myTexture(){
    this->height=0;
    this->width=0;
    this->thissurface=NULL;
    this->thistexture=NULL;
    this->index=0;
}
myTexture::~myTexture(){
    SDL_FreeSurface(this->thissurface);
    SDL_DestroyTexture(this->thistexture);
}

SDL_Rect myTexture::gettexturepart(){
    return this->textturepart;
}

void myTexture::settextturepart(int x,int y, int w, int h){
    this->textturepart.x=x;
    this->textturepart.y=y;
    this->textturepart.w=w;
    this->textturepart.h=h;
}

void myTexture::setpos(int x, int y){
    this->pos.x=x;
    this->pos.y=y;
    //scrollmap=x;
}

void myTexture::setcolor(int r, int g, int b){
    SDL_SetTextureColorMod( this->thistexture, r, g, b );
}

 void myTexture::setalpha(int a){
    SDL_SetTextureBlendMode( this->thistexture, SDL_BLENDMODE_BLEND );
    SDL_SetTextureAlphaMod( this->thistexture, a);
 }

void myTexture::setflip(double angle, int x, int y, SDL_RendererFlip flip){
        this->angle=angle;
        this->center.x=x;
        this->center.y=y;
        this->flip=flip;
  }

void myTexture::frame_flip(SDL_Event *e){
    if(e->key.keysym.sym == SDLK_LEFT){
        this->setflip(180, 100, 40, SDL_FLIP_VERTICAL);
    }
    if(e->key.keysym.sym == SDLK_RIGHT){
        this->setflip(0, 0, 0, SDL_FLIP_NONE);
    }
}

void myTexture::setfont(string path, int textsize){
    this->font = TTF_OpenFont( path.c_str(), textsize );
	if(  this->font == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
	}

}
void myTexture::loadtext(string text, SDL_Color textcolor){
    this->thissurface = TTF_RenderText_Solid( this->font, text.c_str(), textcolor );
	if( this->thissurface == NULL )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
        this->thistexture = SDL_CreateTextureFromSurface( renderer, this->thissurface );
		if( this->thistexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
    }
}

void myTexture::rendertext(int x, int y){
    SDL_Rect textturepos;
    textturepos.x=x;
    textturepos.y=y;
    textturepos.w=this->thissurface->w;
    textturepos.h=this->thissurface->h;
    SDL_RenderCopy(renderer, this->thistexture,NULL,&textturepos);
}

SDL_Point mouseevent(SDL_Event* e){
    SDL_Point mousepos;
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
    {
        SDL_GetMouseState( &mousepos.x, &mousepos.y );
    }
    return mousepos;
}

void mymixer::loadmusic(string path){
    this->music = Mix_LoadMUS( path.c_str() );
    if( this->music == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
    }
}
 void mymixer::loadchunk(string path){
    this->chunk = Mix_LoadWAV( path.c_str() );
    if( this->chunk == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }
 }

 void myTexture::handle(SDL_Event *e){
    if( e->type == SDL_KEYDOWN && e->key.repeat == 0 )
    {
        switch(e->key.keysym.sym){
            case SDLK_UP:{ flag=1;}break;
//            case SDLK_DOWN:tposy+=10;  break;
            case SDLK_LEFT:tposx-=10; break;
            case SDLK_RIGHT:tposx+=10; break;
        }
    }
    else if( e->type == SDL_KEYUP&& e->key.repeat == 0 )
    {
        flag=0;
        switch(e->key.keysym.sym){
            //case SDLK_UP: tposy+=10;  break;
           // case SDLK_DOWN:tposy-=10;  break;
            case SDLK_LEFT:tposx+=10; break;
            case SDLK_RIGHT:tposx-=10; break;
        }
    }
 }


  void inputtext(SDL_Event *e ,string *s, long long text_lenght){
     if(e->type == SDL_TEXTINPUT && *e->text.text!='1' && *e->text.text!='2' && *e->text.text!='3' && *e->text.text!='4' && *e->text.text!='5'){
        *s += e->text.text;
        if((*s).size()>=text_lenght){
            int i;
            for(i=0;(*s)[i]!='\0';i++){
                (*s)[i]=(*s)[i+1];
            }
            (*s).pop_back();
        }
    }
  }

  void mixinput(SDL_Event* e){
    if( e->type == SDL_KEYDOWN ){
        switch( e->key.keysym.sym )
        {
            case SDLK_1:
                mymix.loadchunk("high.wav");
                Mix_PlayChannel( -1, mymix.chunk, 0 );
                break;
            case SDLK_2:
                mymix.loadchunk("medium.wav");
                Mix_PlayChannel( -1, mymix.chunk, 0 );
                break;
            case SDLK_3:
                mymix.loadchunk("low.wav");
                Mix_PlayChannel( -1, mymix.chunk, 0 );
                break;
            case SDLK_4:
                mymix.loadchunk("scratch.wav");
                Mix_PlayChannel( -1, mymix.chunk, 0 );
                break;
            case SDLK_5:
                mymix.loadmusic("music/backgroundmusic.wav");
                if(!Mix_PlayingMusic()){
                    Mix_PlayMusic(mymix.music,-1);
                }
                else{
                        if( Mix_PausedMusic() == 1 )
                        {
                            Mix_ResumeMusic();
                        }
                        else
                            Mix_PauseMusic();
                }
               break;
        }
    }
  }

  void windowhandle(SDL_Event* e, int *w, int *h, int *blockw, int *blockh){
    if( e->type == SDL_WINDOWEVENT )
	{
        *blockw = *w/10;
        *blockh = *h/8;
		switch( e->window.event )
		{
			case SDL_WINDOWEVENT_SIZE_CHANGED:
			*w= e->window.data1;
            *h= e->window.data2;
			break;
		}
	}
  }

tile::tile(){
}

void tile::reset(){
    map_index=0;
    this->getmap("map/defaultmap.txt");
}

void tile::getmap(string path){
    FILE* f=fopen(path.c_str(),"r");
    for(int i=0; i<8;i++){
        for(int j=0;j<numofcollum;j++){
            fscanf(f,"%d",&(maparr[i][j]));
        }
    }
    ++map_index;
    if(map_index==numofmap) map_index=numofmap+1;;
}

void tile::loadmap(){

    string tmp="tiles/";
    for(int i=1; i<=numoftiles;i++){
                tmp+=to_string(i);
                tmp+=".png";
                this->maptexture[i].loadimage(tmp.c_str());
                tmp="tiles/";
    }
}

void tile::rendermap(int *w, int *h){
    this->width=*w/10;
    this->height=*h/8;
    for(int i=0; i<8;i++){
        for(int j=0;j<numofcollum;j++){
            if(maparr[i][j]){
                if(maparr[i][j]==24 || maparr[i][j]==25){
                    this->maptexture[maparr[i][j]].render(this->width*j+64 - scrollmap,this->height*i+64,64, 64,0);
                }
                else
                    this->maptexture[maparr[i][j]].render(this->width*j - scrollmap,this->height*i+3,this->width, this->height,0);
            }
        }
    }

}

int tile::getground(int posx, int *blockw, int* blockh, int fix){
    int x=(posx+scrollmap + fix)/(*blockw);
    if(x>numofcollum-1) return 8*(*blockh);
    int found=0;
    int ground;
    for(int i=7;i>=0 && !found;i--){
        if(maparr[i][x]==0 || maparr[i][x]==17 || maparr[i][x]==18 || maparr[i][x]>=20) {
            found=1;
            ground=i+1;
        }
    }
    return ground*(*blockh);
}

bool collision(SDL_Rect a, SDL_Rect b){
    return ((((a.x<b.x + b.w)&& (a.x>b.x))&&((a.y<=b.y + b.h)&&(a.y>=b.y))) || (((a.x + a.w<b.x + b.w)&& (a.x +a.w>b.x)) && ((a.y + a.h<=b.y + b.h)&& (a.y +a.h>=b.y))));
}

void tile::changemap(myTexture *mytexture, int w, int* blockw, int* blockh, monster arr[30], boss* myboss){

    if(mytexture->getpos().x+w/12 +2 >= w && map_index<=numofmap && myboss->dead_flag){
        string path="map/map";
        path = path+to_string(map_index)+".txt";

        this->getmap(path.c_str());

        scrollmap=0;
        loadmonsterpos(blockw,blockh,(mytexture->getwidth()+40)/2+50,arr);
        mytexture->setpos(0,0);

        myboss->boss_reset();
        myboss->loadboss();
    }
}

character::character(){
    this->attackenergy=0;
    this->jumpenergy=10;
    this->aindex=0;
    this->runindex=0;
    this->jumpindex=0;
    this->skill_1_index=100;
    this->skill_1_energy=100;
    this->skill_2_index=1000;
    this->skill_2_energy=50;
    this->main_hp=500;
    this->dead_flag=0;
    this-> boss_skill_effect=0;
}

void character::main_reset(){
    this->attackenergy=0;
    this->jumpenergy=10;
    this->aindex=0;
    this->runindex=0;
    this->jumpindex=0;
    this->skill_1_index=100;
    this->skill_1_energy=100;
    this->skill_2_index=1000;
    this->skill_2_energy=50;
    this->main_hp=500;
    this->dead_flag=0;
    this->mytexture.setpos(0,300);
    this-> boss_skill_effect=0;

}
void character::loadattackframe(){
    string path;

     this->attack_frame_arr = new SDL_Texture*[10];
        for(int i=0;i<10;i++){
            path="characterimage/main/attack/attack"+to_string(i+1)+".png";
            this->mytexture.thissurface = IMG_Load(path.c_str());
            if( this->mytexture.thissurface != NULL ){
            SDL_SetColorKey( this->mytexture.thissurface, SDL_TRUE, SDL_MapRGB( this->mytexture.thissurface->format, 0, 0xFF, 0xFF ) );
            this->attack_frame_arr[i]=SDL_CreateTextureFromSurface( renderer, this->mytexture.thissurface );
            if(this->attack_frame_arr[i]==NULL) printf("couldnt load frame\n");
            this->mytexture.thissurface=NULL;
        }
    }
}

void character::attack(SDL_Event *e, mymixer* mymix){
    if((e->key.keysym.sym==SDLK_RSHIFT || e->key.keysym.sym==SDLK_DOWN)&& this->attackenergy==11){
        this->attackenergy=1;
    }
    if(e->type==SDL_KEYUP){
        this->attackenergy=11;
    }
    ++this->attackenergy;


    if(e->type==SDL_KEYDOWN && (e->key.keysym.sym==SDLK_DOWN)){
        mymix->loadchunk("music/attack.wav");
        Mix_PlayChannel( -1, mymix->chunk, 0 );
        if(this->skill_1_index==100)
            this->skill_1_index=0;
    }
    if(e->type==SDL_KEYDOWN && (e->key.keysym.sym==SDLK_RSHIFT)){
        if(this->skill_2_index==1000)
            this->skill_2_index=0;
    }
    if(this->skill_1_index==100) this->thisbullet1.pos.x=-100;
    if(this->skill_2_energy==50) this->thisbullet2.pos.x=-1000;

    if(this->skill_1_index==0) {
        if(this->skill_1_index==0) this->skill_1_energy=10;
        this->thisbullet1.pos.x=this->mytexture.getpos().x+100;
        this->thisbullet1.pos.y=this->mytexture.getpos().y;
    }

    if(this->skill_2_index==0) {
        if(this->skill_2_index==0) this->skill_2_energy=10;
        this->thisbullet2.pos.x=this->mytexture.getpos().x+100;
        this->thisbullet2.pos.y=this->mytexture.getpos().y;
    }

    ++this->skill_1_index;
    if(this->skill_1_index >100) this->skill_1_index=100;

    ++this->skill_2_index;
    if(this->skill_2_index >1000) this->skill_2_index=1000;

    if(this->attackenergy>11) this->attackenergy=11;
    if(this->attackenergy<11){
        this->mytexture.thistexture= this->attack_frame_arr[this->attackenergy-1];
    }


}

void character::mymove(SDL_Event* e, int *w, int *h, int ground){
    this->falldown(e, h, ground);
    if(e->type==SDL_KEYDOWN||e->type==SDL_KEYUP){
        this->mytexture.pos.x+=tposx;
        if(this->mytexture.getpos().x==*w/2 && e->key.keysym.sym != SDLK_LEFT && scrollmap<=(*w/10)*numofcollum-*w) {this->mytexture.pos.x -= tposx;  scrollmap+=tposx;}
        if(scrollmap>(*w/10)*numofcollum-*w/2) skillflag=1;
        if( ( this->mytexture.pos.x +90< 0 ) || ( this->mytexture.pos.x + this->mytexture.getwidth() + 60> *w ) )
        {
            this->mytexture.pos.x -= tposx;
        }
        this->mytexture.pos.y+=tposy;
        if( ( this->mytexture.pos.y < 0 ) || ( this->mytexture.pos.y + this->mytexture.getheight() > *h ) )
        {
            //Move back
            this->mytexture.pos.y -= tposy;
        }
        if(this->mytexture.pos.y < 0) this->mytexture.pos.y = 0;
        //SDL_Delay(10); // optimize hieu ung chuyen dong
    }
    this->moveback(&ground);
    //printf("%d ",ground);
  }

void character::falldown(SDL_Event* e, int* h, int ground){
    int step=-25;
      if(this->mytexture.pos.y+this->mytexture.getheight()<=ground &&this->jumpenergy==10) {
        tposy=25;
        ++this->jumpindex;
        if(this->jumpindex==this->numofframe) this->jumpindex=0;
      }
      else {tposy=0;}
      if( this->jumpenergy<10) {
         ++this->jumpindex;
        if(this->jumpindex==this->numofframe) this->jumpindex=0;
        tposy=step;
        this->jumpenergy++;
        this->mytexture.thistexture= this->jump_frame_arr[this->jumpindex];
    }
      if(ground-(this->mytexture.pos.y+this->mytexture.getheight())<=10){
        if(flag) this->jumpenergy=0;
    }
 }

 void character::moveback(int * ground){
    SDL_Rect a;
    SDL_Rect b;

    a.x= this->mytexture.getpos().x+93;
    a.y= this->mytexture.getpos().y+20;
    a.w= this->mytexture.getwidth()-46;
    a.h= 2*this->mytexture.getheight()/3-20;

    for(int i=0;i<8;i++){
        for(int j=0;j<numofcollum;j++){
            if(maparr[i][j]<20){
                if(maparr[i][j] && maparr[i][j]!=17 && maparr[i][j]!=18){

                    b.x= 192*j-scrollmap;
                    b.y= 123*i;
                    b.w= 192;
                    b.h= 123;
                    if(collision(a,b)){
                        if(a.x+a.w<b.x+15) skillflag=1;
                        else skillflag=0;
                        this->mytexture.pos.y -= tposy;
                        this->mytexture.pos.x -= tposx;
                        if(a.y+a.h>b.y+b.h-20) {*ground=738;}
                        else {
                                *ground=b.y;
                                if(flag) this->jumpenergy=0;
                                if(a.y+a.h<*ground || a.y+a.h-*ground<20) this->mytexture.pos.x += tposx;
                            }
                    }
                }
            }

        }
    }
}

void character::loadrunframe( string defaultframe){
    string path;

    this->mytexture.thissurface = IMG_Load(defaultframe.c_str());
    if( this->mytexture.thissurface != NULL ){
    SDL_SetColorKey( this->mytexture.thissurface, SDL_TRUE, SDL_MapRGB( this->mytexture.thissurface->format, 0, 0xFF, 0xFF ) );
    this->mytexture.defaulttexture=SDL_CreateTextureFromSurface( renderer, this->mytexture.thissurface );
    if(this->mytexture.defaulttexture==NULL) printf("couldnt load frame\n");
    this->mytexture.thissurface=NULL;
    }

    this->run_frame_arr = new SDL_Texture*[this->numofframe+1];
        for(int i=0;i<this->numofframe;i++){
            path="characterimage/main/foo"+to_string(i+1)+".png";
            this->mytexture.thissurface = IMG_Load(path.c_str());
            if( this->mytexture.thissurface != NULL ){
            SDL_SetColorKey( this->mytexture.thissurface, SDL_TRUE, SDL_MapRGB( this->mytexture.thissurface->format, 0, 0xFF, 0xFF ) );
            this->run_frame_arr[i]=SDL_CreateTextureFromSurface( renderer, this->mytexture.thissurface );
            if(this->run_frame_arr[i]==NULL) printf("couldnt load frame\n");
            this->mytexture.thissurface=NULL;
        }
    }

}

void character::loadjumpframe(){
     string path;

     this->jump_frame_arr = new SDL_Texture*[10];
        for(int i=0;i<10;i++){
            path="characterimage/main/jump/jump"+to_string(i+1)+".png";
            this->mytexture.thissurface = IMG_Load(path.c_str());
            if( this->mytexture.thissurface != NULL ){
            SDL_SetColorKey( this->mytexture.thissurface, SDL_TRUE, SDL_MapRGB( this->mytexture.thissurface->format, 0, 0xFF, 0xFF ) );
            this->jump_frame_arr[i]=SDL_CreateTextureFromSurface( renderer, this->mytexture.thissurface );
            if(this->jump_frame_arr[i]==NULL) printf("couldnt load frame\n");
            this->mytexture.thissurface=NULL;
        }
    }
}

void character::run(SDL_Event* e){
    if(e->type==SDL_KEYDOWN && (e->key.keysym.sym==SDLK_LEFT||e->key.keysym.sym==SDLK_RIGHT)){
        ++this->runindex;
        if(this->runindex == this->numofframe) this->runindex=0;
        this->mytexture.thistexture = this->run_frame_arr[this->runindex];
    }
    else if(e->type==SDL_KEYUP && this->jumpenergy==10){
        this->mytexture.thistexture = this->mytexture.defaulttexture;
    }
}

void character::setframe(int t){
    this->numofframe=t;
}

void character::loadskillframe(){
     string path;

     this->skill_frame_arr = new SDL_Texture*[10];
        for(int i=0;i<10;i++){
            path="characterimage/main/skill/skill"+to_string(i+1)+".png";
            this->skilltexture.thissurface = IMG_Load(path.c_str());
            if( this->skilltexture.thissurface != NULL ){
            SDL_SetColorKey( this->skilltexture.thissurface, SDL_TRUE, SDL_MapRGB( this->skilltexture.thissurface->format, 0, 0xFF, 0xFF ) );
            this->skill_frame_arr[i]=SDL_CreateTextureFromSurface( renderer, this->skilltexture.thissurface );
            if(this->skill_frame_arr[i]==NULL) printf("couldnt load frame\n");
            this->skilltexture.thissurface=NULL;
        }
    }
 }

void character::skill(SDL_Event* e, int *w){
    if(e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_LEFT) tmp=LEFT;
    else if(e->type == SDL_KEYDOWN  && e->key.keysym.sym == SDLK_RIGHT) tmp=RIGHT;

    if(this->skill_1_index==100){
        skill1handle=tmp;
    }
    if(this->skill_2_index==1000){
        skill2handle=tmp;
    }

    if(this->skill_1_energy<100){
        ++this->skill_1_energy;
        this->skilltexture.thistexture=this->skill_frame_arr[(this->skill_1_energy)/10-1];

        if(this->skill_1_energy<=50){
            if(skill1handle==RIGHT){
               this->thisbullet1.pos.x+=10;
            }
            else this->thisbullet1.pos.x-=10;
        }
        this->thisbullet1.setdemention(100,100);
        this->skilltexture.textturepos.x=this->thisbullet1.pos.x;
        if(this->mytexture.getpos().x+this->mytexture.getwidth()>*w/2-10 && e->key.keysym.sym==SDLK_RIGHT && e->type==SDL_KEYDOWN && !skillflag){
                this->thisbullet1.pos.x-=tposx;
        }
        this->skilltexture.textturepos.y=this->thisbullet1.pos.y;
        this->skilltexture.textturepos.w=this->thisbullet1.width;
        this->skilltexture.textturepos.h=this->thisbullet1.height;

        if(skill1handle==RIGHT){
            this->skilltexture.setflip(0, 0, 0, SDL_FLIP_NONE);
            SDL_RenderCopyEx( renderer, this->skilltexture.thistexture, NULL, &this->skilltexture.textturepos , this->skilltexture.angle, &this->skilltexture.center, this->skilltexture.flip);

        }
        else{
            this->skilltexture.setflip(180, 0, 50, SDL_FLIP_VERTICAL);
            SDL_RenderCopyEx( renderer, this->skilltexture.thistexture, NULL, &this->skilltexture.textturepos , this->skilltexture.angle, &this->skilltexture.center, this->skilltexture.flip);
        }
    }
    if(this->skill_2_energy<50){
        ++this->skill_2_energy;

        this->skilltexture.thistexture=this->skill_frame_arr[(this->skill_2_energy)/10-1];

        this->thisbullet2.setdemention(500,100);
        this->skilltexture.textturepos.x=this->thisbullet2.pos.x;
        if(this->mytexture.getpos().x+this->mytexture.getwidth()>*w/2-10 && e->key.keysym.sym==SDLK_RIGHT && e->type==SDL_KEYDOWN && !skillflag)
            this->thisbullet2.pos.x-=tposx;
        this->skilltexture.textturepos.y=this->thisbullet2.pos.y;
        this->skilltexture.textturepos.w=this->thisbullet2.width;
        this->skilltexture.textturepos.h=this->thisbullet2.height;


        if(skill2handle==RIGHT){
            this->skilltexture.setflip(0, 0, 0, SDL_FLIP_NONE);
            SDL_RenderCopyEx( renderer, this->skilltexture.thistexture, NULL, &this->skilltexture.textturepos , this->skilltexture.angle, &this->skilltexture.center, this->skilltexture.flip);

        }
        else{
            this->skilltexture.setflip(180, 0, 50, SDL_FLIP_VERTICAL);
            SDL_RenderCopyEx( renderer, this->skilltexture.thistexture, NULL, &this->skilltexture.textturepos , this->skilltexture.angle, &this->skilltexture.center, this->skilltexture.flip);
        }
    }
}

void character::boss_effect(int boss_fall_down_sign, bool bosskey){
    if(bosskey==true){
        if(boss_fall_down_sign>=-12 && boss_fall_down_sign<=-8){
            this->boss_skill_effect=25;
        }

        if(this->boss_skill_effect>0){
            this->mytexture.pos.y-=50;
            --this->boss_skill_effect;
        }
    }
}

void character::dead(){
    if(this->main_hp<0){
        this->mytexture.pos.y+=10;
    }
    if(this->mytexture.pos.y>=900) this->dead_flag=1;
}

bullet::bullet(){
    this->width=100;
    this->height=100;
}

void bullet::setdemention(int w,int h){
    this->width=w;
    this->height=h;
}

monster::monster(){
    this->posx=0;
    this->monster_energy=20;
    this->move_sign=-1;
    this->posx=-4;
    this->monster_index=0;
    this->fire_energy=100;
    this->fire_index=100;
    this->dead_flag=0;
    this->dead_index=0;
    this->hp=300;
    this->thisbullet1.pos.x=-500;
}

void monster::reset(){
    this->posx=0;
    this->monster_energy=20;
    this->move_sign=-1;
    this->posx=-4;
    this->monster_index=0;
    this->fire_energy=100;
    this->fire_index=100;
    this->dead_flag=0;
    this->dead_index=0;
    this->hp=300;
    this->thisbullet1.pos.x=-1000;
}

void monster::render(int w, int h){
    this->mytexture.render(this->mytexture.getpos().x - scrollmap, this->mytexture.getpos().y, w, h, 0);
}

void monster::monster_falldown(int ground, SDL_Texture* arr[num_of_monster_frame], SDL_Texture* farr[num_of_monster_fire_frame], SDL_Texture* atarr[num_of_monster_attack_frame]){
    if(this->mytexture.pos.y+this->mytexture.getheight()<=ground){
       this->mytexture.pos.y+=25;
    }
   else{
        this->monster_move(40, arr, farr, atarr);
   }
}

int monster::monster_getground(int posx, int posy, int *blockw, int* blockh, int fixx, int fixy){
    int x=(posx + fixx)/(*blockw);
    int y=(posy+fixy)/(*blockh);
    int found=0;
    int ground;
    for(int i=y;i<=7 && !found;i++){
        if(maparr[i][x] && maparr[i][x]!=17&& maparr[i][x]!=18 && maparr[i][x]<=19) {
            found=1;
            ground=i;
        }
    }
    return ground*(*blockh);
}
void loadmonster_image(string path, monster arr[30]){
    for(int i=0;i<30;i++){
        arr[i].mytexture.loadimage(path.c_str());
    }
}

void loadmonsterpos(int *blockw,int *blockh, int fix, monster arr[30]){
    numofmonster=0;
    for(int i=0;i<30;i++){
        arr[i].mytexture.pos.x=-500;
        arr[i].mytexture.pos.y=-500;
        arr[i].reset();
    }
    for(int i=0;i<numofcollum;i++){
        for(int j=0;j<8;j++){
            if(maparr[j][i]==32){
                arr[numofmonster].mytexture.setpos(i*(*blockw)+35,j*(*blockh));

                ++numofmonster;
            }
        }
    }
}

void rendermonster(monster arr[30], int w, int h){
    for(int i=0;i<numofmonster;i++){
        arr[i].render(w, h);
    }
}

void monsters_falldown(monster arr[30], SDL_Texture* frame_arr[num_of_monster_frame], SDL_Texture* farr[num_of_monster_fire_frame], SDL_Texture* atarr[num_of_monster_attack_frame], SDL_Texture* deadarr[num_of_monster_dead_frame]){
    for(int i=0;i<numofmonster;i++){
         if(!arr[i].dead_flag) arr[i].monster_falldown(arr[i].monster_getground(arr[i].mytexture.getpos().x, arr[i].mytexture.getpos().y,&blockw, &blockh, (arr[i].mytexture.getwidth()+40)/2,70),frame_arr,farr, atarr);
         else arr[i].dead(deadarr);

         if(arr[i].dead_index==num_of_monster_dead_frame*10) delete_arr(arr,i);
    }
}

void monster::monster_move(int scope,SDL_Texture* arr[num_of_monster_frame], SDL_Texture* farr[num_of_monster_fire_frame], SDL_Texture* atarr[num_of_monster_attack_frame]){
    this->monster_energy+=this->move_sign;
    if(this->monster_energy==0 || this->monster_energy==scope){
        this->move_sign=-this->move_sign;
        this->posx=-this->posx;
    }
    this->mytexture.pos.x+=this->posx;

    if((++this->monster_index)==num_of_monster_frame) this->monster_index=0;
    this->mytexture.thistexture=arr[this->monster_index];
    if(this->mytexture.pos.x-scrollmap - main_posx>500 || this->mytexture.pos.x-scrollmap - main_posx<-500 ){
        if(this->move_sign<0)
            this->mytexture.setflip(180, SCREEN_WIDTH/24, SCREEN_HEIGHT/24, SDL_FLIP_VERTICAL);
        else
            this->mytexture.setflip(0, 0, 0, SDL_FLIP_NONE);

        this->fire_energy=101;
        this->fire_index=100;
    }
    else
        this->monster_taget(farr , atarr);
}

void monster::monster_taget(SDL_Texture* arr[num_of_monster_fire_frame], SDL_Texture* atarr[num_of_monster_attack_frame]){
    if(this->mytexture.pos.x-scrollmap > main_posx && this->mytexture.pos.x-scrollmap - main_posx<500){
        this->mytexture.setflip(180, 30, 40, SDL_FLIP_VERTICAL);
        //this->fire();
    }
    else if(this->mytexture.pos.x-scrollmap < main_posx && main_posx - this->mytexture.pos.x-scrollmap<500){
        this->mytexture.setflip(0, 0, 0, SDL_FLIP_NONE);
        //this->fire();
    }

    if(this->mytexture.pos.x-scrollmap - main_posx<500 && this->mytexture.pos.x-scrollmap - main_posx>-500)
        this->fire(arr, 30, 40);

    if(this->fire_index<70) this->mytexture.thistexture = atarr[this->fire_index/10];
    if(this->fire_index/10==0){
        monstermix.loadchunk("music/monsterattack.wav");
        Mix_PlayChannel( -1, monstermix.chunk, 0 );
    }

}

void monster::loadmonster_frame(SDL_Texture* arr[num_of_monster_frame]){
     string path;

        for(int i=0;i<num_of_monster_frame;i++){
            path="characterimage/monster/move/move"+to_string(i+1)+".png";
            this->mytexture.thissurface = IMG_Load(path.c_str());
            if( this->mytexture.thissurface != NULL ){
            SDL_SetColorKey( this->mytexture.thissurface, SDL_TRUE, SDL_MapRGB( this->mytexture.thissurface->format, 0, 0xFF, 0xFF ) );
            arr[i]=SDL_CreateTextureFromSurface( renderer, this->mytexture.thissurface );
            if(arr[i]==NULL) printf("couldnt load frame\n");
            this->mytexture.thissurface=NULL;
        }
    }
}

void monster::loadmonster_fire_frame(SDL_Texture* arr[num_of_monster_fire_frame]){
     string path;

        for(int i=0;i<num_of_monster_frame;i++){
            path="characterimage/monster/fire/fire"+to_string(i+1)+".png";
            this->mytexture.thissurface = IMG_Load(path.c_str());
            if( this->mytexture.thissurface != NULL ){
            SDL_SetColorKey( this->mytexture.thissurface, SDL_TRUE, SDL_MapRGB( this->mytexture.thissurface->format, 0, 0xFF, 0xFF ) );
            arr[i]=SDL_CreateTextureFromSurface( renderer, this->mytexture.thissurface );
            if(arr[i]==NULL) printf("couldnt load frame\n");
            this->mytexture.thissurface=NULL;
        }
    }
}

void boss::load_boss_dead_frame(SDL_Texture* arr[num_of_boss_dead_frame]){
    string path;

        for(int i=0;i<num_of_boss_dead_frame;i++){
            path="characterimage/boss/dead/dead"+to_string(i+1)+".png";
            this->mytexture.thissurface = IMG_Load(path.c_str());
            if( this->mytexture.thissurface != NULL ){
            SDL_SetColorKey( this->mytexture.thissurface, SDL_TRUE, SDL_MapRGB( this->mytexture.thissurface->format, 0, 0xFF, 0xFF ) );
            arr[i]=SDL_CreateTextureFromSurface( renderer, this->mytexture.thissurface );
            if(arr[i]==NULL) printf("couldnt load frame\n");
            this->mytexture.thissurface=NULL;
        }
    }

}

void monster::loadmonster_dead_frame(SDL_Texture* arr[num_of_monster_dead_frame]){
     string path;

        for(int i=0;i<num_of_monster_frame;i++){
            path="characterimage/monster/dead/dead"+to_string(i+1)+".png";
            this->mytexture.thissurface = IMG_Load(path.c_str());
            if( this->mytexture.thissurface != NULL ){
            SDL_SetColorKey( this->mytexture.thissurface, SDL_TRUE, SDL_MapRGB( this->mytexture.thissurface->format, 0, 0xFF, 0xFF ) );
            arr[i]=SDL_CreateTextureFromSurface( renderer, this->mytexture.thissurface );
            if(arr[i]==NULL) printf("couldnt load frame\n");
            this->mytexture.thissurface=NULL;
        }
    }
}

void monster::loadmonster_attack_frame(SDL_Texture* arr[num_of_monster_attack_frame]){
    string path;

        for(int i=0;i<num_of_monster_frame;i++){
            path="characterimage/monster/attack/attack"+to_string(i+1)+".png";
            this->mytexture.thissurface = IMG_Load(path.c_str());
            if( this->mytexture.thissurface != NULL ){
            SDL_SetColorKey( this->mytexture.thissurface, SDL_TRUE, SDL_MapRGB( this->mytexture.thissurface->format, 0, 0xFF, 0xFF ) );
            arr[i]=SDL_CreateTextureFromSurface( renderer, this->mytexture.thissurface );
            if(arr[i]==NULL) printf("couldnt load frame\n");
            this->mytexture.thissurface=NULL;
        }
    }
}

void monster::fire(SDL_Texture* arr[num_of_monster_fire_frame], int cnterx, int centery){
    if(this->fire_index<100) ++this->fire_index;
    if(this->fire_energy>=100){
        this->fire_energy=0;
        this->thisbullet1.setdemention(100,100);
        this->thisbullet1.pos.x=this->mytexture.pos.x-scrollmap;
        this->thisbullet1.pos.y=this->mytexture.pos.y;

        this->fixed=0;
    }
    else ++this->fire_energy;
    if(this->fire_energy==0){
        this->fire_index=0;
    }


    if(this->fire_index<100){
        if(!this->fixed){
            if(this->mytexture.pos.x-scrollmap > main_posx){
                this->skilltexture.setflip(180, cnterx, centery, SDL_FLIP_VERTICAL);
                //if(this->fire_index<50) this->thisbullet1.pos.x-=10;
                this->fire_posx=-10;
                this->fixed=1;
            }
            if(this->mytexture.pos.x-scrollmap < main_posx){
                this->skilltexture.setflip(0, 0, 0, SDL_FLIP_NONE);
                //if(this->fire_index<50) this->thisbullet1.pos.x+=10;
                this->fire_posx=10;
                this->fixed=1;
            }
        }
        if(this->fire_index<50) this->thisbullet1.pos.x+=this->fire_posx;

        this->skilltexture.textturepos.x=this->thisbullet1.pos.x;
        this->skilltexture.textturepos.y=this->thisbullet1.pos.y;
        this->skilltexture.textturepos.w=this->thisbullet1.width;
        this->skilltexture.textturepos.h=this->thisbullet1.height;

        this->skilltexture.thistexture=arr[this->fire_index/10];

        SDL_RenderCopyEx( renderer, this->skilltexture.thistexture, NULL, &this->skilltexture.textturepos , this->skilltexture.angle, &this->skilltexture.center, this->skilltexture.flip);
    }

}

void monster::dead(SDL_Texture* deadarr[num_of_monster_dead_frame]){
    if(this->dead_index<(num_of_monster_dead_frame)*10){
        this->mytexture.thistexture = deadarr[(this->dead_index)/10];
        ++this->dead_index;
    }
}

void get_main_posx(int x){
    main_posx=x+30;
}

void delete_arr(monster arr[30], int x){
    for(int i=x;i<numofmonster-1;i++){
        arr[i]=arr[i+1];
    }
    --numofmonster;
}


void check_dead_condition(boss* myboss, monster arr[30], character *knight){
    for(int i=0;i<numofmonster;i++){
        if(!arr[i].dead_flag){
            if(knight->thisbullet1.pos.x + knight->thisbullet1.width/2 >= arr[i].mytexture.pos.x - scrollmap && knight->thisbullet1.pos.x + knight->thisbullet1.width/2 <= arr[i].mytexture.pos.x +SCREEN_WIDTH/12 - scrollmap){
                if(knight->thisbullet1.pos.y + knight->thisbullet1.height/2 >= arr[i].mytexture.pos.y && knight->thisbullet1.pos.y + knight->thisbullet1.height/2 <= arr[i].mytexture.pos.y +SCREEN_HEIGHT/12){
                    if(arr[i].hp_flag==1) knight->skill_1_energy=50;
                    arr[i].hp_flag++;

                    if(arr[i].hp<=0){
                        arr[i].dead_flag=1;
                        arr[i].dead_index=0;
                    }
                    --arr[i].hp;

                }
            }
            if(knight->thisbullet1.pos.x + knight->thisbullet1.width/2 < arr[i].mytexture.pos.x - scrollmap -100 || knight->thisbullet1.pos.x + knight->thisbullet1.width/2 > arr[i].mytexture.pos.x +SCREEN_WIDTH/12 - scrollmap+100)
                arr[i].hp_flag=0;

            if(skill2handle==RIGHT){
                if(knight->thisbullet2.pos.x <= arr[i].mytexture.pos.x + SCREEN_WIDTH/24- scrollmap && knight->thisbullet2.pos.x + knight->thisbullet2.width >= arr[i].mytexture.pos.x + SCREEN_WIDTH/24- scrollmap){
                    if(knight->thisbullet2.pos.y <= arr[i].mytexture.pos.y + SCREEN_HEIGHT/24 && knight->thisbullet2.pos.y + knight->thisbullet2.height >= arr[i].mytexture.pos.y + SCREEN_HEIGHT/24){
                        if(arr[i].hp==0){
                            arr[i].dead_flag=1;
                            arr[i].dead_index=0;
                        }
                        if(arr[i].hp>=10) arr[i].hp-=10;
                        else arr[i].hp=0;
                    }
               }
            }
            else {
                if(knight->thisbullet2.pos.x >= arr[i].mytexture.pos.x + SCREEN_WIDTH/24- scrollmap && knight->thisbullet2.pos.x - knight->thisbullet2.width <= arr[i].mytexture.pos.x + SCREEN_WIDTH/24- scrollmap){
                    if(knight->thisbullet2.pos.y <= arr[i].mytexture.pos.y + SCREEN_HEIGHT/24 && knight->thisbullet2.pos.y + knight->thisbullet2.height >= arr[i].mytexture.pos.y + SCREEN_HEIGHT/24){
                        if(arr[i].hp==0){
                            arr[i].dead_flag=1;
                            arr[i].dead_index=0;
                        }
                        if(arr[i].hp>=10) arr[i].hp-=10;
                        else arr[i].hp=0;
                    }
               }
            }

        }
    }

    if(!myboss->dead_flag){
            if(knight->thisbullet1.pos.x + knight->thisbullet1.width/2 >= myboss->mytexture.pos.x - scrollmap && knight->thisbullet1.pos.x + knight->thisbullet1.width/2 <= myboss->mytexture.pos.x +myboss->bosswidth - scrollmap){
                if(knight->thisbullet1.pos.y + knight->thisbullet1.height/2 >= myboss->mytexture.pos.y && knight->thisbullet1.pos.y + knight->thisbullet1.height/2 <= myboss->mytexture.pos.y + myboss->bossheight){
                    if(myboss->hp_flag==1) knight->skill_1_energy=50;
                    myboss->hp_flag++;

                    if(myboss->hp<=0){
                        myboss->dead_flag=1;
                       myboss->dead_index=0;
                    }
                    --myboss->hp;

                }
            }
            if(knight->thisbullet1.pos.x + knight->thisbullet1.width/2 < myboss->mytexture.pos.x - scrollmap -100 || knight->thisbullet1.pos.x + knight->thisbullet1.width/2 > myboss->mytexture.pos.x +myboss->bosswidth - scrollmap+100)
                myboss->hp_flag=0;

            if(skill2handle==RIGHT){
                if(knight->thisbullet2.pos.x + knight->thisbullet2.width >= myboss->mytexture.pos.x + myboss->bosswidth/2- scrollmap && knight->thisbullet2.pos.x  <= myboss->mytexture.pos.x + myboss->bosswidth/2 - scrollmap){
                    if(knight->thisbullet2.pos.y + knight->thisbullet2.height/2<= myboss->mytexture.pos.y + myboss->bossheight && knight->thisbullet2.pos.y + knight->thisbullet2.height/2 >= myboss->mytexture.pos.y){
                        if(myboss->hp==0){
                            myboss->dead_flag=1;
                            myboss->dead_index=0;
                        }
                        if(myboss->hp>=10) myboss->hp-=10;
                        else myboss->hp=0;
                    }
               }
            }
            else {
                if(knight->thisbullet2.pos.x >= myboss->mytexture.pos.x + myboss->bosswidth/2- scrollmap && knight->thisbullet2.pos.x - knight->thisbullet2.width<= myboss->mytexture.pos.x + myboss->bosswidth/2 - scrollmap){
                    if(knight->thisbullet2.pos.y + knight->thisbullet2.height/2<= myboss->mytexture.pos.y + myboss->bossheight && knight->thisbullet2.pos.y + knight->thisbullet2.height/2 >= myboss->mytexture.pos.y){
                        if(myboss->hp==0){
                            myboss->dead_flag=1;
                            myboss->dead_index=0;
                        }
                        if(myboss->hp>=10) myboss->hp-=10;
                        else myboss->hp=0;
                    }
               }
            }

        }

}

void fixmonsterbullet(monster arr[30], SDL_Event* e, character* knight){
    if(scrollmap<=(SCREEN_WIDTH/10)*numofcollum-SCREEN_WIDTH && knight->mytexture.getpos().x+knight->mytexture.getwidth()>=SCREEN_WIDTH/2-10 && e->key.keysym.sym!=SDLK_LEFT && e->type==SDL_KEYDOWN)
        for(int i=0;i<numofmonster;i++){
            arr[i].thisbullet1.pos.x-=10;
    }
}

void display_heath_and_mana(character* knight, boss *myboss, monster arr[30], myTexture* heathtexture, myTexture* manatexture, myTexture* emptybar){
    for(int i=0;i<numofmonster;i++){
        emptybar->render(arr[i].mytexture.pos.x - scrollmap -20, arr[i].mytexture.pos.y-20, 150, 20, 0);
        heathtexture->render(arr[i].mytexture.pos.x - scrollmap -30+17, arr[i].mytexture.pos.y-30+14, (arr[i].hp)/2-12, 8, 0);
    }
    int mana=knight->skill_2_index/4;
    emptybar->render(0,0,250,50,0);
    heathtexture->render(10,10,knight->main_hp/2-18,20,0);
    emptybar->render(0,40,250,50,0);
    manatexture->render(10,50,mana-18,20,0);

    emptybar->render(myboss->mytexture.pos.x - scrollmap -120,myboss->mytexture.pos.y-20, 620, 40, 0);
    heathtexture->render(myboss->mytexture.pos.x - scrollmap -100, myboss->mytexture.pos.y-30+16, (myboss->hp)/5-12, 15, 0);
}

void check_main_hp(character* knight, monster arr[30], boss* myboss){
    for(int i=0;i<numofmonster;i++){
       if(knight->mytexture.pos.x<=arr[i].thisbullet1.pos.x +arr[i].thisbullet1.width/2 && knight->mytexture.pos.x + SCREEN_WIDTH/12>=arr[i].thisbullet1.pos.x +arr[i].thisbullet1.width/2){
            if(knight->mytexture.pos.y<=arr[i].thisbullet1.pos.y + arr[i].thisbullet1.height/2 && knight->mytexture.pos.y + SCREEN_HEIGHT/12>=arr[i].thisbullet1.pos.y + arr[i].thisbullet1.height/2){
                knight->main_hp-=1;
            }
       }
    }

    if(knight->mytexture.pos.x +SCREEN_WIDTH/24 <=myboss->thisbullet1.pos.x +myboss->thisbullet1.width&& knight->mytexture.pos.x +SCREEN_WIDTH/24 >=myboss->thisbullet1.pos.x){
        if(knight->mytexture.pos.y +SCREEN_HEIGHT/24 <=myboss->thisbullet1.pos.y +myboss->thisbullet1.height && knight->mytexture.pos.y +SCREEN_HEIGHT/24 >=myboss->thisbullet1.pos.y){
            knight->main_hp-=3;
        }
    }
}

void start(SDL_Event *e,myTexture * bgtexture ,myTexture *starttexture1, myTexture *starttexture2, myTexture* texttexture, myTexture *musicontexture, myTexture* musicofftexture,myTexture* musictexture, int* start_flag, mymixer* mymix){
    clearscreen();
    bgtexture->render(0,0,SCREEN_WIDTH, SCREEN_HEIGHT,0);

    starttexture1->render(100,50,700,900,0);
    starttexture2->setflip(180, 30, 40, SDL_FLIP_VERTICAL);
    starttexture2->render(1700,850,700,900,0);

    g_str="Click to play";
    SDL_Color textColor = { 255, 0, 0 };
    texttexture->loadtext(g_str ,textColor);
    texttexture->rendertext(700,0);

    g_str="Music";
    textColor = { 100, 100, 100 };
    texttexture->loadtext(g_str ,textColor);
    texttexture->rendertext(800,400);

    g_str="Made by ThanhTienLy";
    textColor = { 0, 0, 255 };
    texttexture->loadtext(g_str ,textColor);
    texttexture->rendertext(600,900);

    if(mouseevent(e).x>=800 && mouseevent(e).x<=1000 && mouseevent(e).y>=500 && mouseevent(e).y<=700 && e->type == SDL_MOUSEBUTTONDOWN ){
        mymix->loadmusic("music/backgroundmusic.wav");
        if(musiccontroll==1){
            if(music_flag) music_flag=0;
            else music_flag=1;

                if(!Mix_PlayingMusic()){
                    Mix_PlayMusic(mymix->music,-1);
                }
                else{
                        if( Mix_PausedMusic() == 1 )
                        {
                            Mix_ResumeMusic();
                        }
                        else
                            Mix_PauseMusic();
                }
            }
        musiccontroll++;
    }
    else{
        if(e->type == SDL_MOUSEBUTTONDOWN) *start_flag=0;
        musiccontroll=0;
    }
    if(music_flag) musictexture->thistexture = musicontexture->thistexture;
    else  musictexture->thistexture = musicofftexture->thistexture;

    musictexture->render(800,500,200,200,0);
}

void gameover(boss* myboss,tile *gamemap,monster arr[30], character* knight, SDL_Event *e ,myTexture* endtexture , myTexture* bgtexture, myTexture* texttexture, int* start_flag){
        clearscreen();
        bgtexture->render(0,0,SCREEN_WIDTH, SCREEN_HEIGHT,0);
        endtexture->render(300,200,1000,600,0);

        g_str="Game over";
        SDL_Color textColor = { 0, 0, 0 };
        texttexture->loadtext(g_str ,textColor);
        texttexture->rendertext(900,400);

        g_str="Click to play again";
        texttexture->loadtext(g_str ,textColor);
        texttexture->rendertext(500,200);

        if(e->type == SDL_MOUSEBUTTONDOWN){
            *start_flag=1;
            knight->main_reset();
            gamemap->reset();
            numofmonster=0;
            scrollmap=0;

            for(int i=0;i<30;i++){
                arr[i].mytexture.pos.x=-500;
                arr[i].mytexture.pos.y=-500;
                arr[i].reset();
            }
            loadmonsterpos(&blockw,&blockh,(knight->mytexture.getwidth()+40)/2+50,arr);

            myboss->boss_reset();
            myboss->loadboss();
        }
}

boss::boss(){
    this->bosswidth=300;
    this->bossheight=300;
    this->hp=3000;
    this->dead_flag=1;
    this->special_skill_energy=0;
    this->first_fall_down_key=false;
}
void boss::boss_reset(){
    this->reset();
    this->hp=3000;
    this->dead_flag=1;
    this->first_fall_down_key=false;
}

void boss::loadboss(){
    for(int i=0;i<numofcollum;i++){
        for(int j=0;j<8;j++){
            if(maparr[j][i]==33){
                this->dead_flag=0;
                this->mytexture.setpos(i*blockw,j*blockh);
                break;
            }
        }
    }
}

void boss::boss_render(){
    this->render(this->bosswidth, this->bossheight);
}

void boss::boss_falldown(SDL_Texture* frarr[num_of_boss_frame], SDL_Texture* deadarr[num_of_boss_dead_frame]){
    if(!this->dead_flag){
        int ground = this->monster_getground(this->mytexture.getpos().x, this->mytexture.getpos().y, &blockw, &blockh, (this->mytexture.getwidth()+40)/2+50, 50);
        if(this->mytexture.pos.y+this->mytexture.getheight()-20<=ground){
           this->mytexture.pos.y+=25;
        }
        else{
            this->boss_move(80,frarr);
        }

        if(this->mytexture.pos.y+this->mytexture.getheight()-20>ground){
            this->first_fall_down_key=true;
        }
    }
    else{
        this->boss_dead(deadarr);
    }

}

void boss::boss_move(int scope, SDL_Texture* arr[num_of_boss_frame]){
    if(!this->dead_flag){
        this->monster_energy+=this->move_sign;
        if(this->monster_energy==0 || this->monster_energy==scope){
            this->move_sign=-this->move_sign;
            this->posx=-this->posx;
        }
        this->mytexture.pos.x+=this->posx;

        if((++this->monster_index)==num_of_boss_frame*10) this->monster_index=0;
        this->mytexture.thistexture=arr[this->monster_index/10];
        if(this->mytexture.pos.x-scrollmap - main_posx>1000 || this->mytexture.pos.x-scrollmap - main_posx<-1000 ){
            if(this->move_sign<0){
                this->mytexture.setflip(180, 150, 150, SDL_FLIP_VERTICAL);
            }
            else{
                this->mytexture.setflip(0, 0, 0, SDL_FLIP_NONE);
            }

            this->fire_energy=101;
            this->fire_index=100;
        }
        else{
            this->boss_target();

            int ground = this->monster_getground(this->mytexture.getpos().x, this->mytexture.getpos().y, &blockw, &blockh, (this->mytexture.getwidth()+40)/2+50, 50);
            if(this->mytexture.pos.y+this->mytexture.getheight()-20>ground){
                if(this->special_skill_energy == 0){
                    int ran=rand()%1000;
                    if(ran==0){
                        this->special_skill_energy=40;
                    }
                }
            }
        }
    }
}

void boss::load_boss_frame(SDL_Texture* arr[num_of_boss_frame]){
    string path;

        for(int i=0;i<num_of_boss_frame;i++){
            path="characterimage/boss/move/move"+to_string(i+1)+".png";
            this->mytexture.thissurface = IMG_Load(path.c_str());
            if( this->mytexture.thissurface != NULL ){
            SDL_SetColorKey( this->mytexture.thissurface, SDL_TRUE, SDL_MapRGB( this->mytexture.thissurface->format, 0, 0xFF, 0xFF ) );
            arr[i]=SDL_CreateTextureFromSurface( renderer, this->mytexture.thissurface );
            if(arr[i]==NULL) printf("couldnt load frame\n");
            this->mytexture.thissurface=NULL;
        }
    }
}

void boss::load_boss_attack_frame(SDL_Texture* arr[num_of_boss_attack_frame]){
    string path;

        for(int i=0;i<num_of_boss_attack_frame;i++){
            path="characterimage/boss/attack/attack"+to_string(i+1)+".png";
            this->mytexture.thissurface = IMG_Load(path.c_str());
            if( this->mytexture.thissurface != NULL ){
            SDL_SetColorKey( this->mytexture.thissurface, SDL_TRUE, SDL_MapRGB( this->mytexture.thissurface->format, 0, 0xFF, 0xFF ) );
            arr[i]=SDL_CreateTextureFromSurface( renderer, this->mytexture.thissurface );
            if(arr[i]==NULL) printf("couldnt load frame\n");
            this->mytexture.thissurface=NULL;
        }
    }
}

void boss::boss_target(){
    if(this->mytexture.pos.x+ this->bosswidth/2 -scrollmap > main_posx && this->mytexture.pos.x + this->bosswidth/2-scrollmap - main_posx<1000){
        this->mytexture.setflip(180, this->bosswidth/2, this->bossheight/2, SDL_FLIP_VERTICAL);
    }
    else if(this->mytexture.pos.x-scrollmap < main_posx && main_posx - this->mytexture.pos.x-scrollmap<1000){
        this->mytexture.setflip(0, 0, 0, SDL_FLIP_NONE);
    }



}
void boss::boss_fire(SDL_Texture* arr[num_of_boss_attack_frame], SDL_Texture* firearr[num_of_monster_fire_frame]){
    if(!this->dead_flag){
        if(this->mytexture.pos.x-scrollmap - main_posx<1000 && this->mytexture.pos.x-scrollmap - main_posx>-1000){
            this->thisbullet1.setdemention(300,300);
            this->fire(firearr, this->thisbullet1.width/2, this->thisbullet1.height/2);
        }

        if(this->fire_index<70) this->mytexture.thistexture = arr[this->fire_index/10];
//        if(this->fire_index/10==0) {
//            mymix.loadchunk("music/bossattack.wav");
//            Mix_PlayChannel( -1, mymix.chunk, 0 );
//        }
    }
}

void boss::boss_dead(SDL_Texture* deadarr[num_of_boss_dead_frame]){
    if(this->dead_index<(num_of_boss_dead_frame)*10){
        this->mytexture.thistexture = deadarr[(this->dead_index)/10];
        ++this->dead_index;
    }
    if(this->dead_index==(num_of_boss_dead_frame)*10) {
        this->mytexture.pos.x=-1000;
        this->thisbullet1.pos.x=-1000;
    }
}

void boss::special_skill(){
    if(this->special_skill_energy>0){
        this->mytexture.pos.y-=35;
        --this->special_skill_energy;
    }
}

int boss::send_fall_down_sign(){
    int ground = this->monster_getground(this->mytexture.getpos().x, this->mytexture.getpos().y, &blockw, &blockh, (this->mytexture.getwidth()+40)/2+50, 50);
    return this->mytexture.pos.y+this->mytexture.getheight()-20-ground;
}
