#include <stdio.h>
#include <stdlib.h>

int main() {
    char tnum[3];
    int sum, num;
    sum = 0;
    scanf("%s", tnum);
    num = atoi(tnum);

    for (int i = 1; i<=num; i++) {
        sum += i;
    }

    printf("%d\n", sum);
    return 0;
}
