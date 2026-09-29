#include <ctype.h>
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

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == capacity) {
            size_t new_capacity = capacity == 0 ? 64 : capacity * 2;

            if (new_capacity <= capacity ||
                new_capacity > SIZE_MAX / sizeof *line) {
                free(line);
                return EXIT_FAILURE;
            }

            char *new_line = realloc(line, new_capacity * sizeof *line);
            if (new_line == NULL) {
                free(line);
                return EXIT_FAILURE;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(line);
        return EXIT_FAILURE;
    }

    if (length == capacity) {
        if (capacity == SIZE_MAX) {
            free(line);
            return EXIT_FAILURE;
        }

        char *new_line = realloc(line, (capacity + 1) * sizeof *line);
        if (new_line == NULL) {
            free(line);
            return EXIT_FAILURE;
        }

        line = new_line;
        capacity++;
    }

    line[length] = '\0';

    char *start = line;
    while (isspace((unsigned char)*start)) {
        start++;
    }

    if (*start == '\0' || *start == '-') {
        free(line);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t value = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || value > UINT64_MAX) {
        free(line);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        end++;
    }

    if (*end != '\0') {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);

    uint64_t result = maximum_sum((uint64_t)value);

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}