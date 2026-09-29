#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *const *items;
    size_t count;
} StringTuple;

int flatten_tuple_list(const StringTuple *tuples,
                       size_t tuple_count,
                       const char *separator,
                       char **result)
{
    size_t separator_length;
    size_t total_length = 0;
    size_t position = 0;
    int has_item = 0;
    char *flattened;

    if (result == NULL || separator == NULL) {
        return -1;
    }

    *result = NULL;

    if (tuple_count > 0 && tuples == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    separator_length = strlen(separator);

    for (size_t i = 0; i < tuple_count; ++i) {
        if (tuples[i].count > 0 && tuples[i].items == NULL) {
            return -1;
        }

        for (size_t j = 0; j < tuples[i].count; ++j) {
            size_t item_length;

            if (tuples[i].items[j] == NULL) {
                return -1;
            }

            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            item_length = strlen(tuples[i].items[j]);

            if (has_item) {
                if (separator_length > SIZE_MAX - total_length) {
                    return -1;
                }
                total_length += separator_length;
            }

            if (item_length > SIZE_MAX - total_length) {
                return -1;
            }

            total_length += item_length;
            has_item = 1;
        }
    }

    if (total_length == SIZE_MAX) {
        return -1;
    }

    flattened = malloc(total_length + 1);
    if (flattened == NULL) {
        return -1;
    }

    has_item = 0;

    for (size_t i = 0; i < tuple_count; ++i) {
        for (size_t j = 0; j < tuples[i].count; ++j) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t item_length = strlen(tuples[i].items[j]);

            if (has_item) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(flattened + position, separator, separator_length);
                position += separator_length;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(flattened + position, tuples[i].items[j], item_length);
            position += item_length;
            has_item = 1;
        }
    }

    flattened[position] = '\0';
    *result = flattened;

    return 0;
}

int main(void)
{
    const char *tuple1[] = {"alpha", "beta"};
    const char *tuple2[] = {"gamma", "delta", "epsilon"};
    const char *tuple3[] = {"zeta"};
    const StringTuple tuples[] = {
        {tuple1, sizeof(tuple1) / sizeof(tuple1[0])},
        {tuple2, sizeof(tuple2) / sizeof(tuple2[0])},
        {tuple3, sizeof(tuple3) / sizeof(tuple3[0])}
    };
    char *flattened = NULL;

    if (flatten_tuple_list(
            tuples,
            sizeof(tuples) / sizeof(tuples[0]),
            ", ",
            &flattened) != 0) {
        fputs("Failed to flatten tuple list.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(flattened) == EOF) {
        free(flattened);
        return EXIT_FAILURE;
    }

    free(flattened);
    return EXIT_SUCCESS;
}