#include "integerset.h"
#include <stdlib.h>

static int compare_ints(const void *a, const void *b) {
    int ia = *(const int*)a;
    int ib = *(const int*)b;
    if (ia < ib) return -1;
    if (ia > ib) return 1;
    return 0;
}

IntegerSet* CreateSet(const int *arr, int size) {
    if (size < 0) return NULL;
    
    IntegerSet *set = (IntegerSet*)malloc(sizeof(IntegerSet));
    if (!set) return NULL;
    
    if (size == 0) {
        set->data = NULL;
        set->size = 0;
        return set;
    }
    
    set->data = (int*)malloc(size * sizeof(int));
    if (!set->data) {
        free(set);
        return NULL;
    }
    
    for (int i = 0; i < size; i++) {
        set->data[i] = arr[i];
    }
    
    qsort(set->data, size, sizeof(int), compare_ints);
    
    for (int i = 1; i < size; i++) {
        if (set->data[i] == set->data[i-1]) {
            free(set->data);
            free(set);
            return NULL;
        }
    }
    
    set->size = size;
    return set;
}

int IsInSet(const IntegerSet *set, int value) {
    if (!set || !set->data || set->size == 0) return 0;
    
    int left = 0;
    int right = set->size - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (set->data[mid] == value) {
            return 1;
        }
        if (set->data[mid] < value) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return 0;
}