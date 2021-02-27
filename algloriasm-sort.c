#include <stdio.h>
#include <string.h>

typedef struct {
    int soBaoDanh;
    char hoTen[50];
    float d1, d2, d3;
}sinhVien;

void swap(sinhVien *a, sinhVien *b){
    sinhVien tmp=*a;
    *a=*b;
    *b=tmp;
}

void bubbleSort(sinhVien List[], int n){
    int i, j;
    for(i=0;i<n-1;i++){
        for(j=n-1;j>i;j--){
           if(strcmp(List[j].hoTen, List[j-1].hoTen)<0)
                swap(&List[j], &List[j-1]);
        }
    }
}

void writeFile(char path[20]){
    FILE *f;
    f=fopen(path, "w+");
    int i,n;
    int tmp_sbd;
    char tmp_hoten[50];
    float tmp_d1, tmp_d2, tmp_d3;
    puts("please input number of list");
    scanf("%d",&n);
    for(i=0;i<n;i++){
        puts("nhap so bao danh");
        scanf("%d",&tmp_sbd);
        fflush(stdin);
        puts("nhap ho ten");
        fgets(tmp_hoten, 50, stdin);
        if(tmp_hoten[strlen(tmp_hoten)-1]=='\n') tmp_hoten[strlen(tmp_hoten)-1]='\0';
        puts("nhap diem");
        scanf("%f%f%f",&tmp_d1, &tmp_d2, &tmp_d3);
        fprintf(f,"%10d%-50s%10.2f%10.2f%10.2f\n",tmp_sbd,tmp_hoten,tmp_d1,tmp_d2,tmp_d3);
    }
    fclose(f);
}

void readFile(sinhVien List[], char path[20], int *n){
    FILE *f;
    int i=0;
    f=fopen(path,"r");
    while(!feof(f)){
        fscanf(f,"%d",&List[i].soBaoDanh);
        fgets(List[i].hoTen, 50, f);
        fscanf(f,"%f%f%f", &List[i].d1, &List[i].d2, &List[i].d3);
        ++i;
    }
    fclose(f);
    *n=i-1;
}

void printList(sinhVien List[], int n){
    int i;
    puts("Danh sach sinh vien cua hoc vien gragena");
    for(i=0;i<n;i++){
        printf("%-3d%-10d%-50s%10.2f%10.2f%10.2f\n",i+1,List[i].soBaoDanh,List[i].hoTen,List[i].d1,List[i].d2,List[i].d3);
    }
}

int main(){
    puts("nhap cai ten file dum di");
    char path[20];
    sinhVien List[100];
    int n;
    scanf("%s",path);
//    writeFile(path);
    readFile(List, path, &n);
    printList(List, n);
    bubbleSort(List, n);
    printList(List, n);
    return 0;
}
