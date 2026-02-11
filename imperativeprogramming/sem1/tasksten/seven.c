#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
    long long dist_sq;
} Point;

int compare(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    if (p1->dist_sq < p2->dist_sq) return -1;
    if (p1->dist_sq > p2->dist_sq) return 1;
    return 0;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int k, n = 0;
    scanf("%d", &k);
    
    Point points[100000];
    int x, y;
    
    while (scanf("%d %d", &x, &y) == 2) {
        points[n].x = x;
        points[n].y = y;
        points[n].dist_sq = (long long)x * x + (long long)y * y;
        n++;
    }
    
    qsort(points, n, sizeof(Point), compare);
    
    for (int i = 0; i < k; i++) {
        printf("%d %d\n", points[i].x, points[i].y);
    }
    
    return 0;
}