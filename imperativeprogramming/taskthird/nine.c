#include <stdio.h>
#include <string.h>

void swap_characters(char *a, char *b) {
    char t = *a;
    *a = *b;
    *b = t;
}

void reverse(char *s, int l, int r) {
    while (l < r) {
        swap_characters(&s[l], &s[r]);
        l++;
        r--;
    }
}

int np(char *s, int n) {
    int i = n - 2;
    while (i >= 0 && s[i] >= s[i + 1]) i--;
    if (i < 0) return 0; 

    int j = n - 1;
    while (s[j] <= s[i]) j--;
    swap_characters(&s[i], &s[j]);
    reverse(s, i + 1, n - 1);
    return 0;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    char s[27];

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf(" %c", &s[i]);
    s[n] = '\0';

    np(s, n);

    for (int i = 0; i < n; i++) {
        printf("%c", s[i]);
        if (i != n - 1) printf(" ");
    }
    printf("\n");

    fclose(stdin);
    fclose(stdout);
    return 0;
}
