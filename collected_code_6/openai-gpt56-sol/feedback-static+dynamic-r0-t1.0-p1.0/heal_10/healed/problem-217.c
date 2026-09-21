#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BYTE_VALUES ((size_t)UINT8_MAX + 1U)

static int find_first_repeated_character(const unsigned char *data,
                                         size_t length,
                                         unsigned char *result)
{
    uint8_t seen[BYTE_VALUES] = {0};

    if (result == NULL || (data == NULL && length != 0U)) {
        return 0;
    }

    for (size_t i = 0U; i < length; ++i) {
        const unsigned char ch = data[i];

        if (seen[ch] != 0U) {
            *result = ch;
            return 1;
        }

        seen[ch] = 1U;
    }

    return 0;
}

int main(void)
{
    unsigned char data[BYTE_VALUES + 1U];
    size_t length = 0U;
    int c;

    while (length < BYTE_VALUES + 1U) {
        c = getchar();

        if (c == EOF || c == '\n') {
            break;
        }

        data[length++] = (unsigned char)c;
    }

    if (ferror(stdin) != 0) {
        return EXIT_FAILURE;
    }

    if (length == BYTE_VALUES + 1U) {
        do {
            c = getchar();
        } while (c != EOF && c != '\n');

        if (ferror(stdin) != 0) {
            return EXIT_FAILURE;
        }
    }

    unsigned char repeated;
    const int found = find_first_repeated_character(data, length, &repeated);

    if (found != 0) {
        if (putchar((int)repeated) == EOF || putchar('\n') == EOF) {
            return EXIT_FAILURE;
        }
    } else if (puts("No repeated character") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}