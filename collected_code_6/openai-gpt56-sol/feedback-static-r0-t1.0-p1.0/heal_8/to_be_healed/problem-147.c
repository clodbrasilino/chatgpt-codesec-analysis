#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

#define MAX_INPUT_LINE_LENGTH 1024U

static int discard_line(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    return ferror(stdin) ? -1 : 0;
}

static int read_line(char **buffer)
{
    char *line;
    size_t capacity = MAX_INPUT_LINE_LENGTH + 2U;
    size_t length = 0U;

    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MAX'
     *  'INT_MAX' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
    if (buffer == NULL || capacity > (size_t)INT_MAX) {
        return -1;
    }

    *buffer = NULL;

    line = malloc(capacity);
    if (line == NULL) {
        return -1;
    }

    if (fgets(line, (int)capacity, stdin) == NULL) {
        free(line);
        return -1;
    }

    while (length < capacity && line[length] != '\0') {
        ++length;
    }

    if (length == capacity) {
        free(line);
        return -1;
    }

    if (length > 0U && line[length - 1U] == '\n') {
        line[--length] = '\0';

        if (length > 0U && line[length - 1U] == '\r') {
            line[--length] = '\0';
        }
    } else if (!feof(stdin)) {
        int status = discard_line();
        free(line);
        return status == 0 ? -1 : status;
    }

    *buffer = line;
    return 0;
}

static int read_int64(int64_t *value)
{
    char *buffer;
    char *start;
    char *end;
    intmax_t parsed;

    if (value == NULL || read_line(&buffer) != 0) {
        return -1;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    parsed = strtoimax(start, &end, 10);

    if (start == end || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(buffer);
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return -1;
    }

    *value = (int64_t)parsed;
    free(buffer);
    return 0;
}

static int read_size(size_t *value)
{
    char *buffer;
    char *start;
    char *end;
    uintmax_t parsed;

    if (value == NULL || read_line(&buffer) != 0) {
        return -1;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        free(buffer);
        return -1;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || parsed > SIZE_MAX) {
        free(buffer);
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return -1;
    }

    *value = (size_t)parsed;
    free(buffer);
    return 0;
}

static int checked_triangle_elements(size_t rows, size_t *elements)
{
    size_t a;
    size_t b;

    if (elements == NULL || rows == 0U || rows == SIZE_MAX) {
        return -1;
    }

    a = rows;
    b = rows + 1U;

    if ((a & 1U) == 0U) {
        a /= 2U;
    } else {
        b /= 2U;
    }

    if (a != 0U && b > SIZE_MAX / a) {
        return -1;
    }

    *elements = a * b;
    return 0;
}

static int checked_add_int64(int64_t left, int64_t right, int64_t *result)
{
    if (result == NULL) {
        return -1;
    }

    if ((right > 0 && left > INT64_MAX - right) ||
        (right < 0 && left < INT64_MIN - right)) {
        return -1;
    }

    *result = left + right;
    return 0;
}

static int maximum_path_sum(const int64_t *triangle, size_t rows,
                            int64_t *result)
{
    int64_t *sums;
    size_t elements;
    size_t offset;

    if (triangle == NULL || result == NULL ||
        checked_triangle_elements(rows, &elements) != 0 ||
        rows > SIZE_MAX / sizeof(*sums)) {
        return -1;
    }

    sums = malloc(rows * sizeof(*sums));
    if (sums == NULL) {
        return -1;
    }

    offset = elements - rows;

    for (size_t column = 0U; column < rows; ++column) {
        sums[column] = triangle[offset + column];
    }

    for (size_t row = rows - 1U; row > 0U; --row) {
        size_t a = row;
        size_t b = row - 1U;

        if ((a & 1U) == 0U) {
            a /= 2U;
        } else {
            b /= 2U;
        }

        offset = a * b;

        for (size_t column = 0U; column < row; ++column) {
            int64_t best = sums[column] > sums[column + 1U]
                               ? sums[column]
                               : sums[column + 1U];

            if (checked_add_int64(triangle[offset + column], best,
                                  &sums[column]) != 0) {
                free(sums);
                return -1;
            }
        }
    }

    *result = sums[0];
    free(sums);
    return 0;
}

int main(void)
{
    size_t rows;
    size_t elements;
    int64_t *triangle;
    int64_t result;

    if (read_size(&rows) != 0 ||
        checked_triangle_elements(rows, &elements) != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (elements > SIZE_MAX / sizeof(*triangle)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    triangle = malloc(elements * sizeof(*triangle));
    if (triangle == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < elements; ++i) {
        if (read_int64(&triangle[i]) != 0) {
            fputs("Invalid input\n", stderr);
            free(triangle);
            return EXIT_FAILURE;
        }
    }

    if (maximum_path_sum(triangle, rows, &result) != 0) {
        fputs("Unable to calculate path sum\n", stderr);
        free(triangle);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        free(triangle);
        return EXIT_FAILURE;
    }

    free(triangle);
    return EXIT_SUCCESS;
}