#include <stdio.h>
#include <stdlib.h>

int is_little_endian(unsigned char* bytes) {
    int n_le = bytes[0] | (bytes[1] << 8) | (bytes[2] << 16) | (bytes[3] << 24);
    int n_be = (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];
    
    if (n_le >= 1 && n_le <= 10000) {
        return 1;
    }
    if (n_be >= 1 && n_be <= 10000) {
        return 0;
    }
    return 1;
}

int read_int32(FILE* file, int little_endian) {
    unsigned char bytes[4];
    fread(bytes, 1, 4, file);
    
    if (little_endian) {
        return bytes[0] | (bytes[1] << 8) | (bytes[2] << 16) | (bytes[3] << 24);
    } else {
        return (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];
    }
}

void write_int32(FILE* file, int value, int little_endian) {
    unsigned char bytes[4];
    
    if (little_endian) {
        bytes[0] = value & 0xFF;
        bytes[1] = (value >> 8) & 0xFF;
        bytes[2] = (value >> 16) & 0xFF;
        bytes[3] = (value >> 24) & 0xFF;
    } else {
        bytes[0] = (value >> 24) & 0xFF;
        bytes[1] = (value >> 16) & 0xFF;
        bytes[2] = (value >> 8) & 0xFF;
        bytes[3] = value & 0xFF;
    }
    
    fwrite(bytes, 1, 4, file);
}

int main() {
    FILE* input = fopen("input.txt", "rb");
    FILE* output = fopen("output.txt", "wb");
    
    unsigned char n_bytes[4];
    fread(n_bytes, 1, 4, input);
    
    int little_endian = is_little_endian(n_bytes);
    
    int n;
    if (little_endian) {
        n = n_bytes[0] | (n_bytes[1] << 8) | (n_bytes[2] << 16) | (n_bytes[3] << 24);
    } else {
        n = (n_bytes[0] << 24) | (n_bytes[1] << 16) | (n_bytes[2] << 8) | n_bytes[3];
    }
    
    int sum = 0;
    for (int i = 0; i < n; i++) {
        int num = read_int32(input, little_endian);
        sum += num;
    }
    
    write_int32(output, sum, little_endian);
    
    fclose(input);
    fclose(output);
    return 0;
}