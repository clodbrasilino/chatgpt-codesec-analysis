#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *data;
    size_t length;
} InputString;

typedef struct {
    size_t count;
    const InputString *values;
} InputTuple;

typedef struct {
    size_t count;
    char **values;
} StringTuple;

static void free_tuples(StringTuple *tuples, size_t count)
{
    size_t i;
    size_t j;

    if (tuples == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        if (tuples[i].values != NULL) {
            for (j = 0; j < tuples[i].count; ++j) {
                free(tuples[i].values[j]);
            }
        }

        free(tuples[i].values);
    }

    free(tuples);
}

static int copy_bytes(char *destination,
                      size_t capacity,
                      size_t offset,
                      const char *source,
                      size_t length)
{
    size_t i;

    if (destination == NULL || (source == NULL && length != 0)) {
        return -1;
    }

    if (offset > capacity || length > capacity - offset) {
        return -1;
    }

    for (i = 0; i < length; ++i) {
        destination[offset + i] = source[i];
    }

    return 0;
}

static int concatenate_strings(const InputString *left,
                               const InputString *right,
                               char **result)
{
    size_t joined_length;
    size_t allocation_size;
    char *joined;

    if (left == NULL || right == NULL || result == NULL) {
        return -1;
    }

    *result = NULL;

    if (left->data == NULL || right->data == NULL) {
        return -1;
    }

    if (left->length > SIZE_MAX - right->length) {
        return -1;
    }

    joined_length = left->length + right->length;

    if (joined_length == SIZE_MAX) {
        return -1;
    }

    allocation_size = joined_length + 1;
    joined = malloc(allocation_size);
    if (joined == NULL) {
        return -1;
    }

    if (copy_bytes(joined,
                   joined_length,
                   0,
                   left->data,
                   left->length) != 0) {
        free(joined);
        return -1;
    }

    if (copy_bytes(joined,
                   joined_length,
                   left->length,
                   right->data,
                   right->length) != 0) {
        free(joined);
        return -1;
    }

    joined[joined_length] = '\0';
    *result = joined;

    return 0;
}

static int concatenate_adjacent_elements(const InputTuple *input,
                                         size_t tuple_count,
                                         StringTuple **result)
{
    StringTuple *output;
    size_t i;
    size_t j;

    if (result == NULL || (input == NULL && tuple_count != 0)) {
        return -1;
    }

    *result = NULL;

    if (tuple_count == 0) {
        return 0;
    }

    if (tuple_count > SIZE_MAX / sizeof(*output)) {
        return -1;
    }

    output = calloc(tuple_count, sizeof(*output));
    if (output == NULL) {
        return -1;
    }

    for (i = 0; i < tuple_count; ++i) {
        size_t output_count;
        char **output_values;

        if (input[i].count < 2) {
            continue;
        }

        if (input[i].values == NULL) {
            free_tuples(output, tuple_count);
            return -1;
        }

        output_count = input[i].count - 1;

        if (output_count > SIZE_MAX / sizeof(*output_values)) {
            free_tuples(output, tuple_count);
            return -1;
        }

        output_values = calloc(output_count, sizeof(*output_values));
        if (output_values == NULL) {
            free_tuples(output, tuple_count);
            return -1;
        }

        output[i].count = output_count;
        output[i].values = output_values;

        for (j = 0; j < output_count; ++j) {
            if (concatenate_strings(&input[i].values[j],
                                    &input[i].values[j + 1],
                                    &output[i].values[j]) != 0) {
                free_tuples(output, tuple_count);
                return -1;
            }
        }
    }

    *result = output;
    return 0;
}

static int print_tuples(const StringTuple *tuples, size_t count)
{
    size_t i;
    size_t j;

    if (tuples == NULL && count != 0) {
        return -1;
    }

    if (fputc('[', stdout) == EOF) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        if (i != 0 && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (fputc('(', stdout) == EOF) {
            return -1;
        }

        if (tuples[i].count != 0 && tuples[i].values == NULL) {
            return -1;
        }

        for (j = 0; j < tuples[i].count; ++j) {
            if (j != 0 && fputs(", ", stdout) == EOF) {
                return -1;
            }

            if (tuples[i].values[j] == NULL) {
                return -1;
            }

            if (fprintf(stdout, "\"%s\"", tuples[i].values[j]) < 0) {
                return -1;
            }
        }

        if (fputc(')', stdout) == EOF) {
            return -1;
        }
    }

    if (fputs("]\n", stdout) == EOF) {
        return -1;
    }

    return 0;
}

int main(void)
{
    static const InputString first[] = {
        {"Gfg", sizeof("Gfg") - 1},
        {"is", sizeof("is") - 1},
        {"Best", sizeof("Best") - 1}
    };
    static const InputString second[] = {
        {"Gfg", sizeof("Gfg") - 1},
        {"is", sizeof("is") - 1},
        {"good", sizeof("good") - 1}
    };
    static const InputString third[] = {
        {"Gfg", sizeof("Gfg") - 1},
        {"is", sizeof("is") - 1},
        {"for", sizeof("for") - 1},
        {"Geeks", sizeof("Geeks") - 1}
    };
    static const InputTuple input[] = {
        {sizeof(first) / sizeof(first[0]), first},
        {sizeof(second) / sizeof(second[0]), second},
        {sizeof(third) / sizeof(third[0]), third}
    };
    const size_t tuple_count = sizeof(input) / sizeof(input[0]);
    StringTuple *result = NULL;

    if (concatenate_adjacent_elements(input, tuple_count, &result) != 0) {
        return EXIT_FAILURE;
    }

    if (print_tuples(result, tuple_count) != 0) {
        free_tuples(result, tuple_count);
        return EXIT_FAILURE;
    }

    free_tuples(result, tuple_count);
    return EXIT_SUCCESS;
}