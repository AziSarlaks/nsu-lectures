#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decls.h"

static char* strdup_custom(const char *s) {
    size_t len = strlen(s) + 1;
    char *res = malloc(len);
    if (res) memcpy(res, s, len);
    return res;
}

EXPORT void concat_2(State *state, char *idx0, char *idx1) {
    int i = atoi(idx0);
    int j = atoi(idx1);
    
    if (!state->regs[i] || !state->regs[j]) return;
    
    if (i == j) {
        char *temp = strdup_custom(state->regs[i]);
        size_t len = strlen(temp) * 2;
        char *new_str = malloc(len + 1);
        if (new_str) {
            strcpy(new_str, temp);
            strcat(new_str, temp);
            free(state->regs[i]);
            state->regs[i] = new_str;
        }
        free(temp);
    } else {
        size_t len_a = strlen(state->regs[i]);
        size_t len_b = strlen(state->regs[j]);
        char *new_str = malloc(len_a + len_b + 1);
        if (new_str) {
            memcpy(new_str, state->regs[i], len_a);
            memcpy(new_str + len_a, state->regs[j], len_b);
            new_str[len_a + len_b] = '\0';
            free(state->regs[i]);
            state->regs[i] = new_str;
        }
    }
}

EXPORT void tokenize_1(State *state, char *arg) {
    if (!arg) return;
    
    char *copy = strdup_custom(arg);
    if (!copy) return;
    
    int count = 0;
    char *token = strtok(copy, "_");
    
    while (token && count < 255) {
        count++;
        if (state->regs[count]) free(state->regs[count]);
        state->regs[count] = strdup_custom(token);
        token = strtok(NULL, "_");
    }
    
    char buf[32];
    sprintf(buf, "%d", count);
    if (state->regs[0]) free(state->regs[0]);
    state->regs[0] = strdup_custom(buf);
    
    free(copy);
}