#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static int count_nonempty_substrings(const char *str, uintmax_t *count)
{
    size_t length;
    uintmax_t n;

    if (str == NULL || count == NULL) {
        return -1;
    }

    length = strlen(str);
    n = (uintmax_t)length;

    if (n != 0U && n + 1U > UINTMAX_MAX / n) {
        return -1;
    }

    *count = n * (n + 1U) / 2U;
    return 0;
}

int main(void)
{
    char input[4096];
    uintmax_t count;

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            return 1;
        }
        input[0] = '\0';
    } else {
        size_t length = strlen(input);

        if (length > 0U && input[length - 1U] == '\n') {
            input[length - 1U] = '\0';
        } else if (!feof(stdin)) {
            int ch;

            do {
                ch = getchar();
            } while (ch != '\n' && ch != EOF);

            if (ferror(stdin)) {
                return 1;
            }

            return 1;
        }
    }

    if (count_nonempty_substrings(input, &count) != 0) {
        return 1;
    }

    if (printf("%" PRIuMAX "\n", count) < 0) {
        return 1;
    }

    return 0;
}