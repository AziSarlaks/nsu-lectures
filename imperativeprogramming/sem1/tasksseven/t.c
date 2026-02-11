#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char value[8];
    struct Node* next;
} Node;

Node* nodes[1000001];

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int N;
    scanf("%d", &N);
    
    for (int i = 0; i < N; i++) {
        int key;
        char value[8];
        scanf("%d %s", &key, value);

        Node* new_node = (Node*)malloc(sizeof(Node));
        strcpy(new_node->value, value);
        new_node->next = NULL;

        if (nodes[key] == NULL) {
            nodes[key] = new_node;
        } else {
            Node* current = nodes[key];
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = new_node;
        }
    }

    for (int key = 0; key <= 1000000; key++) {
        Node* current = nodes[key];
        while (current != NULL) {
            printf("%d %s\n", key, current->value);
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}