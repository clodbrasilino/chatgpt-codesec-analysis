#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

int main(void)
{
    unsigned char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    size_t result = 0;
    unsigned char buffer[4096];

    for (;;) {
        size_t count = fread(buffer, 1, sizeof(buffer), stdin);

        for (size_t i = 0; i < count; ++i) {
            if (buffer[i] == '\n') {
                count = i;
                goto input_complete;
            }
        }

        if (count != 0) {
            if (length > SIZE_MAX - count) {
                free(input);
                return EXIT_FAILURE;
            }

            size_t required = length + count;

            if (required > capacity) {
                size_t new_capacity = capacity == 0 ? 64 : capacity;

                while (new_capacity < required) {
                    if (new_capacity > SIZE_MAX / 2) {
                        new_capacity = required;
                        break;
                    }
                    new_capacity *= 2;
                }

                unsigned char *resized = realloc(input, new_capacity);
                if (resized == NULL) {
                    free(input);
                    return EXIT_FAILURE;
                }

                input = resized;
                capacity = new_capacity;
            }

            for (size_t i = 0; i < count; ++i) {
                input[length + i] = buffer[i];
            }
            length += count;
        }

        if (count < sizeof(buffer)) {
            if (ferror(stdin)) {
                free(input);
                return EXIT_FAILURE;
            }
            break;
        }
    }

    goto process_input;

input_complete:
    if (count != 0) {
        if (length > SIZE_MAX - count) {
            free(input);
            return EXIT_FAILURE;
        }

        size_t required = length + count;

        if (required > capacity) {
            size_t new_capacity = capacity == 0 ? 64 : capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            unsigned char *resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        for (size_t i = 0; i < count; ++i) {
            input[length + i] = buffer[i];
        }
        length += count;
    }

process_input:
    if (longest_repeating_subsequence(input, length, &result) != 0) {
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