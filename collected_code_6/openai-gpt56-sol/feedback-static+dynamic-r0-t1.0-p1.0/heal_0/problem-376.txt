#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool replace_duplicates(int *tuple, size_t length, int replacement)
{
    if (tuple == NULL && length != 0U) {
        return false;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (tuple[i] == replacement) {
            continue;
        }

        for (size_t j = i + 1U; j < length; ++j) {
            if (tuple[j] == tuple[i]) {
                tuple[j] = replacement;
            }
        }
    }

    return true;
}

static bool print_tuple(const int *tuple, size_t length)
{
    if (tuple == NULL && length != 0U) {
        return false;
    }

    if (putchar('(') == EOF) {
        return false;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (i != 0U && fputs(", ", stdout) == EOF) {
            return false;
        }

        if (printf("%d", tuple[i]) < 0) {
            return false;
        }
    }

    return putchar(')') != EOF && putchar('\n') != EOF;
}

int main(void)
{
    int tuple[] = {4, 2, 7, 4, 9, 2, 2, 5};
    const size_t length = sizeof tuple / sizeof tuple[0];
    const int replacement = -1;

    if (!replace_duplicates(tuple, length, replacement)) {
        fputs("Failed to replace duplicates.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!print_tuple(tuple, length)) {
        fputs("Failed to print tuple.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        fputs("Failed to flush output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}