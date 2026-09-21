#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int find_first_repeated_character(const unsigned char *data,
                                  size_t length,
                                  unsigned char *result)
{
    unsigned char seen[UCHAR_MAX + 1U] = {0};

    if (result == NULL || (data == NULL && length != 0U)) {
        return 0;
    }

    for (size_t i = 0U; i < length; ++i) {
        const unsigned int index = data[i];

        if (seen[index] != 0U) {
            *result = data[i];
            return 1;
        }

        seen[index] = 1U;
    }

    return 0;
}

int main(void)
{
    unsigned char input[UCHAR_MAX + 2U];
    size_t length = 0U;
    unsigned char result;
    int ch;

    while (length < sizeof input && (ch = getchar()) != EOF && ch != '\n') {
        input[length++] = (unsigned char)ch;
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (ch != EOF && ch != '\n') {
        while ((ch = getchar()) != EOF && ch != '\n') {
        }

        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
    }

    if (find_first_repeated_character(input, length, &result) != 0) {
        if (putchar((int)result) == EOF || putchar('\n') == EOF) {
            return EXIT_FAILURE;
        }
    } else if (puts("No repeated character") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}