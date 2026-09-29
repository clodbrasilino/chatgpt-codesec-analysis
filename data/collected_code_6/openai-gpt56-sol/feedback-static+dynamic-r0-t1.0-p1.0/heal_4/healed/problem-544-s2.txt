#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *first;
    size_t first_length;
    const char *second;
    size_t second_length;
} Tuple;

static int checked_add(size_t a, size_t b, size_t *result)
{
    if (result == NULL || b > SIZE_MAX - a) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int append_bytes(char **position, size_t *remaining,
                        const void *source, size_t length)
{
    if (position == NULL || *position == NULL || remaining == NULL) {
        return 0;
    }

    if (length > *remaining || (length > 0 && source == NULL)) {
        return 0;
    }

    if (length > 0) {
        memcpy(*position, source, length);
        *position += length;
        *remaining -= length;
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

        if (!checked_add(length, 1, &length) ||
            !checked_add(length, tuples[i].first_length, &length) ||
            !checked_add(length, 2, &length) ||
            !checked_add(length, tuples[i].second_length, &length) ||
            !checked_add(length, 1, &length)) {
            return NULL;
        }

        if (i != count - 1 && !checked_add(length, 2, &length)) {
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
        if (!append_bytes(&position, &remaining, "(", 1) ||
            !append_bytes(&position, &remaining,
                          tuples[i].first, tuples[i].first_length) ||
            !append_bytes(&position, &remaining, ", ", 2) ||
            !append_bytes(&position, &remaining,
                          tuples[i].second, tuples[i].second_length) ||
            !append_bytes(&position, &remaining, ")", 1)) {
            free(result);
            return NULL;
        }

        if (i != count - 1 &&
            !append_bytes(&position, &remaining, ", ", 2)) {
            free(result);
            return NULL;
        }
    }

    if (!append_bytes(&position, &remaining, "", 1) || remaining != 0) {
        free(result);
        return NULL;
    }

    return result;
}

int main(void)
{
    static const char apple[] = "apple";
    static const char red[] = "red";
    static const char banana[] = "banana";
    static const char yellow[] = "yellow";
    static const char grape[] = "grape";
    static const char purple[] = "purple";

    const Tuple tuples[] = {
        {apple, sizeof apple - 1, red, sizeof red - 1},
        {banana, sizeof banana - 1, yellow, sizeof yellow - 1},
        {grape, sizeof grape - 1, purple, sizeof purple - 1}
    };

    const size_t count = sizeof tuples / sizeof tuples[0];
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