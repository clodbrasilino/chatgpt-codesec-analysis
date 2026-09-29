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

static int read_size_token(FILE *input, size_t *result)
{
    size_t value = 0;
    int overflow = 0;
    int c;

    if (input == NULL || result == NULL) {
        return 0;
    }

    do {
        c = fgetc(input);
    } while (c != EOF && isspace((unsigned char)c));

    if (c == EOF) {
        return 0;
    }

    if (c == '+') {
        c = fgetc(input);
    }

    if (c == EOF || !isdigit((unsigned char)c)) {
        return 0;
    }

    do {
        size_t digit = (size_t)(c - '0');

        if (value > (SIZE_MAX - digit) / 10) {
            overflow = 1;
        } else if (!overflow) {
            value = value * 10 + digit;
        }

        c = fgetc(input);
    } while (c != EOF && isdigit((unsigned char)c));

    if (c != EOF && !isspace((unsigned char)c)) {
        return 0;
    }

    if (c == EOF && ferror(input)) {
        return 0;
    }

    if (overflow) {
        return 0;
    }

    *result = value;
    return 1;
}

static int read_int64_token(FILE *input, int64_t *result)
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
        c = fgetc(input);
    } while (c != EOF && isspace((unsigned char)c));

    if (c == EOF) {
        return 0;
    }

    if (c == '+' || c == '-') {
        negative = c == '-';
        c = fgetc(input);
    }

    if (c == EOF || !isdigit((unsigned char)c)) {
        return 0;
    }

    limit = (uint64_t)INT64_MAX + (negative ? UINT64_C(1) : UINT64_C(0));

    do {
        uint64_t digit = (uint64_t)(c - '0');

        if (magnitude > (limit - digit) / UINT64_C(10)) {
            overflow = 1;
        } else if (!overflow) {
            magnitude = magnitude * UINT64_C(10) + digit;
        }

        c = fgetc(input);
    } while (c != EOF && isdigit((unsigned char)c));

    if (c != EOF && !isspace((unsigned char)c)) {
        return 0;
    }

    if (c == EOF && ferror(input)) {
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

static TriangleStatus find_maximum_sum(FILE *input, size_t rows, int64_t *result)
{
    int64_t *previous;
    int64_t *current;
    size_t row;
    size_t column;

    if (input == NULL || result == NULL || rows == 0) {
        return TRIANGLE_INVALID_ARGUMENT;
    }

    if (rows > SIZE_MAX / sizeof(*previous)) {
        return TRIANGLE_ALLOCATION_ERROR;
    }

    previous = malloc(rows * sizeof(*previous));
    current = malloc(rows * sizeof(*current));

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
    size_t rows;
    int64_t maximum_sum;
    TriangleStatus status;

    if (!read_size_token(stdin, &rows) || rows == 0) {
        fputs("Invalid triangle size\n", stderr);
        return EXIT_FAILURE;
    }

    status = find_maximum_sum(stdin, rows, &maximum_sum);

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