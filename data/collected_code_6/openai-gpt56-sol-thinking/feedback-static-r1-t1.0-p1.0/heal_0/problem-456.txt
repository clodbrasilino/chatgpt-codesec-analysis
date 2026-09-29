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
        size_t left;
        size_t length = strlen(strings[i]);

        for (left = 0U; left < length / 2U; ++left) {
            size_t right = length - left - 1U;
            char temporary = strings[i][left];

            strings[i][left] = strings[i][right];
            strings[i][right] = temporary;
        }
    }

    return true;
}

int main(int argc, char *argv[])
{
    size_t i;
    size_t count;

    if (argc < 1 || argv == NULL) {
        return EXIT_FAILURE;
    }

    count = (size_t)(argc - 1);

    if (!reverse_strings(&argv[1], count)) {
        (void)fputs("Failed to reverse strings.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; ++i) {
        if (fputs(argv[i + 1U], stdout) == EOF || fputc('\n', stdout) == EOF) {
            (void)fputs("Failed to write output.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    if (fflush(stdout) == EOF) {
        (void)fputs("Failed to flush output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}