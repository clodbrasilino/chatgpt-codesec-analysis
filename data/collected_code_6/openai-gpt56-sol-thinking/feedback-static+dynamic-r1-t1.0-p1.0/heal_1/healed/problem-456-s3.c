#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool reverse_strings(char *const strings[],
                            const size_t lengths[],
                            size_t count)
{
    size_t i;

    if (count > 0U && (strings == NULL || lengths == NULL)) {
        return false;
    }

    for (i = 0U; i < count; ++i) {
        size_t left = 0U;
        size_t right;

        if (strings[i] == NULL) {
            return false;
        }

        right = lengths[i];

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
    char *strings[] = {first, second, third};
    const size_t lengths[] = {
        sizeof(first) - 1U,
        sizeof(second) - 1U,
        sizeof(third) - 1U
    };
    const size_t count = sizeof(strings) / sizeof(strings[0]);
    size_t i;

    if (!reverse_strings(strings, lengths, count)) {
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; ++i) {
        if (puts(strings[i]) == EOF) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}