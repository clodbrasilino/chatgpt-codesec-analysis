#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int reverse_strings(char *const strings[], size_t count);

int reverse_strings(char *const strings[], size_t count)
{
    size_t i;

    if (count > 0U && strings == NULL) {
        return -1;
    }

    for (i = 0U; i < count; ++i) {
        if (strings[i] == NULL) {
            return -1;
        }
    }

    for (i = 0U; i < count; ++i) {
        size_t left = 0U;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t right = strlen(strings[i]);

        while (left < right) {
            char temporary;

            --right;
            temporary = strings[i][left];
            strings[i][left] = strings[i][right];
            strings[i][right] = temporary;
            ++left;
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    size_t count;
    size_t i;

    if (argc < 1 || argv == NULL) {
        return EXIT_FAILURE;
    }

    count = (size_t)(argc - 1);

    if (reverse_strings(argv + 1, count) != 0) {
        (void)fputs("Failed to reverse strings.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; ++i) {
        if (puts(argv[i + 1U]) < 0) {
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