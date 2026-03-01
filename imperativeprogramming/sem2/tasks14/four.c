#include <stdio.h>

int ev(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main()
{
    int N;
    scanf("%d", &N);

    while (N--)
    {
        int A, B;
        scanf("%d %d", &A, &B);
        printf("%d\n", ev(A, B));
    }

    return 0;
}