#include <stdio.h>
#include <string.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    char strs[1001][1001];
    int len = 0;
    int wn = 0;
    for (int i = 0; i < 1001; i++) {
        for (int j = 0; j < 1001; j++) {
            if (scanf("%c", &strs[i][j]) != 1) {
                break;
            }
            if (strs[i][j] == ' ') {
                
            }
            len += 1;
        }
    }
    if (len == 1) {
        printf("%c", strs[0]);
    }
    printf("%d", len);
}