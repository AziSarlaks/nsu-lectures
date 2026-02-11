#include <stdio.h>
#include <string.h>


typedef struct LongNum_s 
{ 
    int len;      // сколько цифр в числе 
    int arr[500]; // массив десятичных цифр числа 
} LongNum;

void iLN(LongNum *num, const char *value) {
    memset(num->arr, 0, sizeof(num->arr));
    
    if (value == NULL || value[0] == '\0') {
        num->len = 0;
        num->arr[0] = 0;
        return;
    }
    
    int value_len = strlen(value);
    
    num->len = value_len;
    
    for (int i = 0; i < value_len; i++) {
        char c = value[value_len - 1 - i];
        if (c >= '0' && c <= '9') {
            num->arr[i] = c - '0';
        } else {
            num->arr[i] = 0;
        }
    }
    
    while (num->len > 1 && num->arr[num->len - 1] == 0) {
        num->len--;
    }
}

LongNum LNS(const LongNum *a, const LongNum *b) {
    LongNum result;
    memset(result.arr, 0, sizeof(result.arr));
    
    int max_len = (a->len > b->len) ? a->len : b->len;
    int carry = 0;
    
    for (int i = 0; i < max_len || carry > 0; i++) {
        int sum = carry;
        
        if (i < a->len) sum += a->arr[i];
        if (i < b->len) sum += b->arr[i];
        
        result.arr[i] = sum % 10;
        carry = sum / 10;
        result.len = i + 1;
    }
    
    return result;
}

void pLN(const LongNum *num) {
    for (int i = num->len - 1; i >= 0; i--) {
        printf("%d", num->arr[i]);
    }
}

void cLN(LongNum *dest, const LongNum *src) {
    dest->len = src->len;
    memcpy(dest->arr, src->arr, sizeof(src->arr[0]) * src->len);
}

LongNum fibonacci(int n) {
    
    LongNum a, b, temp;
    iLN(&a, "0");
    iLN(&b, "1");
    
    for (int i = 2; i <= n; i++) {
        temp = LNS(&a, &b);
        cLN(&a, &b);
        cLN(&b, &temp);
    }
    
    return b;
}

int main() {
    int n;
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%d", &n);
    LongNum res = fibonacci(n);
    pLN(&res);
    fclose(stdin);
    fclose(stdout);
}