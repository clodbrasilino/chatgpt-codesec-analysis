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
    size_t length = 0;
    uintmax_t count;
    int ch;

    while ((ch = getchar()) != EOF && ch != '\n') {
        if (length == SIZE_MAX) {
            return EXIT_FAILURE;
        }
        ++length;
    }

    if (ch == EOF && ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (!count_nonempty_substrings(length, &count)) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIuMAX "\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}