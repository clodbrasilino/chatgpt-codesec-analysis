#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int longest_repeating_subsequence(const unsigned char *string,
                                         size_t length,
                                         size_t *result)
{
    size_t *previous = NULL;
    size_t *current = NULL;
    size_t elements;

    if (result == NULL || (string == NULL && length != 0)) {
        return -1;
    }

    *result = 0;

    if (length == 0) {
        return 0;
    }

    if (length == SIZE_MAX) {
        return -1;
    }

    elements = length + 1;

    if (elements > SIZE_MAX / sizeof(*previous)) {
        return -1;
    }

    previous = calloc(elements, sizeof(*previous));
    current = calloc(elements, sizeof(*current));

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

    if (input == NULL || length == NULL || capacity == NULL ||
        (data == NULL && count != 0) ||
        *length > *capacity ||
        (*input == NULL && *capacity != 0) ||
        (*input != NULL && *capacity == 0)) {
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
        size_t new_capacity = *capacity == 0 ? 64 : *capacity;
        unsigned char *resized;

        while (new_capacity < required) {
            if (new_capacity > SIZE_MAX / 2) {
                new_capacity = required;
                break;
            }

            new_capacity *= 2;
        }

        if (new_capacity < required) {
            return -1;
        }

        resized = realloc(*input, new_capacity);
        if (resized == NULL) {
            return -1;
        }

        *input = resized;
        *capacity = new_capacity;
    }

    if (*input == NULL ||
        *length > *capacity ||
        count > *capacity - *length) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        (*input)[*length + i] = data[i];
    }

    *length = required;
    return 0;
}

int main(void)
{
    enum { BUFFER_SIZE = 4096 };

    unsigned char *input = NULL;
    unsigned char buffer[BUFFER_SIZE];
    size_t capacity = 0;
    size_t length = 0;
    size_t result = 0;
    int input_complete = 0;
    int status = EXIT_FAILURE;

    while (!input_complete) {
        size_t count = fread(buffer, 1, sizeof(buffer), stdin);
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

        if (!input_complete && count < sizeof(buffer)) {
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
    free(input);
    return status;
}