#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#pragma comment(linker, "/STACK:50000000")

typedef struct
{
    const char *s;
    int pos;
} Parser;

double parse_expr(Parser *p);
double parse_term(Parser *p);
double parse_factor(Parser *p);

void skip_spaces(Parser *p)
{
    while (p->s[p->pos] && isspace(p->s[p->pos]))
        p->pos++;
}

double parse_number(Parser *p)
{
    double val = 0;
    skip_spaces(p);
    while (isdigit(p->s[p->pos]))
    {
        val = val * 10 + (p->s[p->pos] - '0');
        p->pos++;
    }
    return val;
}

double parse_factor(Parser *p)
{
    double val;
    int sign = 1;

    skip_spaces(p);

    while (p->s[p->pos] == '-')
    {
        sign = -sign;
        p->pos++;
        skip_spaces(p);
    }

    if (p->s[p->pos] == '(')
    {
        p->pos++;
        val = parse_expr(p);
        skip_spaces(p);
        if (p->s[p->pos] == ')')
            p->pos++;
    }
    else
    {
        val = parse_number(p);
    }

    return sign * val;
}

double parse_term(Parser *p)
{
    double val = parse_factor(p);

    skip_spaces(p);

    while (p->s[p->pos] == '*' || p->s[p->pos] == '/')
    {
        char op = p->s[p->pos];
        p->pos++;
        double next = parse_factor(p);

        if (op == '*')
            val *= next;
        else
            val /= next;

        skip_spaces(p);
    }

    return val;
}

double parse_expr(Parser *p)
{
    double val = parse_term(p);

    skip_spaces(p);

    while (p->s[p->pos] == '+' || p->s[p->pos] == '-')
    {
        char op = p->s[p->pos];
        p->pos++;
        double next = parse_term(p);

        if (op == '+')
            val += next;
        else
            val -= next;

        skip_spaces(p);
    }

    return val;
}

int main()
{
    char *s = malloc(500001);
    fgets(s, 500001, stdin);

    int n = strlen(s);
    if (n > 0 && s[n - 1] == '\n')
        s[n - 1] = '\0';

    Parser p = {s, 0};
    double result = parse_expr(&p);

    printf("%.20f\n", result);

    free(s);
    return 0;
}