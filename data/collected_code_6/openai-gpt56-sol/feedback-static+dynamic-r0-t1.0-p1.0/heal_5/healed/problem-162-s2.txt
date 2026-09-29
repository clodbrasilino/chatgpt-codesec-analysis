#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_positive_sequence(int64_t n, int64_t *result)
{
    int64_t terms;
    int64_t factor;

    if (result == NULL || n <= 0) {
        return -1;
    }

    terms = n / 2 + n % 2;
    factor = n - terms + 1;

    if (terms > INT64_MAX / factor) {
        return -1;
    }

    *result = terms * factor;
    return 0;
}

static int read_int64(int64_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    intmax_t parsed;

    if (value == NULL) {
        return -1;
    }

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return -1;
    }

    if (length > 0 && line[length - 1] == '\n') {
        line[length - 1] = '\0';
    }

    errno = 0;
    parsed = strtoimax(line, &end, 10);

    if (errno == ERANGE || end == line ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(line);
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return -1;
    }

    *value = (int64_t)parsed;
    free(line);
    return 0;
}

int main(void)
{
    int64_t n;
    int64_t sum;

    if (read_int64(&n) != 0) {
        return EXIT_FAILURE;
    }

    if (sum_positive_sequence(n, &sum) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}