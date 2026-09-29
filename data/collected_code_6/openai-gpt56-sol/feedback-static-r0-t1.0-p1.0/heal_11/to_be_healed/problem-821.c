#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    size_t key_length;
    char *value;
} Entry;

typedef struct {
    Entry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

static char *duplicate_string_n(const char *source, size_t length)
{
    char *copy;

    if (source == NULL || length == SIZE_MAX) {
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

static char *duplicate_bounded_string(const char *source, size_t limit)
{
    const char *terminator;

    if (source == NULL || limit == 0U) {
        return NULL;
    }

    terminator = memchr(source, '\0', limit);
    if (terminator == NULL) {
        return NULL;
    }

    return duplicate_string_n(source, (size_t)(terminator - source));
}

static void dictionary_destroy(Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL) {
        return;
    }

    for (i = 0U; i < dictionary->size; ++i) {
        free(dictionary->entries[i].key);
        free(dictionary->entries[i].value);
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->size = 0U;
    dictionary->capacity = 0U;
}

static int dictionary_initialize(Dictionary *dictionary, size_t capacity)
{
    if (dictionary == NULL) {
        return -1;
    }

    dictionary->entries = NULL;
    dictionary->size = 0U;
    dictionary->capacity = 0U;

    if (capacity == 0U) {
        return 0;
    }

    if (capacity > SIZE_MAX / sizeof(*dictionary->entries)) {
        return -1;
    }

    dictionary->entries = calloc(capacity, sizeof(*dictionary->entries));
    if (dictionary->entries == NULL) {
        return -1;
    }

    dictionary->capacity = capacity;
    return 0;
}

static int dictionary_reserve(Dictionary *dictionary, size_t capacity)
{
    Entry *new_entries;
    size_t old_capacity;
    size_t allocation_size;
    size_t added_capacity;

    if (dictionary == NULL) {
        return -1;
    }

    if (capacity <= dictionary->capacity) {
        return 0;
    }

    if (capacity > SIZE_MAX / sizeof(*dictionary->entries)) {
        return -1;
    }

    old_capacity = dictionary->capacity;
    allocation_size = capacity * sizeof(*dictionary->entries);

    new_entries = realloc(dictionary->entries, allocation_size);
    if (new_entries == NULL) {
        return -1;
    }

    added_capacity = capacity - old_capacity;
    memset(&new_entries[old_capacity], 0,
           added_capacity * sizeof(*new_entries));

    dictionary->entries = new_entries;
    dictionary->capacity = capacity;
    return 0;
}

static size_t dictionary_find_n(const Dictionary *dictionary,
                                const char *key,
                                size_t key_length)
{
    size_t i;

    if (dictionary == NULL || key == NULL ||
        dictionary->size > dictionary->capacity ||
        (dictionary->size != 0U && dictionary->entries == NULL)) {
        return SIZE_MAX;
    }

    for (i = 0U; i < dictionary->size; ++i) {
        const Entry *entry = &dictionary->entries[i];

        if (entry->key != NULL &&
            entry->key_length == key_length &&
            (key_length == 0U ||
             memcmp(entry->key, key, key_length) == 0)) {
            return i;
        }
    }

    return SIZE_MAX;
}

static int dictionary_grow(Dictionary *dictionary)
{
    size_t new_capacity;
    size_t maximum_capacity;

    if (dictionary == NULL) {
        return -1;
    }

    maximum_capacity = SIZE_MAX / sizeof(*dictionary->entries);

    if (dictionary->capacity == 0U) {
        /* Possible weaknesses found:
         *  Assignment 'new_capacity=maximum_capacity<4U?maximum_capacity:4U', assigned value is less than 1
         */
        new_capacity = maximum_capacity < 4U ? maximum_capacity : 4U;
        /* Possible weaknesses found:
         *  Condition 'new_capacity==0U' is always true
         *  Condition 'new_capacity==0U' is always true [knownConditionTrueFalse]
         */
        if (new_capacity == 0U) {
            return -1;
        }
    } else {
        if (dictionary->capacity > maximum_capacity / 2U) {
            if (dictionary->capacity == maximum_capacity) {
                return -1;
            }
            new_capacity = maximum_capacity;
        } else {
            new_capacity = dictionary->capacity * 2U;
        }
    }

    return dictionary_reserve(dictionary, new_capacity);
}

static int dictionary_set_n(Dictionary *dictionary,
                            const char *key,
                            size_t key_length,
                            const char *value,
                            size_t value_length)
{
    size_t index;
    char *new_key;
    char *new_value;

    if (dictionary == NULL || key == NULL || value == NULL ||
        key_length == SIZE_MAX || value_length == SIZE_MAX ||
        dictionary->size > dictionary->capacity ||
        (dictionary->capacity != 0U && dictionary->entries == NULL)) {
        return -1;
    }

    new_value = duplicate_string_n(value, value_length);
    if (new_value == NULL) {
        return -1;
    }

    index = dictionary_find_n(dictionary, key, key_length);
    if (index != SIZE_MAX) {
        free(dictionary->entries[index].value);
        dictionary->entries[index].value = new_value;
        return 0;
    }

    new_key = duplicate_string_n(key, key_length);
    if (new_key == NULL) {
        free(new_value);
        return -1;
    }

    if (dictionary->size == dictionary->capacity &&
        dictionary_grow(dictionary) != 0) {
        free(new_key);
        free(new_value);
        return -1;
    }

    index = dictionary->size;
    dictionary->entries[index].key = new_key;
    dictionary->entries[index].key_length = key_length;
    dictionary->entries[index].value = new_value;
    dictionary->size = index + 1U;

    return 0;
}

static int dictionary_set_bounded(Dictionary *dictionary,
                                  const char *key,
                                  size_t key_limit,
                                  const char *value,
                                  size_t value_limit)
{
    const char *key_end;
    const char *value_end;

    if (dictionary == NULL || key == NULL || value == NULL ||
        key_limit == 0U || value_limit == 0U) {
        return -1;
    }

    key_end = memchr(key, '\0', key_limit);
    value_end = memchr(value, '\0', value_limit);

    if (key_end == NULL || value_end == NULL) {
        return -1;
    }

    return dictionary_set_n(dictionary,
                            key, (size_t)(key_end - key),
                            value, (size_t)(value_end - value));
}

static const char *dictionary_get_n(const Dictionary *dictionary,
                                    const char *key,
                                    size_t key_length)
{
    size_t index;

    if (dictionary == NULL || key == NULL) {
        return NULL;
    }

    index = dictionary_find_n(dictionary, key, key_length);
    if (index == SIZE_MAX) {
        return NULL;
    }

    return dictionary->entries[index].value;
}

static const char *dictionary_get_bounded(const Dictionary *dictionary,
                                          const char *key,
                                          size_t key_limit)
{
    const char *key_end;

    if (dictionary == NULL || key == NULL || key_limit == 0U) {
        return NULL;
    }

    key_end = memchr(key, '\0', key_limit);
    if (key_end == NULL) {
        return NULL;
    }

    return dictionary_get_n(dictionary, key, (size_t)(key_end - key));
}

int main(void)
{
    Dictionary dictionary;
    const char *value;
    char *bounded;

    static const char language_key[] = "language";
    static const char language_value[] = "C";
    static const char standard_key[] = "standard";
    static const char c17_value[] = "C17";
    static const char c23_value[] = "C23";
    static const char source_text[] = "dictionary";

    if (dictionary_initialize(&dictionary, 4U) != 0) {
        fputs("Failed to initialize dictionary\n", stderr);
        return EXIT_FAILURE;
    }

    if (dictionary_set_bounded(&dictionary,
                               language_key, sizeof(language_key),
                               language_value, sizeof(language_value)) != 0 ||
        dictionary_set_bounded(&dictionary,
                               standard_key, sizeof(standard_key),
                               c17_value, sizeof(c17_value)) != 0 ||
        dictionary_set_bounded(&dictionary,
                               standard_key, sizeof(standard_key),
                               c23_value, sizeof(c23_value)) != 0) {
        fputs("Failed to update dictionary\n", stderr);
        dictionary_destroy(&dictionary);
        return EXIT_FAILURE;
    }

    bounded = duplicate_bounded_string(source_text, sizeof(source_text));
    if (bounded == NULL) {
        fputs("Failed to duplicate string\n", stderr);
        dictionary_destroy(&dictionary);
        return EXIT_FAILURE;
    }

    value = dictionary_get_bounded(&dictionary,
                                   standard_key,
                                   sizeof(standard_key));
    if (value == NULL) {
        fputs("Dictionary entry not found\n", stderr);
        free(bounded);
        dictionary_destroy(&dictionary);
        return EXIT_FAILURE;
    }

    printf("%s: %s\n", bounded, value);

    free(bounded);
    dictionary_destroy(&dictionary);
    return EXIT_SUCCESS;
}