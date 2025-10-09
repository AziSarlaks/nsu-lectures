#include <stdio.h>
#include <string.h>

typedef struct Label_s { 
    char name[16]; // имя автора (заканчивается нулём) 
    int age;       // возраст автора (сколько лет) 
} Label; 

typedef struct NameStats_s { 
    int cntTotal; // сколько всего подписей 
    int cntLong;  // сколько подписей с именами длиннее 10 букв 
} NameStats; 

typedef struct AgeStats_s { 
    int cntTotal;  // сколько всего подписей 
    int cntAdults; // сколько подписей взрослых (хотя бы 18 лет) 
    int cntKids;   // сколько подписей детей (меньше 14 лет) 
} AgeStats;


void calcStats(const Label *arr, int cnt, NameStats *oNames, AgeStats *oAges) {
    
    for (int i = 0; i < cnt; i++) {
        const Label *current = &arr[i];
        
        if (strlen(current->name) > 10) {
            oNames->cntLong++;
        }
        oNames->cntTotal++;
        
        if (current->age >= 18) {
            oAges->cntAdults++;
        } else if (current->age < 14) {
            oAges->cntKids++;
        }
        oAges->cntTotal++;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int n;
    scanf("%d", &n);
    
    // Создаем массив для хранения всех записей
    Label labels[1000]; // предполагаем максимальное количество
    
    NameStats names = {0, 0};
    AgeStats age = {0, 0, 0};
    
    // Читаем все данные
    for (int i = 0; i < n; i++) {
        scanf("%s %d let\n", labels[i].name, &labels[i].age);
    }
    
    // Обрабатываем все данные сразу
    calcStats(labels, n, &names, &age);
    
    printf("names: total = %d\n", names.cntTotal);
    printf("names: long = %d\n", names.cntLong);
    printf("ages: total = %d\n", age.cntTotal);
    printf("ages: adult = %d\n", age.cntAdults);
    printf("ages: kid = %d\n", age.cntKids);
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}