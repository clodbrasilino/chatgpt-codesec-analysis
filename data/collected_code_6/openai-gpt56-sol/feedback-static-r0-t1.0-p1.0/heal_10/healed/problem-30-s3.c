#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_substrings(const unsigned char *data, size_t length,
                            size_t *result)
{
    size_t frequencies[256] = {0};
    size_t total = 0;

    if (result == NULL || (data == NULL && length != 0U)) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        size_t frequency = frequencies[data[i]];

        if (frequency == SIZE_MAX || total == SIZE_MAX ||
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
    int status = EXIT_FAILURE;
    int character;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length == capacity) {
            size_t new_capacity;
            unsigned char *temporary;

            if (capacity == 0U) {
                new_capacity = 64U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    goto cleanup;
                }
                new_capacity = capacity * 2U;
            }

            if (new_capacity > SIZE_MAX / sizeof(*input)) {
                goto cleanup;
            }

            temporary = realloc(input, new_capacity * sizeof(*input));
            if (temporary == NULL) {
                goto cleanup;
            }

            input = temporary;
            capacity = new_capacity;
        }

        input[length++] = (unsigned char)character;
    }

    if (character == EOF && ferror(stdin)) {
        goto cleanup;
    }

    if (count_substrings(input, length, &count) != 0) {
        goto cleanup;
    }

    if (printf("%zu\n", count) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}