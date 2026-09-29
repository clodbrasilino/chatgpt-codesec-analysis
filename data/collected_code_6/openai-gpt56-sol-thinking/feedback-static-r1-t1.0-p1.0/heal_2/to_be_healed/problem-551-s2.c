#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const int *values;
    size_t length;
} IntRow;

typedef struct {
    const IntRow *rows;
    size_t length;
} NestedIntList;

typedef enum {
    EXTRACT_SUCCESS = 0,
    EXTRACT_INVALID_ARGUMENT,
    EXTRACT_COLUMN_OUT_OF_RANGE,
    EXTRACT_ALLOCATION_FAILURE
} ExtractStatus;

static ExtractStatus extract_column(
    const NestedIntList *list,
    size_t column_index,
    int **column_out,
    size_t *length_out)
{
    int *column;

    if (column_out == NULL || length_out == NULL) {
        return EXTRACT_INVALID_ARGUMENT;
    }

    *column_out = NULL;
    *length_out = 0;

    if (list == NULL || (list->length != 0 && list->rows == NULL)) {
        return EXTRACT_INVALID_ARGUMENT;
    }

    for (size_t i = 0; i < list->length; ++i) {
        const IntRow *row = &list->rows[i];

        if (row->length != 0 && row->values == NULL) {
            return EXTRACT_INVALID_ARGUMENT;
        }

        if (column_index >= row->length) {
            return EXTRACT_COLUMN_OUT_OF_RANGE;
        }
    }

    if (list->length == 0) {
        return EXTRACT_SUCCESS;
    }

    if (list->length > SIZE_MAX / sizeof(*column)) {
        return EXTRACT_ALLOCATION_FAILURE;
    }

    column = malloc(list->length * sizeof(*column));
    if (column == NULL) {
        return EXTRACT_ALLOCATION_FAILURE;
    }

    for (size_t i = 0; i < list->length; ++i) {
        column[i] = list->rows[i].values[column_index];
    }

    *column_out = column;
    *length_out = list->length;

    return EXTRACT_SUCCESS;
}

static bool parse_size(const char *text, size_t *value_out)
{
    size_t value = 0;

    if (text == NULL || value_out == NULL || *text == '\0') {
        return false;
    }

    for (const unsigned char *p = (const unsigned char *)text;
         *p != '\0';
         ++p) {
        size_t digit;

        if (*p < (unsigned char)'0' || *p > (unsigned char)'9') {
            return false;
        }

        digit = (size_t)(*p - (unsigned char)'0');

        if (value > (SIZE_MAX - digit) / 10U) {
            return false;
        }

        value = value * 10U + digit;
    }

    *value_out = value;
    return true;
}

static bool print_column(const int *column, size_t length)
{
    if (length != 0 && column == NULL) {
        return false;
    }

    if (putchar('[') == EOF) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        if (i != 0 && fputs(", ", stdout) == EOF) {
            return false;
        }

        if (printf("%d", column[i]) < 0) {
            return false;
        }
    }

    return fputs("]\n", stdout) != EOF;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char *argv[const])
{
    const int row1[] = {1, 2, 3};
    const int row2[] = {4, 5, 6};
    const int row3[] = {7, 8, 9};
    const IntRow rows[] = {
        {row1, sizeof(row1) / sizeof(row1[0])},
        {row2, sizeof(row2) / sizeof(row2[0])},
        {row3, sizeof(row3) / sizeof(row3[0])}
    };
    const NestedIntList list = {
        rows,
        sizeof(rows) / sizeof(rows[0])
    };
    const char *program_name;
    size_t column_index;
    size_t column_length;
    int *column = NULL;
    ExtractStatus status;

    program_name = argc > 0 && argv[0] != NULL && argv[0][0] != '\0'
                       ? argv[0]
                       : "program";

    if (argc != 2) {
        fprintf(stderr, "Usage: %s COLUMN_INDEX\n", program_name);
        return EXIT_FAILURE;
    }

    if (!parse_size(argv[1], &column_index)) {
        fputs("Invalid column index\n", stderr);
        return EXIT_FAILURE;
    }

    status = extract_column(&list, column_index, &column, &column_length);

    switch (status) {
        case EXTRACT_SUCCESS:
            break;

        case EXTRACT_INVALID_ARGUMENT:
            fputs("Invalid argument\n", stderr);
            return EXIT_FAILURE;

        case EXTRACT_COLUMN_OUT_OF_RANGE:
            fputs("Column index is out of range\n", stderr);
            return EXIT_FAILURE;

        case EXTRACT_ALLOCATION_FAILURE:
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;

        default:
            fputs("Unexpected extraction status\n", stderr);
            return EXIT_FAILURE;
    }

    if (!print_column(column, column_length)) {
        free(column);
        fputs("Output operation failed\n", stderr);
        return EXIT_FAILURE;
    }

    free(column);
    return EXIT_SUCCESS;
}