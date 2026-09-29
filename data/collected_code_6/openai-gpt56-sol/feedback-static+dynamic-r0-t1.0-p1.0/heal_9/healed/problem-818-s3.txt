#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    uintmax_t count = 0;
    unsigned char *buffer = malloc(BUFSIZ);

    if (buffer == NULL) {
        return 1;
    }

    for (;;) {
        size_t bytes_read = fread(buffer, 1, BUFSIZ, stdin);

        for (size_t i = 0; i < bytes_read; ++i) {
            if (islower(buffer[i])) {
                if (count == UINTMAX_MAX) {
                    free(buffer);
                    return 1;
                }
                ++count;
            }
        }

        if (bytes_read < BUFSIZ) {
            if (ferror(stdin)) {
                free(buffer);
                return 1;
            }
            break;
        }
    }

    free(buffer);

    if (printf("%" PRIuMAX "\n", count) < 0) {
        return 1;
    }

    return 0;
}