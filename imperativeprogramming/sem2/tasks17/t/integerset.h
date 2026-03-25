#ifndef INTEGERSET_H
#define INTEGERSET_H

typedef struct IntegerSet {
    int *data;
    int size;
} IntegerSet;

IntegerSet* CreateSet(const int *arr, int size);
int IsInSet(const IntegerSet *set, int value);

#endif