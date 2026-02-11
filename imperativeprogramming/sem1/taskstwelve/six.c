#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int value;
    int index;
} Element;

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int N;
    scanf("%d", &N);

    int *A = malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &A[i]);
    }

    char commands[400005];
    scanf("%s", commands);

    Element *deque = malloc(N * sizeof(Element));
    int front = 0, back = 0;

    int L = 0, R = 0;

    for (int i = 0; i < 2 * N - 1; i++)
    {
        if (commands[i] == 'R')
        {
            while (front < back && deque[back - 1].value <= A[R])
            {
                back--;
            }
            deque[back].value = A[R];
            deque[back].index = R;
            back++;
            R++;
        }
        else
        {
            if (front < back && deque[front].index == L)
            {
                front++;
            }
            L++;
        }

        if (L < R)
        {
            printf("%d\n", deque[front].value);
        }
        else
        {
            printf("0\n");
        }
    }

    free(A);
    free(deque);

    return 0;
}