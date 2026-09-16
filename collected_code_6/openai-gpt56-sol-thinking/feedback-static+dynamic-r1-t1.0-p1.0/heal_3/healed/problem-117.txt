#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    CONVERT_SUCCESS,
    CONVERT_INVALID_ARGUMENT,
    CONVERT_SIZE_ERROR,
    CONVERT_ALLOCATION_ERROR
} ConvertStatus;

static ConvertStatus convert_to_floats(
    char *const *const list,
    size_t count,
    float **result,
    size_t *result_count)
{
    float *values;
    size_t converted = 0;

    if (result == NULL || result_count == NULL ||
        (count != 0 && list == NULL)) {
        return CONVERT_INVALID_ARGUMENT;
    }

    *result = NULL;
    *result_count = 0;

    if (count == 0) {
        return CONVERT_SUCCESS;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        return CONVERT_SIZE_ERROR;
    }

    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        return CONVERT_ALLOCATION_ERROR;
    }

    for (size_t i = 0; i < count; ++i) {
        const char *input = list[i];
        char *end;
        float value;

        if (input == NULL) {
            continue;
        }

        errno = 0;
        value = strtof(input, &end);

        if (end == input || errno == ERANGE) {
            continue;
        }

        while (*end != '\0' && isspace((unsigned char)*end)) {
            ++end;
        }

        if (*end == '\0') {
            values[converted++] = value;
        }
    }

    if (converted == 0) {
        free(values);
        return CONVERT_SUCCESS;
    }

    *result = values;
    *result_count = converted;

    return CONVERT_SUCCESS;
}

int main(int argc, char *argv[])
{
    float *values = NULL;
    size_t value_count = 0;
    char *const *inputs = NULL;
    size_t input_count = 0;

    if (argc > 1) {
        inputs = argv + 1;
        input_count = (size_t)(argc - 1);
    }

    ConvertStatus status = convert_to_floats(
        inputs,
        input_count,
        &values,
        &value_count);

    if (status != CONVERT_SUCCESS) {
        fputs("Failed to convert the input list.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < value_count; ++i) {
        if (printf("%.*g\n", FLT_DECIMAL_DIG, (double)values[i]) < 0) {
            free(values);
            fputs("Failed to write output.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    free(values);

    if (fflush(stdout) == EOF) {
        fputs("Failed to flush output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}