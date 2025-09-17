#include <stdio.h>


int main() {
    freopen("input.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    int sum = 0;
    for (int i = 0; i<n; i++) {
        int l;
        scanf("%d", &l);
        if (l%2!= 0) {
            sum += l;
        }
    }
    fclose(stdin);
    freopen("output.txt", "w", stdout);
    printf("%d", sum);
    fclose(stdout);
    return 0;
}