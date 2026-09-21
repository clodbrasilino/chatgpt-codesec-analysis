#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_ways(size_t n, uint64_t k, uint64_t *result)
{
    uint64_t same;
    uint64_t different;

    if (result == NULL || n == 0 || k == 0) {
        return 0;
    }

    if (n == 1) {
        *result = k;
        return 1;
    }

    if (k - 1 > UINT64_MAX / k) {
        return 0;
    }

    same = k;
    different = k * (k - 1);

    for (size_t i = 3; i <= n; ++i) {
        uint64_t total;

        if (same > UINT64_MAX - different) {
            return 0;
        }

        total = same + different;

        if (k > 1 && total > UINT64_MAX / (k - 1)) {
            return 0;
        }

        same = different;
        different = total * (k - 1);
    }

    if (same > UINT64_MAX - different) {
        return 0;
    }

    *result = same + different;
    return 1;
}

static int read_line(char *buffer, size_t size)
{
    int ch;
    size_t length;

    if (buffer == NULL || size < 2 || fgets(buffer, size, stdin) == NULL) {
        return 0;
    }

    length = 0;
    while (buffer[length] != '\0' && buffer[length] != '\n') {
        ++length;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
        return 1;
    }

    if (feof(stdin)) {
        return 1;
    }

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return 0;
}

static int parse_uintmax(const char **cursor, uintmax_t *value)
{
    char *end;
    uintmax_t parsed;

    while (**cursor == ' ' || **cursor == '\t' || **cursor == '\r' ||
           **cursor == '\v' || **cursor == '\f') {
        ++*cursor;
    }

    if (**cursor == '\0' || **cursor == '+' || **cursor == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(*cursor, &end, 10);

    if (errno == ERANGE || end == *cursor) {
        return 0;
    }

    *cursor = end;
    *value = parsed;
    return 1;
}

static int read_values(size_t *n, uint64_t *k)
{
    char buffer[256];
    const char *cursor;
    uintmax_t n_value;
    uintmax_t k_value;

    if (n == NULL || k == NULL || !read_line(buffer, sizeof(buffer))) {
        return 0;
    }

    cursor = buffer;

    if (!parse_uintmax(&cursor, &n_value) ||
        !parse_uintmax(&cursor, &k_value)) {
        return 0;
    }

    while (*cursor == ' ' || *cursor == '\t' || *cursor == '\r' ||
           *cursor == '\v' || *cursor == '\f') {
        ++cursor;
    }

    if (*cursor != '\0' ||
        n_value == 0 || n_value > SIZE_MAX ||
        k_value == 0 || k_value > UINT64_MAX) {
        return 0;
    }

    *n = (size_t)n_value;
    *k = (uint64_t)k_value;
    return 1;
}

int main(void)
{
    size_t n;
    uint64_t k;
    uint64_t result;

    if (!read_values(&n, &k)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!count_ways(n, k, &result)) {
        fputs("Invalid input or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}