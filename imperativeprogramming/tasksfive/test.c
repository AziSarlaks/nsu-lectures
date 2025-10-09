#include <stdio.h>
void plus(int *num) {
    (*num)++;
    printf("In func %d\n", *num);
}

int main() {
    int n = 100;
    printf("%d Befor func\n", n);
    plus(&n);
    printf("%d After func", n);
}