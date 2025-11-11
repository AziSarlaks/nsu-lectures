#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int id;
    struct Node *next;
} Node;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N, K;
    scanf("%d %d", &N, &K);

    Node *head = NULL, *prev = NULL;

    for (int i = 1; i <= N; i++) {
        Node *node = malloc(sizeof(Node));
        node->id = i;
        node->next = NULL;
        if (!head) head = node;
        else prev->next = node;
        prev = node;
    }
    prev->next = head;

    Node *cur = head;
    Node *before = prev;

    while (N > 0) {
        for (int i = 1; i < K; i++) {
            before = cur;
            cur = cur->next;
        }

        printf("%d\n", cur->id);

        before->next = cur->next;
        free(cur);
        cur = before->next;
        N--;
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}
