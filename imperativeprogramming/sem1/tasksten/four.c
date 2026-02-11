#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_ELEMENTS 100
#define MAX_NAME_LEN 10

typedef struct
{
    char name[MAX_NAME_LEN];
    int count;
} Element;

Element elements[MAX_ELEMENTS];
int elements_count = 0;

void addElement(char *name, int count)
{
    for (int i = 0; i < elements_count; i++)
    {
        if (strcmp(elements[i].name, name) == 0)
        {
            elements[i].count += count;
            return;
        }
    }
    strcpy(elements[elements_count].name, name);
    elements[elements_count].count = count;
    elements_count++;
}

int compareElements(const void *a, const void *b)
{
    return strcmp(((Element *)a)->name, ((Element *)b)->name);
}

char *parseFormula(char *formula, int multiplier, Element *result, int *result_count)
{
    int i = 0;
    Element local_elements[MAX_ELEMENTS];
    int local_count = 0;

    void addLocalElement(char *name, int count)
    {
        for (int j = 0; j < local_count; j++)
        {
            if (strcmp(local_elements[j].name, name) == 0)
            {
                local_elements[j].count += count;
                return;
            }
        }
        strcpy(local_elements[local_count].name, name);
        local_elements[local_count].count = count;
        local_count++;
    }

    while (formula[i] != '\0' && formula[i] != ')')
    {
        if (formula[i] == '(')
        {
            Element bracket_elements[MAX_ELEMENTS];
            int bracket_count = 0;
            char *afterBracket = parseFormula(formula + i + 1, 1, bracket_elements, &bracket_count);

            int bracketMultiplier = 0;
            int j = 0;
            while (isdigit(afterBracket[j]))
            {
                bracketMultiplier = bracketMultiplier * 10 + (afterBracket[j] - '0');
                j++;
            }
            if (bracketMultiplier == 0)
                bracketMultiplier = 1;

            for (int k = 0; k < bracket_count; k++)
            {
                addLocalElement(bracket_elements[k].name, bracket_elements[k].count * bracketMultiplier * multiplier);
            }

            i = (afterBracket + j) - formula;
        }
        else if (isupper(formula[i]))
        {
            char element[MAX_NAME_LEN] = {0};
            int len = 0;
            element[len++] = formula[i++];

            while (islower(formula[i]))
            {
                element[len++] = formula[i++];
            }

            int count = 0;
            while (isdigit(formula[i]))
            {
                count = count * 10 + (formula[i] - '0');
                i++;
            }
            if (count == 0)
                count = 1;

            addLocalElement(element, count * multiplier);
        }
        else
        {
            i++;
        }
    }

    for (int j = 0; j < local_count; j++)
    {
        strcpy(result[*result_count].name, local_elements[j].name);
        result[*result_count].count = local_elements[j].count;
        (*result_count)++;
    }

    if (formula[i] == ')')
    {
        return formula + i + 1;
    }
    return formula + i;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    char formula[1001];
    scanf("%1000s", formula);

    Element result_elements[MAX_ELEMENTS];
    int result_count = 0;

    parseFormula(formula, 1, result_elements, &result_count);

    elements_count = 0;
    for (int i = 0; i < result_count; i++)
    {
        addElement(result_elements[i].name, result_elements[i].count);
    }

    qsort(elements, elements_count, sizeof(Element), compareElements);

    for (int i = 0; i < elements_count; i++)
    {
        printf("%s", elements[i].name);
        if (elements[i].count > 1)
        {
            printf("%d", elements[i].count);
        }
    }
    printf("\n");

    return 0;
}