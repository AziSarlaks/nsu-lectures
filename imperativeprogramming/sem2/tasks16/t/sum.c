#include <stdint.h>
#include <stdlib.h>

static int64_t *prefix;
int len;

void Init(const int *arr, int n) {
    len = n;
    prefix = malloc((n + 1) * sizeof(int64_t));
    prefix[0] = 0;
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + arr[i];
    }
}

int64_t Sum(int l, int r) {
    return prefix[r] - prefix[l];
}