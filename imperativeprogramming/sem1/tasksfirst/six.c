#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    freopen("input.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    int min = 100000, imin = 0, max = -100000, imax = 0;
    for (int i = 0; i<n; i++) {
        int l;
        scanf("%d", &l);
        if (l < min) {
            min = l;
            imin = i+1;
        }
        if (l > max) {
            max = l;
            imax = i+1;
        }
    }
    

    fclose(stdin);
    
    freopen("output.txt", "w", stdout);
    printf("%d %d %d %d", min, imin, max, imax);
    fclose(stdout);
    return 0;
}