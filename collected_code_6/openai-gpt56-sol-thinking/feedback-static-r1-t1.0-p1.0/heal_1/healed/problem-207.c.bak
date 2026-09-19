#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool longest_repeating_subsequence(const char *string, size_t *length)
{
    size_t string_length;
    size_t *previous;
    size_t *current;

    if (string == NULL || length == NULL) {
        return false;
    }

    *length = 0;
    string_length = strlen(string);

    if (string_length == 0) {
        return true;
    }

    if (string_length > SIZE_MAX / sizeof(*previous) - 1) {
        return false;
    }

    previous = calloc(string_length + 1, sizeof(*previous));
    current = calloc(string_length + 1, sizeof(*current));

    if (previous == NULL || current == NULL) {
        free(previous);
        free(current);
        return false;
    }

    for (size_t i = 1; i <= string_length; ++i) {
        current[0] = 0;

        for (size_t j = 1; j <= string_length; ++j) {
            if (i != j && string[i - 1] == string[j - 1]) {
                current[j] = previous[j - 1] + 1;
            } else {
                current[j] = previous[j] > current[j - 1]
                                 ? previous[j]
                                 : current[j - 1];
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

int main(int argc, char *argv[const])
{
    size_t length;
    const char *program_name =
        argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", program_name);
        return EXIT_FAILURE;
    }

    if (!longest_repeating_subsequence(argv[1], &length)) {
        fprintf(stderr,
                "Unable to calculate the longest repeating subsequence.\n");
        return EXIT_FAILURE;
    }

    printf("%zu\n", length);

    return EXIT_SUCCESS;
}