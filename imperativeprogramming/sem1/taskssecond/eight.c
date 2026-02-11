#include <stdio.h>
#include <stdlib.h>

int dim(int month, int year) {
    if (month == 2) {
        if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
            return 29;
        else
            return 28;
    }
    if (month == 4 || month == 6 || month == 9 || month == 11)
        return 30;
    return 31;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int day, month, year, add;
    scanf("%d %d %d %d", &day, &month, &year, &add);
    fclose(stdin);

    while (add > 0) {
        int dimd = dim(month, year);
        int lim = dimd - day + 1;
        if (add < lim) {
            day += add;
            add = 0;
        } else {
            add -= lim;
            day = 1;
            month++;
            if (month > 12) {
                month = 1;
                year++;
            }
        }
    }

    printf("%d %d %d", day, month, year);
    fclose(stdout);
    return 0;
}
