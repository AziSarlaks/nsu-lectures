#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    int prev;
    int data;
    int next;
}Node;

Node nodes[100000];
int head,last,tail;



void addprev(int index, int value) {
    nodes[tail].data = value; 

    if (index == -1) {  
        nodes[tail].next= -1;
        nodes[tail].prev=last;
        if (last != -1) {
            nodes[last].next = tail;
        }
        last = tail;
        if(head== -1){
            head = tail;
        }

    } else {  
        nodes[tail].next=index;
        nodes[tail].prev=nodes[index].prev;

        if (nodes[index].prev != -1){
            nodes[nodes[index].prev].next=tail;
        }else{
            head=tail;        
        }
        nodes[index].prev=tail;
    }
    printf("%d\n",tail);
    tail++;
}

void addnext(int index, int value)
{
    nodes[tail].data=value;
    if (index == -1)
    {
        nodes[tail].prev = -1;
        nodes[tail].next = head;

        if (head != -1) {
            nodes[head].prev = tail;
        }
        
        head = tail;

        if (last == -1) { 
            last = tail;
        }
    }
    else
    {
        nodes[tail].prev = index;
        nodes[tail].next = nodes[index].next;

        if (nodes[index].next != -1) {
            nodes[nodes[index].next].prev = tail;
        } else {
            last = tail; 
        }
        nodes[index].next = tail;
    }
    printf("%d\n",tail);
    tail++;

}


void delete(int index){
    printf("%d\n", nodes[index].data); 

    if (nodes[index].prev != -1) {
        nodes[nodes[index].prev].next = nodes[index].next;
    } else {
        head = nodes[index].next; 
    }

    if (nodes[index].next != -1) {
        nodes[nodes[index].next].prev = nodes[index].prev;
    } else {
        last = nodes[index].prev; 
    }
    
}

void print_list() {
    int current = head;
    while (current != -1) {
        printf("%d\n", nodes[current].data);
        current = nodes[current].next;
    }
    printf("===\n");
}

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int t;
    scanf("%d",&t);
    
    for (int _=0;_<t;_++){
        
        int n,f,l,q;
        scanf("%d %d %d %d",&n,&f,&l,&q);
        head = f;
        last=l;
        tail = n;

        for (int i =0;i<n;i++){
            scanf("%d %d %d",&nodes[i].data,&nodes[i].next,&nodes[i].prev);
        }

        while (q--){
            int type,ind;
            scanf("%d %d",&type,&ind);
            if(type==0){
                delete(ind);
            }else if(type==-1){
                int value;
                scanf("%d",&value);
                addprev(ind,value);
            }else if(type==1){
                int value;
                scanf("%d",&value);
                addnext(ind,value);
            }
        }
        
        printf("===\n");

        print_list();
    }

    fclose(stdin);
    fclose(stdout);
}