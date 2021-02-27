#include <stdio.h>
#include <string.h>
#include <ctype.h>
int len(char s1[]){
    int i;
    for(i=0;s1[i]!='\0';i++){
    }
    return i;
}
int Compare(char s1[], char s2[]){
    int i;
    printf("%d",len(s1));
    if(len(s1)!=len(s2)) return len(s1)-len(s2);
    else {
        strupr(s1);
        strupr(s2);
        puts(s1);
        for(i=0;i<len(s1);i++){
            if(s1[i]!=s2[i]) return s1[i]-s2[i];
        }
        return 0;
    }

}
int main(){
	char s1[500], s2[500];
int len;
fgets(s1,500,stdin);
//Remove '\n' in fgets
len = strlen(s1);
if (s1[len-1]=='\n')
{
    len--;
    s1[len]='\0';
}

fgets(s2,500,stdin);
//Remove '\n' in fgets
len = strlen(s2);
if (s2[len-1]=='\n')
{
    len--;
    s2[len]='\0';
}
if (Compare(s1,s2) < 0) printf("1 < 2");
else if (Compare(s1,s2) > 0) printf("1 > 2");
else printf("1 = 2");
	return 0;
}
