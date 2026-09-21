#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int count_nonempty_substrings(size_t length, uintmax_t *count)
{
    uintmax_t n;
    uintmax_t a;
    uintmax_t b;

    if (count == NULL) {
        return -1;
    }

#if SIZE_MAX > UINTMAX_MAX
    if (length > UINTMAX_MAX) {
        return -1;
    }
#endif

    n = (uintmax_t)length;

    if (n == UINTMAX_MAX) {
        return -1;
    }

    a = n;
    b = n + UINTMAX_C(1);

    if ((a & UINTMAX_C(1)) == 0) {
        a /= UINTMAX_C(2);
    } else {
        b /= UINTMAX_C(2);
    }

    if (a != 0 && b > UINTMAX_MAX / a) {
        return -1;
    }

    *count = a * b;
    return 0;
}

int main(void)
{
    uintmax_t count;
    size_t length = 0;
    int ch;

    while ((ch = getchar()) != EOF && ch != '\n') {
        if (length == SIZE_MAX) {
            return 1;
        }
        ++length;
    }

    if (ferror(stdin)) {
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