#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *f = freopen("input.txt", "r", stdin);
    if (f == NULL) {
        printf("%s", "FILE DOES NOT EXIST");
        return 1;
    }
    int hour, minute, second, add;
    scanf("%d %d %d %d", &hour, &minute, &second, &add);
    int m = hour * 3600 + minute * 60 + second + add;
    second = m % 60;
    m = m % 86400;
    int h = m / 3600;
    m = m % 3600;
    m /= 60;

    fclose(f);
    
    f = freopen("output.txt", "w", stdout);
    printf("%d %d %d", h, m, second);
    fclose(f);
    return 0;
}