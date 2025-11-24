#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct
{
    uint32_t key;
    uint32_t value;
} El;

uint32_t read_uint32(FILE *f)
{
    unsigned char buf[4];
    fread(buf, 1, 4, f);
    return buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24);
}

void write_uint32(FILE *f, uint32_t value)
{
    unsigned char buf[4];
    buf[0] = value & 0xFF;
    buf[1] = (value >> 8) & 0xFF;
    buf[2] = (value >> 16) & 0xFF;
    buf[3] = (value >> 24) & 0xFF;
    fwrite(buf, 1, 4, f);
}

void radix_sort(El *arr, int n)
{
    if (n <= 1)
        return;

    El *output = malloc(n * sizeof(El));
    int count[256];

    for (int shift = 0; shift < 32; shift += 8)
    {
        for (int i = 0; i < 256; i++)
        {
            count[i] = 0;
        }

        for (int i = 0; i < n; i++)
        {
            uint8_t digit = (arr[i].key >> shift) & 0xFF;
            count[digit]++;
        }

        for (int i = 1; i < 256; i++)
        {
            count[i] += count[i - 1];
        }
        for (int i = n - 1; i >= 0; i--)
        {
            uint8_t digit = (arr[i].key >> shift) & 0xFF;
            output[count[digit] - 1] = arr[i];
            count[digit]--;
        }
        for (int i = 0; i < n; i++)
        {
            arr[i] = output[i];
        }
    }

    free(output);
}

int main()
{
    freopen("input.txt", "rb", stdin);
    freopen("output.txt", "wb", stdout);

    uint32_t n = read_uint32(stdin);

    if (n == 0)
    {
        return 0;
    }

    El *arr = malloc(n * sizeof(El));
    for (int i = 0; i < n; i++)
    {
        arr[i].key = read_uint32(stdin);
        arr[i].value = read_uint32(stdin);
    }

    radix_sort(arr, n);

    for (int i = 0; i < n; i++)
    {
        write_uint32(stdout, arr[i].key);
        write_uint32(stdout, arr[i].value);
    }

    free(arr);
    return 0;
}