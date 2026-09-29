#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

static int count_nonempty_substrings(size_t length, uintmax_t *count)
{
    uintmax_t n;
    uintmax_t a;
    uintmax_t b;

    if (count == NULL || length > UINTMAX_MAX) {
        return 0;
    }

    n = (uintmax_t)length;
    a = n;
    b = n + 1;

    if ((a & 1U) == 0) {
        a /= 2;
    } else {
        b /= 2;
    }

    if (a != 0 && b > UINTMAX_MAX / a) {
        return 0;
    }

    *count = a * b;
    return 1;
}

int main(void)
{
    size_t capacity = 128;
    size_t length = 0;
    char *input;
    uintmax_t count;
    int ch;

    input = malloc(capacity);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        ch = getchar();

        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *temporary;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            temporary = realloc(input, new_capacity);
            if (temporary == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = temporary;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    if (!count_nonempty_substrings(length, &count)) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%" PRIuMAX "\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}