#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <ctype.h>

static int read_int64(int64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *start;
    char *end;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (value == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    if (buffer[0] != '\0' && buffer[0] != '\n') {
        size_t length = 0;

        while (buffer[length] != '\0' && buffer[length] != '\n') {
            ++length;
        }

        if (buffer[length] == '\0') {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            return 0;
        }
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    *value = strtoimax(start, &end, 10);

    if (start == end || errno == ERANGE) {
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    return *end == '\0';
}

static int read_size_pair(size_t *rows, size_t *cols)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *start;
    char *end;
    uintmax_t first;
    uintmax_t second;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;
    size_t length = 0;

    if (rows == NULL || cols == NULL ||
        fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    while (buffer[length] != '\0' && buffer[length] != '\n') {
        ++length;
    }

    if (buffer[length] == '\0') {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        return 0;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        return 0;
    }

    errno = 0;
    first = strtoumax(start, &end, 10);
    if (start == end || errno == ERANGE || first == 0 || first > SIZE_MAX) {
        return 0;
    }

    start = end;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        return 0;
    }

    errno = 0;
    second = strtoumax(start, &end, 10);
    if (start == end || errno == ERANGE || second == 0 || second > SIZE_MAX) {
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *rows = (size_t)first;
    *cols = (size_t)second;
    return 1;
}

static int add_int64(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL ||
        (b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int gold_mine_max(const int64_t *mine, size_t rows, size_t cols,
                         int64_t *result)
{
    int64_t *next;
    int64_t *current;
    size_t row;
    size_t col;

    if (mine == NULL || result == NULL || rows == 0 || cols == 0 ||
        rows > SIZE_MAX / sizeof *next) {
        return 0;
    }

    next = malloc(rows * sizeof *next);
    current = malloc(rows * sizeof *current);

    if (next == NULL || current == NULL) {
        free(next);
        free(current);
        return 0;
    }

    for (row = 0; row < rows; ++row) {
        next[row] = mine[row * cols + cols - 1];
    }

    for (col = cols - 1; col > 0; --col) {
        size_t current_col = col - 1;

        for (row = 0; row < rows; ++row) {
            int64_t best = next[row];

            if (row > 0 && next[row - 1] > best) {
                best = next[row - 1];
            }

            if (row + 1 < rows && next[row + 1] > best) {
                best = next[row + 1];
            }

            if (!add_int64(mine[row * cols + current_col], best,
                           &current[row])) {
                free(next);
                free(current);
                return 0;
            }
        }

        {
            int64_t *temporary = next;
            next = current;
            current = temporary;
        }
    }

    *result = next[0];

    for (row = 1; row < rows; ++row) {
        if (next[row] > *result) {
            *result = next[row];
        }
    }

    free(next);
    free(current);
    return 1;
}

int main(void)
{
    size_t rows;
    size_t cols;
    size_t count;
    size_t i;
    int64_t *mine;
    int64_t result;

    if (!read_size_pair(&rows, &cols)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (rows > SIZE_MAX / cols) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    count = rows * cols;

    if (count > SIZE_MAX / sizeof *mine) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    mine = malloc(count * sizeof *mine);
    if (mine == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        if (!read_int64(&mine[i])) {
            fputs("Invalid input\n", stderr);
            free(mine);
            return EXIT_FAILURE;
        }
    }

    if (!gold_mine_max(mine, rows, cols, &result)) {
        fputs("Unable to compute result\n", stderr);
        free(mine);
        return EXIT_FAILURE;
    }

    free(mine);

    if (printf("%" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}