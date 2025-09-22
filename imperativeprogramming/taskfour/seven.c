#include <stdio.h>
#include <string.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    char strs[1001][1001];
    int len = 0;
    int wn = 0;
    for (int i = 0; i < 1001; i++) {
        if (scanf("%c", &strs[0][i]) != 1) {
            break;
        }
        if (strs[0][i] == ' ') {
            
        }
        len += 1;
    }
    if (len == 1) {
        printf("%c", strs[0]);
    }
    printf("%d", len);
}