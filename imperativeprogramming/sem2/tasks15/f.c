#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stderr, "No parameters specified.");
        return 13;
    }

    long long a, b;
    long long result;
    long long mod = 0;
    int has_mod = 0;

    char *operation = NULL;

    if (strcmp(argv[1], "-m") == 0) {
        has_mod = 1;
        mod = atoll(argv[2]);
        operation = argv[3];
        a = atoll(argv[4]);
        b = atoll(argv[5]);
    } else {
        operation = argv[1];
        a = atoll(argv[2]);
        b = atoll(argv[3]);
        if (argc > 4 && strcmp(argv[4], "-m") == 0) {
            has_mod = 1;
            mod = atoll(argv[5]);
        }
    }

    if (strcmp(operation, "add") == 0) {
        result = a + b;
    } else if (strcmp(operation, "sub") == 0) {
        result = a - b;
    } else if (strcmp(operation, "mul") == 0) {
        result = a * b;
    } else {
        return 0;
    }

    if (has_mod) {
        result %= mod;
        if (result < 0)
            result += mod;
    }

    printf("%lld", result);
    return 0;
}