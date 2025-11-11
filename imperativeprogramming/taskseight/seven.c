#include <stdio.h>
#include <string.h>

typedef struct {
    int digits[2000];
    int length;
} LongNum;

void readLongNum(LongNum *num, char *str) {
    num->length = strlen(str);
    for (int i = 0; i < num->length; i++) {
        num->digits[i] = str[num->length - 1 - i] - '0';
    }
}

void multiply(LongNum *a, LongNum *b, LongNum *res) {
    memset(res->digits, 0, sizeof(res->digits));
    res->length = a->length + b->length;

    for (int i = 0; i < a->length; i++) {
        for (int j = 0; j < b->length; j++) {
            res->digits[i + j] += a->digits[i] * b->digits[j];
            if (res->digits[i + j] >= 10) {
                res->digits[i + j + 1] += res->digits[i + j] / 10;
                res->digits[i + j] %= 10;
            }
        }
    }

    while (res->length > 1 && res->digits[res->length - 1] == 0) {
        res->length--;
    }
}

int main() {
    char str1[2001], str2[2001];
    LongNum num1, num2, product;

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%s", str1);
    scanf("%s", str2);

    readLongNum(&num1, str1);
    readLongNum(&num2, str2);

    multiply(&num1, &num2, &product);

    for (int i = product.length - 1; i >= 0; i--) {
        printf("%d", product.digits[i]);
    }

    return 0;
}
