#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int count_nonempty_substrings(size_t length, uintmax_t *count)
{
    uintmax_t n;

    if (count == NULL || length > UINTMAX_MAX) {
        return -1;
    }

    n = (uintmax_t)length;

    if (n != 0 && n + 1 > UINTMAX_MAX / n) {
        return -1;
    }

    *count = n * (n + 1) / 2;
    return 0;
}

int main(void)
{
    size_t length = 0;
    uintmax_t count;
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
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