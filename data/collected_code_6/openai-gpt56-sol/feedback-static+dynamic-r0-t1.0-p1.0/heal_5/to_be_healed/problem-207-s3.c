#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int longest_repeating_subsequence(const char *str, size_t length,
                                         size_t *result)
{
    if (str == NULL || result == NULL || length == SIZE_MAX) {
        return 0;
    }

    size_t columns = length + 1;

    if (columns > SIZE_MAX / sizeof(size_t)) {
        return 0;
    }

    size_t *previous = calloc(columns, sizeof(*previous));
    size_t *current = calloc(columns, sizeof(*current));

    if (previous == NULL || current == NULL) {
        free(previous);
        free(current);
        return 0;
    }

    for (size_t i = 1; i <= length; ++i) {
        current[0] = 0;

        for (size_t j = 1; j <= length; ++j) {
            if (i != j && str[i - 1] == str[j - 1]) {
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

    *result = previous[length];

    free(previous);
    free(current);
    return 1;
}

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    if (buffer == NULL || capacity == NULL || required == 0) {
        return 0;
    }

    if (*capacity >= required) {
        return 1;
    }

    size_t new_capacity = *capacity == 0 ? 64 : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }
        new_capacity *= 2;
    }

    char *resized = realloc(*buffer, new_capacity);

    if (resized == NULL) {
        return 0;
    }

    *buffer = resized;
    *capacity = new_capacity;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin)) {
                free(input);
                return EXIT_FAILURE;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (length > SIZE_MAX - 2) {
            free(input);
            return EXIT_FAILURE;
        }

        size_t required = length + 2;

        if (!grow_buffer(&input, &capacity, required)) {
            free(input);
            return EXIT_FAILURE;
        }

        input[length++] = (char)(unsigned char)character;
    }

    if (length == SIZE_MAX ||
        !grow_buffer(&input, &capacity, length + 1)) {
        free(input);
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    size_t result = 0;

    if (!longest_repeating_subsequence(input, length, &result)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", result) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}