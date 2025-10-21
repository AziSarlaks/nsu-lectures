#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char base_type[32];
    int pointer_level;
} Field;

typedef struct {
    int char_size, short_size, int_size, long_size;
    int float_size, int64_size, double_size, ptr_size;
} Model;

Model MODELS[4] = {
    {1,2,2,4,4,8,8,4}, // 32
    {1,2,4,4,4,8,8,4}, // 32
    {1,2,4,4,4,8,8,8}, // 64
    {1,2,4,8,4,8,8,8}  // 64
};

int fs(const Field *f, const Model *m) {
    if (f->pointer_level > 0) return m->ptr_size;
    if (strcmp(f->base_type, "char") == 0) return m->char_size;
    if (strcmp(f->base_type, "short") == 0) return m->short_size;
    if (strcmp(f->base_type, "int") == 0) return m->int_size;
    if (strcmp(f->base_type, "long") == 0) return m->long_size;
    if (strcmp(f->base_type, "float") == 0) return m->float_size;
    if (strcmp(f->base_type, "int64_t") == 0) return m->int64_size;
    if (strcmp(f->base_type, "double") == 0) return m->double_size;
    return 1;
}

int ssize(const Field *fields, int n, const Model *m, const int *order) {
    int i, offset = 0, sz, max_align = 1;
    int sizes[20];
    for (i = 0; i < n; i++) {
        sizes[i] = fs(&fields[i], m);
        if (sizes[i] > max_align) max_align = sizes[i];
    }
    offset = 0;
    for (i = 0; i < n; i++) {
        sz = sizes[order[i]];
        if (offset % sz != 0)
            offset += sz - (offset % sz);
        offset += sz;
    }

    if (offset % max_align != 0)
        offset += max_align - (offset % max_align);
    return offset;
}

void swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }
void permute(Field *fields, int n, const Model *m, int *order, int depth,
             int *min_sz, int *max_sz) {
    if (depth == n) {
        int sz = ssize(fields, n, m, order);
        if (sz < *min_sz) *min_sz = sz;
        if (sz > *max_sz) *max_sz = sz;
        return;
    }
    for (int i = depth; i < n; i++) {
        swap(&order[depth], &order[i]);
        permute(fields, n, m, order, depth + 1, min_sz, max_sz);
        swap(&order[depth], &order[i]);
    }
}

int main(void) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    Field fields[101];
    int n = 0;
    char line[256];

    while (fgets(line, sizeof(line), stdin)) {
        char *p = line;
        while (isspace((unsigned char)*p)) p++;
        if (strncmp(p, "struct", 6) == 0 || *p == '{' || *p == '}' || *p == ';' || *p == '\n')
            continue;

        char *sc = strchr(p, ';');
        if (sc) *sc = '\0';
        char *nl = strchr(p, '\n');
        if (nl) *nl = '\0';

        while (strstr(p, "  ")) {
            char *q = strstr(p, "  ");
            memmove(q, q + 1, strlen(q));
        }

        char type[32] = {0};
        sscanf(p, "%s", type);
        Field f = {0};
        strcpy(f.base_type, type);
        f.pointer_level = 0;
        char *rest = strstr(p, type);
        if (rest) rest += strlen(type);
        for (; *rest; rest++)
            if (*rest == '*') f.pointer_level++;
        fields[n++] = f;
    }

    int order[2200];
    for (int i = 0; i < n; i++) order[i] = i;

    for (int i = 0; i < 4; i++) {
        int min_sz = 1000000000, max_sz = 0;
        permute(fields, n, &MODELS[i], order, 0, &min_sz, &max_sz);
        fprintf(stdout, "%d %d\n", min_sz, max_sz);
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}