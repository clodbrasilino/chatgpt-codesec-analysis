#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BYTE_VALUES (UINT8_MAX + 1U)

int find_first_repeated_character(const unsigned char *data,
                                  size_t length,
                                  unsigned char *result)
{
    uint8_t seen[BYTE_VALUES] = {0};

    if (result == NULL || (data == NULL && length != 0U)) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
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
    uint8_t seen[BYTE_VALUES] = {0};
    unsigned char repeated = 0;
    int found = 0;
    int c;

    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            break;
        }

        const unsigned char ch = (unsigned char)c;

        if (found == 0) {
            if (seen[ch] != 0U) {
                repeated = ch;
                found = 1;
            } else {
                seen[ch] = 1U;
            }
        }
    }

    if (ferror(stdin) != 0) {
        return EXIT_FAILURE;
    }

    if (found != 0) {
        if (putchar((int)repeated) == EOF || putchar('\n') == EOF) {
            return EXIT_FAILURE;
        }
    } else {
        if (puts("No repeated character") == EOF) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}