#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int find_first_repeated_character(const unsigned char *data,
                                  size_t length,
                                  unsigned char *result)
{
    uint8_t seen[UCHAR_MAX + 1U] = {0};
    size_t i;

    if (result == NULL || (data == NULL && length != 0U)) {
        return -1;
    }

    for (i = 0U; i < length; ++i) {
        unsigned char value = data[i];

        if (seen[value] != 0U) {
            *result = value;
            return 1;
        }

        seen[value] = 1U;
    }

    return 0;
}

int main(void)
{
    enum { INPUT_CAPACITY = 4096 };
    unsigned char input[INPUT_CAPACITY];
    size_t length = 0U;
    unsigned char repeated;
    int ch;
    int status;

    while (length < sizeof input && (ch = getchar()) != EOF && ch != '\n') {
        input[length++] = (unsigned char)ch;
    }

    if (ch != '\n' && ch != EOF) {
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        fputs("Input exceeds maximum permitted length.\n", stderr);
        return EXIT_FAILURE;
    }

    if (ferror(stdin) != 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    status = find_first_repeated_character(input, length, &repeated);

    if (status < 0) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status > 0) {
        if (putchar((int)repeated) == EOF || putchar('\n') == EOF) {
            fputs("Failed to write output.\n", stderr);
            return EXIT_FAILURE;
        }
    } else if (puts("No repeated character found.") == EOF) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}