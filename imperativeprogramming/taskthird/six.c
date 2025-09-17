#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int s, f, c;
    int res = 0;
    scanf("%d %d %d", &s, &f, &c);
    for (int i = s; i <= f-c+1; i++) {
        for (int j = 1; j <= f-s; j++) {
            int temp = i;
            int count = 1;
            while (temp < f) {
                temp += j;
                if (temp <= f) {
                    count++;
                }
            }
            if (count == c) {
                res += 1;
            } else if (count < c) {
                break;
            }
        }
    }
    printf("%d", res);
    fclose(stdin);
    fclose(stdout);
    return 0;
}