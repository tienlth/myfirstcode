#include <stdio.h>
#include <string.h>
#include <C:\Users\ASUS\Documents\myfirstcode\project\queuelib.c>

void readQueue(Queue *Q);
void printQueue(Queue Q);
int main(){
    Queue Q;
    makenullQueue(&Q);
    readQueue(&Q);
    printQueue(Q);
return 0;
}

void readQueue(Queue *Q){
    int n,i;
    ElementType tmp;
    printf("moi nhap so luong sinh vien");
    scanf("%d",&n);
    for(i=1;i<=n;i++){
        printf("moi nhap sinh vien thu %d:",i);
        printf("\nmoi nhap ma so sinh vien thu %d: ",i);
        scanf("%d",&tmp.MSSV);
        printf("moi nhap ho va ten sinh vien thu %d: ",i);
        fflush(stdin);
        fgets(tmp.HoTen,25,stdin);
        tmp.HoTen[strlen(tmp.HoTen)-1]='\0';
        printf("moi nhap diem trung binh sinh vien thu %d: ",i);
        scanf("%f",&tmp.DiemTrungBinh);

        EnQueue(tmp,Q);
    }
}

void printQueue(Queue Q){

    if(!EmptyQueue(Q)){
        int i;
        int stt=0;
        printf("\n%60s\n","DANH SACH SINH VIEN");
        for(i=0;i<105;i++){
            printf("-");
        }
        printf("\n|%-10s|%-30s|%-30s|%-30s|", "STT", "Ho ten", "Ma So Sinh Vien", "Diem Trung Binh");
        for(i=Q.Front;i<=Q.Rear;i++){
            printf("\n|%-10d|%-30s|%-30d|%-30.2f|",++stt,Q.Elements[i].HoTen,Q.Elements[i].MSSV,Q.Elements[i].DiemTrungBinh);
        }
        printf("\n");
        for(i=0;i<105;i++){
            printf("-");
        }
    }
    else printf("Hang Rong");
}
