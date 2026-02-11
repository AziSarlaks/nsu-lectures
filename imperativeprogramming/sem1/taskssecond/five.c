#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    scanf("%d\n", &n);
    int temp = 0;
    int tempi = 0;
    for (int i = 0; i<n; i++) {
        char numc;
        scanf("%c", &numc);
        if (i == (n-1)) {
            if (numc == '1') {
                temp += pow(2, tempi);
            }
            printf("%d", temp);
        } else if (tempi == 7 && i != n) {
            if (numc == '1') {
                temp += pow(2, tempi);
            }
            tempi = 0;
            printf("%d ", temp);
            temp = 0;
        } else {
            if (numc == '1') {
                temp += pow(2, tempi);
                tempi+=1;
            } else {
                tempi+=1;
            }
        }
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}