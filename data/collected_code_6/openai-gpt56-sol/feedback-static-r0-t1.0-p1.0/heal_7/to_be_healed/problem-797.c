#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_odd_naturals(int64_t left, int64_t right, uint64_t *result)
{
    uint64_t first;
    uint64_t last;
    uint64_t count;
    uint64_t factor;

    if (result == NULL || left < 1 || right < left) {
        return 0;
    }

    first = (uint64_t)left;
    last = (uint64_t)right;

    if ((first & UINT64_C(1)) == 0) {
        ++first;
    }

    if ((last & UINT64_C(1)) == 0) {
        --last;
    }

    if (first > last) {
        *result = UINT64_C(0);
        return 1;
    }

    count = (last - first) / UINT64_C(2) + UINT64_C(1);
    factor = first / UINT64_C(2) + last / UINT64_C(2) + UINT64_C(1);

    if (factor != 0 && count > UINT64_MAX / factor) {
        return 0;
    }

    *result = count * factor;
    return 1;
}

static int parse_int64(const char **cursor, int64_t *value)
{
    const char *start;
    char *end;
    intmax_t parsed;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return 0;
    }

    start = *cursor;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    parsed = strtoimax(start, &end, 10);

    if (end == start || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *cursor = end;
    *value = (int64_t)parsed;
    return 1;
}

static int read_line(FILE *stream, char **line)
{
    char *buffer;
    size_t capacity;
    size_t length;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (stream == NULL || line == NULL) {
        return 0;
    }

    capacity = 128;
    length = 0;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stream) || length == 0) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(buffer);
            return 0;
        }

        if (length + 1 >= capacity) {
            char *replacement;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            replacement = realloc(buffer, new_capacity);

            if (replacement == NULL) {
                free(buffer);
                return 0;
            }

            buffer = replacement;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

int main(void)
{
    char *input;
    const char *cursor;
    int64_t left;
    int64_t right;
    uint64_t sum;

    input = NULL;

    if (!read_line(stdin, &input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    if (!parse_int64(&cursor, &left) ||
        !parse_int64(&cursor, &right)) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (!sum_odd_naturals(left, right, &sum)) {
        fputs("Invalid range or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}