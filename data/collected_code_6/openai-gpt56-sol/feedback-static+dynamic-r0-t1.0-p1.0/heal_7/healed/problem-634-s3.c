#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_fourth_powers_of_evens(uint64_t n, uint64_t *result)
{
    uint64_t sum = 0;

    if (result == NULL) {
        return -1;
    }

    for (uint64_t i = 1; i <= n; ++i) {
        uint64_t even;
        uint64_t square;
        uint64_t fourth;

        if (i > UINT64_MAX / UINT64_C(2)) {
            return -1;
        }

        even = i * UINT64_C(2);

        if (even > UINT64_MAX / even) {
            return -1;
        }

        square = even * even;

        if (square > UINT64_MAX / square) {
            return -1;
        }

        fourth = square * square;

        if (sum > UINT64_MAX - fourth) {
            return -1;
        }

        sum += fourth;
    }

    *result = sum;
    return 0;
}

static int read_uint64(uint64_t *value)
{
    char buffer[128];
    char *start;
    char *end;
    uintmax_t parsed;
    size_t length;

    if (value == NULL) {
        return -1;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    length = 0;
    while (buffer[length] != '\0' && buffer[length] != '\n') {
        ++length;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
    } else if (!feof(stdin)) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        return -1;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        return -1;
    }

    if (*start == '+') {
        ++start;
    }

    if (!isdigit((unsigned char)*start)) {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (errno == ERANGE || parsed > UINT64_MAX) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = (uint64_t)parsed;
    return 0;
}

int main(void)
{
    uint64_t n;
    uint64_t result;

    if (read_uint64(&n) != 0) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (sum_fourth_powers_of_evens(n, &result) != 0) {
        fputs("Result exceeds the supported range.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}