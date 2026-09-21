#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
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
        if (strings[i] == NULL) {
            return false;
        }
    }

    for (i = 0U; i < count; ++i) {
        size_t left;

        for (left = 0U; left < lengths[i] / 2U; ++left) {
            size_t right = lengths[i] - left - 1U;
            char temporary = strings[i][left];

            strings[i][left] = strings[i][right];
            strings[i][right] = temporary;
        }
    }

    return true;
}

int main(int argc, char *argv[])
{
    size_t count;
    size_t *lengths = NULL;
    size_t i;

    if (argc < 1 || argv == NULL) {
        return EXIT_FAILURE;
    }

    count = (size_t)(argc - 1);

    if (count > SIZE_MAX / sizeof(*lengths)) {
        (void)fputs("Too many arguments.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > 0U) {
        lengths = malloc(count * sizeof(*lengths));
        if (lengths == NULL) {
            (void)fputs("Failed to allocate memory.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (i = 0U; i < count; ++i) {
        size_t length = 0U;
        const char *argument = argv[i + 1U];

        if (argument == NULL) {
            free(lengths);
            (void)fputs("Invalid argument.\n", stderr);
            return EXIT_FAILURE;
        }

        while (argument[length] != '\0') {
            if (length == SIZE_MAX - 1U) {
                free(lengths);
                (void)fputs("Argument is too long.\n", stderr);
                return EXIT_FAILURE;
            }
            ++length;
        }

        lengths[i] = length;
    }

    if (!reverse_strings(argv + 1, lengths, count)) {
        free(lengths);
        (void)fputs("Failed to reverse strings.\n", stderr);
        return EXIT_FAILURE;
    }

    free(lengths);

    for (i = 0U; i < count; ++i) {
        if (fputs(argv[i + 1U], stdout) == EOF ||
            fputc('\n', stdout) == EOF) {
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