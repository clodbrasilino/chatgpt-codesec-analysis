#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int minimum_swaps(const char *str, size_t length, size_t *result)
{
    size_t open_count = 0;
    size_t close_count = 0;
    size_t imbalance = 0;
    size_t swaps = 0;

    if (result == NULL || (str == NULL && length != 0)) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if (str[i] == '[') {
            if (open_count == SIZE_MAX) {
                return -1;
            }

            ++open_count;

            if (imbalance != 0) {
                if (swaps > SIZE_MAX - imbalance) {
                    return -1;
                }

                swaps += imbalance;
                --imbalance;
            }
        } else if (str[i] == ']') {
            if (close_count == SIZE_MAX) {
                return -1;
            }

            ++close_count;

            if (close_count > open_count) {
                imbalance = close_count - open_count;
            }
        } else {
            return -1;
        }
    }

    if (open_count != close_count) {
        return -1;
    }

    *result = swaps;
    return 0;
}

static int read_input(char **buffer, size_t *length)
{
    size_t capacity = 256;
    char *input;
    int character;

    if (buffer == NULL || length == NULL) {
        return -1;
    }

    input = malloc(capacity);
    if (input == NULL) {
        return -1;
    }

    *length = 0;

    for (;;) {
        character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin)) {
                free(input);
                return -1;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (character == '\r') {
            character = fgetc(stdin);

            if (character == EOF) {
                if (ferror(stdin)) {
                    free(input);
                    return -1;
                }
            } else if (character != '\n' && ungetc(character, stdin) == EOF) {
                free(input);
                return -1;
            }

            break;
        }

        if (character != '[' && character != ']') {
            free(input);
            return -1;
        }

        if (*length == capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity > SIZE_MAX / 2) {
                free(input);
                return -1;
            }

            new_capacity = capacity * 2;
            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return -1;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[*length] = (char)character;
        ++*length;
    }

    *buffer = input;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t swaps;
    int status = EXIT_FAILURE;

    if (read_input(&input, &length) != 0) {
        goto cleanup;
    }

    if (minimum_swaps(input, length, &swaps) != 0) {
        goto cleanup;
    }

    if (printf("%zu\n", swaps) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}