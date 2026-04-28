#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 200005
#define MAX_M 200005

typedef struct Edge
{
    int to;
    struct Edge *next;
} Edge;

Edge *adj[MAX_N];
int dist[MAX_N];
int queue[MAX_N];
int front, rear;

void add_edge(int u, int v)
{
    Edge *e = malloc(sizeof(Edge));
    e->to = v;
    e->next = adj[u];
    adj[u] = e;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 1; i <= N; i++)
    {
        adj[i] = NULL;
        dist[i] = -1;
    }

    for (int i = 0; i < M; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
    }

    dist[1] = 0;
    front = 0;
    rear = 0;
    queue[rear++] = 1;

    while (front < rear)
    {
        int u = queue[front++];
        for (Edge *e = adj[u]; e != NULL; e = e->next)
        {
            int v = e->to;
            if (dist[v] == -1)
            {
                dist[v] = dist[u] + 1;
                queue[rear++] = v;
            }
        }
    }

    for (int i = 1; i <= N; i++)
    {
        printf("%d\n", dist[i]);
    }

    for (int i = 1; i <= N; i++)
    {
        Edge *e = adj[i];
        while (e != NULL)
        {
            Edge *tmp = e;
            e = e->next;
            free(tmp);
        }
    }

    return 0;
}