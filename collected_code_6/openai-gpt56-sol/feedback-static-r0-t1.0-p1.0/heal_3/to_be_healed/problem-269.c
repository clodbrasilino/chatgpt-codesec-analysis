#include <stdio.h>
#include <stdlib.h>

static int ascii_value(unsigned char character)
{
    return (int)character;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[1];
    size_t bytes_read = fread(buffer, sizeof buffer[0], 1, stdin);

    if (bytes_read != 1) {
        return EXIT_FAILURE;
    }

    if (printf("%d\n", ascii_value(buffer[0])) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}