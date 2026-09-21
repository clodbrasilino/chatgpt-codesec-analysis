#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *values;
    size_t length;
} Tuple;

static void free_tuples(Tuple *tuples, size_t count)
{
    if (tuples == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(tuples[i].values);
    }

    free(tuples);
}

static bool append_values(Tuple *tuple, const int *values, size_t count)
{
    if (count == 0) {
        return true;
    }

    if (tuple == NULL || values == NULL ||
        tuple->length > SIZE_MAX - count) {
        return false;
    }

    size_t new_length = tuple->length + count;

    if (new_length > SIZE_MAX / sizeof(*tuple->values)) {
        return false;
    }

    int *new_values = realloc(tuple->values,
                              new_length * sizeof(*new_values));
    if (new_values == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(new_values + tuple->length, values,
           count * sizeof(*values));

    tuple->values = new_values;
    tuple->length = new_length;
    return true;
}

bool join_tuples(const Tuple *input, size_t input_count,
                 Tuple **output, size_t *output_count)
{
    if (output == NULL || output_count == NULL) {
        return false;
    }

    *output = NULL;
    *output_count = 0;

    if (input_count == 0) {
        return true;
    }

    if (input == NULL ||
        input_count > SIZE_MAX / sizeof(Tuple)) {
        return false;
    }

    for (size_t i = 0; i < input_count; ++i) {
        if (input[i].length == 0 || input[i].values == NULL) {
            return false;
        }
    }

    Tuple *joined = calloc(input_count, sizeof(*joined));
    if (joined == NULL) {
        return false;
    }

    size_t joined_count = 0;

    for (size_t i = 0; i < input_count; ++i) {
        size_t destination = joined_count;

        for (size_t j = 0; j < joined_count; ++j) {
            if (joined[j].values[0] == input[i].values[0]) {
                destination = j;
                break;
            }
        }

        if (destination == joined_count) {
            ++joined_count;

            if (!append_values(&joined[destination],
                               input[i].values,
                               input[i].length)) {
                free_tuples(joined, joined_count);
                return false;
            }
        } else if (!append_values(&joined[destination],
                                  input[i].values + 1,
                                  input[i].length - 1)) {
            free_tuples(joined, joined_count);
            return false;
        }
    }

    *output = joined;
    *output_count = joined_count;
    return true;
}

static bool print_tuples(const Tuple *tuples, size_t count)
{
    if (fputc('[', stdout) == EOF) {
        return false;
    }

    for (size_t i = 0; i < count; ++i) {
        if (i > 0 && fputs(", ", stdout) == EOF) {
            return false;
        }

        if (fputc('(', stdout) == EOF) {
            return false;
        }

        for (size_t j = 0; j < tuples[i].length; ++j) {
            if (j > 0 && fputs(", ", stdout) == EOF) {
                return false;
            }

            if (printf("%d", tuples[i].values[j]) < 0) {
                return false;
            }
        }

        if (fputc(')', stdout) == EOF) {
            return false;
        }
    }

    return fputs("]\n", stdout) != EOF;
}

int main(void)
{
    int first[] = {5, 6};
    int second[] = {5, 7};
    int third[] = {5, 8};
    int fourth[] = {6, 10};
    int fifth[] = {7, 13};

    Tuple input[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])},
        {fourth, sizeof(fourth) / sizeof(fourth[0])},
        {fifth, sizeof(fifth) / sizeof(fifth[0])}
    };

    Tuple *output = NULL;
    size_t output_count = 0;

    if (!join_tuples(input, sizeof(input) / sizeof(input[0]),
                     &output, &output_count)) {
        fputs("Failed to join tuples.\n", stderr);
        return EXIT_FAILURE;
    }

    bool printed = print_tuples(output, output_count);
    free_tuples(output, output_count);

    if (!printed) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}