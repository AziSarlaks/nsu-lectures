#include <stdio.h>
#include <stdlib.h>

typedef void (*callback)(void *ctx, int *value);

typedef struct
{
    int sum;
} Context;

void sumEvenCallback(void *ctx, int *value)
{
    Context *context = (Context *)ctx;
    if (*value % 2 == 0)
    {
        context->sum += *value;
    }
}

void arrayForeach(void *ctx, callback func, int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        func(ctx, &arr[i]);
    }
}

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

void listForeach(void *ctx, callback func, Node *head)
{
    Node *current = head;
    while (current != NULL)
    {
        func(ctx, &current->data);
        current = current->next;
    }
}

Node *createNode(int data)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void freeList(Node *head)
{
    Node *current = head;
    while (current != NULL)
    {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    scanf("%d", &n);

    int *array = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &array[i]);
    }

    Node *head = NULL;
    Node *tail = NULL;
    for (int i = 0; i < n; i++)
    {
        Node *newNode = createNode(array[i]);
        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }

    Context ctx1 = {0};
    arrayForeach(&ctx1, sumEvenCallback, array, n);

    Context ctx2 = {0};
    listForeach(&ctx2, sumEvenCallback, head);

    printf("%d %d\n", ctx1.sum, ctx2.sum);

    free(array);
    freeList(head);

    return 0;
}