#include <stdio.h>
#include <C:\Users\ASUS\Documents\myfirstcode\project\stacklib.c>

int main(){
//    Stack s;
//    makenullStack(&s);
//    readStack(&s);
//    printStack(s);
//move(3,'A','B','C');
d2b(10);
return 0;
}
//void readStack(Stack *s){
//   int n;
//   ElementType t;
//   printf("moi nhap so luong sinh vien: ");
//   scanf("%d",&n);
//   for(int i=1;i<=n;i++){
//        printf("\nMoi nhap ho ten sinh vien thu %d: ",i);
//        fflush(stdin);
//        fgets(t.HoTen, 25, stdin);
//        t.HoTen[strlen(t.HoTen)-1]='\0';
//        printf("Moi nhap ma so sinh vien sinh vien thu %d: ",i);
//        scanf("%d",&t.MaSo);
//        printf("Moi nhap diem trung binh sinh vien sinh vien thu %d: ",i);
//        scanf("%f",&t.DiemTrungBinh);
//        Push(t,s);
//   }
//}
//void printStack(Stack s){
//    if(!EmptyStack(s)){
//        int i,stt=1;
//        printf("\n%60s\n","DANH SACH SINH VIEN");
//        for(i=0;i<105;i++){
//            printf("-");
//        }
//        printf("\n|%-10s|%-30s|%-30s|%-30s|", "STT", "Ho ten", "Ma So Sinh Vien", "Diem Trung Binh");
//        while(!EmptyStack(s)){
//            printf("\n|%-10d|%-30s|%-30d|%-30.2f|",stt++,Top(s).HoTen,Top(s).MaSo, Top(s).DiemTrungBinh);
//            Pop(&s);
//        }
//        printf("\n");
//        for(i=0;i<105;i++){
//            printf("-");
//        }
//    }
//    else printf("LOI! DANH SACH RONG");
//}

//void move(int n, char A, char B, char C){
//    ElementType tmp, tmp1;
//    tmp.n=n;
//    tmp.A=A;
//    tmp.B=B;
//    tmp.C=C;
//    Stack s;
//    makenullStack(&s);
//    Push(tmp,&s);
//    while(!EmptyStack(s)){
//        tmp=Top(s);
//        Pop(&s);
//        if(tmp.n==1) printf("chuyen %c->%c\n",tmp.A,tmp.C);
//        else{
//            tmp1.n=tmp.n-1;
//            tmp1.A=tmp.C;
//            tmp1.B=tmp.B;
//            tmp1.C=tmp.A;
//            Push(tmp1,&s);
//
//            tmp1.n=1;
//            tmp1.A=tmp.A;
//            tmp1.B=tmp.B;
//            tmp1.C=tmp.C;
//            Push(tmp1,&s);
//
//            tmp1.n=tmp.n-1;
//            tmp1.A=tmp.A;
//            tmp1.B=tmp.C;
//            tmp1.C=tmp.B;
//            Push(tmp1,&s);
//        }
//    }
//}

void d2b(int n){
    if(n<2) printf("%d",n);
    else{
        Stack s;
        makenullStack(&s);
        while(n>0){
            Push(n%2,&s);
            n/=2;
        }
        while(!EmptyStack(s)){
            printf("%d",Top(s));
            Pop(&s);
        }
    }
}
