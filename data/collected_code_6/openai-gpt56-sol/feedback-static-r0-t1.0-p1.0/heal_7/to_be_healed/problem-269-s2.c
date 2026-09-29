#include <stdio.h>
#include <stdlib.h>

static unsigned int ascii_value(unsigned char character)
{
    return (unsigned int)character;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[1];
    size_t bytes_read = fread(buffer, sizeof buffer[0], sizeof buffer, stdin);

    if (bytes_read != sizeof buffer) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
        } else {
            fputs("No character provided.\n", stderr);
        }
        return EXIT_FAILURE;
    }

    if (printf("%u\n", ascii_value(buffer[0])) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}