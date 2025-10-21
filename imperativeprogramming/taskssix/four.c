#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fin = fopen("input.txt", "rb");
    FILE *fout = fopen("output.txt", "wb");
    
    int N;
    if (fread(&N, 4, 1, fin) != 1) return 1;
    
    // Читаем кодировки
    int *lengths = malloc(N * sizeof(int));
    char **bits = malloc(N * sizeof(char*));
    
    for (int i = 0; i < N; i++) {
        if (fread(&lengths[i], 4, 1, fin) != 1) return 1;
        bits[i] = malloc(lengths[i]);
        if (fread(bits[i], 1, lengths[i], fin) != lengths[i]) return 1;
    }
    
    // Читаем M
    int M;
    if (fread(&M, 4, 1, fin) != 1) return 1;
    
    // Читаем символы
    short *symbols = malloc(M * sizeof(short));
    if (fread(symbols, 2, M, fin) != M) return 1;
    
    // Кодируем
    char byte = 0;
    int bit_count = 0;
    
    for (int i = 0; i < M; i++) {
        int sym = symbols[i];
        if (sym < 0 || sym >= N) continue;
        
        int L = lengths[sym];
        for (int j = 0; j < L; j++) {
            if (bits[sym][j]) {
                byte |= (1 << bit_count);
            }
            bit_count++;
            
            if (bit_count == 8) {
                fwrite(&byte, 1, 1, fout);
                byte = 0;
                bit_count = 0;
            }
        }
    }
    
    // Последний байт
    if (bit_count > 0) {
        fwrite(&byte, 1, 1, fout);
    }
    
    // Очистка
    for (int i = 0; i < N; i++) {
        free(bits[i]);
    }
    free(bits);
    free(lengths);
    free(symbols);
    
    fclose(fin);
    fclose(fout);
    return 0;
}