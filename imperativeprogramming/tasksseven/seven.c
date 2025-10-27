#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXQ 200000
#define MAXN 700

typedef struct {
    int *data;
    int size;
    int cap;
} Node;

Node nodes[MAXN * 3];
int nodeCount = 1; 
int total = 0;
int B; 

void init_node(Node *n) {
    n->cap = B * 2 + 5;
    n->size = 0;
    n->data = (int*)malloc(sizeof(int) * n->cap);
}

void insert_in_node(Node *n, int pos, int val) {
    if (n->size + 1 > n->cap) {
        n->cap *= 2;
        n->data = (int*)realloc(n->data, sizeof(int) * n->cap);
    }
    for (int i = n->size; i > pos; --i)
        n->data[i] = n->data[i - 1];
    n->data[pos] = val;
    n->size++;
}

void split_node(int idx) {
    Node *n = &nodes[idx];
    if (n->size <= 2 * B) return;

    int mid = n->size / 2;
    for (int i = nodeCount; i > idx + 1; --i)
        nodes[i] = nodes[i - 1];
    nodeCount++;

    init_node(&nodes[idx + 1]);
    Node *nn = &nodes[idx + 1];
    for (int i = mid; i < n->size; ++i)
        insert_in_node(nn, nn->size, n->data[i]);
    n->size = mid;
}

void merge_nodes() {
    for (int i = 0; i + 1 < nodeCount; ++i) {
        if (nodes[i].size + nodes[i + 1].size <= B) {
            Node *a = &nodes[i];
            Node *b = &nodes[i + 1];
            for (int j = 0; j < b->size; ++j)
                insert_in_node(a, a->size, b->data[j]);
            free(b->data);
            for (int k = i + 1; k + 1 < nodeCount; ++k)
                nodes[k] = nodes[k + 1];
            nodeCount--;
            i--;
        }
    }
}

void find_pos(int k, int *ni, int *pos) {
    int i = 0;
    while (i < nodeCount) {
        if (k <= nodes[i].size) {
            *ni = i;
            *pos = k;
            return;
        }
        k -= nodes[i].size;
        i++;
    }
    *ni = nodeCount - 1;
    *pos = nodes[*ni].size;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int Q;
    if (scanf("%d", &Q) != 1) return 0;
    B = (int)sqrt(Q) + 1;
    for (int i = 0; i < MAXN * 3; ++i) nodes[i].data = NULL;
    init_node(&nodes[0]);

    for (int qi = 0; qi < Q; ++qi) {
        int type;
        scanf("%d", &type);
        if (type == 0) {
            int k, v;
            scanf("%d %d", &k, &v);
            int ni, pos;
            find_pos(k, &ni, &pos);
            insert_in_node(&nodes[ni], pos, v);
            total++;
            split_node(ni);
            merge_nodes();
        } else if (type == 1) {
            int k;
            scanf("%d", &k);
            int i = 0;
            while (i < nodeCount && k >= nodes[i].size) {
                k -= nodes[i].size;
                i++;
            }
            if (i < nodeCount)
                printf("%d\n", nodes[i].data[k]);
        }
    }

    for (int i = 0; i < nodeCount; ++i)
        free(nodes[i].data);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
