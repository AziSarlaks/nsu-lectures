#include <stdio.h>
#include <string.h>

int readTime(char *iStr, int *oHours, int *oMinutes, int *oSeconds) {
    int h = 0, m = 0, s = 0;
    
    if (iStr[1] == '|') {
        if (oHours) *oHours = -1;
        if (oMinutes) *oMinutes = -1;
        if (oSeconds) *oSeconds = -1;
        return 0;
    }
    int count = sscanf(iStr, "%d:%d:%d", &h, &m, &s);
    if (count != 3 && count != 2) {
        if (oHours) *oHours = -1;
        if (oMinutes) *oMinutes = -1;
        if (oSeconds) *oSeconds = -1;
        return 0;
    }

    if (h < 0 || h > 23 || m < 0 || m > 59 || s < 0 || s > 59) {
        if (oHours) *oHours = -1;
        if (oMinutes) *oMinutes = -1;
        if (oSeconds) *oSeconds = -1;
        return 0;
    }
    
    if (oHours) *oHours = h;
    if (oMinutes) *oMinutes = m;
    if (oSeconds) *oSeconds = s;
    
    return 1;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    char s[1000001];
    int hours = 0, minutes = 0, seconds = 0;
    scanf("%s", s);
    int res = readTime(s, &hours, &minutes, &seconds);
    printf("%d %d %d %d\n", res, hours, minutes, seconds);
    res = readTime(s, &hours, &minutes, NULL);
    printf("%d %d %d\n", res, hours, minutes);
    res = readTime(s, &hours, NULL, NULL);
    printf("%d %d", res, hours);
    fclose(stdin);
    fclose(stdout);
}