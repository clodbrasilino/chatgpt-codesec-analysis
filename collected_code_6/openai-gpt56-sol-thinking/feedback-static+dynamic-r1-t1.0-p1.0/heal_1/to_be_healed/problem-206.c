#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    size_t count;
    const char *const *values;
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
        for (j = 0; j < tuples[i].count; ++j) {
            free(tuples[i].values[j]);
        }
        free(tuples[i].values);
    }

    free(tuples);
}

static int concatenate_strings(const char *left, const char *right, char **result)
{
    size_t left_length;
    size_t right_length;
    char *joined;

    if (left == NULL || right == NULL || result == NULL) {
        return -1;
    }

    *result = NULL;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    left_length = strlen(left);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    right_length = strlen(right);

    if (left_length > SIZE_MAX - right_length - 1) {
        return -1;
    }

    joined = malloc(left_length + right_length + 1);
    if (joined == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(joined, left, left_length);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(joined + left_length, right, right_length + 1);
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
        if (input[i].count < 2) {
            continue;
        }

        if (input[i].values == NULL) {
            free_tuples(output, tuple_count);
            return -1;
        }

        output[i].count = input[i].count - 1;

        if (output[i].count > SIZE_MAX / sizeof(*output[i].values)) {
            free_tuples(output, tuple_count);
            return -1;
        }

        output[i].values = calloc(output[i].count, sizeof(*output[i].values));
        if (output[i].values == NULL) {
            free_tuples(output, tuple_count);
            return -1;
        }

        for (j = 0; j < output[i].count; ++j) {
            if (concatenate_strings(input[i].values[j],
                                    input[i].values[j + 1],
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

        for (j = 0; j < tuples[i].count; ++j) {
            if (j != 0 && fputs(", ", stdout) == EOF) {
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
    static const char *const first[] = {"Gfg", "is", "Best"};
    static const char *const second[] = {"Gfg", "is", "good"};
    static const char *const third[] = {"Gfg", "is", "for", "Geeks"};
    static const InputTuple input[] = {
        {sizeof(first) / sizeof(first[0]), first},
        {sizeof(second) / sizeof(second[0]), second},
        {sizeof(third) / sizeof(third[0]), third}
    };
    StringTuple *result = NULL;
    const size_t tuple_count = sizeof(input) / sizeof(input[0]);

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