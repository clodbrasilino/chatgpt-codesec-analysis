#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>

static int count_nonempty_substrings(const char *str, uintmax_t *count)
{
    size_t length;

    if (str == NULL || count == NULL) {
        return 0;
    }

    length = strlen(str);

    if (length > 0 && (uintmax_t)length > (UINTMAX_MAX - 1) / (uintmax_t)length) {
        return 0;
    }

    *count = (uintmax_t)length * ((uintmax_t)length + 1) / 2;
    return 1;
}

int main(void)
{
    char input[4096];
    uintmax_t count;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    size_t length = strlen(input);

    if (length > 0 && input[length - 1] == '\n') {
        input[length - 1] = '\0';
    } else if (!feof(stdin)) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        if (ch == EOF && ferror(stdin)) {
            return 1;
        }

        return 1;
    }

    if (!count_nonempty_substrings(input, &count)) {
        return 1;
    }

    if (printf("%" PRIuMAX "\n", count) < 0) {
        return 1;
    }

    return 0;
}