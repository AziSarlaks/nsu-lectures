#include <stdio.h>
#include <math.h>

typedef struct {
    double c0, c1, c2, c3;
} Polynomial;

typedef struct {
    double l, r;
    Polynomial x, y, z;
} Span;

double eval_poly(const Polynomial *p, double t, double l) {
    double dt = t - l;
    return p->c0 + p->c1 * dt + p->c2 * dt * dt + p->c3 * dt * dt * dt;
}

double eval_deriv(const Polynomial *p, double t, double l) {
    double dt = t - l;
    return p->c1 + 2.0 * p->c2 * dt + 3.0 * p->c3 * dt * dt;
}

double integrand(double t, void *data) {
    Span *span = (Span*)data;
    double dx = eval_deriv(&span->x, t, span->l);
    double dy = eval_deriv(&span->y, t, span->l);
    double dz = eval_deriv(&span->z, t, span->l);
    return sqrt(dx*dx + dy*dy + dz*dz);
}

double simpson(double (*f)(double, void*), void *data, double a, double b, int n) {
    double h = (b - a) / n;
    double sum = f(a, data) + f(b, data);
    
    for (int i = 1; i < n; i += 2) {
        sum += 4.0 * f(a + i * h, data);
    }
    for (int i = 2; i < n; i += 2) {
        sum += 2.0 * f(a + i * h, data);
    }
    
    return sum * h / 3.0;
}

int main() {
    int N;
    scanf("%d", &N);
    
    Span spans[1000];
    
    for (int i = 0; i < N; i++) {
        scanf("%lf %lf", &spans[i].l, &spans[i].r);
        scanf("%lf %lf %lf %lf", &spans[i].x.c0, &spans[i].x.c1, &spans[i].x.c2, &spans[i].x.c3);
        scanf("%lf %lf %lf %lf", &spans[i].y.c0, &spans[i].y.c1, &spans[i].y.c2, &spans[i].y.c3);
        scanf("%lf %lf %lf %lf", &spans[i].z.c0, &spans[i].z.c1, &spans[i].z.c2, &spans[i].z.c3);
    }
    
    double total_length = 0.0;
    
    for (int i = 0; i < N; i++) {
        int n_intervals = 1000;
        double prev_result = 0.0;
        double result = 0.0;
        
        do {
            prev_result = result;
            result = simpson(integrand, &spans[i], spans[i].l, spans[i].r, n_intervals);
            n_intervals *= 2;
        } while (fabs(result - prev_result) > 1e-12 && n_intervals <= 1000000);
        
        total_length += result;
    }
    
    printf("%.15f\n", total_length);
    
    return 0;
}