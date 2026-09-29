#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <ctype.h>

#define INPUT_BUFFER_SIZE 4096U

enum GoldMineStatus {
    GOLD_MINE_OK = 0,
    GOLD_MINE_INVALID_ARGUMENT,
    GOLD_MINE_ALLOCATION_FAILURE,
    GOLD_MINE_ARITHMETIC_OVERFLOW
};

struct InputReader {
    FILE *stream;
    unsigned char buffer[INPUT_BUFFER_SIZE];
    size_t position;
    size_t length;
};

static int input_reader_init(struct InputReader *reader, FILE *stream)
{
    if (reader == NULL || stream == NULL) {
        return 0;
    }

    reader->stream = stream;
    reader->position = 0;
    reader->length = 0;
    return 1;
}

static int input_reader_get(struct InputReader *reader, unsigned char *value)
{
    if (reader == NULL || reader->stream == NULL || value == NULL) {
        return -1;
    }

    if (reader->position == reader->length) {
        reader->length = fread(
            reader->buffer,
            sizeof(reader->buffer[0]),
            sizeof(reader->buffer) / sizeof(reader->buffer[0]),
            reader->stream);
        reader->position = 0;

        if (reader->length == 0) {
            return ferror(reader->stream) ? -1 : 0;
        }
    }

    *value = reader->buffer[reader->position];
    ++reader->position;
    return 1;
}

static int read_size(struct InputReader *reader, size_t *value)
{
    unsigned char ch;
    size_t result = 0;
    int valid = 1;
    int has_digit = 0;
    int read_status;

    if (reader == NULL || value == NULL) {
        return -1;
    }

    do {
        read_status = input_reader_get(reader, &ch);
    } while (read_status == 1 && isspace((unsigned char)ch));

    if (read_status <= 0) {
        return read_status;
    }

    if (ch == (unsigned char)'+') {
        read_status = input_reader_get(reader, &ch);
    } else if (ch == (unsigned char)'-') {
        valid = 0;
        read_status = input_reader_get(reader, &ch);
    }

    while (read_status == 1 && !isspace((unsigned char)ch)) {
        if (!isdigit((unsigned char)ch)) {
            valid = 0;
        } else {
            size_t digit = (size_t)(ch - (unsigned char)'0');

            has_digit = 1;

            if (valid) {
                if (result > (SIZE_MAX - digit) / (size_t)10) {
                    valid = 0;
                } else {
                    result = result * (size_t)10 + digit;
                }
            }
        }

        read_status = input_reader_get(reader, &ch);
    }

    if (read_status < 0 || !valid || !has_digit) {
        return -1;
    }

    *value = result;
    return 1;
}

static int read_int64(struct InputReader *reader, int64_t *value)
{
    unsigned char ch;
    uint64_t magnitude = 0;
    uint64_t limit;
    int negative = 0;
    int valid = 1;
    int has_digit = 0;
    int read_status;

    if (reader == NULL || value == NULL) {
        return -1;
    }

    do {
        read_status = input_reader_get(reader, &ch);
    } while (read_status == 1 && isspace((unsigned char)ch));

    if (read_status <= 0) {
        return read_status;
    }

    if (ch == (unsigned char)'+' || ch == (unsigned char)'-') {
        negative = ch == (unsigned char)'-';
        read_status = input_reader_get(reader, &ch);
    }

    limit = negative
        ? (uint64_t)INT64_MAX + UINT64_C(1)
        : (uint64_t)INT64_MAX;

    while (read_status == 1 && !isspace((unsigned char)ch)) {
        if (!isdigit((unsigned char)ch)) {
            valid = 0;
        } else {
            uint64_t digit = (uint64_t)(ch - (unsigned char)'0');

            has_digit = 1;

            if (valid) {
                if (magnitude > (limit - digit) / UINT64_C(10)) {
                    valid = 0;
                } else {
                    magnitude = magnitude * UINT64_C(10) + digit;
                }
            }
        }

        read_status = input_reader_get(reader, &ch);
    }

    if (read_status < 0 || !valid || !has_digit) {
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

static int checked_add_int64(int64_t left, int64_t right, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if ((right > 0 && left > INT64_MAX - right) ||
        (right < 0 && left < INT64_MIN - right)) {
        return 0;
    }

    *result = left + right;
    return 1;
}

static int checked_multiply_size(size_t left, size_t right, size_t *result)
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

int solve_gold_mine(const int64_t *mine, size_t rows, size_t columns,
                    int64_t *maximum_gold)
{
    int64_t *previous = NULL;
    int64_t *current = NULL;
    size_t cell_count;
    size_t matrix_size;
    size_t row_size;
    size_t row;
    size_t column;
    int status = GOLD_MINE_OK;

    if (mine == NULL || maximum_gold == NULL ||
        rows == 0 || columns == 0) {
        return GOLD_MINE_INVALID_ARGUMENT;
    }

    if (!checked_multiply_size(rows, columns, &cell_count) ||
        !checked_multiply_size(cell_count, sizeof(*mine), &matrix_size) ||
        !checked_multiply_size(rows, sizeof(*previous), &row_size)) {
        return GOLD_MINE_INVALID_ARGUMENT;
    }

    if (matrix_size == 0 || row_size == 0) {
        return GOLD_MINE_INVALID_ARGUMENT;
    }

    previous = malloc(row_size);
    current = malloc(row_size);

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
    struct InputReader reader;
    size_t rows;
    size_t columns;
    size_t cell_count;
    size_t allocation_size;
    size_t index;
    int64_t *mine;
    int64_t maximum_gold;
    int status;

    if (!input_reader_init(&reader, stdin)) {
        fputs("Input initialization failed\n", stderr);
        return EXIT_FAILURE;
    }

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
            cell_count, sizeof(*mine), &allocation_size)) {
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
        mine, rows, columns, &maximum_gold);

    free(mine);

    if (status != GOLD_MINE_OK) {
        switch (status) {
            case GOLD_MINE_ALLOCATION_FAILURE:
                fputs("Memory allocation failed\n", stderr);
                break;

            case GOLD_MINE_ARITHMETIC_OVERFLOW:
                fputs("Arithmetic overflow\n", stderr);
                break;

            case GOLD_MINE_INVALID_ARGUMENT:
            default:
                fputs("Invalid argument\n", stderr);
                break;
        }

        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", maximum_gold) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}