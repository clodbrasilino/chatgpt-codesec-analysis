#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    size_t longest = 0;
    size_t current = 0;
    unsigned char buffer[4096];

    for (;;) {
        size_t bytes_read = fread(buffer, sizeof buffer[0], sizeof buffer, stdin);

        for (size_t i = 0; i < bytes_read; ++i) {
            if (isalnum(buffer[i])) {
                if (current == SIZE_MAX) {
                    fputs("Input token is too long.\n", stderr);
                    return 1;
                }

                ++current;

                if (current > longest) {
                    longest = current;
                }
            } else {
                current = 0;
            }
        }

        if (bytes_read != sizeof buffer) {
            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                return 1;
            }
            break;
        }
    }

    if (printf("%zu\n", longest) < 0) {
        fputs("Failed to write output.\n", stderr);
        return 1;
    }

    return 0;
}