#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int longest_repeating_subsequence(const unsigned char *string,
                                         size_t length,
                                         size_t *result)
{
    size_t *previous;
    size_t *current;

    if (result == NULL || (string == NULL && length != 0)) {
        return -1;
    }

    *result = 0;

    if (length == 0) {
        return 0;
    }

    if (length == SIZE_MAX ||
        length + 1 > SIZE_MAX / sizeof(*previous)) {
        return -1;
    }

    previous = calloc(length + 1, sizeof(*previous));
    current = calloc(length + 1, sizeof(*current));

    if (previous == NULL || current == NULL) {
        free(previous);
        free(current);
        return -1;
    }

    for (size_t i = 1; i <= length; ++i) {
        current[0] = 0;

        for (size_t j = 1; j <= length; ++j) {
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

    *result = previous[length];

    free(previous);
    free(current);
    return 0;
}

static int append_bytes(unsigned char **input,
                        size_t *length,
                        size_t *capacity,
                        const unsigned char *data,
                        size_t count)
{
    size_t required;
    /* Possible weaknesses found:
     *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
     */
    size_t new_capacity;
    unsigned char *resized;

    if (input == NULL || length == NULL || capacity == NULL ||
        (data == NULL && count != 0) || *length > *capacity ||
        (*input == NULL && *capacity != 0)) {
        return -1;
    }

    if (count == 0) {
        return 0;
    }

    if (*length > SIZE_MAX - count) {
        return -1;
    }

    required = *length + count;

    if (required > *capacity) {
        new_capacity = *capacity == 0 ? 64 : *capacity;

        while (new_capacity < required) {
            if (new_capacity > SIZE_MAX / 2) {
                new_capacity = required;
                break;
            }
            new_capacity *= 2;
        }

        resized = realloc(*input, new_capacity);
        if (resized == NULL) {
            return -1;
        }

        *input = resized;
        *capacity = new_capacity;
    }

    if (*input == NULL || required > *capacity) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(*input + *length, data, count);
    *length = required;
    return 0;
}

int main(void)
{
    unsigned char *input = NULL;
    unsigned char *buffer = NULL;
    size_t capacity = 0;
    size_t length = 0;
    size_t result = 0;
    const size_t buffer_size = 4096;
    int input_complete = 0;
    int status = EXIT_FAILURE;

    buffer = malloc(buffer_size);
    if (buffer == NULL) {
        goto cleanup;
    }

    while (!input_complete) {
        size_t count = fread(buffer, 1, buffer_size, stdin);
        size_t usable = count;

        for (size_t i = 0; i < count; ++i) {
            if (buffer[i] == '\n') {
                usable = i;
                input_complete = 1;
                break;
            }
        }

        if (append_bytes(&input, &length, &capacity, buffer, usable) != 0) {
            goto cleanup;
        }

        if (!input_complete && count < buffer_size) {
            if (ferror(stdin)) {
                goto cleanup;
            }
            input_complete = 1;
        }
    }

    if (longest_repeating_subsequence(input, length, &result) != 0) {
        goto cleanup;
    }

    if (printf("%zu\n", result) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(buffer);
    free(input);
    return status;
}