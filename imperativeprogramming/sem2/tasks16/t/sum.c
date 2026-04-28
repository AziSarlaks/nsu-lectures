typedef long long int64_t;

static int64_t *prefix;
int len;

void *malloc(unsigned long size);
void free(void *ptr);

void Init(const int *arr, int n) {
    len = n;
    prefix = (int64_t*)malloc((n + 1) * sizeof(int64_t));
    prefix[0] = 0;
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + arr[i];
    }
}

int64_t Sum(int l, int r) {
    return prefix[r] - prefix[l];
}