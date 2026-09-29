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

typedef struct {
    FILE *stream;
    bool read_error;
} Input;

static bool input_init(Input *input, FILE *stream)
{
    if (input == NULL || stream == NULL) {
        return false;
    }

    input->stream = stream;
    input->read_error = false;
    return true;
}

static int input_get(Input *input)
{
    int character;

    if (input == NULL || input->stream == NULL || input->read_error) {
        return EOF;
    }

    character = fgetc(input->stream);

    if (character == EOF && ferror(input->stream)) {
        input->read_error = true;
    }

    return character;
}

static bool read_decimal(Input *input, bool *negative, uintmax_t *magnitude)
{
    int character;
    bool is_negative = false;
    bool have_digit = false;
    bool valid = true;
    uintmax_t result = 0;

    if (input == NULL || negative == NULL || magnitude == NULL) {
        return false;
    }

    do {
        character = input_get(input);
    } while (character != EOF && isspace((unsigned char)character));

    if (character == EOF) {
        return false;
    }

    if (character == '+' || character == '-') {
        is_negative = character == '-';
        character = input_get(input);
    }

    while (character != EOF && !isspace((unsigned char)character)) {
        if (character >= '0' && character <= '9') {
            uintmax_t digit = (uintmax_t)(character - '0');

            have_digit = true;

            if (valid) {
                if (result > (UINTMAX_MAX - digit) / UINTMAX_C(10)) {
                    valid = false;
                } else {
                    result = result * UINTMAX_C(10) + digit;
                }
            }
        } else {
            valid = false;
        }

        character = input_get(input);
    }

    if (input->read_error || !valid || !have_digit) {
        return false;
    }

    *negative = is_negative;
    *magnitude = result;
    return true;
}

static bool read_size(Input *input, size_t *value)
{
    bool negative;
    uintmax_t magnitude;

    if (value == NULL ||
        !read_decimal(input, &negative, &magnitude) ||
        negative ||
        magnitude > (uintmax_t)SIZE_MAX) {
        return false;
    }

    *value = (size_t)magnitude;
    return true;
}

static bool read_int(Input *input, int *value)
{
    bool negative;
    uintmax_t magnitude;
    uintmax_t negative_limit;

    if (value == NULL ||
        !read_decimal(input, &negative, &magnitude)) {
        return false;
    }

    negative_limit = (uintmax_t)(-(INT_MIN + 1)) + UINTMAX_C(1);

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
    Tuple *result = NULL;
    bool *selected = NULL;
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

    for (size_t order_index = 0;
         order_index < order_count;
         ++order_index) {
        for (size_t tuple_index = 0;
             tuple_index < tuple_count;
             ++tuple_index) {
            if (!selected[tuple_index] &&
                tuples[tuple_index].key == order[order_index]) {
                result[output_index] = tuples[tuple_index];
                selected[tuple_index] = true;
                ++output_index;
            }
        }
    }

    for (size_t tuple_index = 0;
         tuple_index < tuple_count;
         ++tuple_index) {
        if (!selected[tuple_index]) {
            result[output_index] = tuples[tuple_index];
            ++output_index;
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
    Input input;
    Tuple *tuples = NULL;
    int *order = NULL;
    size_t tuple_count;
    size_t order_count;
    int status = EXIT_FAILURE;

    if (!input_init(&input, stdin)) {
        fputs("Unable to initialize input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!read_size(&input, &tuple_count) ||
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
        if (!read_int(&input, &tuples[index].key) ||
            !read_int(&input, &tuples[index].value)) {
            fputs("Invalid tuple input.\n", stderr);
            goto cleanup;
        }
    }

    if (!read_size(&input, &order_count) ||
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
        if (!read_int(&input, &order[index])) {
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