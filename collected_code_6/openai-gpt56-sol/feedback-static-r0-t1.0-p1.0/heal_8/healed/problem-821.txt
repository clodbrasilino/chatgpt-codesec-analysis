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
    new_entries = realloc(dictionary->entries,
                          capacity * sizeof(*dictionary->entries));
    if (new_entries == NULL) {
        return -1;
    }

    memset(new_entries + old_capacity, 0,
           (capacity - old_capacity) * sizeof(*new_entries));

    dictionary->entries = new_entries;
    dictionary->capacity = capacity;
    return 0;
}

static size_t dictionary_find_n(const Dictionary *dictionary,
                                const char *key,
                                size_t key_length)
{
    size_t i;

    if (dictionary == NULL || key == NULL) {
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

    if (dictionary == NULL) {
        return -1;
    }

    if (dictionary->capacity == 0U) {
        new_capacity = 4U;
    } else {
        if (dictionary->capacity > SIZE_MAX / 2U) {
            return -1;
        }
        new_capacity = dictionary->capacity * 2U;
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

    if (dictionary == NULL || key == NULL || value == NULL) {
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
    dictionary->size++;
    return 0;
}

static int dictionary_set(Dictionary *dictionary,
                          const char *key,
                          const char *value)
{
    if (key == NULL || value == NULL) {
        return -1;
    }

    return dictionary_set_n(dictionary, key, strlen(key),
                            value, strlen(value));
}

static const char *dictionary_get_n(const Dictionary *dictionary,
                                    const char *key,
                                    size_t key_length)
{
    size_t index = dictionary_find_n(dictionary, key, key_length);

    if (index == SIZE_MAX) {
        return NULL;
    }

    return dictionary->entries[index].value;
}

static const char *dictionary_get(const Dictionary *dictionary,
                                  const char *key)
{
    if (key == NULL) {
        return NULL;
    }

    return dictionary_get_n(dictionary, key, strlen(key));
}

int main(void)
{
    Dictionary dictionary;
    const char *value;
    char *bounded;

    if (dictionary_initialize(&dictionary, 4U) != 0) {
        fputs("Failed to initialize dictionary\n", stderr);
        return EXIT_FAILURE;
    }

    if (dictionary_set(&dictionary, "language", "C") != 0 ||
        dictionary_set(&dictionary, "standard", "C17") != 0 ||
        dictionary_set(&dictionary, "standard", "C23") != 0) {
        fputs("Failed to update dictionary\n", stderr);
        dictionary_destroy(&dictionary);
        return EXIT_FAILURE;
    }

    bounded = duplicate_bounded_string("dictionary", sizeof("dictionary"));
    if (bounded == NULL) {
        fputs("Failed to duplicate string\n", stderr);
        dictionary_destroy(&dictionary);
        return EXIT_FAILURE;
    }

    value = dictionary_get(&dictionary, "standard");
    if (value != NULL) {
        printf("%s: %s\n", bounded, value);
    }

    free(bounded);
    dictionary_destroy(&dictionary);
    return EXIT_SUCCESS;
}