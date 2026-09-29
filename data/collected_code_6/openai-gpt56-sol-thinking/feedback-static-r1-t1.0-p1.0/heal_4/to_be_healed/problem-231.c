#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    TRIANGLE_SUCCESS,
    TRIANGLE_INVALID_ARGUMENT,
    TRIANGLE_INPUT_ERROR,
    TRIANGLE_ALLOCATION_ERROR,
    TRIANGLE_OVERFLOW
} TriangleStatus;

typedef struct {
    FILE *stream;
    int ended;
    int error;
} InputReader;

static void input_reader_init(InputReader *reader, FILE *stream)
{
    if (reader == NULL) {
        return;
    }

    reader->stream = stream;
    reader->ended = 0;
    reader->error = 0;
}

static int input_reader_get(InputReader *reader)
{
    int c;

    if (reader == NULL || reader->stream == NULL || reader->ended) {
        return EOF;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    c = fgetc(reader->stream);

    if (c == EOF) {
        reader->error = ferror(reader->stream) != 0;
        reader->ended = 1;
    }

    return c;
}

static int input_reader_has_error(const InputReader *reader)
{
    return reader != NULL && reader->error;
}

static int read_size_token(InputReader *input, size_t *result)
{
    size_t value = 0;
    int overflow = 0;
    int c;

    if (input == NULL || result == NULL) {
        return 0;
    }

    do {
        c = input_reader_get(input);
    } while (c != EOF && isspace((unsigned char)c));

    if (c == '+') {
        c = input_reader_get(input);
    }

    if (c == EOF || !isdigit((unsigned char)c)) {
        return 0;
    }

    do {
        size_t digit = (size_t)(c - '0');

        if (!overflow) {
            if (value > (SIZE_MAX - digit) / (size_t)10) {
                overflow = 1;
            } else {
                value = value * (size_t)10 + digit;
            }
        }

        c = input_reader_get(input);
    } while (c != EOF && isdigit((unsigned char)c));

    if (c != EOF && !isspace((unsigned char)c)) {
        return 0;
    }

    if (c == EOF && input_reader_has_error(input)) {
        return 0;
    }

    if (overflow) {
        return 0;
    }

    *result = value;
    return 1;
}

static int read_int64_token(InputReader *input, int64_t *result)
{
    uint64_t magnitude = 0;
    uint64_t limit;
    int negative = 0;
    int overflow = 0;
    int c;

    if (input == NULL || result == NULL) {
        return 0;
    }

    do {
        c = input_reader_get(input);
    } while (c != EOF && isspace((unsigned char)c));

    if (c == '+' || c == '-') {
        negative = c == '-';
        c = input_reader_get(input);
    }

    if (c == EOF || !isdigit((unsigned char)c)) {
        return 0;
    }

    limit = (uint64_t)INT64_MAX + (negative ? UINT64_C(1) : UINT64_C(0));

    do {
        uint64_t digit = (uint64_t)(c - '0');

        if (!overflow) {
            if (magnitude > (limit - digit) / UINT64_C(10)) {
                overflow = 1;
            } else {
                magnitude = magnitude * UINT64_C(10) + digit;
            }
        }

        c = input_reader_get(input);
    } while (c != EOF && isdigit((unsigned char)c));

    if (c != EOF && !isspace((unsigned char)c)) {
        return 0;
    }

    if (c == EOF && input_reader_has_error(input)) {
        return 0;
    }

    if (overflow) {
        return 0;
    }

    if (negative) {
        if (magnitude == (uint64_t)INT64_MAX + UINT64_C(1)) {
            *result = INT64_MIN;
        } else {
            *result = -(int64_t)magnitude;
        }
    } else {
        *result = (int64_t)magnitude;
    }

    return 1;
}

static int add_int64_checked(int64_t left, int64_t right, int64_t *result)
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

static TriangleStatus find_maximum_sum(InputReader *input, size_t rows,
                                       int64_t *result)
{
    int64_t *previous = NULL;
    int64_t *current = NULL;
    size_t allocation_size;
    size_t row;
    size_t column;

    if (input == NULL || result == NULL || rows == 0) {
        return TRIANGLE_INVALID_ARGUMENT;
    }

    if (rows > SIZE_MAX / sizeof(*previous)) {
        return TRIANGLE_ALLOCATION_ERROR;
    }

    allocation_size = rows * sizeof(*previous);

    previous = malloc(allocation_size);
    current = malloc(allocation_size);

    if (previous == NULL || current == NULL) {
        free(previous);
        free(current);
        return TRIANGLE_ALLOCATION_ERROR;
    }

    for (row = 0; row < rows; ++row) {
        for (column = 0; column <= row; ++column) {
            int64_t value;
            int64_t parent;

            if (!read_int64_token(input, &value)) {
                free(previous);
                free(current);
                return TRIANGLE_INPUT_ERROR;
            }

            if (row == 0) {
                current[0] = value;
                continue;
            }

            if (column == 0) {
                parent = previous[0];
            } else if (column == row) {
                parent = previous[column - 1];
            } else {
                parent = previous[column - 1] > previous[column]
                             ? previous[column - 1]
                             : previous[column];
            }

            if (!add_int64_checked(parent, value, &current[column])) {
                free(previous);
                free(current);
                return TRIANGLE_OVERFLOW;
            }
        }

        {
            int64_t *temporary = previous;
            previous = current;
            current = temporary;
        }
    }

    *result = previous[0];

    for (column = 1; column < rows; ++column) {
        if (previous[column] > *result) {
            *result = previous[column];
        }
    }

    free(previous);
    free(current);
    return TRIANGLE_SUCCESS;
}

int main(void)
{
    InputReader input;
    size_t rows;
    int64_t maximum_sum;
    TriangleStatus status;

    input_reader_init(&input, stdin);

    if (!read_size_token(&input, &rows) || rows == 0) {
        fputs("Invalid triangle size\n", stderr);
        return EXIT_FAILURE;
    }

    status = find_maximum_sum(&input, rows, &maximum_sum);

    switch (status) {
        case TRIANGLE_SUCCESS:
            break;
        case TRIANGLE_INPUT_ERROR:
            fputs("Invalid triangle data\n", stderr);
            return EXIT_FAILURE;
        case TRIANGLE_ALLOCATION_ERROR:
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        case TRIANGLE_OVERFLOW:
            fputs("Integer overflow\n", stderr);
            return EXIT_FAILURE;
        case TRIANGLE_INVALID_ARGUMENT:
        default:
            fputs("Invalid argument\n", stderr);
            return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", maximum_sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}