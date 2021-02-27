#include <stdio.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define MAXLEN 100
#define	BODY 219
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

int score=0;
int huong=RIGHT;
int oldstatus=RIGHT;
typedef struct{
	int energy;
	int mode;
}skill;
skill speed;
typedef struct{
	int x;
	int y;
}toado;
typedef struct{
	toado left;
	toado right;
}snakebody;
snakebody snake[MAXLEN];
snakebody tail;
snakebody food;

int len=3;
void drawwall();
void resizeConsole(int, int);
void gotoxy(int ,int);
void Nocursortype();
void setsnake(int, int);
void displaysnake();
void move();
void SetColor(WORD);
void event();
int testlose();
void deletetail();
void createfood();
int testeat();
void runspeed();
void writescore();
int main(){
	int i;
	resizeConsole(3000,3000);
	while(1){
	system("CLS");
	drawwall();
	setsnake(6,2);
	createfood();
	while(1){
		event();
		move();
		if(testlose()==0) break;
		displaysnake(snake);
		deletetail();
		if(testeat()){
			createfood();
		}
		writescore();
		Nocursortype();
		runspeed();
	}
	writescore();
	getch();
	}
	return 0;
}
void SetColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}
void gotoxy(int x, int y)
{
  static HANDLE h = NULL;
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };
  SetConsoleCursorPosition(h,c);
}
void Nocursortype()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
void drawwall(){
	SetColor(11);
	int i;
	for(i=1;i<43;i++){
		gotoxy(166,i);
		printf("%c",(char)BODY);
	}
	for(i=1;i<43;i++){
		gotoxy(1,i);
		printf("%c",(char)BODY);
	}
	for(i=1;i<167;i++){
		gotoxy(i,0);
		printf("%c",(char)220);
	}
	for(i=1;i<167;i++){
		gotoxy(i,43);
		printf("%c",(char)223);
	}
	for(i=1;i<43;i++){
		gotoxy(150,i);
		printf("%c",(char)BODY);
	}
}
void setsnake(int X,int Y){
	len=3;
	score=0;
	oldstatus=RIGHT;
	huong=RIGHT;
	speed.energy=0;
	snake[0].left.x=X;
	snake[0].left.y=Y;
	snake[1].left.x=snake[0].left.x-2;
	snake[1].left.y=snake[0].left.y;
	snake[2].left.x=snake[1].left.x-2;
	snake[2].left.y=snake[1].left.y;

	snake[0].right.x=X+1;
	snake[0].right.y=Y;
	snake[1].right.x=snake[0].right.x-2;
	snake[1].right.y=snake[0].right.y;
	snake[2].right.x=snake[1].right.x-2;
	snake[2].right.y=snake[1].right.y;
}
void displaysnake(){
	int i;
	SetColor(12);
	for(i=0;i<len;i++){
		gotoxy(snake[i].left.x,snake[i].left.y);
		printf("%c",BODY);
		gotoxy(snake[i].right.x,snake[i].right.y);
		printf("%c",BODY);
	}
}
void event(){
	char key;
	if(kbhit()){
        key = getch();
	        switch(key){
			case 100:
				huong=RIGHT;
				break;
			case 97:
				huong=LEFT;
				break;
			case 119:
				huong=UP;
				break;
			case 115:
				huong=DOWN;
				break;
		}
    }
}
void move(){
	int i;
	tail.left.x=snake[len-1].left.x;
	tail.left.y=snake[len-1].left.y;
	tail.right.x=snake[len-1].right.x;
	tail.right.y=snake[len-1].right.y;
	for(i=len-1;i>0;i--){
		snake[i].left.x=snake[i-1].left.x;
		snake[i].left.y=snake[i-1].left.y;
		snake[i].right.x=snake[i-1].right.x;
		snake[i].right.y=snake[i-1].right.y;
	}
		switch(huong){
		case 2:
			if(oldstatus!=LEFT) {
				snake[0].left.x+=2;
				snake[0].right.x+=2;
				oldstatus=huong;
			}
			else {
				snake[0].left.x-=2;
				snake[0].right.x-=2;
				huong=LEFT;
			}
			break;
		case 4:
			if(oldstatus!=RIGHT){
				 snake[0].left.x-=2;
				 snake[0].right.x-=2;
				 oldstatus=huong;
			}
			else {
				huong=RIGHT;
				snake[0].left.x+=2;
				snake[0].right.x+=2;
			}
			break;
		case 1:
			if(oldstatus!=DOWN) {
				snake[0].left.y--;
				snake[0].right.y--;
				oldstatus=huong;
			}
			else {
				snake[0].left.y++;
				snake[0].right.y++;
				huong=UP;
			}
			break;
		case 3:
		if(oldstatus!=UP) {
				snake[0].left.y++;
				snake[0].right.y++;
				oldstatus=huong;
			}
			else {
				snake[0].left.y--;
				snake[0].right.y--;
				huong=DOWN;
			}
			break;
	}
}
void deletetail(){
	gotoxy(tail.left.x,tail.left.y);
	printf(" ");
	gotoxy(tail.right.x,tail.right.y);
	printf(" ");
}
int testlose(){
	int i,a,b,c,d,h1,h2,h3,h4;
	h1=snake[0].left.x;
	h2=snake[0].left.y;
	h3=snake[0].right.x;
	h4=snake[0].right.y;
	for(i=1;i<len;i++){
		a=snake[i].left.x;
		b=snake[i].left.y;
		c=snake[i].right.x;
		d=snake[i].right.y;
		if((a==h1&&b==h2)||(a==h3&&b==h4)||(c==h1&&d==h2)){
			return 0;
		}
	}
	if(snake[0].left.x<1||snake[0].right.x>149||snake[0].left.y<1||snake[0].left.y>42)
		return 0;
	else return 1;
}
void createfood(){
	int i;
	srand(time(NULL));
	food.left.x=2+rand()%148;
	food.left.y=2+rand()%41;
	food.right.x=food.left.x+1;
	food.right.y=food.left.y;
	if(score%4==0&&score>0) {
		speed.mode=1;
		SetColor(50);
	}
	else {
		SetColor(20);
		speed.mode=0;
	}
	gotoxy(food.left.x,food.left.y);
	printf("%c",BODY);
	gotoxy(food.right.x,food.right.y);
	printf("%c",BODY);
}
int testeat(){
	int a=snake[0].left.x;
	int b=snake[0].left.y;
	int c=snake[0].right.x;
	int d=snake[0].right.y;
	int f1=food.left.x;
	int f2=food.left.y;
	int f3=food.right.x;
	int f4=food.right.y;
	if((a==f3&&b==f4)||(c==f1&&d==f2)||(a==f1&&b==f2)){
		score++;
		if(speed.mode==1) speed.energy=100;
		len++;
		if((a==f3&&b==f4)){
			gotoxy(f1,f2);
			printf(" ");
		}
		if((c==f1&&d==f2)){
			gotoxy(f3,f4);
			printf(" ");
		}
		if((a==f1&&b==f2)||((a==f3&&b==f4)&&huong==LEFT)||((c==f1&&d==f2)&&huong==RIGHT)){
			gotoxy(food.left.x,food.left.y);
			printf("%c",BODY);
			gotoxy(food.right.x,food.right.y);
			printf("%c",BODY);
		}
		return 1;
	}
	else return 0;
}
void runspeed(){
	if(speed.energy>0){
			Sleep(50);
			speed.energy--;
		}
		else
			Sleep(150);
	}
void writescore(){
	int i;
	SetColor(30);
	for(i=160;i<=163;i++){
		gotoxy(i,2);
		printf(" ");
	}
	gotoxy(152,2);
	printf("Score: %d",score);
	if(testlose()==0){
			gotoxy(153,20);
			printf("game over");
	}
}

