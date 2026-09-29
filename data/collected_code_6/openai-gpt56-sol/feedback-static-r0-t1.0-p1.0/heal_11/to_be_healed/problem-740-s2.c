#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValue;

static char *duplicate_string(const char *source, size_t max_length)
{
    const char *terminator;
    size_t length;
    char *copy;

    if (source == NULL || max_length == 0U) {
        return NULL;
    }

    terminator = memchr(source, '\0', max_length);
    if (terminator == NULL) {
        return NULL;
    }

    length = (size_t)(terminator - source);
    if (length > SIZE_MAX - 1U) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    if (length > 0U) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
    }
    copy[length] = '\0';

    return copy;
}

static void free_dictionary(KeyValue *dictionary, size_t count)
{
    size_t index;

    if (dictionary == NULL) {
        return;
    }

    for (index = 0U; index < count; ++index) {
        free(dictionary[index].key);
        free(dictionary[index].value);
    }

    free(dictionary);
}

static int tuple_to_dictionary(const char *const tuple[],
                               size_t tuple_count,
                               size_t maximum_string_length,
                               KeyValue **dictionary,
                               size_t *dictionary_count)
{
    KeyValue *result;
    size_t pair_count;
    size_t index;

    if (dictionary == NULL || dictionary_count == NULL) {
        return -1;
    }

    *dictionary = NULL;
    *dictionary_count = 0U;

    if (tuple == NULL ||
        tuple_count == 0U ||
        (tuple_count % 2U) != 0U ||
        maximum_string_length == 0U) {
        return -1;
    }

    pair_count = tuple_count / 2U;
    if (pair_count > SIZE_MAX / sizeof(*result)) {
        return -1;
    }

    result = calloc(pair_count, sizeof(*result));
    if (result == NULL) {
        return -1;
    }

    for (index = 0U; index < pair_count; ++index) {
        size_t tuple_index = index * 2U;

        if (tuple[tuple_index] == NULL ||
            tuple[tuple_index + 1U] == NULL) {
            free_dictionary(result, pair_count);
            return -1;
        }

        result[index].key =
            duplicate_string(tuple[tuple_index], maximum_string_length);
        if (result[index].key == NULL) {
            free_dictionary(result, pair_count);
            return -1;
        }

        result[index].value =
            duplicate_string(tuple[tuple_index + 1U],
                             maximum_string_length);
        if (result[index].value == NULL) {
            free_dictionary(result, pair_count);
            return -1;
        }
    }

    *dictionary = result;
    *dictionary_count = pair_count;

    return 0;
}

int main(void)
{
    static const char *const tuple[] = {
        "name", "Alice",
        "age", "30",
        "city", "London"
    };
    KeyValue *dictionary = NULL;
    size_t dictionary_count = 0U;
    size_t index;

    if (tuple_to_dictionary(tuple,
                            sizeof(tuple) / sizeof(tuple[0]),
                            1024U,
                            &dictionary,
                            &dictionary_count) != 0) {
        fputs("Failed to convert tuple\n", stderr);
        return EXIT_FAILURE;
    }

    for (index = 0U; index < dictionary_count; ++index) {
        if (printf("%s: %s\n",
                   dictionary[index].key,
                   dictionary[index].value) < 0) {
            free_dictionary(dictionary, dictionary_count);
            return EXIT_FAILURE;
        }
    }

    free_dictionary(dictionary, dictionary_count);
    return EXIT_SUCCESS;
}