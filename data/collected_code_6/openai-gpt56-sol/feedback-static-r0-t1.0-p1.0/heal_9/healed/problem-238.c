#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

static int count_nonempty_substrings(size_t length, uintmax_t *count)
{
    uintmax_t a;
    uintmax_t b;

    if (count == NULL || length > UINTMAX_MAX) {
        return 0;
    }

    a = (uintmax_t)length;

    if (a == UINTMAX_MAX) {
        return 0;
    }

    b = a + UINTMAX_C(1);

    if ((a & UINTMAX_C(1)) == 0) {
        a /= UINTMAX_C(2);
    } else {
        b /= UINTMAX_C(2);
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
    char *input = malloc(capacity);
    uintmax_t count;

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        int ch = getchar();

        if (ch == EOF) {
            if (ferror(stdin)) {
                free(input);
                return EXIT_FAILURE;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length >= capacity - 1) {
            size_t new_capacity;
            char *temporary;

            if (capacity > SIZE_MAX / 2) {
                free(input);
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2;
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