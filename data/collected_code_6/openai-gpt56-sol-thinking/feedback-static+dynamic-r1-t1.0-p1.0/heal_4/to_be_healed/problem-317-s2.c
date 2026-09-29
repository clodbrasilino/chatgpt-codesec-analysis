#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    ENCODED_SINGLE,
    ENCODED_RUN
} EncodingKind;

typedef struct {
    EncodingKind kind;
    int value;
    size_t count;
} EncodedItem;

int modified_run_length_encode(const int *input,
                               size_t length,
                               EncodedItem **output,
                               size_t *output_length)
{
    EncodedItem *items;
    size_t input_index = 0;
    size_t output_index = 0;

    if (output == NULL || output_length == NULL) {
        return EINVAL;
    }

    *output = NULL;
    *output_length = 0;

    if (length == 0) {
        return 0;
    }

    if (input == NULL) {
        return EINVAL;
    }

    if (length > SIZE_MAX / sizeof(*items)) {
        return EOVERFLOW;
    }

    items = malloc(length * sizeof(*items));
    if (items == NULL) {
        return ENOMEM;
    }

    while (input_index < length) {
        size_t run_end = input_index + 1;
        size_t count;

        while (run_end < length &&
               input[run_end] == input[input_index]) {
            ++run_end;
        }

        count = run_end - input_index;

        items[output_index].kind =
            count == 1 ? ENCODED_SINGLE : ENCODED_RUN;
        items[output_index].value = input[input_index];
        items[output_index].count = count;

        ++output_index;
        input_index = run_end;
    }

    *output = items;
    *output_length = output_index;

    return 0;
}

static int print_encoding(const EncodedItem *items, size_t length)
{
    size_t i;

    if (length != 0 && items == NULL) {
        return EINVAL;
    }

    if (fputc('[', stdout) == EOF) {
        return EIO;
    }

    for (i = 0; i < length; ++i) {
        if (i != 0 && fputs(", ", stdout) == EOF) {
            return EIO;
        }

        switch (items[i].kind) {
        case ENCODED_SINGLE:
            if (fprintf(stdout, "%d", items[i].value) < 0) {
                return EIO;
            }
            break;

        case ENCODED_RUN:
            if (fprintf(stdout,
                        "(%zu, %d)",
                        items[i].count,
                        items[i].value) < 0) {
                return EIO;
            }
            break;

        default:
            return EINVAL;
        }
    }

    if (fputs("]\n", stdout) == EOF || fflush(stdout) == EOF) {
        return EIO;
    }

    return 0;
}

static int parse_arguments(int argc,
                           /* Possible weaknesses found:
                            * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
                            *  Parameter 'argv' can be declared as const array [constParameter]
                            */
                           char *argv[const],
                           int **input,
                           size_t *input_length)
{
    int *values = NULL;
    size_t length;
    size_t i;

    if (argv == NULL || input == NULL || input_length == NULL || argc < 0) {
        return EINVAL;
    }

    *input = NULL;
    *input_length = 0;

    length = argc > 1 ? (size_t)(argc - 1) : 0;

    if (length == 0) {
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*values)) {
        return EOVERFLOW;
    }

    values = malloc(length * sizeof(*values));
    if (values == NULL) {
        return ENOMEM;
    }

    for (i = 0; i < length; ++i) {
        const char *argument = argv[i + 1];
        char *end = NULL;
        long value;

        if (argument == NULL) {
            free(values);
            return EINVAL;
        }

        errno = 0;
        value = strtol(argument, &end, 10);

        if (errno == ERANGE ||
            end == argument ||
            *end != '\0' ||
            value < INT_MIN ||
            value > INT_MAX) {
            free(values);
            return EINVAL;
        }

        values[i] = (int)value;
    }

    *input = values;
    *input_length = length;

    return 0;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char *argv[const])
{
    int *input = NULL;
    EncodedItem *encoded = NULL;
    size_t input_length = 0;
    size_t encoded_length = 0;
    int status;

    status = parse_arguments(argc, argv, &input, &input_length);
    if (status != 0) {
        return EXIT_FAILURE;
    }

    status = modified_run_length_encode(input,
                                        input_length,
                                        &encoded,
                                        &encoded_length);

    free(input);

    if (status != 0) {
        free(encoded);
        return EXIT_FAILURE;
    }

    status = print_encoding(encoded, encoded_length);

    free(encoded);

    return status == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}