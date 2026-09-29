#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    if (string_length > (SIZE_MAX / sizeof(*previous)) - 1U) {
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
            if (i != j && string[i - 1] == string[j - 1]) {
                current[j] = previous[j - 1] + 1U;
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

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char *argv[const])
{
    size_t length;
    size_t string_length;
    const char *program_name;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2 || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <string>\n", program_name);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    string_length = strlen(argv[1]);

    if (!longest_repeating_subsequence(argv[1], string_length, &length)) {
        fprintf(stderr,
                "Unable to calculate the longest repeating subsequence.\n");
        return EXIT_FAILURE;
    }

    printf("%zu\n", length);
    return EXIT_SUCCESS;
}