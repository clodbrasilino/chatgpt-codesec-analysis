#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int reverse_strings(char *const strings[], const size_t lengths[], size_t count);

static int argument_length(const char *string, size_t *length)
{
    size_t result = 0U;

    if (string == NULL || length == NULL) {
        return -1;
    }

    while (string[result] != '\0') {
        if (result == SIZE_MAX - 1U) {
            return -1;
        }
        ++result;
    }

    *length = result;
    return 0;
}

int reverse_strings(char *const strings[], const size_t lengths[], size_t count)
{
    size_t i;

    if (count > 0U && (strings == NULL || lengths == NULL)) {
        return -1;
    }

    for (i = 0U; i < count; ++i) {
        if (strings[i] == NULL) {
            return -1;
        }
    }

    for (i = 0U; i < count; ++i) {
        size_t left = 0U;
        size_t right = lengths[i];

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
    char **strings;
    size_t *lengths;
    size_t count;
    size_t i;

    if (argc < 1 || argv == NULL) {
        return EXIT_FAILURE;
    }

    count = (size_t)(argc - 1);
    strings = argv + 1;
    lengths = NULL;

    if (count > 0U) {
        if (count > SIZE_MAX / sizeof(*lengths)) {
            (void)fputs("Too many input strings.\n", stderr);
            return EXIT_FAILURE;
        }

        lengths = malloc(count * sizeof(*lengths));
        if (lengths == NULL) {
            (void)fputs("Failed to allocate memory.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (i = 0U; i < count; ++i) {
        if (argument_length(strings[i], &lengths[i]) != 0) {
            free(lengths);
            (void)fputs("Invalid input string.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    if (reverse_strings(strings, lengths, count) != 0) {
        free(lengths);
        (void)fputs("Failed to reverse strings.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; ++i) {
        if (fwrite(strings[i], 1U, lengths[i], stdout) != lengths[i] ||
            fputc('\n', stdout) == EOF) {
            free(lengths);
            (void)fputs("Failed to write output.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    free(lengths);

    if (fflush(stdout) == EOF) {
        (void)fputs("Failed to flush output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}