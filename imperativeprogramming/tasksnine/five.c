#include <stdio.h>
#include <stdlib.h>

int read_int32(FILE *f) {
    unsigned char buf[4];
    fread(buf, 1, 4, f);
    return buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24);
}

void write_int32(FILE *f, int value) {
    unsigned char buf[4];
    buf[0] = value & 0xFF;
    buf[1] = (value >> 8) & 0xFF;
    buf[2] = (value >> 16) & 0xFF;
    buf[3] = (value >> 24) & 0xFF;
    fwrite(buf, 1, 4, f);
}

void quicksort(int *arr, int low, int high) {
    if (low >= high) return;
    
    int pivot = arr[(low + high) / 2];
    int i = low - 1;
    int j = high + 1;
    
    while (1) {
        do {
            i++;
        } while (arr[i] < pivot);
        
        do {
            j--;
        } while (arr[j] > pivot);
        
        if (i >= j) break;
        
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
    
    quicksort(arr, low, j);
    quicksort(arr, j + 1, high);
}

int main() {
    freopen("input.txt", "rb", stdin);
    freopen("output.txt", "wb", stdout);
    
    int n = read_int32(stdin);
    
    if (n == 0) {
        return 0;
    }
    
    int *arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = read_int32(stdin);
    }
    
    quicksort(arr, 0, n - 1);
    
    for (int i = 0; i < n; i++) {
        write_int32(stdout, arr[i]);
    }
    
    free(arr);
    return 0;
}