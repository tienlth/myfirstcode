#include <stdio.h>
#include <string.h>

#define MAXLENGHT 100

typedef struct{
    int n;
    char A, B, C;
}colum;

typedef struct{
    int MaSo;
    char HoTen[25];
    float DiemTrungBinh;
}SinhVien;
typedef int ElementType;
typedef struct{
    ElementType Elements[MAXLENGHT];
    int Top_index;
}Stack;

//int Equal(ElementType a, ElementType b){
//    return a.MaSo==b.MaSo&&strcmp(a.HoTen, b.HoTen)==0&&a.DiemTrungBinh==b.DiemTrungBinh;
//}

void makenullStack(Stack* s){
    s->Top_index=MAXLENGHT;
}

int EmptyStack(Stack s){
    return s.Top_index==MAXLENGHT;
}

int FullStack(Stack s){
    return s.Top_index==0;
}

ElementType Top(Stack s){
    if(!EmptyStack(s)) return s.Elements[s.Top_index];
    else printf("LOI! NGAN XEP RONG");
}

void Pop(Stack *s){
    if(!EmptyStack(*s)){
        ++s->Top_index;
    }
    else printf("LOI!NGAN XEP RONG");
}

void Push(ElementType x, Stack *s){
    if(!FullStack(*s)){
        s->Elements[--s->Top_index]=x;
    }
    else printf("LOI! NGAN XEP DAY");
}





