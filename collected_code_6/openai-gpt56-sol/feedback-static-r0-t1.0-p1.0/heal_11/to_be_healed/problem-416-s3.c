#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t maximum_sum(uint64_t n)
{
    if (n < 12) {
        return n;
    }

    uint64_t a = maximum_sum(n / 2);
    uint64_t b = maximum_sum(n / 3);
    uint64_t c = maximum_sum(n / 4);

    if (a > UINT64_MAX - b) {
        return UINT64_MAX;
    }

    uint64_t sum = a + b;

    if (c > UINT64_MAX - sum) {
        return UINT64_MAX;
    }

    sum += c;
    return sum > n ? sum : n;
}

static int read_input(char **line)
{
    size_t capacity = 64;
    size_t length = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            if (ch == EOF && ferror(stdin)) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (length == capacity - 1) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            size_t new_capacity = capacity * 2;
            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';

    int ch;
    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch == '\n');

    if (ch != EOF || ferror(stdin)) {
        free(buffer);
        return 0;
    }

    *line = buffer;
    return 1;
}

int main(void)
{
    char *buffer = NULL;

    if (!read_input(&buffer)) {
        return EXIT_FAILURE;
    }

    char *start = buffer;

    while (*start == ' ' || *start == '\t' || *start == '\r' ||
           *start == '\v' || *start == '\f') {
        start++;
    }

    if (*start == '\0' || *start == '-') {
        free(buffer);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t value = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || value > UINT64_MAX) {
        free(buffer);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\v' || *end == '\f') {
        end++;
    }

    if (*end != '\0') {
        free(buffer);
        return EXIT_FAILURE;
    }

    uint64_t result = maximum_sum((uint64_t)value);
    free(buffer);

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}