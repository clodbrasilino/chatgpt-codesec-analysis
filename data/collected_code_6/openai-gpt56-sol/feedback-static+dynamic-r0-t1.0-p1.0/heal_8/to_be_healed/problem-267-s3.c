#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

static int sum_odd_squares(uint64_t n, uint64_t *result)
{
    const uint64_t limit = UINT64_C(1903309);
    uint64_t a;
    uint64_t b;
    uint64_t c;

    if (result == NULL || n > limit) {
        return 0;
    }

    a = n;
    b = UINT64_C(2) * n - UINT64_C(1);
    c = UINT64_C(2) * n + UINT64_C(1);

    if (a % UINT64_C(3) == 0) {
        a /= UINT64_C(3);
    } else if (b % UINT64_C(3) == 0) {
        b /= UINT64_C(3);
    } else {
        c /= UINT64_C(3);
    }

    if (a != 0 && b > UINT64_MAX / a) {
        return 0;
    }

    a *= b;

    if (c != 0 && a > UINT64_MAX / c) {
        return 0;
    }

    *result = a * c;
    return 1;
}

static int read_uint64(uint64_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t length = 0;
    char *start;
    char *end;
    uintmax_t parsed;
    int ch;

    if (value == NULL) {
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (length == capacity) {
            size_t new_capacity;
            char *new_line;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(line);
                    return 0;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity <= length) {
                free(line);
                return 0;
            }

            new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                free(line);
                return 0;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
    }

    if (ch == EOF && (ferror(stdin) || length == 0)) {
        free(line);
        return 0;
    }

    if (length == capacity) {
        char *new_line;

        if (capacity == SIZE_MAX) {
            free(line);
            return 0;
        }

        new_line = realloc(line, capacity + 1);
        if (new_line == NULL) {
            free(line);
            return 0;
        }

        line = new_line;
        /* Possible weaknesses found:
         *  Variable 'capacity' is assigned a value that is never used. [unreadVariable]
         */
        capacity++;
    }

    line[length] = '\0';
    start = line;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '+' || *start == '-') {
        free(line);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || parsed > UINT64_MAX) {
        free(line);
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return 0;
    }

    *value = (uint64_t)parsed;
    free(line);
    return 1;
}

int main(void)
{
    uint64_t value;
    uint64_t result;

    if (!read_uint64(&value)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_odd_squares(value, &result)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}