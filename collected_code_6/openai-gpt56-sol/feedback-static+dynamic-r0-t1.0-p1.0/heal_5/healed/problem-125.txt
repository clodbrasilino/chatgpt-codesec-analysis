#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH 1000000U

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

static int discard_remainder(FILE *stream)
{
    char discard_buffer[4096];

    if (stream == NULL) {
        return 0;
    }

    while (fgets(discard_buffer, sizeof discard_buffer, stream) != NULL) {
        size_t i = 0;

        while (discard_buffer[i] != '\0') {
            if (discard_buffer[i] == '\n') {
                return 1;
            }
            ++i;
        }
    }

    return !ferror(stream);
}

static int read_binary_line(char *buffer, size_t capacity, size_t *length)
{
    size_t used = 0;
    int complete = 0;

    if (buffer == NULL || length == NULL || capacity < 2U) {
        return 0;
    }

    *length = 0;

    while (!complete) {
        size_t available = capacity - used;

        if (available < 2U) {
            if (!discard_remainder(stdin)) {
                return 0;
            }
            return 0;
        }

        if (fgets(buffer + used, (int)available, stdin) == NULL) {
            if (ferror(stdin) || used == 0U) {
                return 0;
            }
            break;
        }

        while (buffer[used] != '\0') {
            if (buffer[used] == '\n') {
                buffer[used] = '\0';
                complete = 1;
                break;
            }

            if (buffer[used] == '\r') {
                if (buffer[used + 1U] == '\n') {
                    buffer[used] = '\0';
                    complete = 1;
                    break;
                }

                if (buffer[used + 1U] == '\0') {
                    int next = fgetc(stdin);

                    if (next == '\n' || next == EOF) {
                        if (next == EOF && ferror(stdin)) {
                            return 0;
                        }
                        buffer[used] = '\0';
                        complete = 1;
                        break;
                    }

                    if (!discard_remainder(stdin)) {
                        return 0;
                    }
                    return 0;
                }

                if (!discard_remainder(stdin)) {
                    return 0;
                }
                return 0;
            }

            if (buffer[used] != '0' && buffer[used] != '1') {
                if (!discard_remainder(stdin)) {
                    return 0;
                }
                return 0;
            }

            ++used;

            if (used >= capacity - 1U) {
                if (!discard_remainder(stdin)) {
                    return 0;
                }
                return 0;
            }
        }
    }

    if (used == 0U) {
        return 0;
    }

    buffer[used] = '\0';
    *length = used;
    return 1;
}

int main(void)
{
    const size_t capacity = (size_t)MAX_INPUT_LENGTH + 1U;
    char *input;
    size_t length;
    size_t start;
    size_t end;
    int result;

    input = malloc(capacity);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    if (!read_binary_line(input, capacity, &length)) {
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