#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    const char *first;
    size_t first_length;
    const char *second;
    size_t second_length;
} Tuple;

static int checked_add(size_t a, size_t b, size_t *result)
{
    if (result == NULL || a > SIZE_MAX - b) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int append_bytes(char **position, size_t *remaining,
                        const char *source, size_t source_length)
{
    if (position == NULL || *position == NULL || remaining == NULL ||
        (source_length > 0 && source == NULL) ||
        source_length > *remaining) {
        return 0;
    }

    if (source_length > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(*position, source, source_length);
        *position += source_length;
        *remaining -= source_length;
    }

    return 1;
}

static char *flatten_tuple_list(const Tuple *tuples, size_t count)
{
    size_t length = 0;

    if (count > 0 && tuples == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        if ((tuples[i].first_length > 0 && tuples[i].first == NULL) ||
            (tuples[i].second_length > 0 && tuples[i].second == NULL)) {
            return NULL;
        }

        if (!checked_add(length, tuples[i].first_length, &length) ||
            !checked_add(length, tuples[i].second_length, &length) ||
            !checked_add(length, 4, &length) ||
            (i + 1 < count && !checked_add(length, 2, &length))) {
            return NULL;
        }
    }

    if (!checked_add(length, 1, &length)) {
        return NULL;
    }

    char *result = malloc(length);
    if (result == NULL) {
        return NULL;
    }

    char *position = result;
    size_t remaining = length;

    for (size_t i = 0; i < count; ++i) {
        static const char opening[] = "(";
        static const char separator[] = ", ";
        static const char closing[] = ")";

        if (!append_bytes(&position, &remaining, opening, 1) ||
            !append_bytes(&position, &remaining,
                          tuples[i].first, tuples[i].first_length) ||
            !append_bytes(&position, &remaining, separator, 2) ||
            !append_bytes(&position, &remaining,
                          tuples[i].second, tuples[i].second_length) ||
            !append_bytes(&position, &remaining, closing, 1) ||
            (i + 1 < count &&
             !append_bytes(&position, &remaining, separator, 2))) {
            free(result);
            return NULL;
        }
    }

    if (remaining != 1) {
        free(result);
        return NULL;
    }

    *position = '\0';
    return result;
}

int main(void)
{
    static const char first0[] = "apple";
    static const char second0[] = "red";
    static const char first1[] = "banana";
    static const char second1[] = "yellow";
    static const char first2[] = "grape";
    static const char second2[] = "purple";

    const Tuple tuples[] = {
        {first0, sizeof(first0) - 1, second0, sizeof(second0) - 1},
        {first1, sizeof(first1) - 1, second1, sizeof(second1) - 1},
        {first2, sizeof(first2) - 1, second2, sizeof(second2) - 1}
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