#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_column(const char *tuple, size_t tuple_length, size_t column)
{
    const char *start;
    const char *end;
    size_t remaining;
    size_t current;
    size_t field_length;
    size_t result_size;
    char *result;

    if (tuple == NULL) {
        return NULL;
    }

    start = tuple;
    remaining = tuple_length;

    for (current = 0; current < column; ++current) {
        end = memchr(start, ':', remaining);
        if (end == NULL) {
            return NULL;
        }

        field_length = (size_t)(end - start);
        start = end + 1;
        remaining -= field_length + 1;
    }

    end = memchr(start, ':', remaining);
    field_length = end == NULL ? remaining : (size_t)(end - start);

    if (field_length == SIZE_MAX) {
        return NULL;
    }

    result_size = field_length + 1;
    result = malloc(result_size);
    if (result == NULL) {
        return NULL;
    }

    if (field_length > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result, start, field_length);
    }
    result[field_length] = '\0';

    return result;
}

int main(void)
{
    static const char tuple[] = "alpha:beta:gamma";
    const size_t column = 1;
    char *value;

    value = get_column(tuple, sizeof(tuple) - 1, column);
    if (value == NULL) {
        fputs("Unable to get column\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", value) < 0) {
        free(value);
        return EXIT_FAILURE;
    }

    free(value);
    return EXIT_SUCCESS;
}