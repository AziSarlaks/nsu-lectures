#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

int n;
char maze[MAX_N][MAX_N + 1];
int visited[MAX_N][MAX_N];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

void dfs(int x, int y) {
    visited[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < n && ny >= 0 && ny < n && !visited[nx][ny] && maze[nx][ny] == ' ') {
            dfs(nx, ny);
        }
    }
}

int main() {
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    
    fscanf(in, "%d", &n);
    
    for (int i = 0; i < n; i++) {
        int j = 0;
        char c;
        while (j < n) {
            c = fgetc(in);
            if (c == '*' || c == ' ') {
                maze[i][j] = c;
                j++;
            } else if (c == '\n') {
                continue;
            }
        }
    }
    
    fclose(in);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            visited[i][j] = 0;
        }
    }
    
    int start_y = -1;
    for (int j = 0; j < n; j++) {
        if (maze[0][j] == ' ') {
            start_y = j;
            break;
        }
    }
    
    if (start_y != -1) {
        dfs(0, start_y);
    }
    
    int inaccessible = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (maze[i][j] == ' ' && !visited[i][j]) {
                inaccessible++;
            }
        }
    }
    
    fprintf(out, "%d\n", inaccessible);
    fclose(out);
    
    return 0;
}