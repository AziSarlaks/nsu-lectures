#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265358979323846

int main() {
    int q;
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%d", &q);
    double x1, y1, x2, y2, x3, y3, res;
    
    for (int i = 0; i < q; i++) {
        scanf("%lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3);
        
        double ab_x = x2 - x1;
        double ab_y = y2 - y1;
        double ac_x = x3 - x1;
        double ac_y = y3 - y1;
        
    
        double scalar = ab_x * ac_x + ab_y * ac_y;
        
        double cross = ab_x * ac_y - ab_y * ac_x;
        
        double len_ab = sqrt(ab_x * ab_x + ab_y * ab_y);
        double len_ac = sqrt(ac_x * ac_x + ac_y * ac_y);
        
        if (len_ab == 0 || len_ac == 0) {
            res = 0;
        } else {
            
            res = atan2(fabs(cross), scalar) * 180.0 / M_PI;
            
        }
        
        printf("%0.20g\n", res);
    }
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}