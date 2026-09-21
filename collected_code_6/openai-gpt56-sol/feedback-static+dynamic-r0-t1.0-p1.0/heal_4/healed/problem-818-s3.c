#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    uintmax_t count = 0;
    unsigned char buffer[4096];

    for (;;) {
        size_t bytes_read = fread(buffer, sizeof buffer[0], sizeof buffer, stdin);

        for (size_t i = 0; i < bytes_read; ++i) {
            if (islower((int)buffer[i]) != 0) {
                if (count == UINTMAX_MAX) {
                    return 1;
                }
                ++count;
            }
        }

        if (bytes_read < sizeof buffer) {
            if (ferror(stdin) != 0) {
                return 1;
            }
            break;
        }
    }

    if (printf("%" PRIuMAX "\n", count) < 0) {
        return 1;
    }

    return 0;
}