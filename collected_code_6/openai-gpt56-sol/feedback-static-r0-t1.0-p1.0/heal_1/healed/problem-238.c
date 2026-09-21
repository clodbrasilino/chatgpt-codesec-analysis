#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define INPUT_CAPACITY 4096U

static int count_nonempty_substrings(size_t length, uintmax_t *count)
{
    uintmax_t n;

    if (count == NULL) {
        return 0;
    }

    n = (uintmax_t)length;

    if (n > 0 && n > (UINTMAX_MAX - 1U) / n) {
        return 0;
    }

    *count = n * (n + 1U) / 2U;
    return 1;
}

int main(void)
{
    char input[INPUT_CAPACITY];
    size_t length = 0;
    uintmax_t count;
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length + 1U >= sizeof input) {
            while (ch != '\n' && ch != EOF) {
                ch = getchar();
            }
            return 1;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        return 1;
    }

    input[length] = '\0';

    if (!count_nonempty_substrings(length, &count)) {
        return 1;
    }

    if (printf("%" PRIuMAX "\n", count) < 0) {
        return 1;
    }

    return 0;
}