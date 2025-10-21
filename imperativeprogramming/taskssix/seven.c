#include <stdio.h>
#include <stdlib.h>

int main(void) {
    freopen("input.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    
    long long *m = malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        scanf("%llx", &m[i]);
    }
    fclose(stdin);
    
    long long c = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((m[i] & m[j]) == 0) {
                c++;
            }
        }
    }
    freopen("output.txt", "w", stdout);
    printf("%lld\n", c);
    fclose(stdout);
    free(m);
    return 0;
}