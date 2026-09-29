#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    uintmax_t count = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[4096];

    for (;;) {
        size_t bytes_read = fread(buffer, 1, sizeof buffer, stdin);

        for (size_t i = 0; i < bytes_read; ++i) {
            if (islower(buffer[i])) {
                if (count == UINTMAX_MAX) {
                    return 1;
                }
                ++count;
            }
        }

        if (bytes_read != sizeof buffer) {
            if (ferror(stdin)) {
                return 1;
            }
            break;
        }
    }

    return printf("%" PRIuMAX "\n", count) < 0 ? 1 : 0;
}