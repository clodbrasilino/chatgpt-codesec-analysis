#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096U

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
    unsigned char buffer[BUFFER_SIZE];
    size_t length = 0U;
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
        if (length >= sizeof buffer) {
            do {
                character = getchar();
            } while (character != '\n' && character != EOF);

            if (character == EOF && ferror(stdin)) {
                perror("stdin");
            } else {
                fputs("Input too long\n", stderr);
            }

            return EXIT_FAILURE;
        }

        buffer[length++] = (unsigned char)character;
    }

    if (character == EOF && ferror(stdin)) {
        perror("stdin");
        return EXIT_FAILURE;
    }

    unsigned char result = add_characters(buffer, length);

    if (putchar((int)result) == EOF) {
        perror("stdout");
        return EXIT_FAILURE;
    }

    if (putchar('\n') == EOF) {
        perror("stdout");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}