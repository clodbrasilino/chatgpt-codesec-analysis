#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValue;

typedef struct {
    KeyValue *entries;
    size_t count;
} Dictionary;

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
    if (length >= SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    if (length > 0U) {
        memcpy(copy, source, length);
    }
    copy[length] = '\0';

    return copy;
}

static void free_dictionary(Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL) {
        return;
    }

    for (i = 0U; i < dictionary->count; ++i) {
        free(dictionary->entries[i].key);
        free(dictionary->entries[i].value);
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->count = 0U;
}

static int tuple_to_dictionary(const char *const tuple[],
                               const size_t lengths[],
                               size_t tuple_size,
                               Dictionary *dictionary)
{
    Dictionary result = {NULL, 0U};
    size_t pair_count;
    size_t i;

    if (dictionary == NULL ||
        (tuple_size != 0U && (tuple == NULL || lengths == NULL))) {
        return -1;
    }

    if ((tuple_size % 2U) != 0U) {
        return -1;
    }

    pair_count = tuple_size / 2U;
    if (pair_count == 0U) {
        dictionary->entries = NULL;
        dictionary->count = 0U;
        return 0;
    }

    if (pair_count > SIZE_MAX / sizeof(*result.entries)) {
        return -1;
    }

    result.entries = calloc(pair_count, sizeof(*result.entries));
    if (result.entries == NULL) {
        return -1;
    }
    result.count = pair_count;

    for (i = 0U; i < pair_count; ++i) {
        size_t key_index = i * 2U;
        size_t value_index = key_index + 1U;

        if (tuple[key_index] == NULL ||
            tuple[value_index] == NULL ||
            lengths[key_index] == 0U ||
            lengths[value_index] == 0U) {
            free_dictionary(&result);
            return -1;
        }

        result.entries[i].key =
            duplicate_string(tuple[key_index], lengths[key_index]);
        if (result.entries[i].key == NULL) {
            free_dictionary(&result);
            return -1;
        }

        result.entries[i].value =
            duplicate_string(tuple[value_index], lengths[value_index]);
        if (result.entries[i].value == NULL) {
            free_dictionary(&result);
            return -1;
        }
    }

    dictionary->entries = result.entries;
    dictionary->count = result.count;
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
    const size_t lengths[] = {
        sizeof(name_key), sizeof(name_value),
        sizeof(age_key), sizeof(age_value),
        sizeof(city_key), sizeof(city_value)
    };
    Dictionary dictionary = {NULL, 0U};
    size_t i;

    if (tuple_to_dictionary(tuple,
                            lengths,
                            sizeof(tuple) / sizeof(tuple[0]),
                            &dictionary) != 0) {
        fputs("Failed to convert tuple to dictionary.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < dictionary.count; ++i) {
        if (printf("%s: %s\n",
                   dictionary.entries[i].key,
                   dictionary.entries[i].value) < 0) {
            free_dictionary(&dictionary);
            return EXIT_FAILURE;
        }
    }

    free_dictionary(&dictionary);
    return EXIT_SUCCESS;
}