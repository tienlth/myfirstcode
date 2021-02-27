#include <iostream>
#include <string>
#include <math.h>
using namespace std;
class bignum{
public:
    string value;
    void firstadd(char c){
        this->value+=' ';
        for(int i=this->value.size();i>=0;i--){
            this->value[i]=this->value[i-1];
        }
        this->value[0]=c;
    }
    void optimize(){
        for(int j=0;j<this->value.size();j++){
            if(this->value[j]=='-') continue;
            if(this->value[j]=='0'){
                for(int l=j;l<this->value.size()-1;l++){
                    this->value[l]=this->value[l+1];
                }
                this->value.pop_back();
                --j;
            }
            else break;
        }
        if(this->value.size()==0) this->value="0";
    }
    bignum operator+(const bignum &s){
        bignum a, b;
        if(this->value.size()>s.value.size()){
            a=(*this);
            b=s;
        }
        else {
            b=(*this);
            a=s;
        }
        a.optimize();
        b.optimize();
        bignum c={""};
        int tmp=0;
        int mem=0;
        for(int i=0;i<a.value.size();i++){
            if(i>=b.value.size() ){
                tmp=(a.value[a.value.size()-i-1]-48+mem)%10;
                mem=(a.value[a.value.size()-i-1]-48+mem)/10;
                c.firstadd((char)(tmp+48));
            }
            else {
                tmp=(a.value[a.value.size()-i-1]-48+b.value[b.value.size()-i-1]-48+mem)%10;
                mem=(a.value[a.value.size()-i-1]-48+b.value[b.value.size()-i-1]-48+mem)/10;
                c.firstadd((char)(tmp+48));
            }
            if(i==a.value.size()-1 && mem) c.firstadd((char)(mem+48));
        }
        return c;
    }
    int operator>(const bignum &b){
        if(this->value.size()>b.value.size()) return 1;
        else if(this->value.size()<b.value.size()) return 0;
        else {
            int flag=0;
            for(int i=0;i<this->value.size()&&!flag;i++){
                if(this->value[i]>b.value[i]) flag=1;
                else if(this->value[i]<b.value[i]) return 0;
            }
            return flag;
        }
    }
    bignum operator-(const bignum &s){
        bignum a, b, d;
        this->optimize();
        d=s;
        d.optimize();
        int flag=0;
        if(this->value.size()>d.value.size()){
            a=(*this);
            b=d;
        }
        else if(this->value.size()<d.value.size()){
            b=(*this);
            a=d;
            flag=1;
        }
        else {
            for(int j=0;j<d.value.size();j++){
                if(this->value[j]>d.value[j]){
                    a=(*this);
                    b=d;
                    break;
                }
                else if(this->value[j]<d.value[j]){
                    b=(*this);
                    a=d;
                    flag=1;
                    break;
                }
            }
        }
        bignum c={""};
        int tmp=0, tmp1=0, tmp2=0;
        int mem=0;
        for(int i=0;i<a.value.size();i++){
            tmp1=a.value[a.value.size()-i-1]-48;
            if(i<b.value.size()) tmp2=b.value[b.value.size()-i-1]-48;
            else tmp2=0;
            tmp2+=mem;
            if(tmp1<tmp2){
                tmp1+=10;
                mem=1;
            }
            else mem=0;
            tmp=tmp1-tmp2;
            if(i<a.value.size()-1 || tmp) c.firstadd((char)(tmp+48));
        }
        if(flag) c.firstadd('-');
        c.optimize();
        if(c.value.size()==0) c.value="0";
        return c;
    }

    bignum operator*(const bignum &s){
        this->optimize();
        bignum b=s;
        b.optimize();
        int tmp=0, mem=0;
        bignum c={"0"};
        bignum tmp1={""};
        for(int i=0;i<b.value.size();i++){
            mem=0;
            tmp1.value="";
            for(int j=this->value.size()-1;j>=0;j--){
                tmp=((this->value[j]-48)*(b.value[i]-48)+mem)%10;
                mem=((this->value[j]-48)*(b.value[i]-48)+mem)/10;
                tmp1.firstadd((char)(tmp+48));
                if(j==0 && mem) tmp1.firstadd((char)(mem+48));
            }
            c=c+tmp1;
            if(i<b.value.size()-1) c.value+="0";
        }
        if(c.value[0]=='0') c.value="0";
        return c;
    }

    bignum operator/(const bignum &b){
        bignum r={""};
        bignum d=b;
        bignum q={""};
        bignum tmpq={"0"};
        bignum one={"1"};
        bignum tmpr;
        this->optimize();
        int i=0;
        while(d>r){
            r.value=r.value+this->value[i];
            ++i;
        }
        for(;i<=this->value.size();i++){
            tmpr=r;
            tmpq={"0"};
            while(!(d>tmpr)){
                tmpr=tmpr-d;
                tmpq=tmpq+one;
            }
            r=r-(tmpq*d);
            q.value=q.value+tmpq.value;
            if(r.value[0]=='0') r.value="";
            r.value=r.value+this->value[i];
            if(i==30) break;
        }
        return q;
    }


};

bignum gt(bignum n){
    bignum res={"1"};
    bignum i={"1"};
    bignum step={"1"};
    while((n+step)>i){
        res=res*i;
        i=i+step;
    }
    return res;
}

bignum heso(bignum n){
    bignum res={"1"};
    bignum two={"2"};
    bignum i=n+two;
    bignum step={"1"};
    while((two*n+step)>i){
        res=res*i;
        i=i+step;
    }
    return res;
}

int main(){
    int n;
    cin>>n;
    bignum bn;
    bignum two={"2"};
    bignum one={"1"};
    bn.value=to_string(n);
    cout<<(heso(bn)/gt(bn)).value;
    return 0;
}
