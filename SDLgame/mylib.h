#ifndef MYLIB_H_INCLUDED
#define MYLIB_H_INCLUDED

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
using namespace std;

static int SCREEN_WIDTH = 1920;
static int SCREEN_HEIGHT = 986;
static const int numofcollum=24;
static const int numofmap=3;
static const int num_of_monster_frame=10;
static const int num_of_monster_attack_frame=8;
static const int num_of_monster_fire_frame=10;
static const int num_of_monster_dead_frame=7;

static const int num_of_boss_frame=8;
static const int num_of_boss_attack_frame=8;
static const int num_of_boss_dead_frame=10;
static SDL_Window* window = NULL;
static SDL_Surface* surface = NULL;
static SDL_Renderer* renderer = NULL;
static  int tposx=0 ;
static int tposy=0;
static string g_str ="a";
static int flag=1;
static int blockw = SCREEN_WIDTH/10;
static int blockh = SCREEN_HEIGHT/8;
static int energy=0;
static int maparr[8][numofcollum];
static int scrollmap=0;
static const int LEFT=0;
static const int RIGHT=1;
static int skill1handle = RIGHT;
static int skill2handle = RIGHT;
static int tmp = RIGHT;
static const int numoftiles=31;
static bool skillflag=0;
static bool reserve_flag=0;
static int numofmonster=0;
static SDL_Texture* monster_frame[num_of_monster_frame];
static SDL_Texture* monster_fire_frame[num_of_monster_fire_frame];
static SDL_Texture* monster_attack_frame[num_of_monster_attack_frame];
static SDL_Texture* monster_dead_frame[num_of_monster_dead_frame];

static SDL_Texture* boss_frame[num_of_boss_frame];
static SDL_Texture* boss_attack_frame[num_of_boss_attack_frame];
static SDL_Texture* boss_dead_frame[num_of_boss_dead_frame];

static int main_posx=0;
static int start_flag=1;
static bool music_flag=0;
static int musiccontroll=0;
static int map_index=0;

class mymixer{
private:
public:
    Mix_Chunk* chunk=NULL;
    Mix_Music* music=NULL;
    void loadmusic(string);
    void loadchunk(string);
};

class myTexture{
private:
    int height;
    int width;
    int index;
public:
    SDL_Point pos;
    myTexture();
    ~myTexture();
    SDL_Surface* thissurface;
    SDL_Texture* thistexture;
    SDL_Rect textturepos;
    SDL_Rect textturepart;
    double angle;
    SDL_Point center;
    SDL_RendererFlip flip;
    TTF_Font* font;
    SDL_Texture *defaulttexture;

    int getwidth();
    int getheight();

    void render(int , int , int ,int, bool );
    void loadimage(string);

    SDL_Rect gettexturepart();
    SDL_Point getpos();
    void setpos(int , int);
    void settextturepart(int ,int, int, int);

    void setcolor(int, int, int);
    void setalpha(int );

    void setflip(double , int, int, SDL_RendererFlip);

    void loadtext(string, SDL_Color);
    void setfont(string, int);
    void rendertext(int, int);

    void handle(SDL_Event*);

    void frame_flip(SDL_Event *);
};


class bullet{
public:
    bullet();
    SDL_Point pos;
    int width;
    int height;
    void setdemention(int ,int );
};

class character{
public:
    myTexture mytexture;
    myTexture skilltexture;
    SDL_Texture **attack_frame_arr;
    SDL_Texture **jump_frame_arr;
    SDL_Texture **run_frame_arr;
    SDL_Texture ** skill_frame_arr;
    int numofframe;


    character();
    int boss_skill_effect;
    int jumpenergy;
    int attackenergy;
    int skill_1_energy;
    int skill_2_energy;
    int main_hp;
    int dead_flag;
    void moveback(int *);
    int aindex;
    int runindex;
    int jumpindex;
    int skill_1_index;
    int skill_2_index;
    void falldown(SDL_Event*, int *, int);

    void setframe(int );
    void loadattackframe();
    void loadjumpframe();
    void loadrunframe(string);
    void loadskillframe();

    void run(SDL_Event* );
    void attack(SDL_Event*,  mymixer*);
    void skill(SDL_Event*, int *);
    void mymove(SDL_Event*, int*, int*, int);
    void dead();
    void main_reset();
    void boss_effect(int, bool);

    bullet thisbullet1;
    bullet thisbullet2;

};

class monster:public character{
public:
    monster();
    int hp;
    bool fixed;
    int fire_posx;
    int fire_energy;
    int hp_flag;
    int fire_index;
    int dead_flag;
    int dead_index;
    void monster_falldown(int ,SDL_Texture* arr[num_of_monster_frame],SDL_Texture* farr[num_of_monster_fire_frame], SDL_Texture* atarr[num_of_monster_attack_frame]);
    void render(int , int);
    int monster_getground(int ,int , int* ,int*, int, int);
    int posx;
    int monster_energy;
    int move_sign;
    int monster_index;
    void dead(SDL_Texture* deadarr[num_of_monster_dead_frame]);
    void monster_move(int, SDL_Texture* arr[num_of_monster_frame],SDL_Texture* farr[num_of_monster_fire_frame],SDL_Texture* atarr[num_of_monster_attack_frame]);
    void loadmonster_frame(SDL_Texture* arr[num_of_monster_frame]);
    void loadmonster_fire_frame(SDL_Texture* arr[num_of_monster_fire_frame]);
    void loadmonster_attack_frame(SDL_Texture* arr[num_of_monster_attack_frame]);
    void loadmonster_dead_frame(SDL_Texture* arr[num_of_monster_dead_frame]);
    void monster_taget(SDL_Texture* arr[num_of_monster_fire_frame], SDL_Texture* atarr[num_of_monster_attack_frame]);
    void fire(SDL_Texture* arr[num_of_monster_fire_frame], int , int);
    void reset();

};

class boss:public monster{
public:
    boss();
    int special_skill_energy;
    int bosswidth;
    int bossheight;
    void loadboss();
    void boss_render();
    void boss_falldown(SDL_Texture* frarr[num_of_boss_frame],  SDL_Texture* deadarr[num_of_boss_dead_frame]);
    void boss_move(int , SDL_Texture* arr[num_of_boss_frame]);
    void load_boss_frame(SDL_Texture* arr[num_of_boss_frame]);
    void load_boss_attack_frame(SDL_Texture* arr[num_of_boss_attack_frame]);
    void load_boss_dead_frame(SDL_Texture* arr[num_of_boss_dead_frame]);
    void boss_target();
    void boss_fire(SDL_Texture* arr[num_of_boss_attack_frame], SDL_Texture* monster_fire_frame[num_of_monster_fire_frame]);
    void boss_dead(SDL_Texture* deadarr[num_of_boss_dead_frame]);
    void boss_reset();
    void special_skill();
    int send_fall_down_sign();
    bool first_fall_down_key;
};

class tile{
private:
    int width, height;
public:
    myTexture maptexture[numoftiles];
   //int maparr[8][10];
    tile();
    void getmap(string);
    void loadmap();
    void rendermap(int *, int *);
    int getground(int, int*, int*, int);
    void changemap(myTexture*, int, int*, int* , monster arr[30], boss*);
    void reset();
};

static mymixer monstermix;
static tile gamemap;
static myTexture mytexture;
static myTexture bgtexture;
static myTexture texttexture;
static myTexture monster_fire_texture;
static character knight;
static monster mymonster;
static myTexture heathtexture;
static myTexture manatexture;
static myTexture emptybartexture;
static myTexture starttexture1;
static myTexture starttexture2;
static myTexture musicontexture;
static myTexture musicofftexture;
static myTexture musictexture;
static myTexture endtexture;
static boss myboss;


static monster monster_arr[30];


static mymixer mymix;

bool init();
void updatescreen();
bool createrenderwindow(string);
void windowhandle(SDL_Event* ,int*, int*, int *, int*);
void clearscreen();
void close();
void getquit();
void setviewport(int, int , int , int);
SDL_Point mouseevent(SDL_Event*);
void inputtext(SDL_Event* ,string*,long long);
void mixinput(SDL_Event*);
bool collision(SDL_Rect , SDL_Rect );
void loadmonsterpos(int *,int *, int, monster arr[30]);
void loadmonster_image(string , monster arr[30]);
void rendermonster(monster arr[30], int, int);
void monsters_falldown(monster arr[30] ,SDL_Texture* frame_arr[num_of_monster_frame],SDL_Texture* farr[num_of_monster_fire_frame], SDL_Texture* atarr[num_of_monster_attack_frame], SDL_Texture* deadarr[num_of_monster_dead_frame]);
void get_main_posx(int x);
void delete_arr(monster arr[30], int x);
void check_dead_condition(boss*, monster arr[30],  character* );
void fixmonsterbullet(monster arr[30], SDL_Event* , character* );
void display_heath_and_mana(character*, boss*, monster arr[30], myTexture*, myTexture*, myTexture*);
void check_main_hp(character* ,monster arr[30], boss* );
void start(SDL_Event*,myTexture* ,myTexture*, myTexture*, myTexture*, myTexture*,myTexture*, myTexture*, int*, mymixer*);
void gameover(boss*, tile *,monster arr[30],character* ,SDL_Event *, myTexture*,  myTexture*, myTexture*, int*);

#endif // MYLIB_H_INCLUDED
