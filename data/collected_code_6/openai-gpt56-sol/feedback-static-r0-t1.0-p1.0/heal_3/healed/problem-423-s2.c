#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>

static int read_line(char **line)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;

    if (line == NULL) {
        return -1;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        char chunk[256];

        if (fgets(chunk, sizeof(chunk), stdin) == NULL) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return -1;
            }
            break;
        }

        size_t chunk_length = strlen(chunk);
        int has_newline =
            chunk_length > 0 && chunk[chunk_length - 1] == '\n';

        if (has_newline) {
            --chunk_length;
            if (chunk_length > 0 && chunk[chunk_length - 1] == '\r') {
                --chunk_length;
            }
        }

        if (chunk_length > SIZE_MAX - length - 1) {
            free(buffer);
            return -1;
        }

        size_t required = length + chunk_length + 1;
        if (required > capacity) {
            size_t new_capacity = capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            char *temporary = realloc(buffer, new_capacity);
            if (temporary == NULL) {
                free(buffer);
                return -1;
            }

            buffer = temporary;
            capacity = new_capacity;
        }

        memcpy(buffer + length, chunk, chunk_length);
        length += chunk_length;

        if (has_newline) {
            break;
        }
    }

    buffer[length] = '\0';
    *line = buffer;
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

static int read_size_pair(size_t *rows, size_t *cols)
{
    char *buffer;
    char *cursor;
    char *end;
    uintmax_t first;
    uintmax_t second;

    if (rows == NULL || cols == NULL || read_line(&buffer) != 0) {
        return -1;
    }

    cursor = buffer;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '-' || *cursor == '\0') {
        free(buffer);
        return -1;
    }

    errno = 0;
    first = strtoumax(cursor, &end, 10);
    if (cursor == end || errno == ERANGE) {
        free(buffer);
        return -1;
    }

    cursor = end;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '-' || *cursor == '\0') {
        free(buffer);
        return -1;
    }

    errno = 0;
    second = strtoumax(cursor, &end, 10);
    if (cursor == end || errno == ERANGE) {
        free(buffer);
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || first == 0 || second == 0 ||
        first > SIZE_MAX || second > SIZE_MAX) {
        free(buffer);
        return -1;
    }

    *rows = (size_t)first;
    *cols = (size_t)second;
    free(buffer);
    return 0;
}

static int64_t max3(int64_t a, int64_t b, int64_t c)
{
    int64_t result = a;

    if (b > result) {
        result = b;
    }
    if (c > result) {
        result = c;
    }

    return result;
}

static int gold_mine_max(const int64_t *mine, size_t rows, size_t cols,
                         int64_t *result)
{
    int64_t *next;
    int64_t *current;

    if (mine == NULL || result == NULL || rows == 0 || cols == 0 ||
        rows > SIZE_MAX / sizeof(*next)) {
        return -1;
    }

    next = malloc(rows * sizeof(*next));
    current = malloc(rows * sizeof(*current));

    if (next == NULL || current == NULL) {
        free(next);
        free(current);
        return -1;
    }

    for (size_t row = 0; row < rows; ++row) {
        next[row] = mine[row * cols + (cols - 1)];
    }

    for (size_t col = cols - 1; col > 0; --col) {
        size_t current_col = col - 1;

        for (size_t row = 0; row < rows; ++row) {
            int64_t right = next[row];
            int64_t right_up = row > 0 ? next[row - 1] : INT64_MIN;
            int64_t right_down =
                row + 1 < rows ? next[row + 1] : INT64_MIN;
            int64_t best = max3(right, right_up, right_down);
            int64_t value = mine[row * cols + current_col];

            if ((best > 0 && value > INT64_MAX - best) ||
                (best < 0 && value < INT64_MIN - best)) {
                free(next);
                free(current);
                return -1;
            }

            current[row] = value + best;
        }

        int64_t *temporary = next;
        next = current;
        current = temporary;
    }

    *result = next[0];
    for (size_t row = 1; row < rows; ++row) {
        if (next[row] > *result) {
            *result = next[row];
        }
    }

    free(next);
    free(current);
    return 0;
}

int main(void)
{
    size_t rows;
    size_t cols;
    size_t count;
    int64_t *mine;
    int64_t result;

    if (read_size_pair(&rows, &cols) != 0) {
        fputs("Invalid dimensions\n", stderr);
        return EXIT_FAILURE;
    }

    if (rows > SIZE_MAX / cols) {
        fputs("Dimensions are too large\n", stderr);
        return EXIT_FAILURE;
    }

    count = rows * cols;
    if (count > SIZE_MAX / sizeof(*mine)) {
        fputs("Dimensions are too large\n", stderr);
        return EXIT_FAILURE;
    }

    mine = malloc(count * sizeof(*mine));
    if (mine == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (read_int64(&mine[i]) != 0) {
            fputs("Invalid mine data\n", stderr);
            free(mine);
            return EXIT_FAILURE;
        }
    }

    if (gold_mine_max(mine, rows, cols, &result) != 0) {
        fputs("Unable to compute result\n", stderr);
        free(mine);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", result);
    free(mine);
    return EXIT_SUCCESS;
}