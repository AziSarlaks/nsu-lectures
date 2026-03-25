#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decls.h"

EXPORT void echo_0(State *state) {
    printf("ECHO: \n");
    fflush(stdout);
}

EXPORT void echo_1(State *state, char *arg0) {
    printf("ECHO: %s\n", arg0);
    fflush(stdout);
}

EXPORT void echo_2(State *state, char *arg0, char *arg1) {
    printf("ECHO: %s|%s\n", arg0, arg1);
    fflush(stdout);
}

EXPORT void echo_3(State *state, char *arg0, char *arg1, char *arg2) {
    printf("ECHO: %s|%s|%s\n", arg0, arg1, arg2);
    fflush(stdout);
}

EXPORT void print_1(State *state, char *idx) {
    int i = atoi(idx);
    if (state->regs[i]) {
        printf("%s\n", state->regs[i]);
        fflush(stdout);
    }
}

EXPORT void printregs_0(State *state) {
    int i;
    for (i = 0; i < 256; i++) {
        if (state->regs[i]) {
            printf("%d = %s\n", i, state->regs[i]);
            fflush(stdout);
        }
    }
}

EXPORT void store_2(State *state, char *idx, char *what) {
    int i = atoi(idx);
    if (state->regs[i]) free(state->regs[i]);
    state->regs[i] = malloc(strlen(what) + 1);
    strcpy(state->regs[i], what);
}

EXPORT void copy_2(State *state, char *dst, char *src) {
    int d = atoi(dst);
    int s = atoi(src);
    if (d == s) return;
    if (state->regs[d]) free(state->regs[d]);
    state->regs[d] = malloc(strlen(state->regs[s]) + 1);
    strcpy(state->regs[d], state->regs[s]);
}

EXPORT void clear_1(State *state, char *idx) {
    int i = atoi(idx);
    if (state->regs[i]) {
        free(state->regs[i]);
        state->regs[i] = NULL;
    }
}