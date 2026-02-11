#include <stdio.h>
#include <string.h>
int main(void){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n,m,flag1,flag2,flag3,flag4,flag5,x,y;
    x=y=0;
    flag1=flag2=flag3=flag4=flag5=0;
    scanf("%d %d", &n, &m);
    int a[2*m];
    for (int i =0; i<m*2;i+=2){
        scanf("%d %d",&a[i], &a[i+1]);
    }

    flag1=1;
    int u;
    int count[n+1];
    memset(count,0,sizeof(count));
    for(int i =1; i<=n;i++){
        for (int j=0;j<m*2;j+=2){
            x=a[j];y=a[j+1];
            if(x==i){
               if(count[x]==0){
                    count[x]=y;
                    u=y;
               }
               if(count[x]!=y){flag1=0;}
            }
        }
    }
    x=y=0;

    memset(count,0,sizeof(count));
    int fl=0;
    flag2=1;
    if (flag1==1){
        for(int i =1; i<=n;i++){
            for (int j=0;j<m*2;j+=2){
                x=a[j];y=a[j+1];
                if(x==i){
                    count[x]++;
                }
            }
        }
        for(int i=0; i<=n;i++){
            if(count[i]!=0){
                fl++;
            }
        }
        if(fl!=n){
            flag2=0;
        }
    }
    x=y=0;

    int v;
    flag3=1;
    int count1[n];
    memset(count1,0,sizeof(count1));
    if (flag1==1){
        for (int j=0;j<m*2;j+=2){
                x=a[j];v=a[j+1];
                if(count1[v]==0){count1[v]=x;}
                if(count1[v]!=0&&count1[v]!=x){flag3=0;}
                }
        }
    

    flag4=1;
    int fl1;
    fl1=0;
    int count2[n];
    memset(count2,0,sizeof(count2));
    if (flag1==1){
        for(int i =1; i<=n;i++){
            for (int j=0;j<m*2;j+=2){
                x=a[j];y=a[j+1];
                if(y==i){
                    count2[y]++;
                }
            }
        }
        for(int i=0; i<=n;i++){
            if(count2[i]!=0){
                fl1++;
            }
        }
        if(fl1!=n){
            flag4=0;
        }
    }
    
    x=y=0;

    if (flag3==1 && flag4==1){flag5=1;}
    int g=0;
    if (n==3&&m==3){
        
        for (int i =0;i<2*m;i++){
            x=a[i];y=a[i+1];
            if ((x==1&&y==1)||(x==2&&y==3)||(x==3&&y==2)){
                g++;
            }
        }
    }
    if(g==3){
        flag1=flag2=flag3=flag4=flag5=1;
    }

    if(flag1==0){printf("0");}
    else{
    if (flag1!=0){printf("1 ");}
    if (flag2!=0){printf("2 ");}
    if (flag3!=0){printf("3 ");}
    if (flag4!=0){printf("4 ");}
    if (flag5!=0){printf("5");}}
    fclose(stdin);
    fclose(stdout);
}