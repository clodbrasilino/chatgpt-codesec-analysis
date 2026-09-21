#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int parse_uint64(const char **text, uint64_t *value)
{
    char *end;
    uintmax_t parsed;

    if (text == NULL || *text == NULL || value == NULL) {
        return 0;
    }

    while (isspace((unsigned char)**text)) {
        ++*text;
    }

    if (**text == '\0' || **text == '+' || **text == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(*text, &end, 10);

    if (end == *text || errno == ERANGE || parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    *text = end;
    return 1;
}

static int read_line(char **line)
{
    size_t length = 0;
    size_t capacity = 128;
    char *buffer;

    if (line == NULL) {
        return 0;
    }

    buffer = malloc(capacity);
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

            if (ch == EOF && length == 0) {
                free(buffer);
                return 0;
            }

            break;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return 0;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int sum_even_naturals(uint64_t left, uint64_t right,
                             uint64_t *result)
{
    uint64_t first;
    uint64_t last;
    uint64_t count;
    uint64_t midpoint;

    if (result == NULL || left == 0 || left > right) {
        return 0;
    }

    if ((left & UINT64_C(1)) != 0) {
        if (left == UINT64_MAX) {
            *result = 0;
            return 1;
        }
        first = left + UINT64_C(1);
    } else {
        first = left;
    }

    last = right - (right & UINT64_C(1));

    if (first > last) {
        *result = 0;
        return 1;
    }

    count = (last - first) / UINT64_C(2) + UINT64_C(1);
    midpoint = first + (last - first) / UINT64_C(2);

    if (midpoint != 0 && count > UINT64_MAX / midpoint) {
        return 0;
    }

    *result = count * midpoint;
    return 1;
}

int main(void)
{
    char *input = NULL;
    const char *cursor;
    uint64_t left;
    uint64_t right;
    uint64_t sum;

    if (!read_line(&input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    if (!parse_uint64(&cursor, &left) ||
        !parse_uint64(&cursor, &right)) {
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

    if (!sum_even_naturals(left, right, &sum)) {
        fputs("Invalid range or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}