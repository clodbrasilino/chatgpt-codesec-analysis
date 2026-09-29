#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

static uint64_t integer_sqrt(uint64_t value)
{
    uint64_t low = 0;
    uint64_t high = value < UINT64_C(4294967295)
                  ? value
                  : UINT64_C(4294967295);
    uint64_t result = 0;

    while (low <= high) {
        uint64_t middle = low + (high - low) / 2;

        if (middle == 0 || middle <= value / middle) {
            result = middle;
            low = middle + 1;
        } else {
            high = middle - 1;
        }
    }

    return result;
}

static uint64_t count_elements_with_odd_number_of_factors(uint64_t lower,
                                                           uint64_t upper)
{
    uint64_t first_root;
    uint64_t last_root;

    if (lower > upper) {
        return 0;
    }

    first_root = integer_sqrt(lower);

    if (first_root * first_root < lower) {
        ++first_root;
    }

    last_root = integer_sqrt(upper);

    return first_root > last_root ? 0 : last_root - first_root + 1;
}

static int read_input_line(char **buffer)
{
    enum { INITIAL_CAPACITY = 64 };
    char *line;
    size_t length = 0;
    size_t capacity = INITIAL_CAPACITY;

    if (buffer == NULL) {
        return 0;
    }

    *buffer = NULL;
    line = malloc(capacity);

    if (line == NULL) {
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            if (ch == EOF && (ferror(stdin) || length == 0)) {
                free(line);
                return 0;
            }

            line[length] = '\0';
            *buffer = line;
            return 1;
        }

        if (length == SIZE_MAX - 1) {
            free(line);
            return 0;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *temporary;

            if (capacity > SIZE_MAX / 2) {
                free(line);
                return 0;
            }

            new_capacity = capacity * 2;
            temporary = realloc(line, new_capacity);

            if (temporary == NULL) {
                free(line);
                return 0;
            }

            line = temporary;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
    }
}

static int parse_uint64(const char **cursor, uint64_t *value)
{
    const unsigned char *p;
    uint64_t result = 0;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return 0;
    }

    p = (const unsigned char *)*cursor;

    while (*p != '\0' && isspace(*p)) {
        ++p;
    }

    if (!isdigit(*p)) {
        return 0;
    }

    do {
        unsigned int digit = (unsigned int)(*p - (unsigned char)'0');

        if (result > (UINT64_MAX - digit) / UINT64_C(10)) {
            return 0;
        }

        result = result * UINT64_C(10) + digit;
        ++p;
    } while (isdigit(*p));

    if (*p != '\0' && !isspace(*p)) {
        return 0;
    }

    *cursor = (const char *)p;
    *value = result;
    return 1;
}

static int parse_input(const char *input, uint64_t *lower, uint64_t *upper)
{
    const char *cursor;

    if (input == NULL || lower == NULL || upper == NULL) {
        return 0;
    }

    cursor = input;

    if (!parse_uint64(&cursor, lower) ||
        !parse_uint64(&cursor, upper)) {
        return 0;
    }

    while (*cursor != '\0' && isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    return *cursor == '\0';
}

int main(void)
{
    char *input = NULL;
    uint64_t lower;
    uint64_t upper;
    uint64_t count;

    if (!read_input_line(&input)) {
        if (ferror(stdin)) {
            fputs("Input error\n", stderr);
        } else {
            fputs("Invalid input\n", stderr);
        }
        return EXIT_FAILURE;
    }

    if (!parse_input(input, &lower, &upper)) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (lower > upper) {
        fputs("Invalid range\n", stderr);
        return EXIT_FAILURE;
    }

    count = count_elements_with_odd_number_of_factors(lower, upper);

    if (printf("%" PRIu64 "\n", count) < 0) {
        fputs("Output error\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}