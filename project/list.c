#include <stdio.h>
#include <string.h>

#define MAX_LENGHT 100

typedef struct {
    char Ho_Ten[25];
    int Ma_So;
    float Diem_Tb;
}Sinh_Vien;

typedef Sinh_Vien Element_Type;
typedef int Position;

typedef struct {
    Element_Type Element_Array[MAX_LENGHT];
    int Last;
}List;

Position First_List(List );
Position End_List(List );
void Make_NULL_List(List* );
int Empty_List(List );
Element_Type Retrieve(List , Position);
Position Locate(List , Element_Type);
Position Next(List , Position );
Position Previous(List , Position );
int Compare_Element(Element_Type, Element_Type);
void Insert_List(List* , Position, Element_Type);
void Assignment(Element_Type* , Element_Type );
void Delete_List(List* , Position);
void Read_List(List* );
void Print_List(List );

int main(){

    List l;
    Make_NULL_List(&l);
    Read_List(&l);
    Print_List(l);

return 0;
}

void Make_NULL_List(List *L){
    L->Last=0;
}

Position First_List(List L){
    return 1;
}

Position End_List(List L){
    return L.Last+1;
}

int Empty_List(List L){
    return L.Last==0;
}

Element_Type Retrieve(List L, Position p){
    return L.Element_Array[p-1];
}

Position Next(List L, Position p){
    if(p<First_List(L) || p>L.Last){
        printf("Vi tri khong hop le!\n");
    }
    else return p+1;
}

Position Previous(List L, Position p){
    if(p<First_List(L) || p>L.Last){
        printf("Vi tri khong hop le!\n");
    }
    else return p-1;
}

void Assignment(Element_Type *a, Element_Type b){
    strcpy(a->Ho_Ten, b.Ho_Ten);
    a->Ma_So = b.Ma_So;
    a->Diem_Tb = b.Diem_Tb;
}

int Compare_Element(Element_Type a, Element_Type b){
    if(a.Ma_So==b.Ma_So && a.Diem_Tb==b.Diem_Tb && strcmp(a.Ho_Ten, b.Ho_Ten)==0)
        return 1;
    else return 0;
}

Position Locate(List L, Element_Type x){
    int Found=0;
    Position p=First_List(L);
    while(p!=End_List(L) && !Found){
        if(Compare_Element(Retrieve(L, p),x)) Found = 1;
        else p=Next(L, p);
    }
    return p;
}

void Insert_List(List *L, Position p, Element_Type x){
    if(L->Last==MAX_LENGHT) printf("Danh sach da day!\n");
    else if(p<First_List(*L) || p>End_List(*L)){
        printf("Vi tri khong hop le!\n");
    }
    else{
        Position q = End_List(*L);
        while(q>p){
            Assignment(&L->Element_Array[q-1], Retrieve(*L, q-1));
            q=Previous(*L, q);
        }
        Assignment(&L->Element_Array[p-1], x);
        ++L->Last;
    }
}

void Delete_List(List* L, Position p){
    if(L->Last==MAX_LENGHT) printf("Danh sach da day!\n");
    else if(p<First_List(*L) || p>L->Last){
        printf("Vi tri khong hop le!\n");
    }
    else{
        Position q = p;
        while(q<L->Last){
            Assignment(&L->Element_Array[q-1], Retrieve(*L, q+1));
            q=Next(*L, q);
        }
        --L->Last;
    }
}

void Read_List(List *L){
    printf("vui long nhap so luong sinh vien cua danh sach! ");
    int n, i;
    Element_Type sv;
    scanf("%d",&n);
    for(i=1;i<=n;i++){
        printf("\nmoi nhap sinh vien thu %d:\n",i);
        fflush(stdin);
        printf("moi nhap ho ten: ");
        fgets(sv.Ho_Ten, 25, stdin);
        sv.Ho_Ten[strlen(sv.Ho_Ten)-1]='\0';
        printf("moi nhap ma so sinh vien: ");
        scanf("%d",&sv.Ma_So);
        printf("moi nhap diem trung binh: ");
        scanf("%f",&sv.Diem_Tb);
        Insert_List(L, End_List(*L),sv);
    }
}

void Print_List(List L){
    if(!Empty_List(L)){
        int i;
        printf("\n%60s\n","DANH SACH SINH VIEN");
        for(i=0;i<105;i++){
            printf("-");
        }
        printf("\n|%-10s|%-30s|%-30s|%-30s|", "STT", "Ho ten", "Ma So Sinh Vien", "Diem Trung Binh");
        Position pos=First_List(L);
        for(;pos<=L.Last;pos=Next(L, pos)){
            printf("\n|%-10d|%-30s|%-30d|%-30.2f|",pos, Retrieve(L, pos).Ho_Ten, Retrieve(L, pos).Ma_So, Retrieve(L, pos).Diem_Tb);
        }
        printf("\n");
        for(i=0;i<105;i++){
            printf("-");
        }
    }
    else printf("\nDanh sach trong!");
}
