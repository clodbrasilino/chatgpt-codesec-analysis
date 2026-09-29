#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

enum GoldMineStatus {
    GOLD_MINE_OK = 0,
    GOLD_MINE_INVALID_ARGUMENT,
    GOLD_MINE_ALLOCATION_FAILURE,
    GOLD_MINE_ARITHMETIC_OVERFLOW
};

typedef struct {
    FILE *stream;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[4096];
    size_t position;
    size_t length;
    int error;
    int ended;
} InputReader;

static void input_reader_init(InputReader *reader, FILE *stream)
{
    if (reader == NULL) {
        return;
    }

    reader->stream = stream;
    reader->position = 0;
    reader->length = 0;
    reader->error = 0;
    reader->ended = 0;
}

static int input_reader_get(InputReader *reader)
{
    if (reader == NULL || reader->stream == NULL || reader->ended) {
        return EOF;
    }

    if (reader->position >= reader->length) {
        reader->position = 0;
        reader->length = fread(
            reader->buffer,
            sizeof(reader->buffer[0]),
            sizeof(reader->buffer) / sizeof(reader->buffer[0]),
            reader->stream
        );

        if (reader->length == 0) {
            reader->error = ferror(reader->stream) != 0;
            reader->ended = 1;
            return EOF;
        }
    }

    return (int)reader->buffer[reader->position++];
}

static int is_input_space(int ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static int is_decimal_digit(int ch)
{
    return ch >= '0' && ch <= '9';
}

static int read_size(InputReader *reader, size_t *value)
{
    size_t result = 0;
    int ch;
    int valid = 1;
    int has_digit = 0;

    if (reader == NULL || value == NULL) {
        return -1;
    }

    do {
        ch = input_reader_get(reader);
    } while (ch != EOF && is_input_space(ch));

    if (ch == EOF) {
        return reader->error ? -1 : 0;
    }

    if (ch == '+') {
        ch = input_reader_get(reader);
    } else if (ch == '-') {
        valid = 0;
        ch = input_reader_get(reader);
    }

    while (ch != EOF && !is_input_space(ch)) {
        if (!is_decimal_digit(ch)) {
            valid = 0;
        } else {
            size_t digit = (size_t)(ch - '0');

            has_digit = 1;

            if (valid) {
                if (result > (SIZE_MAX - digit) / (size_t)10) {
                    valid = 0;
                } else {
                    result = result * (size_t)10 + digit;
                }
            }
        }

        ch = input_reader_get(reader);
    }

    if (ch == EOF && reader->error) {
        return -1;
    }

    if (!valid || !has_digit) {
        return -1;
    }

    *value = result;
    return 1;
}

static int read_int64(InputReader *reader, int64_t *value)
{
    uint64_t magnitude = 0;
    uint64_t limit;
    int ch;
    int negative = 0;
    int valid = 1;
    int has_digit = 0;

    if (reader == NULL || value == NULL) {
        return -1;
    }

    do {
        ch = input_reader_get(reader);
    } while (ch != EOF && is_input_space(ch));

    if (ch == EOF) {
        return reader->error ? -1 : 0;
    }

    if (ch == '+' || ch == '-') {
        negative = ch == '-';
        ch = input_reader_get(reader);
    }

    limit = negative
        ? (uint64_t)INT64_MAX + UINT64_C(1)
        : (uint64_t)INT64_MAX;

    while (ch != EOF && !is_input_space(ch)) {
        if (!is_decimal_digit(ch)) {
            valid = 0;
        } else {
            uint64_t digit = (uint64_t)(ch - '0');

            has_digit = 1;

            if (valid) {
                if (magnitude > (limit - digit) / UINT64_C(10)) {
                    valid = 0;
                } else {
                    magnitude = magnitude * UINT64_C(10) + digit;
                }
            }
        }

        ch = input_reader_get(reader);
    }

    if (ch == EOF && reader->error) {
        return -1;
    }

    if (!valid || !has_digit) {
        return -1;
    }

    if (negative) {
        if (magnitude == (uint64_t)INT64_MAX + UINT64_C(1)) {
            *value = INT64_MIN;
        } else {
            *value = -(int64_t)magnitude;
        }
    } else {
        *value = (int64_t)magnitude;
    }

    return 1;
}

static int checked_multiply_size(
    size_t left,
    size_t right,
    size_t *result
)
{
    if (result == NULL) {
        return 0;
    }

    if (left != 0 && right > SIZE_MAX / left) {
        return 0;
    }

    *result = left * right;
    return 1;
}

static int checked_add_int64(
    int64_t left,
    int64_t right,
    int64_t *result
)
{
    if (result == NULL) {
        return 0;
    }

    if (right > 0 && left > INT64_MAX - right) {
        return 0;
    }

    if (right < 0 && left < INT64_MIN - right) {
        return 0;
    }

    *result = left + right;
    return 1;
}

int solve_gold_mine(
    const int64_t *mine,
    size_t rows,
    size_t columns,
    int64_t *maximum_gold
)
{
    int64_t *previous = NULL;
    int64_t *current = NULL;
    size_t cell_count;
    size_t mine_size;
    size_t workspace_size;
    size_t row;
    size_t column;
    int status = GOLD_MINE_OK;

    if (mine == NULL || maximum_gold == NULL ||
        rows == 0 || columns == 0) {
        return GOLD_MINE_INVALID_ARGUMENT;
    }

    if (!checked_multiply_size(rows, columns, &cell_count) ||
        !checked_multiply_size(cell_count, sizeof(*mine), &mine_size) ||
        !checked_multiply_size(rows, sizeof(*previous), &workspace_size)) {
        return GOLD_MINE_INVALID_ARGUMENT;
    }

    previous = malloc(workspace_size);
    current = malloc(workspace_size);

    if (previous == NULL || current == NULL) {
        free(previous);
        free(current);
        return GOLD_MINE_ALLOCATION_FAILURE;
    }

    for (row = 0; row < rows; ++row) {
        previous[row] = mine[row * columns];
    }

    for (column = 1; column < columns; ++column) {
        for (row = 0; row < rows; ++row) {
            int64_t best = previous[row];

            if (row > 0 && previous[row - 1] > best) {
                best = previous[row - 1];
            }

            if (row < rows - 1 && previous[row + 1] > best) {
                best = previous[row + 1];
            }

            if (!checked_add_int64(
                    best,
                    mine[row * columns + column],
                    &current[row])) {
                status = GOLD_MINE_ARITHMETIC_OVERFLOW;
                goto cleanup;
            }
        }

        {
            int64_t *temporary = previous;
            previous = current;
            current = temporary;
        }
    }

    *maximum_gold = previous[0];

    for (row = 1; row < rows; ++row) {
        if (previous[row] > *maximum_gold) {
            *maximum_gold = previous[row];
        }
    }

cleanup:
    free(previous);
    free(current);
    return status;
}

int main(void)
{
    InputReader reader;
    size_t rows;
    size_t columns;
    size_t cell_count;
    size_t allocation_size;
    size_t index;
    int64_t *mine;
    int64_t maximum_gold;
    int status;

    input_reader_init(&reader, stdin);

    if (read_size(&reader, &rows) != 1 ||
        read_size(&reader, &columns) != 1 ||
        rows == 0 || columns == 0) {
        fputs("Invalid dimensions\n", stderr);
        return EXIT_FAILURE;
    }

    if (!checked_multiply_size(rows, columns, &cell_count)) {
        fputs("Matrix dimensions are too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (!checked_multiply_size(
            cell_count,
            sizeof(*mine),
            &allocation_size)) {
        fputs("Matrix is too large\n", stderr);
        return EXIT_FAILURE;
    }

    mine = malloc(allocation_size);

    if (mine == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (index = 0; index < cell_count; ++index) {
        if (read_int64(&reader, &mine[index]) != 1) {
            fputs("Invalid mine data\n", stderr);
            free(mine);
            return EXIT_FAILURE;
        }
    }

    status = solve_gold_mine(
        mine,
        rows,
        columns,
        &maximum_gold
    );

    free(mine);

    if (status != GOLD_MINE_OK) {
        if (status == GOLD_MINE_ALLOCATION_FAILURE) {
            fputs("Memory allocation failed\n", stderr);
        } else if (status == GOLD_MINE_ARITHMETIC_OVERFLOW) {
            fputs("Arithmetic overflow\n", stderr);
        } else {
            fputs("Invalid argument\n", stderr);
        }

        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", maximum_gold) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}