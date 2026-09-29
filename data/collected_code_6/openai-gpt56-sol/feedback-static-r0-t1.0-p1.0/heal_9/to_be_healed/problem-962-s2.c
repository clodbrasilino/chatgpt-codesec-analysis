#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int parse_uint64(const char **cursor, uint64_t *value)
{
    const char *start;
    char *end;
    uintmax_t parsed;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return 0;
    }

    start = *cursor;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '+' || *start == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed > UINT64_MAX) {
        return 0;
    }

    *cursor = end;
    *value = (uint64_t)parsed;
    return 1;
}

static int read_line(char **line)
{
    enum { MAX_LINE_LENGTH = 4096 };
    char *buffer;
    size_t length;
    int ch;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc((size_t)MAX_LINE_LENGTH + 1U);

    if (buffer == NULL) {
        return 0;
    }

    length = 0;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length == (size_t)MAX_LINE_LENGTH) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = fgetc(stdin);
            } while (ch != EOF && ch != '\n');

            free(buffer);
            return 0;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && (ferror(stdin) || length == 0U)) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int read_range(uint64_t *left, uint64_t *right)
{
    char *input;
    const char *cursor;
    int valid;

    if (left == NULL || right == NULL) {
        return 0;
    }

    input = NULL;

    if (!read_line(&input)) {
        return 0;
    }

    cursor = input;
    valid = parse_uint64(&cursor, left) &&
            parse_uint64(&cursor, right);

    if (valid) {
        while (isspace((unsigned char)*cursor)) {
            ++cursor;
        }

        valid = (*cursor == '\0');
    }

    free(input);
    return valid;
}

static int sum_even_natural_numbers(uint64_t left, uint64_t right,
                                    uint64_t *result)
{
    uint64_t first;
    uint64_t last;
    uint64_t count;
    uint64_t half;
    uint64_t factor;

    if (result == NULL || left == 0U || left > right) {
        return 0;
    }

    first = left;

    if ((first & UINT64_C(1)) != 0U) {
        if (first == UINT64_MAX) {
            *result = 0;
            return 1;
        }

        ++first;
    }

    last = right - (right & UINT64_C(1));

    if (first > last) {
        *result = 0;
        return 1;
    }

    count = (last - first) / UINT64_C(2) + UINT64_C(1);

    if ((count & UINT64_C(1)) == 0U) {
        half = count / UINT64_C(2);

        if (last > UINT64_MAX - first) {
            return 0;
        }

        factor = first + last;
    } else {
        half = first / UINT64_C(2) + last / UINT64_C(2);
        factor = count;
    }

    if (half != 0U && factor > UINT64_MAX / half) {
        return 0;
    }

    *result = half * factor;
    return 1;
}

int main(void)
{
    uint64_t left;
    uint64_t right;
    uint64_t sum;

    if (!read_range(&left, &right)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_even_natural_numbers(left, right, &sum)) {
        fputs("Invalid range or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}