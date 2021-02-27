#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char HoTen[25];
    int MaSo;
    float DiemTrungBinh;

}SinhVien;

typedef SinhVien ElementType;

struct Node{
    ElementType Element;
    struct Node* Next;
};

typedef struct Node* Position;
typedef struct Node* List;

void makenullList(List* Header){
    (*Header) = (List*)malloc(sizeof(struct Node));
    (*Header)->Next=NULL;
}

int EmptyList(List L){
    return L->Next==NULL;
}

int Equal(ElementType a, ElementType b){
    return (a.MaSo==b.MaSo && !strcmp(a.HoTen, b.HoTen) && a.DiemTrungBinh==b.DiemTrungBinh);
}
Position Next(Position p){
    if(p->Next!=NULL) return p->Next;
}

Position Previous(Position p, List Header){
    Position q = Header;
    int found=0;
    while(q->Next!=NULL && !found){
        if(q->Next==p) found=1;
        else q=Next(q);
    }
    return q;
}

Position First(List Header){
    return Header;
}

Position End(List Header){
    Position p = Header;
    while(p->Next!=NULL ){
        p=Next(p);
    }
    return p;
}

ElementType Retrieve(Position p){
    if(p->Next!=NULL){
        return p->Next->Element;
    }
}

Position locate(ElementType x, List Header){
    Position p = Header;
    int found=0;
    while(p->Next!=NULL && !found){
        if(Equal(x,Retrieve(p))){
            found=1;
        }
        else p=Next(p);
    }
    return p;
}

void insertList(ElementType x, Position p){
        List q;
        q=(List)malloc(sizeof(struct Node));
        q->Element=x;
        q->Next=p->Next;
        p->Next=q;
}

void deleteList(Position p){
    if(p->Next!=NULL){
        p->Next=p->Next->Next;
    }
    else p->Next=NULL;
}




