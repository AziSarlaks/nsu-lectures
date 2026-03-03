#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void Init(const int *arr, int n);
int Query(int l, int64_t sum);

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int *A = malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    Init(A, N);

    for (int i = 0; i < M; i++) {
        int L;
        int64_t S;
        scanf("%d %lld", &L, &S);
        int R = Query(L, S);
        printf("%d\n", R);
    }

    free(A);
    return 0;
}