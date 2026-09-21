#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int minimum_swaps(const char *str, size_t length, size_t *result)
{
    size_t open_count = 0;
    size_t close_count = 0;
    size_t imbalance = 0;
    size_t swaps = 0;

    if (str == NULL || result == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        if (str[i] == '[') {
            if (open_count == SIZE_MAX) {
                return 0;
            }

            ++open_count;

            if (imbalance != 0) {
                if (swaps > SIZE_MAX - imbalance) {
                    return 0;
                }

                swaps += imbalance;
                --imbalance;
            }
        } else if (str[i] == ']') {
            if (close_count == SIZE_MAX) {
                return 0;
            }

            ++close_count;
            imbalance = close_count > open_count
                      ? close_count - open_count
                      : 0;
        } else {
            return 0;
        }
    }

    if (open_count != close_count) {
        return 0;
    }

    *result = swaps;
    return 1;
}

static int read_bracket_string(FILE *stream, char **buffer, size_t *length)
{
    char *data = NULL;
    size_t used = 0;
    size_t capacity = 0;
    int character = EOF;

    if (stream == NULL || buffer == NULL || length == NULL) {
        return 0;
    }

    *buffer = NULL;
    *length = 0;

    for (;;) {
        character = fgetc(stream);

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

        if (character == '\r') {
            int next = fgetc(stream);

            if (next == EOF) {
                if (ferror(stream)) {
                    free(data);
                    return 0;
                }
                break;
            }

            if (next == '\n') {
                break;
            }

            free(data);
            return -1;
        }

        if (character != '[' && character != ']') {
            free(data);
            return -1;
        }

        if (used == capacity) {
            size_t new_capacity;
            char *new_data;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(data);
                    return 0;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity <= used) {
                free(data);
                return 0;
            }

            new_data = realloc(data, new_capacity);
            if (new_data == NULL) {
                free(data);
                return 0;
            }

            data = new_data;
            capacity = new_capacity;
        }

        data[used++] = (char)character;
    }

    if (data == NULL) {
        data = malloc(1);
        if (data == NULL) {
            return 0;
        }
    }

    *buffer = data;
    *length = used;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t swaps = 0;
    int read_status;
    int status = EXIT_FAILURE;

    read_status = read_bracket_string(stdin, &input, &length);

    if (read_status < 0) {
        fputs("Invalid bracket string\n", stderr);
        return EXIT_FAILURE;
    }

    if (read_status == 0) {
        return EXIT_FAILURE;
    }

    if (!minimum_swaps(input, length, &swaps)) {
        fputs("Invalid bracket string\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", swaps) >= 0) {
        status = EXIT_SUCCESS;
    }

    free(input);
    return status;
}