#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int N;
    if (scanf("%d", &N) != 1) return 0;

    char **arr = malloc(sizeof(char*) * N);
    for (int i = 0; i < N; i++) arr[i] = NULL;

    int created = 0;

    for (int i = 0; i < N; i++) {
        int t;
        if (scanf("%d", &t) != 1) break;

        if (t == 0) {
            int l;
            scanf("%d", &l);
            char *buf = malloc(l + 1);
            scanf("%s", buf);
            buf[l] = '\0';
            arr[created++] = buf;
        } 
        else if (t == 1) {
            int k;
            scanf("%d", &k);
            if (k >= 0 && k < created && arr[k]) {
                free(arr[k]);
                arr[k] = NULL;
            }
        } 
        else if (t == 2) {
            int k;
            scanf("%d", &k);
            if (k >= 0 && k < created && arr[k]) {
                printf("%s\n", arr[k]);
            }
        } 
        else if (t == 3) {
            int k;
            char ch;
            scanf("%d %c", &k, &ch);
            if (k >= 0 && k < created && arr[k]) {
                int cnt = 0;
                for (char *p = arr[k]; *p; ++p)
                    if (*p == ch) cnt++;
                printf("%d\n", cnt);
            }
        }
    }

    for (int i = 0; i < created; i++)
        free(arr[i]);
    free(arr);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
