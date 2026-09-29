#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValue;

static char *duplicate_string(const char *source, size_t source_size)
{
    const char *terminator;
    size_t length;
    char *copy;

    if (source == NULL || source_size == 0U) {
        return NULL;
    }

    terminator = memchr(source, '\0', source_size);
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

    if (length != 0U) {
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
                               const size_t tuple_sizes[],
                               size_t tuple_count,
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
        tuple_sizes == NULL ||
        tuple_count == 0U ||
        tuple_count % 2U != 0U) {
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
        size_t key_index = index * 2U;
        size_t value_index = key_index + 1U;

        result[index].key =
            duplicate_string(tuple[key_index], tuple_sizes[key_index]);
        if (result[index].key == NULL) {
            free_dictionary(result, pair_count);
            return -1;
        }

        result[index].value =
            duplicate_string(tuple[value_index], tuple_sizes[value_index]);
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
    static const char name_key[] = "name";
    static const char name_value[] = "Alice";
    static const char age_key[] = "age";
    static const char age_value[] = "30";
    static const char city_key[] = "city";
    static const char city_value[] = "London";

    const char *const tuple[] = {
        name_key, name_value,
        age_key, age_value,
        city_key, city_value
    };

    const size_t tuple_sizes[] = {
        sizeof(name_key), sizeof(name_value),
        sizeof(age_key), sizeof(age_value),
        sizeof(city_key), sizeof(city_value)
    };

    KeyValue *dictionary = NULL;
    size_t dictionary_count = 0U;
    size_t index;

    if (tuple_to_dictionary(tuple,
                            tuple_sizes,
                            sizeof(tuple) / sizeof(tuple[0]),
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