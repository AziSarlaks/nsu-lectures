#include <stdio.h>
#include <string.h>

typedef struct Label_s
{
    char name[16]; // имя автора (заканчивается нулём)
    int age;       // возраст автора (сколько лет)
} Label;
typedef struct NameStats_s
{
    int cntTotal; // сколько всего подписей
    int cntLong;  // сколько подписей с именами длиннее 10 букв
} NameStats;
typedef struct AgeStats_s
{
    int cntTotal;  // сколько всего подписей
    int cntAdults; // сколько подписей взрослых (хотя бы 18 лет)
    int cntKids;   // сколько подписей детей (меньше 14 лет)
} AgeStats;

void calcStats(const Label *arr, int cnt, NameStats *oNames, AgeStats *oAges)
{
    for (int i = 0; i < cnt; i++)
    {
        const Label *cur = &arr[i];
        oNames->cntTotal++;
        oAges->cntTotal++;
        if (strlen(cur->name) > 10)
        {
            oNames->cntLong++;
        }
        if (cur->age < 14)
        {
            oAges->cntKids++;
        }
        if (cur->age >= 18)
        {
            oAges->cntAdults++;
        }
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    int n;
    Label arr[1000];
    scanf("%d", &n);
    NameStats names = {0, 0};
    AgeStats ages = {0, 0, 0};
    for (int i = 0; i < n; i++)
    {
        scanf("%s %d let\n",  arr[i].name, &arr[i].age);
    }

    calcStats(arr, n, &names, &ages);

    printf("names: total = %d\n", names.cntTotal);
    printf("names: long = %d\n", names.cntLong);
    printf("ages: total = %d\n", ages.cntTotal);
    printf("ages: adult = %d\n", ages.cntAdults);
    printf("ages: kid = %d\n", ages.cntKids);
    return 0;
}