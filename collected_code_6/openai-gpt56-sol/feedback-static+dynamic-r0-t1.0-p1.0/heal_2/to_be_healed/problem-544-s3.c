#include <errno.h>
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

static int checked_add_size(size_t a, size_t b, size_t *result)
{
    if (result == NULL || a > SIZE_MAX - b) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int append_bytes(char **cursor, size_t *remaining,
                        const char *source, size_t length)
{
    if (cursor == NULL || *cursor == NULL || remaining == NULL ||
        (length > 0 && source == NULL) || length > *remaining) {
        return 0;
    }

    if (length > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(*cursor, source, length);
        *cursor += length;
        *remaining -= length;
    }

    return 1;
}

static char *flatten_tuple_list(const Tuple *tuples, size_t count)
{
    static const char tuple_separator[] = ", ";
    static const char item_separator[] = ": ";
    const size_t tuple_separator_length = sizeof(tuple_separator) - 1;
    const size_t item_separator_length = sizeof(item_separator) - 1;
    size_t content_length = 0;
    size_t allocation_size;
    size_t remaining;
    char *output;
    char *cursor;

    if (count > 0 && tuples == NULL) {
        errno = EINVAL;
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        if ((tuples[i].first_length > 0 && tuples[i].first == NULL) ||
            (tuples[i].second_length > 0 && tuples[i].second == NULL)) {
            errno = EINVAL;
            return NULL;
        }

        if (!checked_add_size(content_length, tuples[i].first_length,
                              &content_length) ||
            !checked_add_size(content_length, item_separator_length,
                              &content_length) ||
            !checked_add_size(content_length, tuples[i].second_length,
                              &content_length) ||
            (i + 1 < count &&
             !checked_add_size(content_length, tuple_separator_length,
                               &content_length))) {
            errno = EOVERFLOW;
            return NULL;
        }
    }

    if (!checked_add_size(content_length, 1, &allocation_size)) {
        errno = EOVERFLOW;
        return NULL;
    }

    output = malloc(allocation_size);
    if (output == NULL) {
        return NULL;
    }

    cursor = output;
    remaining = content_length;

    for (size_t i = 0; i < count; ++i) {
        if (!append_bytes(&cursor, &remaining, tuples[i].first,
                          tuples[i].first_length) ||
            !append_bytes(&cursor, &remaining, item_separator,
                          item_separator_length) ||
            !append_bytes(&cursor, &remaining, tuples[i].second,
                          tuples[i].second_length) ||
            (i + 1 < count &&
             !append_bytes(&cursor, &remaining, tuple_separator,
                           tuple_separator_length))) {
            free(output);
            errno = EOVERFLOW;
            return NULL;
        }
    }

    if (remaining != 0) {
        free(output);
        errno = EINVAL;
        return NULL;
    }

    *cursor = '\0';
    return output;
}

int main(void)
{
    static const char name_key[] = "name";
    static const char name_value[] = "Alice";
    static const char age_key[] = "age";
    static const char age_value[] = "30";
    static const char city_key[] = "city";
    static const char city_value[] = "London";

    const Tuple tuples[] = {
        {name_key, sizeof(name_key) - 1, name_value, sizeof(name_value) - 1},
        {age_key, sizeof(age_key) - 1, age_value, sizeof(age_value) - 1},
        {city_key, sizeof(city_key) - 1, city_value, sizeof(city_value) - 1}
    };
    const size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    char *flattened = flatten_tuple_list(tuples, tuple_count);

    if (flattened == NULL) {
        perror("flatten_tuple_list");
        return EXIT_FAILURE;
    }

    if (puts(flattened) == EOF) {
        free(flattened);
        return EXIT_FAILURE;
    }

    free(flattened);
    return EXIT_SUCCESS;
}