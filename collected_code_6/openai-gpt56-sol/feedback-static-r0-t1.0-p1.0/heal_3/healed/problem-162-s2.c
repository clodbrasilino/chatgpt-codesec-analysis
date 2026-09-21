#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int sum_positive_sequence(int64_t n, int64_t *result)
{
    int64_t a;
    int64_t b;

    if (result == NULL || n <= 0 || n == INT64_MAX) {
        return -1;
    }

    a = n;
    b = n + 1;

    if (a % 2 == 0) {
        a /= 2;
    } else {
        b /= 2;
    }

    if (a > INT64_MAX / b) {
        return -1;
    }

    *result = a * b;
    return 0;
}

int main(void)
{
    char input[128];
    char *end;
    int64_t sum;
    intmax_t parsed;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoimax(input, &end, 10);

    if (errno == ERANGE || end == input ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    if (sum_positive_sequence((int64_t)parsed, &sum) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}