#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main() {
  int number = getvalue();
  printf("Значение переменной: %d\n", number);
  return 0;
}

int getvalue() {
  char value[50];
  fgets(value, 50, stdin);
  int num;
  num = atoi(value);
  return num;
}