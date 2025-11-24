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
    
    Point points[10000];
    
    while (scanf("%d %d", &points[n].x, &points[n].y) != EOF) {
        points[n].dist_sq = (long long)points[n].x * points[n].x + (long long)points[n].y * points[n].y;
        n++;
    }

    qsort(points, n, sizeof(Point), compare);
    
    for (int i = 0; i < k && i < n; i++) {
        printf("%d %d\n", points[i].x, points[i].y);
    }
    return 0;
}