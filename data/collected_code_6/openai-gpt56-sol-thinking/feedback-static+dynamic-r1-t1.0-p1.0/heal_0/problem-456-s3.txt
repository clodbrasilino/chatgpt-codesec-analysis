#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool reverse_strings(char *const strings[], size_t count)
{
    size_t i;

    if (count > 0U && strings == NULL) {
        return false;
    }

    for (i = 0U; i < count; ++i) {
        if (strings[i] == NULL) {
            return false;
        }
    }

    for (i = 0U; i < count; ++i) {
        size_t left = 0U;
        size_t right = strlen(strings[i]);

        while (left < right) {
            char temporary;

            --right;
            if (left >= right) {
                break;
            }

            temporary = strings[i][left];
            strings[i][left] = strings[i][right];
            strings[i][right] = temporary;
            ++left;
        }
    }

    return true;
}

int main(void)
{
    char first[] = "Hello";
    char second[] = "World";
    char third[] = "C programming";
    char *strings[] = { first, second, third };
    const size_t count = sizeof(strings) / sizeof(strings[0]);
    size_t i;

    if (!reverse_strings(strings, count)) {
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; ++i) {
        if (puts(strings[i]) == EOF) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}