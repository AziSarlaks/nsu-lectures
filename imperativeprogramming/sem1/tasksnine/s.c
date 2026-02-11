#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void merge(int32_t *arr, int32_t left, int32_t mid, int32_t right)
{
    int32_t n1 = mid - left + 1;
    int32_t n2 = right - mid;

    int32_t *L = malloc(n1 * sizeof(int32_t));
    int32_t *R = malloc(n2 * sizeof(int32_t));

    for (int32_t i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int32_t j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int32_t i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(int32_t *arr, int32_t left, int32_t right)
{
    if (left < right)
    {
        int32_t mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

int main()
{
    freopen("input.txt", "rb", stdin);
    freopen("output.txt", "wb", stdout);

    int32_t N;
    fread(&N, sizeof(int32_t), 1, stdin);

    int32_t *A = malloc(N * sizeof(int32_t));

    fread(A, sizeof(int32_t), N, stdin);

    mergeSort(A, 0, N - 1);
    

    fwrite(A, sizeof(int32_t), N, stdout);

    free(A);

    return 0;
}