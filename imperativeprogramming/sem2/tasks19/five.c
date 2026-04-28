#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 105

typedef struct
{
    int x, y;
} Point;

int M, N;
char maze[MAX_N][MAX_N];
int dist[MAX_N][MAX_N];
Point queue[MAX_N * MAX_N];
int front, rear;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d %d", &M, &N);

    int start_x = -1, start_y = -1;
    int finish_x = -1, finish_y = -1;

    for (int i = 0; i < M; i++)
    {
        scanf("%s", maze[i]);
        for (int j = 0; j < N; j++)
        {
            if (maze[i][j] == 'S')
            {
                start_x = i;
                start_y = j;
                maze[i][j] = '.';
            }
            else if (maze[i][j] == 'F')
            {
                finish_x = i;
                finish_y = j;
                maze[i][j] = '.';
            }
            dist[i][j] = -1;
        }
    }

    if (start_x == -1 || finish_x == -1)
    {
        printf("-1\n");
        return 0;
    }

    front = 0;
    rear = 0;
    dist[start_x][start_y] = 0;
    queue[rear++] = (Point){start_x, start_y};

    while (front < rear)
    {
        Point p = queue[front++];

        if (p.x == finish_x && p.y == finish_y)
        {
            printf("%d\n", dist[p.x][p.y]);
            return 0;
        }

        for (int i = 0; i < 4; i++)
        {
            int nx = p.x + dx[i];
            int ny = p.y + dy[i];

            if (nx >= 0 && nx < M && ny >= 0 && ny < N && maze[nx][ny] == '.' && dist[nx][ny] == -1)
            {
                dist[nx][ny] = dist[p.x][p.y] + 1;
                queue[rear++] = (Point){nx, ny};
            }
        }
    }

    printf("-1\n");

    return 0;
}