#include <stdio.h>
#include <string.h>

typedef struct
{
    int digits[2000];
    int length;
} LongNum;

void readLongNum(LongNum *num, char *str)
{
    memset(num->digits, 0, sizeof(num->digits));
    num->length = strlen(str);
    for (int i = 0; i < num->length; i++)
        num->digits[i] = str[num->length - 1 - i] - '0';
}

int comp(LongNum *a, LongNum *b)
{
    if (a->length != b->length)
        return a->length > b->length ? 1 : -1;
    for (int i = a->length - 1; i >= 0; i--)
    {
        if (a->digits[i] != b->digits[i])
            return a->digits[i] > b->digits[i] ? 1 : -1;
    }
    return 0;
}

void subtract(LongNum *a, LongNum *b)
{
    for (int i = 0; i < a->length; i++)
    {
        a->digits[i] -= (i < b->length ? b->digits[i] : 0);
        if (a->digits[i] < 0)
        {
            a->digits[i] += 10;
            a->digits[i + 1]--;
        }
    }
    while (a->length > 1 && a->digits[a->length - 1] == 0)
        a->length--;
}

void divide(LongNum *a, LongNum *b, LongNum *q)
{
    LongNum r, divisor, temp;
    memset(q->digits, 0, sizeof(q->digits));
    q->length = a->length;
    memset(&r, 0, sizeof(r));
    r.length = 0;

    for (int i = a->length - 1; i >= 0; i--)
    {
        for (int j = r.length; j > 0; j--)
            r.digits[j] = r.digits[j - 1];
        r.digits[0] = a->digits[i];
        if (r.length == 0 && r.digits[0] != 0)
            r.length = 1;
        else if (r.length > 0)
            r.length++;

        while (r.length > 1 && r.digits[r.length - 1] == 0)
            r.length--;

        int count = 0;
        while (comp(&r, b) >= 0)
        {
            subtract(&r, b);
            count++;
        }
        q->digits[i] = count;
    }

    while (q->length > 1 && q->digits[q->length - 1] == 0)
        q->length--;
}

int main()
{
    char str1[2001], str2[2001];
    LongNum num1, num2, product;

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%s", str1);
    scanf("%s", str2);

    readLongNum(&num1, str1);
    readLongNum(&num2, str2);

    divide(&num1, &num2, &product);

    for (int i = product.length - 1; i >= 0; i--)
    {
        printf("%d", product.digits[i]);
    }

    return 0;
}