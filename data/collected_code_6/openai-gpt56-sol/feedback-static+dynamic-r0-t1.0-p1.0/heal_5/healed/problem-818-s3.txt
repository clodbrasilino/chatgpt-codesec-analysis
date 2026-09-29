#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    uintmax_t count = 0;
    unsigned char buffer[4096];

    while (!feof(stdin)) {
        size_t bytes_read = fread(buffer, 1, sizeof buffer, stdin);

        for (size_t i = 0; i < bytes_read; ++i) {
            if (islower(buffer[i])) {
                if (count == UINTMAX_MAX) {
                    return 1;
                }
                ++count;
            }
        }

        if (ferror(stdin)) {
            return 1;
        }
    }

    if (printf("%" PRIuMAX "\n", count) < 0) {
        return 1;
    }

    return 0;
}