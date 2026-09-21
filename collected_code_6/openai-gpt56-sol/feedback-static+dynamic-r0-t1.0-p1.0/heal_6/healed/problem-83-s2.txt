#include <limits.h>
#include <stddef.h>
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
    unsigned char buffer[4096];
    size_t length = 0U;
    int character = 0;

    while (length < sizeof buffer &&
           (character = getchar()) != EOF &&
           character != '\n') {
        buffer[length++] = (unsigned char)character;
    }

    if (character == EOF && ferror(stdin)) {
        perror("stdin");
        return EXIT_FAILURE;
    }

    if (length == sizeof buffer && character != '\n' && character != EOF) {
        do {
            character = getchar();
        } while (character != '\n' && character != EOF);

        if (character == EOF && ferror(stdin)) {
            perror("stdin");
        }

        fputs("Input too long\n", stderr);
        return EXIT_FAILURE;
    }

    unsigned char result = add_characters(buffer, length);

    if (putchar((int)result) == EOF || putchar('\n') == EOF) {
        perror("stdout");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}