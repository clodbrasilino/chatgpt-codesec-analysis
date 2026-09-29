#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_cubes(uint64_t n, uint64_t k, uint64_t *result)
{
    uint64_t per_side;

    if (result == NULL || k == 0 || k > n) {
        return 0;
    }

    per_side = n / k;

    if (per_side > UINT64_MAX / per_side) {
        return 0;
    }

    if (per_side * per_side > UINT64_MAX / per_side) {
        return 0;
    }

    *result = per_side * per_side * per_side;
    return 1;
}

static int read_uint64_pair(uint64_t *n, uint64_t *k)
{
    char buffer[256];
    char *cursor;
    char *end;
    uintmax_t first;
    uintmax_t second;
    size_t length;

    if (n == NULL || k == NULL) {
        return 0;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    length = 0;
    while (length < sizeof buffer && buffer[length] != '\0') {
        ++length;
    }

    if (length == 0 || (buffer[length - 1] != '\n' && !feof(stdin))) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        return 0;
    }

    cursor = buffer;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '-' || *cursor == '\0') {
        return 0;
    }

    errno = 0;
    first = strtoumax(cursor, &end, 10);
    if (cursor == end || errno == ERANGE || first > UINT64_MAX) {
        return 0;
    }

    cursor = end;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '-' || *cursor == '\0') {
        return 0;
    }

    errno = 0;
    second = strtoumax(cursor, &end, 10);
    if (cursor == end || errno == ERANGE || second > UINT64_MAX) {
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *n = (uint64_t)first;
    *k = (uint64_t)second;
    return 1;
}

int main(void)
{
    uint64_t n;
    uint64_t k;
    uint64_t result;

    if (!read_uint64_pair(&n, &k)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!count_cubes(n, k, &result)) {
        fputs("Invalid dimensions or result overflow\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}