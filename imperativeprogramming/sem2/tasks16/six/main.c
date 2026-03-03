#include <assert.h>
#include <stdio.h>
#include "primes.h"

int main() {
    assert(isPrime(0) == 0);
    assert(isPrime(1) == 0);
    assert(isPrime(2) == 1);
    assert(isPrime(3) == 1);
    assert(isPrime(4) == 0);
    assert(isPrime(17) == 1);
    assert(isPrime(9973) == 1);
    assert(isPrime(10000000) == 0);
    assert(isPrime(9999991) == 1);

    assert(findNextPrime(0) == 2);
    assert(findNextPrime(1) == 2);
    assert(findNextPrime(2) == 2);
    assert(findNextPrime(3) == 3);
    assert(findNextPrime(4) == 5);
    assert(findNextPrime(10) == 11);
    assert(findNextPrime(100) == 101);
    assert(findNextPrime(9999991) == 9999991);
    assert(findNextPrime(10000000) == 10000019);

    assert(getPrimesCount(0, 10) == 4);
    assert(getPrimesCount(4, 7) == 1);
    assert(getPrimesCount(10, 20) == 4);
    assert(getPrimesCount(2, 3) == 1);
    assert(getPrimesCount(2, 2) == 0);
    assert(getPrimesCount(1, 1) == 0);
    assert(getPrimesCount(0, 2) == 0);
    assert(getPrimesCount(0, 3) == 1);
    assert(getPrimesCount(0, 10000001) == 664579);

    printf("All tests passed.\n");
    return 0;
}