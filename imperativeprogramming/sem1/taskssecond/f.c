#include <stdio.h>
#include <string.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    char s[12];
    scanf("%s", s);
    fclose(stdin);
    if (strcmp(s, "M") == 0 || strcmp(s, "Mo") == 0 || strcmp(s, "Mon") == 0 || strcmp(s, "Mond") == 0 || strcmp(s, "Monda") == 0 || strcmp(s, "Monday") == 0) {
        printf("1");
    } else if (strcmp(s, "Tu") == 0 || strcmp(s, "Tue") == 0 || strcmp(s, "Tues") == 0 || strcmp(s, "Tuesd") == 0 || strcmp(s, "Tuesda") == 0 || strcmp(s, "Tuesday") == 0) {
        printf("2");
    } else if (strcmp(s, "W") == 0 || strcmp(s, "We") == 0 || strcmp(s, "Wed") == 0 || strcmp(s, "Wedn") == 0 || strcmp(s, "Wedne") == 0 || strcmp(s, "Wednes") == 0 || strcmp(s, "Wednesd") == 0 || strcmp(s, "Wednesda") == 0 || strcmp(s, "Wednesday") == 0) {
        printf("3");
    } else if (strcmp(s, "Th") == 0 || strcmp(s, "Thu") == 0 || strcmp(s, "Thur") == 0 || strcmp(s, "Thurs") == 0 || strcmp(s, "Thursd") == 0 || strcmp(s, "Thursda") == 0 || strcmp(s, "Thursday") == 0) {
        printf("4");
    } else if (strcmp(s, "F") == 0 || strcmp(s, "Fr") == 0 || strcmp(s, "Fri") == 0 || strcmp(s, "Frid") == 0 || strcmp(s, "Frida") == 0 || strcmp(s, "Friday") == 0) {
        printf("5");
    } else if (strcmp(s, "Sa") == 0 || strcmp(s, "Sat") == 0 || strcmp(s, "Satu") == 0 || strcmp(s, "Satur") == 0 || strcmp(s, "Saturd") == 0 || strcmp(s, "Saturda") == 0 || strcmp(s, "Saturday") == 0) {
        printf("6");
    } else if (strcmp(s, "Su") == 0 || strcmp(s, "Sun") == 0 || strcmp(s, "Sund") == 0 || strcmp(s, "Sunda") == 0 || strcmp(s, "Sunday") == 0) {
        printf("7");
    } else if (strcmp(s, "T") == 0 || strcmp(s, "S") == 0) {
        printf("Ambiguous");
    } else {
        printf("Invalid");
    }
    fclose(stdout);
    return 0;
}