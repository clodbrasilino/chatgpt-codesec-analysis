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

static bool read_decimal(FILE *stream, bool *negative, uintmax_t *magnitude)
{
    int character;
    bool is_negative = false;
    bool have_digit = false;
    bool valid = true;
    uintmax_t result = 0;

    if (stream == NULL || negative == NULL || magnitude == NULL) {
        return false;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stream);
    } while (character != EOF && isspace((unsigned char)character));

    if (character == EOF) {
        return false;
    }

    if (character == '+' || character == '-') {
        is_negative = character == '-';
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stream);
    }

    while (character != EOF && !isspace((unsigned char)character)) {
        if (character >= '0' && character <= '9') {
            uintmax_t digit = (uintmax_t)(character - '0');

            have_digit = true;

            if (valid) {
                if (result > (UINTMAX_MAX - digit) / 10) {
                    valid = false;
                } else {
                    result = result * 10 + digit;
                }
            }
        } else {
            valid = false;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stream);
    }

    if (character == EOF && ferror(stream)) {
        return false;
    }

    if (!valid || !have_digit) {
        return false;
    }

    *negative = is_negative;
    *magnitude = result;
    return true;
}

static bool read_size(FILE *stream, size_t *value)
{
    bool negative;
    uintmax_t magnitude;

    if (value == NULL ||
        !read_decimal(stream, &negative, &magnitude) ||
        negative ||
        magnitude > (uintmax_t)SIZE_MAX) {
        return false;
    }

    *value = (size_t)magnitude;
    return true;
}

static bool read_int(FILE *stream, int *value)
{
    bool negative;
    uintmax_t magnitude;
    uintmax_t negative_limit;

    if (value == NULL ||
        !read_decimal(stream, &negative, &magnitude)) {
        return false;
    }

    negative_limit = (uintmax_t)(-(INT_MIN + 1)) + 1u;

    if (negative) {
        if (magnitude > negative_limit) {
            return false;
        }

        if (magnitude == negative_limit) {
            *value = INT_MIN;
        } else {
            *value = -(int)magnitude;
        }
    } else {
        if (magnitude > (uintmax_t)INT_MAX) {
            return false;
        }

        *value = (int)magnitude;
    }

    return true;
}

bool rearrange_tuples(Tuple *tuples, size_t tuple_count,
                      const int *order, size_t order_count)
{
    Tuple *result;
    unsigned char *selected;
    size_t output_index = 0;

    if ((tuple_count > 0 && tuples == NULL) ||
        (order_count > 0 && order == NULL) ||
        tuple_count > SIZE_MAX / sizeof(*result)) {
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
        for (size_t tuple_index = 0; tuple_index < tuple_count; ++tuple_index) {
            if (selected[tuple_index] == 0 &&
                tuples[tuple_index].key == order[order_index]) {
                result[output_index] = tuples[tuple_index];
                selected[tuple_index] = 1;
                ++output_index;
            }
        }
    }

    for (size_t tuple_index = 0; tuple_index < tuple_count; ++tuple_index) {
        if (selected[tuple_index] == 0) {
            result[output_index] = tuples[tuple_index];
            ++output_index;
        }
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
    size_t tuple_count;
    size_t order_count;
    int status = EXIT_FAILURE;

    if (!read_size(stdin, &tuple_count) ||
        tuple_count > SIZE_MAX / sizeof(*tuples)) {
        fputs("Invalid tuple count.\n", stderr);
        goto cleanup;
    }

    if (tuple_count > 0) {
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

    if (order_count > 0) {
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

    if (putchar('\n') == EOF) {
        fputs("Output error.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(order);
    free(tuples);
    return status;
}