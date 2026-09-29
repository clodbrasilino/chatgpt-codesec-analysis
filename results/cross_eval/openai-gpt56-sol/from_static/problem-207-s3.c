#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int longest_repeating_subsequence(const unsigned char *str,
                                         size_t length,
                                         size_t *result)
{
    if (result == NULL || (str == NULL && length != 0) ||
        length == SIZE_MAX ||
        length + 1 > SIZE_MAX / sizeof(size_t)) {
        return 0;
    }

    size_t columns = length + 1;
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

static int read_line(unsigned char **buffer, size_t *length)
{
    if (buffer == NULL || length == NULL) {
        return 0;
    }

    *buffer = NULL;
    *length = 0;

    size_t capacity = 64;
    unsigned char *data = malloc(capacity);

    if (data == NULL) {
        return 0;
    }

    for (;;) {
        if (*length == capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(data);
                return 0;
            }

            size_t new_capacity = capacity * 2;
            unsigned char *resized = realloc(data, new_capacity);

            if (resized == NULL) {
                free(data);
                return 0;
            }

            data = resized;
            capacity = new_capacity;
        }

        size_t available = capacity - *length;
        size_t chunk_size = available > (size_t)INT32_MAX
                                ? (size_t)INT32_MAX
                                : available;

        if (fgets((char *)data + *length, (int)chunk_size, stdin) == NULL) {
            if (ferror(stdin)) {
                free(data);
                return 0;
            }

            if (*length == 0) {
                free(data);
                data = NULL;
            }

            *buffer = data;
            return 1;
        }

        size_t start = *length;

        while (*length < capacity && data[*length] != '\0' &&
               data[*length] != '\n') {
            ++*length;
        }

        if (*length < capacity && data[*length] == '\n') {
            *buffer = data;
            return 1;
        }

        if (*length < capacity && data[*length] == '\0') {
            if (*length == start) {
                *buffer = data;
                return 1;
            }

            continue;
        }
    }
}

int main(void)
{
    unsigned char *input = NULL;
    size_t length = 0;
    size_t result = 0;

    if (!read_line(&input, &length)) {
        return EXIT_FAILURE;
    }

    if (!longest_repeating_subsequence(input, length, &result)) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}