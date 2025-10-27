#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>


typedef struct Node {
    struct Node *prev, *next;
    double value;
} Node;

double *initList() {
    Node *head = (Node*)malloc(sizeof(Node));
    head->prev = head->next = head;
    head->value = 0.0;
    return &(head->value);
}

Node *getNode(double *pval) {
    return (Node*)((char*)pval - offsetof(Node, value));
}

void freeList(double *head_val) {
    Node *head = getNode(head_val);
    Node *cur = head->next;
    while (cur != head) {
        Node *tmp = cur->next;
        free(cur);
        cur = tmp;
    }
    free(head);
}

double *getNext(double *curr_val) {
    Node *curr = getNode(curr_val);
    return &(curr->next->value);
}

double *getPrev(double *curr_val) {
    Node *curr = getNode(curr_val);
    return &(curr->prev->value);
}

double *addAfter(double *where_val, double newval) {
    Node *where = getNode(where_val);
    Node *n = (Node*)malloc(sizeof(Node));
    n->value = newval;
    n->next = where->next;
    n->prev = where;
    where->next->prev = n;
    where->next = n;
    return &(n->value);
}

double *addBefore(double *where_val, double newval) {
    Node *where = getNode(where_val);
    Node *n = (Node*)malloc(sizeof(Node));
    n->value = newval;
    n->prev = where->prev;
    n->next = where;
    where->prev->next = n;
    where->prev = n;
    return &(n->value);
}

void erase(double *what_val) {
    Node *what = getNode(what_val);
    what->prev->next = what->next;
    what->next->prev = what->prev;
    free(what);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int T;
    scanf("%d", &T);
    while (T--) {
        int Q;
        scanf("%d", &Q);
        double *head = initList();
        double **nodes = (double**)malloc(sizeof(double*) * (Q + 5));
        int count = 0;

        for (int i = 0; i < Q; ++i) {
            int type, idx;
            scanf("%d %d", &type, &idx);

            if (type == 1) {
                double val;
                scanf("%lf", &val);
                double *where = (idx == -1 ? head : nodes[idx]);
                nodes[count] = addBefore(where, val);
                printf("%d\n", count);
                count++;
            } else if (type == -1) {
                double val;
                scanf("%lf", &val);
                double *where = (idx == -1 ? head : nodes[idx]);
                nodes[count] = addAfter(where, val);
                printf("%d\n", count);
                count++;
            } else if (type == 0) {
                double *what = nodes[idx];
                printf("%0.3lf\n", *what);
                erase(what);
            }
        }

        printf("===\n");

        double *cur = getNext(head);
        while (cur != head) {
            printf("%0.3lf\n", *cur);
            cur = getNext(cur);
        }
        printf("===\n");

        free(nodes);
        freeList(head);
    }

    return 0;
}
