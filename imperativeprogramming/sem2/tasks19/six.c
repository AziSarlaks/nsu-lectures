#include <stdio.h>
#include <stdlib.h>

#define MAX_N 5000
#define MAX_M 100000

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N, M;
    scanf("%d %d", &N, &M);

    int **adj = malloc((N + 1) * sizeof(int *));
    int *adj_size = calloc(N + 1, sizeof(int));
    int *indeg = calloc(N + 1, sizeof(int));

    for (int i = 1; i <= N; i++)
    {
        adj[i] = malloc((MAX_M / N + 10) * sizeof(int));
    }

    for (int i = 0; i < M; i++)
    {
        int B, A;
        scanf("%d %d", &B, &A);
        adj[B][adj_size[B]++] = A;
        indeg[A]++;
    }

    int *queue = malloc((N + 1) * sizeof(int));
    int *result = malloc(N * sizeof(int));
    int front = 0, rear = 0;

    for (int i = 1; i <= N; i++)
    {
        if (indeg[i] == 0)
        {
            queue[rear++] = i;
        }
    }

    int idx = 0;
    while (front < rear)
    {
        int min_pos = front;
        for (int i = front + 1; i < rear; i++)
        {
            if (queue[i] < queue[min_pos])
            {
                min_pos = i;
            }
        }
        int u = queue[min_pos];
        for (int i = min_pos; i > front; i--)
        {
            queue[i] = queue[i - 1];
        }
        queue[front] = u;
        front++;

        result[idx++] = u;

        for (int i = 0; i < adj_size[u]; i++)
        {
            int v = adj[u][i];
            indeg[v]--;
            if (indeg[v] == 0)
            {
                queue[rear++] = v;
            }
        }
    }

    if (idx != N)
    {
        printf("bad course\n");
    }
    else
    {
        for (int i = 0; i < N; i++)
        {
            printf("%d ", result[i]);
        }
        printf("\n");
    }

    for (int i = 1; i <= N; i++)
    {
        free(adj[i]);
    }
    free(adj);
    free(adj_size);
    free(indeg);
    free(queue);
    free(result);

    return 0;
}