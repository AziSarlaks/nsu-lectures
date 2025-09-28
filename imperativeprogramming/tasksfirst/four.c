#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int main() {
    freopen("input.txt", "r", stdin);
    bool issimple = true;
    int num;
    int res = 0;
    scanf("%d", &num);
    if (num <= 1) {
        issimple = false;
    } else {
        for (int i = 2; i<=floor(num/2.0); i++) {
            if (num % i == 0) {
                issimple = false;
                break;
            }
        }
    }
    fclose(stdin);
    if (issimple) {
        freopen("output.txt", "w", stdout);
        printf("YES");
        fclose(stdout);
        return 0;
    } else {
        freopen("output.txt", "w", stdout);
        printf("NO");
        fclose(stdout);
        return 0;
    }
}