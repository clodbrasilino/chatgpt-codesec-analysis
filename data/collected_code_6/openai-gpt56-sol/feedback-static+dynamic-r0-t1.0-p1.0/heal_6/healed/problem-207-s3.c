#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int longest_repeating_subsequence(const char *str, size_t length,
                                         size_t *result)
{
    if (str == NULL || result == NULL || length == SIZE_MAX) {
        return 0;
    }

    const size_t columns = length + 1;

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

static int read_line(FILE *stream, char **buffer, size_t *length)
{
    if (stream == NULL || buffer == NULL || length == NULL) {
        return 0;
    }

    char *data = NULL;
    size_t capacity = 0;
    size_t used = 0;

    for (;;) {
        int character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream)) {
                free(data);
                return 0;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (used > SIZE_MAX - 2) {
            free(data);
            return 0;
        }

        if (!grow_buffer(&data, &capacity, used + 2)) {
            free(data);
            return 0;
        }

        data[used] = (char)(unsigned char)character;
        ++used;
    }

    if (used == SIZE_MAX ||
        !grow_buffer(&data, &capacity, used + 1)) {
        free(data);
        return 0;
    }

    data[used] = '\0';
    *buffer = data;
    *length = used;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t result = 0;

    if (!read_line(stdin, &input, &length)) {
        return EXIT_FAILURE;
    }

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