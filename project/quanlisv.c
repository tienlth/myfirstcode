#include <stdio.h>
#include <C:\Users\ASUS\Documents\myfirstcode\project\linkedlist.c>
#include <string.h>

void readList(List*);
void printList(List );

void replace(ElementType a, Position *b){
    insertList(a,*b);
    deleteList(Next(*b));

}

void swap(Position *a, Position *b){
    ElementType x=Retrieve(*a);
    ElementType y=Retrieve(*b);
    replace(x,b);
    replace(y,a);
}

void sort(List *L){
    Position p=First(*L);
    Position q;
    while(p!=Previous(End(*L), *L)){
        q=Next(p);
        while(q!=End(*L)){
            if(Retrieve(p).MaSo>Retrieve(q).MaSo) swap(&p,&q);
            q=Next(q);
        }
        p=Next(p);
    }
}

int main(){
    List L;
    makenullList(&L);
    readList(&L);
    sort(&L);
    printList(L);

return 0;
}

void readList(List* L){
    ElementType t;
    int n, i;
    printf("Moi nhap so luong phan tu cua danh sach");
    scanf("%d",&n);
    for(i=1;i<=n;i++){
        printf("\nMoi nhap ho ten sinh vien thu %d: ",i);
        fflush(stdin);
        fgets(t.HoTen, 25, stdin);
        t.HoTen[strlen(t.HoTen)-1]='\0';
        printf("Moi nhap ma so sinh vien sinh vien thu %d: ",i);
        scanf("%d",&t.MaSo);
        printf("Moi nhap diem trung binh sinh vien sinh vien thu %d: ",i);
        scanf("%f",&t.DiemTrungBinh);
        insertList(t,End(*L));
    }
}

void printList(List L){
    if(!EmptyList(L)){
        int i, stt=1;
        printf("\n%60s\n","DANH SACH SINH VIEN");
        for(i=0;i<105;i++){
            printf("-");
        }
        printf("\n|%-10s|%-30s|%-30s|%-30s|", "STT", "Ho ten", "Ma So Sinh Vien", "Diem Trung Binh");
        Position pos=First(L);
        while(pos!=End(L)){
            printf("\n|%-10d|%-30s|%-30d|%-30.2f|",stt++,Retrieve(pos).HoTen, Retrieve(pos).MaSo, Retrieve(pos).DiemTrungBinh);
            pos=Next(pos);
        }
        printf("\n");
        for(i=0;i<105;i++){
            printf("-");
        }
    }
    else printf("\nDanh sach trong!");
}

