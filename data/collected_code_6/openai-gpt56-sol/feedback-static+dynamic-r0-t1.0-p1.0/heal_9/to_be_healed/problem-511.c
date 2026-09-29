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

    for (uint64_t factor = 3; factor <= n / factor; factor += 2) {
        while (n % factor == 0) {
            if (sum > UINT64_MAX - factor) {
                return 0;
            }
            sum += factor;
            n /= factor;
        }
    }

    if (n > 1) {
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
    int status = 0;

    if (value == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == capacity) {
            size_t new_capacity;
            char *new_line;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    goto cleanup;
                }
                new_capacity = capacity * 2;
            }

            new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                goto cleanup;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
    }

    if (ch == EOF && (ferror(stdin) || length == 0)) {
        goto cleanup;
    }

    if (length == capacity) {
        size_t new_capacity;
        char *new_line;

        if (capacity == SIZE_MAX) {
            goto cleanup;
        }

        new_capacity = capacity + 1;
        new_line = realloc(line, new_capacity);
        if (new_line == NULL) {
            goto cleanup;
        }

        line = new_line;
        /* Possible weaknesses found:
         *  Value stored to 'capacity' is never read [deadcode.DeadStores]
         */
        capacity = new_capacity;
    }

    line[length] = '\0';
    start = line;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        goto cleanup;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || parsed == 0 ||
        parsed > UINT64_MAX) {
        goto cleanup;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        goto cleanup;
    }

    *value = (uint64_t)parsed;
    status = 1;

cleanup:
    free(line);
    return status;
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