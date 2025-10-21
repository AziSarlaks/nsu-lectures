#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int N;
    scanf("%d", &N);
    
    for (int i = 0; i < N; i++) {
        long long P, Q, M;
        char xog[10];
        
        scanf("%lld/%lld %s %llx", &P, &Q, xog, &M);
        
        double X = (double)P / Q;
        
        unsigned long long x_bits;
        memcpy(&x_bits, &X, sizeof(double));
        
        unsigned long long result_bits = x_bits ^ M;
        
        double result;
        memcpy(&result, &result_bits, sizeof(double));
        
        printf("%0.15g\n", result);
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}