#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

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

static int read_token(char *buffer, size_t size)
{
    int ch;
    size_t length = 0U;

    if (buffer == NULL || size < 2U) {
        return -1;
    }

    do {
        ch = getchar();
        if (ch == EOF) {
            return -1;
        }
    } while (isspace((unsigned char)ch));

    do {
        if (length + 1U >= size) {
            while ((ch = getchar()) != EOF &&
                   !isspace((unsigned char)ch)) {
            }
            return -1;
        }

        buffer[length++] = (char)ch;
        ch = getchar();
    } while (ch != EOF && !isspace((unsigned char)ch));

    buffer[length] = '\0';
    return 0;
}

static int read_size(size_t *value)
{
    char buffer[128];
    char *end = NULL;
    uintmax_t parsed;

    if (value == NULL || read_token(buffer, sizeof(buffer)) != 0 ||
        buffer[0] == '-') {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > SIZE_MAX) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_int64(int64_t *value)
{
    char buffer[128];
    char *end = NULL;
    intmax_t parsed;

    if (value == NULL || read_token(buffer, sizeof(buffer)) != 0) {
        return -1;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return -1;
    }

    *value = (int64_t)parsed;
    return 0;
}

static int gold_mine_max(const int64_t *mine, size_t rows, size_t cols,
                         int64_t *result)
{
    int64_t *next;
    int64_t *current;

    if (mine == NULL || result == NULL || rows == 0U || cols == 0U ||
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

    for (size_t row = 0U; row < rows; ++row) {
        next[row] = mine[row * cols + cols - 1U];
    }

    for (size_t col = cols - 1U; col > 0U; --col) {
        size_t current_col = col - 1U;

        for (size_t row = 0U; row < rows; ++row) {
            int64_t right = next[row];
            int64_t right_up = row > 0U ? next[row - 1U] : INT64_MIN;
            int64_t right_down =
                row + 1U < rows ? next[row + 1U] : INT64_MIN;
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

        {
            int64_t *temporary = next;
            next = current;
            current = temporary;
        }
    }

    *result = next[0];

    for (size_t row = 1U; row < rows; ++row) {
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

    if (read_size(&rows) != 0 || read_size(&cols) != 0 ||
        rows == 0U || cols == 0U) {
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

    for (size_t index = 0U; index < count; ++index) {
        if (read_int64(&mine[index]) != 0) {
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