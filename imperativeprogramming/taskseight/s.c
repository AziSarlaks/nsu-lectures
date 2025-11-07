#include <stdio.h>
#include <stdlib.h>

int binsearch(int arr[], int s, int t)
{
    int start = 0;
    int finish = s - 1;
    int result = -1;

    while (start <= finish)
    {
        int mid = start + (finish - start) / 2;

        if (arr[mid] == t)
        {
            result = mid;
            start = mid + 1;
        }
        else if (arr[mid] < t)
            start = mid + 1;
        else
            finish = mid - 1;
    }
    return result;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N, Q, Xj, Yj, Rj;

    scanf("%d", &N);
    int *arr = malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &arr[i]);
    }

    Rj = 0;
    scanf("%d", &Q);
    for (int i = 0; i < Q; i++)
    {
        scanf("%d", &Xj);
        Yj = Xj + Rj;
        Rj = binsearch(arr, N, Yj);
        printf("%d\n", Rj);
    }

    
    free(arr);
    fclose(stdin);
    fclose(stdout);
    return 0;
}