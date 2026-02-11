#include <stdio.h>
#include <math.h>

int main() {
    FILE *f = freopen("input.txt", "r", stdin);
    if (f == NULL) {
        printf("%s", "FILE DOES NOT EXIST");
        return 1;
    }
    float n;
    int m, p, k, l, kpf, temp, res = 1;
    scanf("%f\n%d %d %d %d", &n, &m, &p, &k, &l);
    kpf = m/(l*(p-1)+(k-1));
    temp = ceil(n/kpf);
    while (temp > l) {
        temp -= l;
        res += 1;
    }

    fclose(f);
    
    f = freopen("output.txt", "w", stdout);
    printf("%d %d", res, temp);
    fclose(f);
    return 0;
}