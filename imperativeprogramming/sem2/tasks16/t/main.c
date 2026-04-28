typedef long long int64_t;

void Init(const int *arr, int n);
int Query(int l, int64_t sum);

int scanf(const char *fmt, ...);
int printf(const char *fmt, ...);
void *malloc(unsigned long size);
void free(void *ptr);

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int *A = (int*)malloc(N * sizeof(int));
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