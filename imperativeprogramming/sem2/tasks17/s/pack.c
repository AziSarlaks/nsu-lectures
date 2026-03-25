#include "pack.h"
#include <stdarg.h>
#include <string.h>
#include <stdint.h>

int pack(char *buffer, const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    int total_bytes = 0;
    int buffer_pos = 0;
    
    for (const char *f = format; *f; f++) {
        switch (*f) {
            case '%': {
                f++;
                
                switch (*f) {
                    case 'd': {
                        int val = va_arg(args, int);
                        if (buffer) {
                            buffer[buffer_pos] = val & 0xFF;
                            buffer[buffer_pos + 1] = (val >> 8) & 0xFF;
                            buffer[buffer_pos + 2] = (val >> 16) & 0xFF;
                            buffer[buffer_pos + 3] = (val >> 24) & 0xFF;
                        }
                        total_bytes += 4;
                        buffer_pos += 4;
                        break;
                    }
                    
                    case 'l': {
                        double val = va_arg(args, double);
                        if (buffer) {
                            uint64_t bits;
                            memcpy(&bits, &val, 8);
                            for (int i = 0; i < 8; i++) {
                                buffer[buffer_pos + i] = (bits >> (i * 8)) & 0xFF;
                            }
                        }
                        total_bytes += 8;
                        buffer_pos += 8;
                        break;
                    }
                    
                    case 's': {
                        char *str = va_arg(args, char*);
                        int len = strlen(str) + 1;
                        
                        if (buffer) {
                            memcpy(buffer + buffer_pos, str, len);
                        }
                        
                        total_bytes += len;
                        buffer_pos += len;
                        break;
                    }
                }
                break;
            }
        }
    }
    
    va_end(args);
    return total_bytes;
}