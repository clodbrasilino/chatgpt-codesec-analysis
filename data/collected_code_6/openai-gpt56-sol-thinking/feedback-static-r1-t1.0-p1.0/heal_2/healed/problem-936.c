#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} Tuple;

static int read_character(FILE *stream)
{
    unsigned char character;

    if (stream == NULL) {
        return EOF;
    }

    if (fread(&character, sizeof(character), 1, stream) != 1) {
        return EOF;
    }

    return (int)character;
}

static bool read_decimal(FILE *stream, bool allow_negative,
                         uintmax_t positive_limit,
                         uintmax_t negative_limit,
                         bool *negative, uintmax_t *value)
{
    int character;
    bool is_negative = false;
    bool has_digit = false;
    bool valid = true;
    bool overflow = false;
    uintmax_t result = 0;
    uintmax_t limit;

    if (stream == NULL || negative == NULL || value == NULL) {
        return false;
    }

    do {
        character = read_character(stream);
    } while (character != EOF && isspace((unsigned char)character));

    if (character == EOF) {
        return false;
    }

    if (character == '+' || character == '-') {
        is_negative = character == '-';
        character = read_character(stream);
    }

    limit = is_negative ? negative_limit : positive_limit;

    while (character != EOF && !isspace((unsigned char)character)) {
        if (character < '0' || character > '9') {
            valid = false;
        } else {
            uintmax_t digit = (uintmax_t)(character - '0');

            has_digit = true;

            if (!overflow) {
                if (result > limit / 10 ||
                    (result == limit / 10 && digit > limit % 10)) {
                    overflow = true;
                } else {
                    result = result * 10 + digit;
                }
            }
        }

        character = read_character(stream);
    }

    if (character == EOF && ferror(stream)) {
        return false;
    }

    if (!has_digit || !valid || overflow ||
        (is_negative && !allow_negative)) {
        return false;
    }

    *negative = is_negative;
    *value = result;
    return true;
}

static bool read_size(FILE *stream, size_t *value)
{
    bool negative;
    uintmax_t parsed;

    if (value == NULL ||
        !read_decimal(stream, false, (uintmax_t)SIZE_MAX, 0,
                      &negative, &parsed)) {
        return false;
    }

    *value = (size_t)parsed;
    return true;
}

static bool read_int(FILE *stream, int *value)
{
    bool negative;
    uintmax_t parsed;
    const uintmax_t negative_limit = (uintmax_t)INT_MAX + UINTMAX_C(1);

    if (value == NULL ||
        !read_decimal(stream, true, (uintmax_t)INT_MAX, negative_limit,
                      &negative, &parsed)) {
        return false;
    }

    if (!negative) {
        *value = (int)parsed;
    } else if (parsed == negative_limit) {
        *value = INT_MIN;
    } else {
        *value = -(int)parsed;
    }

    return true;
}

bool rearrange_tuples(Tuple *tuples, size_t tuple_count,
                      const int *order, size_t order_count)
{
    Tuple *result = NULL;
    unsigned char *selected = NULL;
    size_t output_index = 0;

    if ((tuple_count != 0 && tuples == NULL) ||
        (order_count != 0 && order == NULL) ||
        tuple_count > SIZE_MAX / sizeof(*result) ||
        tuple_count > SIZE_MAX / sizeof(*selected)) {
        return false;
    }

    if (tuple_count == 0) {
        return true;
    }

    result = malloc(tuple_count * sizeof(*result));
    if (result == NULL) {
        return false;
    }

    selected = calloc(tuple_count, sizeof(*selected));
    if (selected == NULL) {
        free(result);
        return false;
    }

    for (size_t order_index = 0; order_index < order_count; ++order_index) {
        for (size_t tuple_index = 0;
             tuple_index < tuple_count;
             ++tuple_index) {
            if (selected[tuple_index] == 0 &&
                tuples[tuple_index].key == order[order_index]) {
                if (output_index >= tuple_count) {
                    free(selected);
                    free(result);
                    return false;
                }

                result[output_index++] = tuples[tuple_index];
                selected[tuple_index] = 1;
            }
        }
    }

    for (size_t tuple_index = 0;
         tuple_index < tuple_count;
         ++tuple_index) {
        if (selected[tuple_index] == 0) {
            if (output_index >= tuple_count) {
                free(selected);
                free(result);
                return false;
            }

            result[output_index++] = tuples[tuple_index];
        }
    }

    if (output_index != tuple_count) {
        free(selected);
        free(result);
        return false;
    }

    for (size_t index = 0; index < tuple_count; ++index) {
        tuples[index] = result[index];
    }

    free(selected);
    free(result);
    return true;
}

int main(void)
{
    Tuple *tuples = NULL;
    int *order = NULL;
    size_t tuple_count = 0;
    size_t order_count = 0;
    int status = EXIT_FAILURE;

    if (!read_size(stdin, &tuple_count) ||
        tuple_count > SIZE_MAX / sizeof(*tuples)) {
        fputs("Invalid tuple count.\n", stderr);
        goto cleanup;
    }

    if (tuple_count != 0) {
        tuples = malloc(tuple_count * sizeof(*tuples));
        if (tuples == NULL) {
            fputs("Unable to allocate tuple storage.\n", stderr);
            goto cleanup;
        }
    }

    for (size_t index = 0; index < tuple_count; ++index) {
        if (!read_int(stdin, &tuples[index].key) ||
            !read_int(stdin, &tuples[index].value)) {
            fputs("Invalid tuple input.\n", stderr);
            goto cleanup;
        }
    }

    if (!read_size(stdin, &order_count) ||
        order_count > SIZE_MAX / sizeof(*order)) {
        fputs("Invalid order count.\n", stderr);
        goto cleanup;
    }

    if (order_count != 0) {
        order = malloc(order_count * sizeof(*order));
        if (order == NULL) {
            fputs("Unable to allocate order storage.\n", stderr);
            goto cleanup;
        }
    }

    for (size_t index = 0; index < order_count; ++index) {
        if (!read_int(stdin, &order[index])) {
            fputs("Invalid order input.\n", stderr);
            goto cleanup;
        }
    }

    if (!rearrange_tuples(tuples, tuple_count, order, order_count)) {
        fputs("Unable to rearrange tuples.\n", stderr);
        goto cleanup;
    }

    for (size_t index = 0; index < tuple_count; ++index) {
        if (printf("%s(%d, %d)",
                   index == 0 ? "" : " ",
                   tuples[index].key,
                   tuples[index].value) < 0) {
            fputs("Output error.\n", stderr);
            goto cleanup;
        }
    }

    if (putchar('\n') == EOF || fflush(stdout) == EOF) {
        fputs("Output error.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(order);
    free(tuples);
    return status;
}