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
    const char *const list[],
    size_t count,
    float **result,
    size_t *result_count)
{
    float *values;
    size_t converted = 0;
    size_t i;

    if (result == NULL || result_count == NULL ||
        (count > 0 && list == NULL)) {
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

    for (i = 0; i < count; ++i) {
        const char *text = list[i];
        char *end;
        float value;

        if (text == NULL) {
            continue;
        }

        errno = 0;
        value = strtof(text, &end);

        if (end == text || errno == ERANGE) {
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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    const char **arguments = NULL;
    float *values = NULL;
    size_t argument_count;
    size_t value_count = 0;
    size_t i;
    ConvertStatus status;

    argument_count = argc > 1 ? (size_t)(argc - 1) : 0;

    if (argument_count > 0) {
        if (argument_count > SIZE_MAX / sizeof(*arguments)) {
            fputs("Input list is too large.\n", stderr);
            return EXIT_FAILURE;
        }

        arguments = malloc(argument_count * sizeof(*arguments));
        if (arguments == NULL) {
            fputs("Failed to allocate the input list.\n", stderr);
            return EXIT_FAILURE;
        }

        for (i = 0; i < argument_count; ++i) {
            arguments[i] = argv[i + 1];
        }
    }

    status = convert_to_floats(
        arguments,
        argument_count,
        &values,
        &value_count);

    free(arguments);

    if (status != CONVERT_SUCCESS) {
        fputs("Failed to convert the input list.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < value_count; ++i) {
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