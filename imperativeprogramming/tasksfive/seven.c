#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double p;
    double s;
    double l;
} Asymptotic;

void parse_asymptotic(char* str, Asymptotic* a) {
    
    a->p = 1.0;
    a->s = 0.0;
    a->l = 0.0;
    
    char* start = strstr(str, "O(");
    if (start == NULL) return;
    
    start += 2; 
    
    
    if (strstr(start, "1") && !strstr(start, "^")) {
        return;
    }
    
    
    char* token = strtok(start, " )");
    while (token != NULL) {
        if (strstr(token, "^N")) {
            sscanf(token, "%lf^N", &(a->p));
        } else if (strstr(token, "N^")) {
            sscanf(token, "N^%lf", &(a->s));
        } else if (strstr(token, "logN^")) {
            sscanf(token, "logN^%lf", &(a->l));
        } else if (strcmp(token, "N") == 0) {
            a->s = 1.0;
        } else if (strcmp(token, "logN") == 0) {
            a->l = 1.0;
        }
        token = strtok(NULL, " )");
    }
}

int compare_asymptotics(const Asymptotic* a1, const Asymptotic* a2) {
    if (fabs(a1->p - a2->p) > 1e-12) {
        return (a1->p < a2->p) ? -1 : 1;
    }
    
    if (fabs(a1->s - a2->s) > 1e-12) {
        return (a1->s < a2->s) ? -1 : 1;
    }
    
    if (fabs(a1->l - a2->l) > 1e-12) {
        return (a1->l < a2->l) ? -1 : 1;
    }
    
    return 0;
}

int main() {
    int Q;
    freopen("input.txt", "r", stdin);
    scanf("%d\n", &Q);
    
    for (int i = 0; i < Q; i++) {
        char line1[100], line2[100];
        
        fgets(line1, sizeof(line1), stdin);
        line1[strcspn(line1, "\n")] = 0;
        
        fgets(line2, sizeof(line2), stdin);
        line2[strcspn(line2, "\n")] = 0;
        
        Asymptotic a1, a2;
        
        // Создаем копии для strtok
        char copy1[100], copy2[100];
        strcpy(copy1, line1);
        strcpy(copy2, line2);
        
        parse_asymptotic(copy1, &a1);
        parse_asymptotic(copy2, &a2);
        
        int result = compare_asymptotics(&a1, &a2);
        printf("%d\n", result);
    }
    
    return 0;
}