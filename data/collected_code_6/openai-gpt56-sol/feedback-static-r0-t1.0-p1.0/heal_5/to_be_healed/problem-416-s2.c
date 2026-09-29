#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t max_exchange_sum(uint64_t n)
{
    if (n < UINT64_C(12)) {
        return n;
    }

    uint64_t a = max_exchange_sum(n / UINT64_C(2));
    uint64_t b = max_exchange_sum(n / UINT64_C(3));
    uint64_t c = max_exchange_sum(n / UINT64_C(4));

    if (a > UINT64_MAX - b) {
        return UINT64_MAX;
    }

    uint64_t sum = a + b;

    if (sum > UINT64_MAX - c) {
        return UINT64_MAX;
    }

    sum += c;
    return sum > n ? sum : n;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == capacity) {
            size_t new_capacity = capacity == 0 ? 64 : capacity * 2;

            if (new_capacity < capacity || new_capacity > SIZE_MAX - 1) {
                free(line);
                fputs("Invalid input\n", stderr);
                return EXIT_FAILURE;
            }

            char *new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                free(line);
                fputs("Invalid input\n", stderr);
                return EXIT_FAILURE;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(line);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == 0 && ch == EOF) {
        free(line);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == capacity) {
        if (capacity == SIZE_MAX) {
            free(line);
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        char *new_line = realloc(line, capacity + 1);
        if (new_line == NULL) {
            free(line);
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        line = new_line;
    }

    line[length] = '\0';

    char *start = line;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        free(line);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t value = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || value > UINT64_MAX) {
        free(line);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(line);

    uint64_t result = max_exchange_sum((uint64_t)value);

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}