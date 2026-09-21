#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int minimum_factor_sum(uint64_t n, uint64_t *result)
{
    uint64_t sum = 0;

    if (n == 0 || result == NULL) {
        return 0;
    }

    while ((n & UINT64_C(1)) == 0) {
        if (sum > UINT64_MAX - UINT64_C(2)) {
            return 0;
        }

        sum += UINT64_C(2);
        n /= UINT64_C(2);
    }

    for (uint64_t factor = UINT64_C(3);
         factor <= n / factor;
         factor += UINT64_C(2)) {
        while (n % factor == 0) {
            if (sum > UINT64_MAX - factor) {
                return 0;
            }

            sum += factor;
            n /= factor;
        }
    }

    if (n > UINT64_C(1)) {
        if (sum > UINT64_MAX - n) {
            return 0;
        }

        sum += n;
    }

    *result = sum;
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

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *new_line;
        /* Possible weaknesses found:
         *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
         */
        size_t new_capacity;

        if (ch == '\0') {
            free(line);
            return 0;
        }

        if (length == capacity) {
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

    if (ch == EOF && ferror(stdin)) {
        free(line);
        return 0;
    }

    if (length == 0 && ch == EOF) {
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

    if (length > 0 && line[length - 1] == '\r') {
        line[--length] = '\0';
    }

    start = line;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-' || *start == '+') {
        free(line);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || parsed == 0 ||
        parsed > UINT64_MAX) {
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
        return EXIT_FAILURE;
    }

    if (!minimum_factor_sum(value, &result)) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}