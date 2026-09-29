#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int count_nonempty_substrings(size_t length, uintmax_t *count)
{
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

    a = (uintmax_t)length;

    if (a == UINTMAX_MAX) {
        return -1;
    }

    b = a + UINTMAX_C(1);

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
    char input[4096];
    size_t length = 0;
    uintmax_t count;

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            return 1;
        }
    } else {
        while (input[length] != '\0' && input[length] != '\n') {
            ++length;
        }

        if (input[length] != '\n' && !feof(stdin)) {
            int ch;

            do {
                ch = getchar();

                if (ch == EOF) {
                    if (ferror(stdin)) {
                        return 1;
                    }
                    break;
                }

                if (length == SIZE_MAX) {
                    return 1;
                }

                ++length;
            } while (ch != '\n');

            if (ch == '\n') {
                --length;
            }
        }
    }

    if (count_nonempty_substrings(length, &count) != 0) {
        return 1;
    }

    if (printf("%" PRIuMAX "\n", count) < 0) {
        return 1;
    }

    return 0;
}