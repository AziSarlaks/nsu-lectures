#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int c = 0;
int nc = 0;

void quicksort(int arr[], int left, int right) {
        if (left >= right) return;
        int p = arr[right];
        int i = left - 1;
        for (int j = left; j < right; j++) {
            if (arr[j] < p) {
                i++;
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
        int tmp = arr[i + 1];
        arr[i + 1] = arr[right];
        arr[right] = tmp;
        quicksort(arr, left, i);
        quicksort(arr, i + 2, right);
}

void set(int arr[], int arrr[], int finish) {
    quicksort(arr, 0, finish-1);
    nc += 1;
    int f = 0;
    arrr[0] = arr[0]; 
    for (int i = 1; i<finish; i++) {
        f = 0;
        for (int j = 0; j<nc; j++) {
            if (arr[i] == arrr[j]) {
                f = 1;
                break;
            }
        }
        if (f == 0) {
            arrr[nc] = arr[i];
            nc += 1;
        }
    }
}


void m(int arra[], int finish, int finish2, int arrb[], int arrr[]) {
    int ti = 0;
    int f = 0;
    for (int i = 0; i<finish; i++) {
        f = 0;
        for (int j = 0; j<finish2; j++) {
            if (arra[i]==arrb[j]) {
                f = 1;
                break;
            }
        }
        if (f == 0) {
            c+=1;
            arrr[ti] = arra[i];
            ti+=1;
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n1;
    scanf("%d", &n1);
    int arr1[100000];
    for (int i = 0; i<n1; i++) {
        scanf("%d", &arr1[i]);
    }
    int n2;
    scanf("%d", &n2);
    int arr2[100000];
    for (int i = 0; i<n2; i++) {
        scanf("%d", &arr2[i]);
    }
    int arrr[100000];
    int sarr[100000];
    set(arr1, sarr, n1);
    m(sarr, nc, n2, arr2, arrr);
    if (c != 0) {
        printf("%d\n", c);
        for (int i = 0; i<c; i++) {
            if (i == c-1) {
                printf("%d", arrr[i]);
            } else {
               printf("%d ", arrr[i]);
            }
        }
    } else {
        printf("%d", c);
    }
    fclose(stdout);
    return 0;
}