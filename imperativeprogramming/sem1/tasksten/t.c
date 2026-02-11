#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *a;
    int h, t, cap;
} Deck;

void init(Deck *d, int n)
{
    d->cap = 2 * n + 1;
    d->a = malloc(sizeof(int) * d->cap);
    d->h = d->t = 0;
}

int empty(Deck *d)
{
    return d->h == d->t;
}

void push_front(Deck *d, int x)
{
    d->h = (d->h - 1 + d->cap) % d->cap;
    d->a[d->h] = x;
}

void push_back(Deck *d, int x)
{
    d->a[d->t] = x;
    d->t = (d->t + 1) % d->cap;
}

int pop_front(Deck *d)
{
    int v = d->a[d->h];
    d->h = (d->h + 1) % d->cap;
    return v;
}

int pop_back(Deck *d)
{
    d->t = (d->t - 1 + d->cap) % d->cap;
    return d->a[d->t];
}

void print(Deck *d)
{
    int k = (d->t - d->h + d->cap) % d->cap;
    printf("%d ", k);
    for (int i = 0; i < k; i++)
    {
        int pos = (d->h + i) % d->cap;
        printf(" %d", d->a[pos]);
    }
    printf("\n");
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int N, M;
    scanf("%d %d", &N, &M);

    Deck L, R;
    init(&L, N);
    init(&R, N);

    for (int i = 1; i <= N; i++)
        push_back(&L, i);
    for (int i = 1; i <= N; i++)
        push_back(&R, -i);

    char *s = malloc(M + 1);
    scanf("%s", s);

    for (int i = 0; i < M; i++)
    {
        int x = (s[i] <= '9' ? s[i] - '0' : s[i] - 'A' + 10);

        int take_right = (x & 8) != 0;
        int take_bottom = (x & 4) != 0;
        int put_right = (x & 2) != 0;
        int put_bottom = (x & 1) != 0;

        Deck *from = take_right ? &R : &L;
        Deck *to = put_right ? &R : &L;

        if (empty(from))
            continue;

        int card;
        if (take_bottom)
            card = pop_back(from);
        else
            card = pop_front(from);

        if (put_bottom)
            push_back(to, card);
        else
            push_front(to, card);
    }

    print(&L);
    print(&R);

    return 0;
}