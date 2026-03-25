#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void radix(int *r, int *a, int *b, int n, int m) {
    int *cnt = calloc(m, sizeof(int));
    for (int i = 0; i < n; i++) cnt[r[a[i]]]++;
    for (int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; i--) b[--cnt[r[a[i]]]] = a[i];
    free(cnt);
}

void dc3(int *r, int *sa, int n, int m) {
    int n0 = (n + 2) / 3;
    int n1 = (n + 1) / 3;
    int n2 = n / 3;
    int n12 = n1 + n2;

    int *a = malloc(n12 * sizeof(int));
    int *b = malloc(n12 * sizeof(int));
    int *rn = malloc(n12 * sizeof(int));
    int *sa12 = malloc(n12 * sizeof(int));
    int *pos = malloc((n + 3) * sizeof(int));

    int j = 0;
    for (int i = 0; i < n; i++)
        if (i % 3) {
            pos[i] = j;
            a[j++] = i;
        }

    radix(r + 2, a, b, n12, m);
    radix(r + 1, b, a, n12, m);
    radix(r, a, b, n12, m);

    int p = 1;
    rn[pos[b[0]]] = 0;

    for (int i = 1; i < n12; i++) {
        if (r[b[i]] == r[b[i - 1]] &&
            r[b[i] + 1] == r[b[i - 1] + 1] &&
            r[b[i] + 2] == r[b[i - 1] + 2])
            rn[pos[b[i]]] = p - 1;
        else
            rn[pos[b[i]]] = p++;
    }

    if (p < n12) {
        dc3(rn, sa12, n12, p);
        for (int i = 0; i < n12; i++) b[i] = a[sa12[i]];
    } else {
        for (int i = 0; i < n12; i++) sa12[rn[i]] = i;
        for (int i = 0; i < n12; i++) b[i] = a[sa12[i]];
    }

    int *sa0 = malloc(n0 * sizeof(int));
    j = 0;
    for (int i = 0; i < n12; i++)
        if (b[i] % 3 == 1) sa0[j++] = b[i] - 1;

    radix(r, sa0, sa, n0, m);

    int i = 0, k = 0;
    j = 0;

    while (k < n) {
        int x = (i < n0) ? sa[i] : -1;
        int y = (j < n12) ? b[j] : -1;

        int take_x;

        if (y == -1) take_x = 1;
        else if (x == -1) take_x = 0;
        else if (y % 3 == 1)
            take_x = (r[x] < r[y]) ||
                     (r[x] == r[y] && rn[pos[x + 1]] <= rn[pos[y + 1]]);
        else
            take_x = (r[x] < r[y]) ||
                     (r[x] == r[y] &&
                     (r[x + 1] < r[y + 1] ||
                     (r[x + 1] == r[y + 1] &&
                      rn[pos[x + 2]] <= rn[pos[y + 2]])));

        if (take_x) {
            sa[k++] = x;
            i++;
        } else {
            sa[k++] = y;
            j++;
        }
    }

    free(a);
    free(b);
    free(rn);
    free(sa12);
    free(sa0);
    free(pos);
}

int main() {
    char s_str[500005];
    scanf("%s", s_str);

    int n = strlen(s_str);

    int *s = malloc((n + 3) * sizeof(int));
    int *sa = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) s[i] = s_str[i];
    s[n] = s[n + 1] = s[n + 2] = 0;

    dc3(s, sa, n, 256);

    for (int i = 0; i < n; i++) {
        if (i) printf(" ");
        printf("%d", sa[i]);
    }
    printf("\n");

    return 0;
}