#include <stdio.h>
#include <stdlib.h>

int main() {
    freopen("input.txt", "r", stdin);
    int day, month, year, add;
    scanf("%d %d %d %d", &day, &month, &year, &add);
    fclose(stdin);
    while (add != 0) {
        if (add >= 366 && ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))) {
            year += 1;
            day -= 1;
            if (day == 0) {
                month -= 1;
                if (((month % 2 != 0 && month < 8) || (month % 2 == 0 && month > 7)) && month != 2) {
                    day = 31;
                } else if (month == 2) {
                    day = 28;
                } else {
                    day = 30;
                }
            }
            add -= 366;
            continue;
        } else if (add >= 365 && ((year % 400 != 0) && (year % 4 != 0))) {
            year += 1;
            if (((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))) {
                day += 1;
            }
            add -= 365;
            continue;
        } else if (add >= 31 && ((month % 2 != 0 && month < 8) || (month % 2 == 0 && month > 7)) && month != 2) {
            month += 1;
            add -= 31;
            continue;
        } else if (add >= 30 && ((month % 2 == 0 && month < 8) || (month % 2 != 0 && month > 7)) && month != 2) {
            month += 1;
            add -= 30;
            continue;
        } else if (add >= 29 && month == 2 && ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))) {
            month += 1;
            add -= 29;
            continue;
        } else if (add >= 29 && month == 2 && ((year % 400 != 0) && (year % 4 != 0))) {
            month += 1;
            add -= 28;
            continue;
        } else {
            add += day-1;
            day = 1;
            if (add >= 31 && ((month % 2 != 0 && month < 8) || (month % 2 == 0 && month > 7)) && month != 2) {
                month += 1;
                add -= 31;
                day = add;
                add = 0;
            } else if (add >= 30 && ((month % 2 == 0 && month < 8) || (month % 2 != 0 && month > 7)) && month != 2) {
                month += 1;
                add -= 30;
                day = add;
                add = 0;
            } else if (add >= 29 && month == 2 && ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))) {
                month += 1;
                add -= 29;
                day = add;
                add = 0;
            } else if (add >= 29 && month == 2 && ((year % 400 != 0) && (year % 4 != 0))) {
                month += 1;
                add -= 28;
                day = add;
                add = 0;
            }
        }
    }
    
    freopen("output.txt", "w", stdout);
    printf("%d %d %d", day, month, year);
    fclose(stdout);
    return 0;
}