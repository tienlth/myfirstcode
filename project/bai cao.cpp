#include <iostream>
#include <string>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
using namespace std;

struct bai{
	int chat;
	int nut;
	int numOfBoBai;
};
bai boBai[52];
int batsukien=0;
struct player{
	bai baiTrenTay[3];
	int toaDoBai[3][2];
	string name;
	int sonut(){
		return baiTrenTay[0].nut+baiTrenTay[1].nut+baiTrenTay[2].nut;
	}
};
 	player player[4];
void chiabai();
void setplayer();
void settoadobai();
void hienthi();
void hienthibaiup(int , int);
void hienthibaingua();
void hienthichatbai(int , int, int);
void hienthiplayer(int , int);
void gotoxy(int x, int y);
void Nocursortype();
void setbobai(bai boBai[]){
	int count=1;

	for(int i=0;i<52;i++){
		switch((i+1)%4){
			case 1: boBai[i].chat = 1; //bich
			break;
			case 2: boBai[i].chat = 2;//chuon
			break;
			case 3: boBai[i].chat = 3;//ro
			break;
			case 0: boBai[i].chat = 4;//co
			break;
	}
}
	for(int l=0;l<40;l++){
		boBai[l].nut=count;
		if(boBai[l].chat==4){
			++count;
		}
	}
		for(int p=40;p<

		52;p++){
		boBai[p].nut=0;
	}
}
 	int key;
int main(){
	Nocursortype();
	setbobai(boBai);
	setplayer();
	settoadobai();
	while(1){
	chiabai();
	hienthi();
}
//	getch();
	return 0;
}
	void chiabai( ){
	int tmp;
	srand(time(NULL));
//	for(int i=0;i<=2;i++){
//		tmp=rand()%52;
//		while(boBai[tmp].nut==11){
//		tmp=rand()%52;
//	}
//	    player[0].baiTrenTay[i].numOfBoBai=tmp;
//		player[0].baiTrenTay[i].nut=boBai[tmp].nut;
//		player[0].baiTrenTay[i].chat=boBai[tmp].chat;
//		boBai[tmp].nut=11;
//	}
//	for(int i=0;i<=2;i++){
//		tmp=rand()%52;
//		while(boBai[tmp].nut==11){
//		tmp=rand()%52;
//	}
//	    player[1].baiTrenTay[i].numOfBoBai=tmp;
//		player[1].baiTrenTay[i].nut=boBai[tmp].nut;
//		player[1].baiTrenTay[i].chat=boBai[tmp].chat;
//		boBai[tmp].nut=11;
//	}
	for(int k=0;k<=3;k++){
		for(int i=0;i<=2;i++){
		tmp=rand()%52;
		while(boBai[tmp].nut==11){
		tmp=rand()%52;
	}
	    player[k].baiTrenTay[i].numOfBoBai=tmp;
		player[k].baiTrenTay[i].nut=boBai[tmp].nut;
		player[k].baiTrenTay[i].chat=boBai[tmp].chat;
		boBai[tmp].nut=11;
	}
	}

//	for(int i=0;i<=2;i++){
//		tmp=rand()%52;
//		while(boBai[tmp].nut==11){
//		tmp=rand()%52;
//	}
//	    player[3].baiTrenTay[i].numOfBoBai=tmp;
//		player[3].baiTrenTay[i].nut=boBai[tmp].nut;
//		player[3].baiTrenTay[i].chat=boBai[tmp].chat;
//		boBai[tmp].nut=11;
//	}

}
	void setplayer(){
		player[0].name="Long Tu";
		player[1].name="Thach Chi Khang";
		player[2].name="Chau nhuan phat";
		player[3].name="Nhiep Van Long";

	}
	void hienthi(){
		for(int i=1;i<118;i++){
			gotoxy(i,0);
			cout<< char(220);
			gotoxy(i,29);
			cout<< char(223);
		}
		for(int i=1;i<29;i++){
			gotoxy(1,i);
			cout<< char(221);
			gotoxy(117,i);
			cout<< char(222);
		}
		key=getch();  //bat su kien ban phim
		hienthiplayer(6,12);
		hienthiplayer(105,12);
		hienthiplayer(56,3);
		hienthiplayer(56,22);
	}
	void hienthiplayer(int a , int b){
		int dem=8;
		int array[22][2];
		array[0][0]=a+3;
		array[0][1]=b;
		array[1][0]=a+4;
		array[1][1]=b;
		array[2][0]=a+2;
		array[2][1]=b+1;
		array[3][0]=a+5;
		array[3][1]=b+1;
		array[4][0]=a+2;
		array[4][1]=b+2;
		array[5][0]=a+5;
		array[5][1]=b+2;
		array[6][0]=a;
		array[6][1]=b+4;
		array[7][0]=a+7;
		array[7][1]=b+4;
		for(int i=1;i<=6;i++){
			array[dem][0]=a+i;
			array[dem][1]=b+3;
			dem++;
		}
		for(int j=0;j<=8;j++){
			array[dem][0]=a+j;
			array[dem][1]=b+5;
			dem++;
		}
		if(key==13){
		for(int i=0;i<22;i++){
		   gotoxy(array[i][0],array[i][1]);
		   cout<< "*";
		}
		gotoxy(6,18);
		cout<<player[0].name;
		gotoxy(102,18);
		cout<<player[1].name;
		gotoxy(56,9);
		cout<<player[2].name;
		gotoxy(51,28);
		cout<<player[3].name;
	}
		if(key==32){
		hienthibaiup(player[0].toaDoBai[0][0], player[0].toaDoBai[0][1]);
		hienthibaiup(player[0].toaDoBai[1][0], player[0].toaDoBai[1][1]);
		hienthibaiup(player[0].toaDoBai[2][0], player[0].toaDoBai[2][1]);
		hienthibaiup(player[1].toaDoBai[0][0], player[1].toaDoBai[0][1]);
		hienthibaiup(player[1].toaDoBai[1][0], player[1].toaDoBai[1][1]);
		hienthibaiup(player[1].toaDoBai[2][0], player[1].toaDoBai[2][1]);
		hienthibaiup(player[2].toaDoBai[0][0], player[2].toaDoBai[0][1]);
		hienthibaiup(player[2].toaDoBai[1][0], player[2].toaDoBai[1][1]);
		hienthibaiup(player[2].toaDoBai[2][0], player[2].toaDoBai[2][1]);
		hienthibaiup(player[3].toaDoBai[0][0], player[3].toaDoBai[0][1]);
		hienthibaiup(player[3].toaDoBai[1][0], player[3].toaDoBai[1][1]);
		hienthibaiup(player[3].toaDoBai[2][0], player[3].toaDoBai[2][1]);
		}
		if(key==97){
			hienthibaingua();
		}
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
void hienthibaiup(int x, int y){
	gotoxy(x,y);
	for(int i=1;i<9;i++){
		gotoxy(x,y+i);
		for(int j=1;j<=7;j++){
			cout<< "*";
		}
	}
}
void settoadobai(){
	player[0].toaDoBai[0][0]=31;
	player[0].toaDoBai[0][1]=1;
	player[0].toaDoBai[1][0]=39;
	player[0].toaDoBai[1][1]=1;
	player[0].toaDoBai[2][0]=47;
	player[0].toaDoBai[2][1]=1;
	player[1].toaDoBai[0][0]=16;
	player[1].toaDoBai[0][1]=14;
	player[1].toaDoBai[1][0]=24;
	player[1].toaDoBai[1][1]=14;
	player[1].toaDoBai[2][0]=32;
	player[1].toaDoBai[2][1]=14;
	player[2].toaDoBai[0][0]=66;
	player[2].toaDoBai[0][1]=20;
	player[2].toaDoBai[1][0]=74;
	player[2].toaDoBai[1][1]=20;
	player[2].toaDoBai[2][0]=82;
	player[2].toaDoBai[2][1]=20;
	player[3].toaDoBai[0][0]=80;
	player[3].toaDoBai[0][1]=6;
	player[3].toaDoBai[1][0]=88;
	player[3].toaDoBai[1][1]=6;
	player[3].toaDoBai[2][0]=96;
	player[3].toaDoBai[2][1]=6;
}
void hienthibaingua(){
		for(int i=0;i<=3;i++){
			for(int j=0;j<=2;j++){
				for(int p=1;p<=6;p++){
					gotoxy(player[i].toaDoBai[j][0]+1,player[i].toaDoBai[j][1]+1+p);
					for(int o=1;o<=5;o++){
				cout<<" ";
					}
				}
			gotoxy(player[i].toaDoBai[j][0]+1,player[i].toaDoBai[j][1]+2);
			if(player[i].baiTrenTay[j].numOfBoBai<40){
			cout<<player[i].baiTrenTay[j].nut;
				}
			else if(player[i].baiTrenTay[j].numOfBoBai>=40&&player[i].baiTrenTay[j].numOfBoBai<=43){
				cout<<"J";
				}
			else if(player[i].baiTrenTay[j].numOfBoBai>=44&&player[i].baiTrenTay[j].numOfBoBai<=47){
				cout<<"Q";
				}
			else{
				cout<<"K";
				}
			hienthichatbai(player[i].baiTrenTay[j].chat,player[i].toaDoBai[j][0]+1,player[i].toaDoBai[j][1]+2);
			}
		}
	}
void hienthichatbai(int chatbai,int a,int b){
	int bich[11][2];
	int chuon[11][2];
	int ro[8][2];
	int co[8][2];
	bich[0][0]=a+2;
	bich[0][1]=b;
	bich[1][0]=a+1;
	bich[1][1]=b+1;
	bich[2][0]=a+3;
	bich[2][1]=b+1;
	bich[3][0]=a;
	bich[3][1]=b+2;
	bich[4][0]=a+4;
	bich[4][1]=b+2;
	bich[5][0]=a+1;
	bich[5][1]=b+3;
	bich[6][0]=a+3;
	bich[6][1]=b+3;
	bich[7][0]=a+2;
	bich[7][1]=b+4;
	bich[8][0]=a+1;
	bich[8][1]=b+5;
	bich[9][0]=a+2;
	bich[9][1]=b+5;
	bich[10][0]=a+3;
	bich[10][1]=b+5;
	chuon[0][0]=a+2;
	chuon[0][1]=b;
	chuon[1][0]=a+1;
	chuon[1][1]=b+1;
	chuon[2][0]=a+3;
	chuon[2][1]=b+1;
	chuon[3][0]=a;
	chuon[3][1]=b+2;
	chuon[4][0]=a+2;
	chuon[4][1]=b+2;
	chuon[5][0]=a+4;
	chuon[5][1]=b+2;
	chuon[6][0]=a+1;
	chuon[6][1]=b+3;
	chuon[7][0]=a+3;
	chuon[7][1]=b+3;
	chuon[8][0]=a+1;
	chuon[8][1]=b+4;
	chuon[9][0]=a+2;
	chuon[9][1]=b+4;
	chuon[10][0]=a+3;
	chuon[10][1]=b+4;
	ro[0][0]=a+2;
	ro[0][1]=b;
	ro[1][0]=a+1;
	ro[1][1]=b+1;
	ro[2][0]=a+3;
	ro[2][1]=b+1;
	ro[3][0]=a;
	ro[3][1]=b+2;
	ro[4][0]=a+4;
	ro[4][1]=b+2;
	ro[5][0]=a+1;
	ro[5][1]=b+3;
	ro[6][0]=a+3;
	ro[6][1]=b+3;
	ro[7][0]=a+2;
	ro[7][1]=b+4;
	co[0][0]=a+1;
	co[0][1]=b;
	co[1][0]=a+3;
	co[1][1]=b;
	co[2][0]=a;
	co[2][1]=b+1;
	co[3][0]=a+2;
	co[3][1]=b+1;
	co[4][0]=a+4;
	co[4][1]=b+1;
	co[5][0]=a+1;
	co[5][1]=b+2;
	co[6][0]=a+3;
	co[6][1]=b+2;
	co[7][0]=a+2;
	co[7][1]=b+3;
	if(chatbai==1){
		for(int i=0;i<=10;i++){
			gotoxy(bich[i][0],bich[i][1]);
			cout<<"*";
		}
	}
	if(chatbai==2){
		for(int i=0;i<=10;i++){
			gotoxy(chuon[i][0],chuon[i][1]);
			cout<<"*";
		}
	}
		if(chatbai==3){
		for(int i=0;i<=7;i++){
			gotoxy(ro[i][0],ro[i][1]);
			cout<<"*";
		}
	}
		if(chatbai==4){
		for(int i=0;i<=7;i++){
			gotoxy(co[i][0],co[i][1]);
			cout<<"*";
		}
	}
}



