#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_substrings(const unsigned char *data, size_t length,
                            size_t *result)
{
    size_t frequencies[256] = {0};
    size_t total = 0;

    if ((data == NULL && length != 0U) || result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        size_t frequency = frequencies[data[i]];

        if (frequency == SIZE_MAX ||
            frequency > SIZE_MAX - total - 1U) {
            return -1;
        }

        total += frequency + 1U;
        frequencies[data[i]] = frequency + 1U;
    }

    *result = total;
    return 0;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    size_t count = 0;
    int character;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != EOF && character != '\n') {
        if (length == capacity) {
            size_t new_capacity;
            unsigned char *new_input;

            if (capacity == 0U) {
                new_capacity = 64U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2U;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length] = (unsigned char)character;
        ++length;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (count_substrings(input, length, &count) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", count) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}