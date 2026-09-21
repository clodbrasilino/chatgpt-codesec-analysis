#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stddef.h>
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

    if (length > 0 && items == NULL) {
        return EINVAL;
    }

    if (printf("[") < 0) {
        return EIO;
    }

    for (i = 0; i < length; ++i) {
        if (i > 0 && printf(", ") < 0) {
            return EIO;
        }

        switch (items[i].kind) {
        case ENCODED_SINGLE:
            if (printf("%d", items[i].value) < 0) {
                return EIO;
            }
            break;

        case ENCODED_RUN:
            if (printf("(%zu, %d)",
                       items[i].count,
                       items[i].value) < 0) {
                return EIO;
            }
            break;

        default:
            return EINVAL;
        }
    }

    if (printf("]\n") < 0) {
        return EIO;
    }

    if (fflush(stdout) == EOF) {
        return EIO;
    }

    return 0;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
static int run_program(int argc, char *const argv[const])
{
    int *input = NULL;
    EncodedItem *encoded = NULL;
    size_t input_length;
    size_t encoded_length = 0;
    size_t i;
    int status;

    if (argc < 0 || argv == NULL) {
        return EXIT_FAILURE;
    }

    input_length = argc > 1 ? (size_t)(argc - 1) : 0;

    if (input_length > 0) {
        if (input_length > SIZE_MAX / sizeof(*input)) {
            return EXIT_FAILURE;
        }

        input = malloc(input_length * sizeof(*input));
        if (input == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < input_length; ++i) {
        const char *const argument = argv[i + 1];
        char *end = NULL;
        long value;

        if (argument == NULL) {
            free(input);
            return EXIT_FAILURE;
        }

        errno = 0;
        value = strtol(argument, &end, 10);

        if (errno == ERANGE ||
            end == argument ||
            *end != '\0' ||
            value < INT_MIN ||
            value > INT_MAX) {
            free(input);
            return EXIT_FAILURE;
        }

        input[i] = (int)value;
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

int main(int argc, char *argv[])
{
    return run_program(argc, argv);
}