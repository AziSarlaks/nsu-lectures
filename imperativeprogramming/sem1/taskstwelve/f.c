#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *createNode(int value)
{
    TreeNode *node = malloc(sizeof(TreeNode));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

TreeNode *insert(TreeNode *root, int value)
{
    if (root == NULL)
    {
        return createNode(value);
    }
    if (value <= root->value)
    {
        root->left = insert(root->left, value);
    }
    else
    {
        root->right = insert(root->right, value);
    }
    return root;
}

void iT(TreeNode *root, int *output, int *index)
{
    if (root != NULL)
    {
        iT(root->left, output, index);
        output[(*index)++] = root->value;
        iT(root->right, output, index);
    }
}

void freeTree(TreeNode *root)
{
    if (root != NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main()
{
    freopen("input.txt", "rb", stdin);
    freopen("output.txt", "wb", stdout);

    int N;
    fread(&N, sizeof(int), 1, stdin);

    int *A = malloc(N * sizeof(int));
    fread(A, sizeof(int), N, stdin);

    TreeNode *root = NULL;
    for (int i = 0; i < N; i++)
    {
        root = insert(root, A[i]);
    }

    int *sorted = malloc(N * sizeof(int));
    int idx = 0;
    iT(root, sorted, &idx);

    fwrite(sorted, sizeof(int), N, stdout);

    freeTree(root);
    free(A);
    free(sorted);
    return 0;
}