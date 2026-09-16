#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool replace_duplicates(int *values, size_t count, int replacement)
{
    if (values == NULL && count != 0U) {
        return false;
    }

    for (size_t i = 0U; i < count; ++i) {
        bool duplicate = false;

        for (size_t j = 0U; j < i; ++j) {
            if (values[j] == values[i]) {
                duplicate = true;
                break;
            }
        }

        if (duplicate) {
            values[i] = replacement;
        }
    }

    return true;
}

static bool print_tuple(const int *values, size_t count)
{
    if (values == NULL && count != 0U) {
        return false;
    }

    if (putchar('(') == EOF) {
        return false;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (i != 0U && fputs(", ", stdout) == EOF) {
            return false;
        }

        if (printf("%d", values[i]) < 0) {
            return false;
        }
    }

    return puts(")") != EOF;
}

int main(void)
{
    int tuple[] = {4, 2, 4, 7, 2, 9, 7};
    const size_t count = sizeof(tuple) / sizeof(tuple[0]);
    const int replacement = -1;

    if (!replace_duplicates(tuple, count, replacement)) {
        fputs("Failed to replace duplicates.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!print_tuple(tuple, count)) {
        fputs("Failed to print the tuple.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}