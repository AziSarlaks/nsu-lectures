#include <stdio.h>
#include <string.h>

typedef struct LongNum_s 
{ 
    int len;
    int arr[3000];
} LongNum;

void iLN(LongNum *num, const char *value) {
    memset(num->arr, 0, sizeof(num->arr));
    
    if (value == NULL || value[0] == '\0') {
        num->len = 1;
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

LongNum LNM(const LongNum *a, int b) {
    LongNum result;
    memset(result.arr, 0, sizeof(result.arr));
    
    if (b == 0) {
        result.len = 1;
        result.arr[0] = 0;
        return result;
    }
    
    int carry = 0;
    result.len = 0;
    
    for (int i = 0; i < a->len || carry > 0; i++) {
        int current_sum = carry;
        
        if (i < a->len) {
            current_sum += a->arr[i] * b;
        }
        
        result.arr[i] = current_sum % 10;
        carry = current_sum / 10;
        result.len = i + 1;
        
    }
    
    return result;
}

void pLN(const LongNum *num) {
    for (int i = num->len - 1; i >= 0; i--) {
        printf("%d", num->arr[i]);
    }
}

LongNum factorial(int n) {
    LongNum result, temp;
    iLN(&result, "1");
    
    for (int i = 2; i <= n; i++) {
        temp = LNM(&result, i);
        result.len = temp.len;
        memcpy(result.arr, temp.arr, sizeof(temp.arr[0]) * temp.len);
    }
    
    return result;
}

int main() {
    int n;
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%d", &n);
    LongNum res = factorial(n);
    pLN(&res);
    fclose(stdin);
    fclose(stdout);
    return 0;
}