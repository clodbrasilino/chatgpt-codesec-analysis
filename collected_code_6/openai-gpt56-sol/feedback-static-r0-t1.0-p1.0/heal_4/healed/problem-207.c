#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int longest_repeating_subsequence(const char *string,
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

static int read_line(FILE *stream, char **buffer, size_t *length)
{
    char *data = NULL;
    size_t used = 0;
    size_t capacity = 0;

    if (stream == NULL || buffer == NULL || length == NULL) {
        return -1;
    }

    *buffer = NULL;
    *length = 0;

    for (;;) {
        if (used == capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(data);
                    return -1;
                }

                new_capacity = capacity * 2;
            }

            char *resized = realloc(data, new_capacity);
            if (resized == NULL) {
                free(data);
                return -1;
            }

            data = resized;
            capacity = new_capacity;
        }

        size_t available = capacity - used;
        int read_size = available > (size_t)INT_MAX
                            ? INT_MAX
                            : (int)available;

        if (fgets(data + used, read_size, stream) == NULL) {
            if (ferror(stream)) {
                free(data);
                return -1;
            }

            break;
        }

        size_t count = 0;

        while (count < available &&
               data[used + count] != '\0' &&
               data[used + count] != '\n') {
            ++count;
        }

        if (count < available && data[used + count] == '\n') {
            used += count;
            break;
        }

        used += count;

        if (count + 1 < available) {
            break;
        }
    }

    if (used > 0 && data[used - 1] == '\r') {
        --used;
    }

    if (used == 0) {
        free(data);
        data = NULL;
    } else {
        char *resized = realloc(data, used);
        if (resized != NULL) {
            data = resized;
        }
    }

    *buffer = data;
    *length = used;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t result = 0;

    if (read_line(stdin, &input, &length) != 0) {
        return EXIT_FAILURE;
    }

    if (longest_repeating_subsequence(input, length, &result) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}