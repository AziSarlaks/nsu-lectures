#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int height(Node *node)
{
    return node ? node->height : 0;
}

int balanceFactor(Node *node)
{
    return node ? height(node->left) - height(node->right) : 0;
}

Node *createNode(int value)
{
    Node *node = malloc(sizeof(Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

Node *rR(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node *lR(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

Node *insert(Node *node, int value, int *added)
{
    if (!node)
    {
        *added = 1;
        return createNode(value);
    }

    if (value < node->value)
    {
        node->left = insert(node->left, value, added);
    }
    else if (value > node->value)
    {
        node->right = insert(node->right, value, added);
    }
    else
    {
        *added = 0;
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = balanceFactor(node);

    if (balance > 1 && value < node->left->value)
    {
        return rR(node);
    }

    if (balance < -1 && value > node->right->value)
    {
        return lR(node);
    }

    if (balance > 1 && value > node->left->value)
    {
        node->left = lR(node->left);
        return rR(node);
    }

    if (balance < -1 && value < node->right->value)
    {
        node->right = rR(node->right);
        return lR(node);
    }

    return node;
}

Node *minValueNode(Node *node)
{
    Node *current = node;
    while (current && current->left)
    {
        current = current->left;
    }
    return current;
}

Node *deleteNode(Node *root, int value, int *removed)
{
    if (!root)
    {
        *removed = 0;
        return NULL;
    }

    if (value < root->value)
    {
        root->left = deleteNode(root->left, value, removed);
    }
    else if (value > root->value)
    {
        root->right = deleteNode(root->right, value, removed);
    }
    else
    {
        *removed = 1;

        if (!root->left || !root->right)
        {
            Node *temp = root->left ? root->left : root->right;

            if (!temp)
            {
                temp = root;
                root = NULL;
            }
            else
            {
                *root = *temp;
            }
            free(temp);
        }
        else
        {
            Node *temp = minValueNode(root->right);
            root->value = temp->value;
            root->right = deleteNode(root->right, temp->value, removed);
        }
    }

    if (!root)
        return NULL;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = balanceFactor(root);

    if (balance > 1 && balanceFactor(root->left) >= 0)
    {
        return rR(root);
    }

    if (balance > 1 && balanceFactor(root->left) < 0)
    {
        root->left = lR(root->left);
        return rR(root);
    }

    if (balance < -1 && balanceFactor(root->right) <= 0)
    {
        return lR(root);
    }

    if (balance < -1 && balanceFactor(root->right) > 0)
    {
        root->right = rR(root->right);
        return lR(root);
    }

    return root;
}

int lowerBound(Node *root, int value, int *found)
{
    Node *current = root;
    Node *result = NULL;

    while (current)
    {
        if (current->value >= value)
        {
            result = current;
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    if (result)
    {
        *found = 1;
        return result->value;
    }
    else
    {
        *found = 0;
        return -1;
    }
}

void freeTree(Node *root)
{
    if (root)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int M;
    scanf("%d", &M);

    Node *root = NULL;
    char operation[10];
    int value;

    for (int i = 0; i < M; i++)
    {
        scanf("%s", operation);

        if (operation[0] == 'a')
        {
            scanf("%d", &value);
            int added;
            root = insert(root, value, &added);
            printf("%s\n", added ? "added" : "dupe");
        }
        else if (operation[0] == 'r' && operation[1] == 'e' && operation[2] == 'm')
        {
            scanf("%d", &value);
            int removed;
            root = deleteNode(root, value, &removed);
            printf("%s\n", removed ? "removed" : "miss");
        }
        else if (operation[0] == 'l')
        {
            scanf("%d", &value);
            int found;
            int result = lowerBound(root, value, &found);
            if (found)
            {
                printf("%d\n", result);
            }
            else
            {
                printf("###\n");
            }
        }
    }

    freeTree(root);

    return 0;
}