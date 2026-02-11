#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

uint32_t read_u32_le(FILE *f) {
    uint8_t b[4];
    fread(b, 1, 4, f);
    return ((uint32_t)b[0]) | ((uint32_t)b[1] << 8) | ((uint32_t)b[2] << 16) | ((uint32_t)b[3] << 24);
}

int32_t read_i32_le(FILE *f) {
    return (int32_t)read_u32_le(f);
}

uint64_t read_u64_le(FILE *f) {
    uint8_t b[8];
    fread(b, 1, 8, f);
    uint64_t v = 0;
    for (int i = 0; i < 8; i++) {
        v |= ((uint64_t)b[i]) << (i * 8);
    }
    return v;
}

int64_t read_i64_le(FILE *f) {
    return (int64_t)read_u64_le(f);
}

void write_i64_le(FILE *f, int64_t val) {
    uint64_t v = (uint64_t)val;
    for (int i = 0; i < 8; i++) {
        fputc((v >> (i * 8)) & 0xFF, f);
    }
}

struct FileEntry {
    char name[21];
    int64_t size;
    uint8_t is_dir;
    int64_t created;
    int64_t modified;
    uint8_t is_hidden;
};

void read_entry(FILE *f, struct FileEntry *e) {
    fread(e->name, 1, 21, f);
    e->size = read_i64_le(f);
    e->is_dir = (uint8_t)fgetc(f);
    e->created = read_i64_le(f);
    e->modified = read_i64_le(f);
    e->is_hidden = (uint8_t)fgetc(f);
}

void write_entry(FILE *f, const struct FileEntry *e) {
    fwrite(e->name, 1, 21, f);
    write_i64_le(f, e->size);
    fputc(e->is_dir, f);
    write_i64_le(f, e->created);
    write_i64_le(f, e->modified);
    fputc(e->is_hidden, f);
}

int cmp_entries(const void *pa, const void *pb) {
    const struct FileEntry *a = *(const struct FileEntry **)pa;
    const struct FileEntry *b = *(const struct FileEntry **)pb;
    return strcmp(a->name, b->name);
}

int main() {
    FILE *in = fopen("input.txt", "rb");

    int32_t n = read_i32_le(in);
    int64_t a = read_i64_le(in);
    int64_t b = read_i64_le(in);

    struct FileEntry *entries = (struct FileEntry *)malloc(n * sizeof(struct FileEntry));

    for (int i = 0; i < n; i++) {
        read_entry(in, &entries[i]);
    }
    fclose(in);

    struct FileEntry **selected = (struct FileEntry **)malloc(n * sizeof(struct FileEntry *));

    int sel_count = 0;
    for (int i = 0; i < n; i++) {
        struct FileEntry *e = &entries[i];
        if (e->is_dir == 0 && e->is_hidden == 0 && e->created >= a && e->modified <= b) {
            selected[sel_count++] = e;
        }
    }

    qsort(selected, sel_count, sizeof(struct FileEntry *), cmp_entries);

    FILE *out = fopen("output.txt", "wb");

    for (int i = 0; i < sel_count; i++) {
        write_entry(out, selected[i]);
    }
    fclose(out);

    free(selected);
    free(entries);
    return 0;
}