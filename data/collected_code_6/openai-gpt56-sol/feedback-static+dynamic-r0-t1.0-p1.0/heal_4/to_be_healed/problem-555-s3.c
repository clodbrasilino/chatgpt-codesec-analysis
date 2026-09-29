#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_difference(uint64_t n, uint64_t *result)
{
    __uint128_t sum;
    __uint128_t difference;

    if (result == NULL) {
        return 0;
    }

    sum = (__uint128_t)n * ((__uint128_t)n + 1) / 2;
    difference = sum * sum - sum;

    if (difference > UINT64_MAX) {
        return 0;
    }

    *result = (uint64_t)difference;
    return 1;
}

static int read_line(char **line)
{
    size_t length = 0;
    size_t capacity = 32;
    int ch;
    char *buffer;

    if (line == NULL) {
        return 0;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ferror(stdin) || (ch == EOF && length == 0)) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

int main(void)
{
    char *buffer;
    char *end;
    uintmax_t value;
    uint64_t difference;

    if (!read_line(&buffer)) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    errno = 0;
    value = strtoumax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE || value > UINT64_MAX) {
        free(buffer);
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    free(buffer);

    if (!calculate_difference((uint64_t)value, &difference)) {
        fprintf(stderr, "Result is out of range\n");
        return 1;
    }

    printf("%" PRIu64 "\n", difference);
    return 0;
}