#include <stdio.h>
#define MAXLENGHT 100
typedef struct {
    char HoTen[25];
    int MSSV;
    float DiemTrungBinh;
}SinhVien;

typedef SinhVien ElementType;
typedef struct {
    ElementType Elements[MAXLENGHT];
    int Front;
    int Rear;
}Queue;

void makenullQueue(Queue *Q){
    Q->Front=-1;
    Q->Rear=-1;
}

int FullQueue(Queue Q){
    return (Q.Rear-Q.Front+1)==MAXLENGHT;
}

int EmptyQueue(Queue Q){
    return Q.Front==-1;
}

void deQueue(Queue *Q){
    if(!EmptyQueue(*Q)){
        ++Q->Front;
        if(Q->Front>Q->Rear) makenullQueue(Q);
    }
    else printf("Hang Rong!");
}

void EnQueue(ElementType x, Queue *Q){
    if(!FullQueue(*Q)){
        if(Q->Rear==MAXLENGHT-1){
            int i;
            for(i=Q->Front;i<=Q->Rear;i++){
                Q->Elements[i-Q->Front]=Q->Elements[i];
            }
            Q->Rear=Q->Rear-Q->Front;
            Q->Front=0;
        }
        ++Q->Rear;
        Q->Elements[Q->Rear]=x;
        if(EmptyQueue(*Q)) Q->Front=0;
    }
    else printf("Hang Day!");
}
