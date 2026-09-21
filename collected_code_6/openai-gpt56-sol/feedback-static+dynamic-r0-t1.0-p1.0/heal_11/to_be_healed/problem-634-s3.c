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
    char *line = NULL;
    size_t capacity = 0;
    size_t length = 0;
    char *start;
    char *end;
    uintmax_t parsed;
    int ch;

    if (value == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *resized;
        /* Possible weaknesses found:
         *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
         */
        size_t new_capacity;

        if (length == SIZE_MAX - 1) {
            free(line);
            return -1;
        }

        if (length + 1 >= capacity) {
            if (capacity == 0) {
                new_capacity = 32;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(line);
                    return -1;
                }
                new_capacity = capacity * 2;
            }

            resized = realloc(line, new_capacity);
            if (resized == NULL) {
                free(line);
                return -1;
            }

            line = resized;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(line);
        return -1;
    }

    if (ch == EOF && length == 0) {
        free(line);
        return -1;
    }

    if (length + 1 > capacity) {
        char *resized = realloc(line, length + 1);

        if (resized == NULL) {
            free(line);
            return -1;
        }

        line = resized;
    }

    line[length] = '\0';
    start = line;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        free(line);
        return -1;
    }

    if (*start == '+') {
        ++start;
    }

    if (!isdigit((unsigned char)*start)) {
        free(line);
        return -1;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (errno == ERANGE || parsed > UINT64_MAX) {
        free(line);
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return -1;
    }

    *value = (uint64_t)parsed;
    free(line);
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