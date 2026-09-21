#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int count_nonempty_substrings(size_t length, uintmax_t *count)
{
    uintmax_t n;
    uintmax_t a;
    uintmax_t b;

    if (count == NULL || length > UINTMAX_MAX) {
        return -1;
    }

    n = (uintmax_t)length;
    a = n;
    b = n + 1;

    if (b == 0) {
        return -1;
    }

    if ((a & UINTMAX_C(1)) == 0) {
        a /= 2;
    } else {
        b /= 2;
    }

    if (a != 0 && b > UINTMAX_MAX / a) {
        return -1;
    }

    *count = a * b;
    return 0;
}

int main(void)
{
    size_t length = 0;
    uintmax_t count;
    int ch;

    for (;;) {
        ch = getchar();

        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (length == SIZE_MAX) {
            return 1;
        }

        ++length;
    }

    if (ch == EOF && ferror(stdin)) {
        return 1;
    }

    if (count_nonempty_substrings(length, &count) != 0) {
        return 1;
    }

    if (printf("%" PRIuMAX "\n", count) < 0) {
        return 1;
    }

    return 0;
}