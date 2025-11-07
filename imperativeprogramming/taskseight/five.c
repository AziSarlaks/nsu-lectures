#include <stdio.h>
#include <stdlib.h>

void find_closest(int arr[], int n, int X, int *ci, int *md) {
    int start = 0, finish = n - 1;
    int best_index = 0;
    int best_diff = abs(arr[0] - X);

    while (start <= finish) {
        int mid = start + (finish - start) / 2;
        int diff = abs(arr[mid] - X);

        if (diff < best_diff) {
            best_diff = diff;
            best_index = mid;
        }

        if (arr[mid] < X) {
            start = mid + 1;
        } else if (arr[mid] > X) {
            finish = mid - 1;
        } else {
            best_index = mid;
            best_diff = 0;
            break;
        }
    }

    *ci = best_index;
    *md = best_diff;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N, Q, R, t;

    scanf("%d", &N);
    int *arr = malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &arr[i]);
    }

    scanf("%d", &Q);
    for (int i = 0; i < Q; i++)
    {
        int index, diff;
        scanf("%d", &t);
        find_closest(arr, N, t, &index, &diff);
        printf("%d %d\n", index, diff);
    }

    
    free(arr);
    fclose(stdin);
    fclose(stdout);
    return 0;
}