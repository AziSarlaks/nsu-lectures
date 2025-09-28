#include <stdio.h>
#include <stdlib.h>

int main() {
  int number1 = getvalue();
  int number2 = getvalue();
  int sum = number1 + number2;
  printf("%d\n", sum);
  return 0;
}

int getvalue() {
  char value[6];
  fgets(value, 6, stdin);
  int num;
  num = atoi(value);
  return num;
}