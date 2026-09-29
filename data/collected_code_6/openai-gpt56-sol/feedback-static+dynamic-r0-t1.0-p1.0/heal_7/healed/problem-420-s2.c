#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <ctype.h>

static int cube_sum_even(uint64_t n, uint64_t *result)
{
    uint64_t a;
    uint64_t b;

    if (result == NULL || n == UINT64_MAX) {
        return -1;
    }

    a = n;
    b = n + UINT64_C(1);

    if ((a & UINT64_C(1)) == 0) {
        a /= UINT64_C(2);
    } else {
        b /= UINT64_C(2);
    }

    if (a != 0 && b > UINT64_MAX / a) {
        return -1;
    }

    a *= b;

    if (a != 0 && a > UINT64_MAX / a) {
        return -1;
    }

    a *= a;

    if (a > UINT64_MAX / UINT64_C(2)) {
        return -1;
    }

    *result = UINT64_C(2) * a;
    return 0;
}

static int read_number(uint64_t *value)
{
    char buffer[256];
    char *start;
    char *end;
    uintmax_t parsed;
    size_t length;

    if (value == NULL) {
        return -1;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return ferror(stdin) ? -2 : -3;
    }

    length = 0;
    while (length < sizeof buffer && buffer[length] != '\0') {
        ++length;
    }

    if (length == sizeof buffer) {
        return -3;
    }

    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[--length] = '\0';
        if (length > 0 && buffer[length - 1] == '\r') {
            buffer[--length] = '\0';
        }
    } else {
        int ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }

            if (ch == EOF && ferror(stdin)) {
                return -2;
            }

            return -3;
        }

        if (ch == EOF && ferror(stdin)) {
            return -2;
        }
    }

    start = buffer;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        return -3;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || parsed > UINT64_MAX) {
        return -3;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -3;
    }

    *value = (uint64_t)parsed;
    return 0;
}

int main(void)
{
    uint64_t input;
    uint64_t result;
    int status;

    status = read_number(&input);
    if (status != 0) {
        if (status == -2) {
            fputs("Failed to read input.\n", stderr);
        } else if (status == -1) {
            fputs("Unable to store input.\n", stderr);
        } else {
            fputs("Invalid input.\n", stderr);
        }

        return EXIT_FAILURE;
    }

    if (cube_sum_even(input, &result) != 0) {
        fputs("Result exceeds the supported range.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}