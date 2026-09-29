#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH ((size_t)1000000)

static int maximum_difference(const char *binary_string,
                              size_t length,
                              size_t *start,
                              size_t *end)
{
    int maximum = 0;
    int current = 0;
    size_t current_start = 0;

    if (binary_string == NULL || start == NULL || end == NULL) {
        return -1;
    }

    *start = 0;
    *end = 0;

    for (size_t i = 0; i < length; ++i) {
        int value;

        if (binary_string[i] == '0') {
            value = 1;
        } else if (binary_string[i] == '1') {
            value = -1;
        } else {
            return -1;
        }

        if (current < 0) {
            current = value;
            current_start = i;
        } else {
            current += value;
        }

        if (current > maximum) {
            maximum = current;
            *start = current_start;
            *end = i;
        }
    }

    return maximum;
}

int main(void)
{
    char *input;
    size_t capacity = MAX_INPUT_LENGTH + 2U;
    size_t length;
    size_t start;
    size_t end;
    int result;

    input = malloc(capacity);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    if (fgets(input, (int)capacity, stdin) == NULL) {
        free(input);
        return EXIT_FAILURE;
    }

    for (length = 0; input[length] != '\0' && input[length] != '\n'; ++length) {
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (length > MAX_INPUT_LENGTH) {
        free(input);
        return EXIT_FAILURE;
    } else {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stdin);

        if (character != EOF && character != '\n') {
            free(input);
            return EXIT_FAILURE;
        }

        if (ferror(stdin)) {
            free(input);
            return EXIT_FAILURE;
        }
    }

    if (length > 0U && input[length - 1U] == '\r') {
        input[--length] = '\0';
    }

    if (length == 0U) {
        free(input);
        return EXIT_FAILURE;
    }

    result = maximum_difference(input, length, &start, &end);
    free(input);

    if (result < 0) {
        return EXIT_FAILURE;
    }

    if (printf("%d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}