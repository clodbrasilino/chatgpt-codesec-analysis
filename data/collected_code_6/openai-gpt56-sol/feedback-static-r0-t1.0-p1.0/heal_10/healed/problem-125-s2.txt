#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

static int max_zero_one_difference(const char *string, size_t length,
                                   size_t *start, size_t *end)
{
    int current = 0;
    int maximum = 0;
    size_t current_start = 0;

    if (string == NULL || start == NULL || end == NULL ||
        length == 0 || length > (size_t)INT_MAX) {
        return -1;
    }

    *start = 0;
    *end = 0;

    for (size_t i = 0; i < length; ++i) {
        int value;

        if (string[i] == '0') {
            value = 1;
        } else if (string[i] == '1') {
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

static int append_character(char **input, size_t *length, size_t *capacity,
                            char character)
{
    char *new_input;
    size_t new_capacity;

    if (input == NULL || length == NULL || capacity == NULL ||
        *length >= (size_t)INT_MAX) {
        return -1;
    }

    if (*length == *capacity) {
        if (*capacity == 0) {
            new_capacity = 64;
        } else {
            if (*capacity > (size_t)INT_MAX / 2) {
                new_capacity = (size_t)INT_MAX;
            } else {
                new_capacity = *capacity * 2;
            }
        }

        if (new_capacity <= *capacity ||
            new_capacity > SIZE_MAX / sizeof **input) {
            return -1;
        }

        new_input = realloc(*input, new_capacity * sizeof **input);
        if (new_input == NULL) {
            return -1;
        }

        *input = new_input;
        *capacity = new_capacity;
    }

    (*input)[*length] = character;
    ++(*length);
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    size_t start;
    size_t end;
    int character;
    int result;
    int status = EXIT_FAILURE;

    for (;;) {
        character = getchar();

        if (character == EOF) {
            if (ferror(stdin)) {
                goto cleanup;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (character == '\r') {
            character = getchar();

            if (character == EOF) {
                if (ferror(stdin)) {
                    goto cleanup;
                }
            } else if (character != '\n' && ungetc(character, stdin) == EOF) {
                goto cleanup;
            }

            break;
        }

        if (character != '0' && character != '1') {
            goto cleanup;
        }

        if (append_character(&input, &length, &capacity,
                             (char)character) != 0) {
            goto cleanup;
        }
    }

    if (length == 0) {
        goto cleanup;
    }

    result = max_zero_one_difference(input, length, &start, &end);
    if (result < 0) {
        goto cleanup;
    }

    if (printf("%d\n", result) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}