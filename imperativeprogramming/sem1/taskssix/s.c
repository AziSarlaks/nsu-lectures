#include <stdio.h>
#include <stdint.h>

int main() {
    FILE *input = fopen("input.txt", "rb");
    FILE *output = fopen("output.txt", "wb");
    
    uint32_t p;
    uint8_t b;
    
    while (fread(&b, 1, 1, input)) {
        if (b < 0x80) {
            p = b;
        } else if ((b & 0xE0) == 0xC0) {
            uint8_t b2; 
            if (!fread(&b2, 1, 1, input)) break;
            if ((b2 & 0xC0) != 0x80) break;
            p = ((b & 0x1F) << 6) | (b2 & 0x3F);
            if (p < 0x80) p = 0xFFFD;
        } else if ((b & 0xF0) == 0xE0) {
            uint8_t b2, b3; 
            if (!fread(&b2, 1, 1, input)) break;
            if (!fread(&b3, 1, 1, input)) break;
            if ((b2 & 0xC0) != 0x80 || (b3 & 0xC0) != 0x80) break;
            p = ((b & 0x0F) << 12) | ((b2 & 0x3F) << 6) | (b3 & 0x3F);
            if (p < 0x800) p = 0xFFFD;
        } else if ((b & 0xF8) == 0xF0) {
            uint8_t b2, b3, b4;
            if (!fread(&b2, 1, 1, input)) break;
            if (!fread(&b3, 1, 1, input)) break;
            if (!fread(&b4, 1, 1, input)) break;
            if ((b2 & 0xC0) != 0x80 || (b3 & 0xC0) != 0x80 || (b4 & 0xC0) != 0x80) break;
            p = ((b & 0x07) << 18) | ((b2 & 0x3F) << 12) | ((b3 & 0x3F) << 6) | (b4 & 0x3F);
            if (p < 0x10000) p = 0xFFFD;
        } else {
            break;
        }
        
        if (p > 0x10FFFF || (p >= 0xD800 && p <= 0xDFFF)) {
            p = 0xFFFD;
        }
        
        fwrite(&p, 4, 1, output);
    }
    
    fclose(input);
    fclose(output);
    return 0;
}