#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static size_t minimum_rotations(const char *string, size_t length)
{
    size_t *prefix;
    size_t matched = 0;
    size_t period;
    size_t rotations;

    if (string == NULL || length == 0) {
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*prefix)) {
        return length;
    }

    prefix = calloc(length, sizeof(*prefix));
    if (prefix == NULL) {
        return length;
    }

    for (size_t index = 1; index < length; ++index) {
        while (matched > 0 && string[index] != string[matched]) {
            matched = prefix[matched - 1];
        }

        if (string[index] == string[matched]) {
            ++matched;
        }

        prefix[index] = matched;
    }

    period = length - prefix[length - 1];
    rotations = length % period == 0 ? period : length;

    free(prefix);
    return rotations;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    unsigned char buffer[4096];

    for (;;) {
        size_t count = fread(buffer, 1, sizeof(buffer), stdin);

        for (size_t index = 0; index < count; ++index) {
            char *resized;
            size_t required;
            size_t new_capacity;

            if (buffer[index] == '\n') {
                goto input_complete;
            }

            if (length == SIZE_MAX) {
                free(input);
                return EXIT_FAILURE;
            }

            required = length + 1;

            if (required > capacity) {
                new_capacity = capacity == 0 ? 64 : capacity;

                while (new_capacity < required) {
                    if (new_capacity > SIZE_MAX / 2) {
                        new_capacity = required;
                        break;
                    }
                    new_capacity *= 2;
                }

                resized = realloc(input, new_capacity);
                if (resized == NULL) {
                    free(input);
                    return EXIT_FAILURE;
                }

                input = resized;
                capacity = new_capacity;
            }

            input[length++] = (char)buffer[index];
        }

        if (count < sizeof(buffer)) {
            if (ferror(stdin)) {
                free(input);
                return EXIT_FAILURE;
            }
            break;
        }
    }

input_complete:
    printf("%zu\n", minimum_rotations(input, length));
    free(input);
    return EXIT_SUCCESS;
}