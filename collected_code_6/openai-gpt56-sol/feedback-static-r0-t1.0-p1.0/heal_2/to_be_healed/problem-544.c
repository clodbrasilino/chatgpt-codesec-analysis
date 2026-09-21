#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    const char *first;
    const char *second;
} Tuple;

static int checked_add(size_t a, size_t b, size_t *result)
{
    if (result == NULL || a > SIZE_MAX - b) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int bounded_string_length(const char *string, size_t limit,
                                 size_t *length)
{
    const char *terminator;

    if (string == NULL || length == NULL) {
        return 0;
    }

    terminator = memchr(string, '\0', limit);
    if (terminator == NULL) {
        return 0;
    }

    *length = (size_t)(terminator - string);
    return 1;
}

static char *flatten_tuple_list(const Tuple *tuples, size_t count)
{
    const size_t maximum_string_length = 1024U * 1024U;
    size_t *lengths = NULL;
    size_t output_length = 0;
    size_t allocation_size;
    size_t offset = 0;
    char *result = NULL;

    if (count > 0 && tuples == NULL) {
        return NULL;
    }

    if (count > SIZE_MAX / (2U * sizeof(*lengths))) {
        return NULL;
    }

    if (count > 0) {
        lengths = malloc(count * 2U * sizeof(*lengths));
        if (lengths == NULL) {
            return NULL;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        size_t first_length;
        size_t second_length;

        if (!bounded_string_length(tuples[i].first, maximum_string_length,
                                   &first_length) ||
            !bounded_string_length(tuples[i].second, maximum_string_length,
                                   &second_length)) {
            free(lengths);
            return NULL;
        }

        lengths[i * 2U] = first_length;
        lengths[i * 2U + 1U] = second_length;

        if (!checked_add(output_length, first_length, &output_length) ||
            !checked_add(output_length, 1U, &output_length) ||
            !checked_add(output_length, second_length, &output_length) ||
            (i + 1U < count &&
             !checked_add(output_length, 1U, &output_length))) {
            free(lengths);
            return NULL;
        }
    }

    if (!checked_add(output_length, 1U, &allocation_size)) {
        free(lengths);
        return NULL;
    }

    result = malloc(allocation_size);
    if (result == NULL) {
        free(lengths);
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        size_t first_length = lengths[i * 2U];
        size_t second_length = lengths[i * 2U + 1U];

        if (first_length > output_length - offset) {
            free(result);
            free(lengths);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + offset, tuples[i].first, first_length);
        offset += first_length;

        if (offset >= output_length) {
            free(result);
            free(lengths);
            return NULL;
        }
        result[offset++] = ',';

        if (second_length > output_length - offset) {
            free(result);
            free(lengths);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + offset, tuples[i].second, second_length);
        offset += second_length;

        if (i + 1U < count) {
            if (offset >= output_length) {
                free(result);
                free(lengths);
                return NULL;
            }
            result[offset++] = ' ';
        }
    }

    if (offset != output_length) {
        free(result);
        free(lengths);
        return NULL;
    }

    result[offset] = '\0';
    free(lengths);
    return result;
}

int main(void)
{
    const Tuple tuples[] = {
        {"apple", "red"},
        {"banana", "yellow"},
        {"grape", "purple"}
    };
    const size_t count = sizeof(tuples) / sizeof(tuples[0]);
    char *flattened = flatten_tuple_list(tuples, count);

    if (flattened == NULL) {
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