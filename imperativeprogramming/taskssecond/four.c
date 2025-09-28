#include <stdio.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int a1, a2, b1, b2, c1, c2;
    scanf("%d %d %d %d %d %d", &a1, &a2, &b1, &b2, &c1, &c2);
    fclose(stdin);
    if (a1 < a2) {
        int temp = a1;
        a1 = a2;
        a2 = temp;
    }
    if (b1 < b2) {
        int temp = b1;
        b1 = b2;
        b2 = temp;
    }
    if (c1 < c2) {
        int temp = c1;
        c1 = c2;
        c2 = temp;
    }
    if (a1*a2 >= (b1*b2 + c1*c2)) {
        if (a1 >= b1 && a1 >= c1 && a2 >= b2+c2) {
            printf("YES");
            fclose(stdout);
        } else if (a1 >= b1+c1 && a2 >= b2 && a2 >= c2) {
            printf("YES");
            fclose(stdout);
        } else if (a1 >= b1+c2 && a2 >= b2 && a2 >= c1) {
            printf("YES");
            fclose(stdout);
        } else if (a1 >= b2+c1 && a2 >= b1 && a2 >= c2) {
            printf("YES");
            fclose(stdout);
        } else if (a1 >= b2+c2 && a2 >= b1 && a2 >= c1) {
            printf("YES");
            fclose(stdout);
        } else {
            printf("NO");
            fclose(stdout);
        }
    } else {
        printf("NO");
        fclose(stdout);
    }
    return 0;
}