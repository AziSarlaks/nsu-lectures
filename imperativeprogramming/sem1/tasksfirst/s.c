#include <stdio.h>
#include <stdlib.h>

int main() {
    freopen("input.txt", "r", stdin);
    int x, y, z;
    int res = 0;
    scanf("%d %d %d", &x, &y, &z);
    fclose(stdin);
    int arr[] = {x, y, z};
    if (x > 0 && y > 0 && z > 0) {
        res = x*y*2 + x*z*2 + y*z*2;
        freopen("output.txt", "w", stdout);
        printf("%d", res);
        fclose(stdout);
        return 0;
    } else {
        for (int i = 0; i<3; i++) {
            if (arr[i] <= 0) {
                freopen("output.txt", "w", stdout);
                printf("-%d", i+1);
                fclose(stdout);
                return 0;
            }
        }
    }
}