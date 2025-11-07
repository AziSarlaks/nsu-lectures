#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATTERN "GGGGCC"
#define PATTERN_LEN 6
#define PATHO_THRESHOLD 30

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int T;
    scanf("%d", &T);

    char *sequence = (char*)malloc(T + 1);
    scanf("%s", sequence);

    int count = 0;
    for (int i = 0; i <= T - PATTERN_LEN; i++) {
        if (strncmp(sequence + i, PATTERN, PATTERN_LEN) == 0) {
            count++;
        }
    }

    if (count > PATHO_THRESHOLD)
        printf("Pathogenic\n");
    else
        printf("Non-pathogenic\n");

    free(sequence);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
