#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool bounded_string_length(const char *string,
                                  size_t maximum_length,
                                  size_t *length)
{
    size_t index = 0;

    if (string == NULL || length == NULL) {
        return false;
    }

    for (;;) {
        if (string[index] == '\0') {
            *length = index;
            return true;
        }

        if (index == maximum_length) {
            return false;
        }

        ++index;
    }
}

bool longest_repeating_subsequence(const char *string,
                                   size_t string_length,
                                   size_t *length)
{
    size_t *previous;
    size_t *current;

    if (string == NULL || length == NULL) {
        return false;
    }

    *length = 0;

    if (string_length == 0) {
        return true;
    }

    if (string_length > SIZE_MAX / sizeof(*previous) - 1U) {
        return false;
    }

    previous = calloc(string_length + 1U, sizeof(*previous));
    current = calloc(string_length + 1U, sizeof(*current));

    if (previous == NULL || current == NULL) {
        free(previous);
        free(current);
        return false;
    }

    for (size_t i = 1; i <= string_length; ++i) {
        current[0] = 0;

        for (size_t j = 1; j <= string_length; ++j) {
            if (i != j && string[i - 1U] == string[j - 1U]) {
                current[j] = previous[j - 1U] + 1U;
            } else {
                current[j] = previous[j] > current[j - 1U]
                                 ? previous[j]
                                 : current[j - 1U];
            }
        }

        size_t *temporary = previous;
        previous = current;
        current = temporary;
    }

    *length = previous[string_length];

    free(previous);
    free(current);
    return true;
}

int main(int argc, char **argv)
{
    size_t length;
    size_t string_length;
    size_t maximum_length;
    const char *program_name;

    program_name = argc > 0 && argv != NULL && argv[0] != NULL
                       ? argv[0]
                       : "program";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <string>\n", program_name);
        return EXIT_FAILURE;
    }

    maximum_length = SIZE_MAX / sizeof(size_t) - 1U;

    if (!bounded_string_length(argv[1], maximum_length, &string_length)) {
        fprintf(stderr, "Input string is too long.\n");
        return EXIT_FAILURE;
    }

    if (!longest_repeating_subsequence(argv[1], string_length, &length)) {
        fprintf(stderr,
                "Unable to calculate the longest repeating subsequence.\n");
        return EXIT_FAILURE;
    }

    printf("%zu\n", length);
    return EXIT_SUCCESS;
}