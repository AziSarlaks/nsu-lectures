#include <stdio.h>

#define MAX 100000

typedef struct {
    long long x,y;
} Point;

Point p[MAX], hull[MAX];
int n;

long long cross(Point a, Point b, Point c){
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}

long long dist2(Point a, Point b){
    long long dx=a.x-b.x, dy=a.y-b.y;
    return dx*dx+dy*dy;
}

int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%lld%lld",&p[i].x,&p[i].y);

    int left=0;
    for(int i=1;i<n;i++)
        if(p[i].x<p[left].x || (p[i].x==p[left].x && p[i].y<p[left].y))
            left=i;

    int cur=left, k=0;
    do{
        hull[k++]=p[cur];
        int next=(cur+1)%n;
        for(int i=0;i<n;i++){
            long long c=cross(p[cur],p[next],p[i]);
            if(c<0 || (c==0 && dist2(p[cur],p[i])>dist2(p[cur],p[next])))
                next=i;
        }
        cur=next;
    }while(cur!=left);

    printf("%d\n",k);
    for(int i=0;i<k;i++)
        printf("%lld %lld\n",hull[i].x,hull[i].y);

    return 0;
}