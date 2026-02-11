#include <stdio.h>
#include <ctype.h>

#define M 6

int main(void) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int pi[M], k = 0;
    char pat[] = "GGGGCC";
    pi[0] = 0;
    for (int q = 1; q < M; q++) {
        while (k > 0 && pat[k] != pat[q]) k = pi[k - 1];
        if (pat[k] == pat[q]) k++;
        pi[q] = k;
    }

    long long T;
    if (scanf("%lld", &T) != 1) return 1;
    int c = getchar();
    if (c != '\n' && c != ' ' && c != '\r') ungetc(c, stdin);

    long long count = 0;
    int q = 0;
    int ch;
    long long read = 0;

    while ((ch = getchar()) != EOF && read < T) {
        if (!isalpha(ch)) continue;
        read++;

        ch = toupper(ch);
        if (ch == 'U') ch = 'T';

        while (q > 0 && ch != pat[q]) q = pi[q - 1];
        if (ch == pat[q]) q++;
        if (q == M) {
            count++;
            q = pi[q - 1];
        }
        if (count > 30) break;
    }

    printf("%s", (count > 30 ? "Pathogenic" : "Non-pathogenic"));
    fclose(stdin);
    fclose(stdout);
    return 0;
}
