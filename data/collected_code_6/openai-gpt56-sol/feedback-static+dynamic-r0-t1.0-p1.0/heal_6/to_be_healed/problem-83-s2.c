#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned char add_characters(const unsigned char *string, size_t length)
{
    unsigned int sum = 0U;

    for (size_t i = 0U; i < length; ++i) {
        sum = (sum + string[i]) % (UCHAR_MAX + 1U);
    }

    return (unsigned char)sum;
}

int main(void)
{
    unsigned int sum = 0U;
    int character;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != EOF && character != '\n') {
        sum = (sum + (unsigned char)character) % (UCHAR_MAX + 1U);
    }

    if (character == EOF && ferror(stdin)) {
        perror("stdin");
        return EXIT_FAILURE;
    }

    unsigned char result = (unsigned char)sum;

    if (putchar((int)result) == EOF || putchar('\n') == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}