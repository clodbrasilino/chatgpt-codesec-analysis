#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    size_t count;
    size_t capacity;
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
    if (length == SIZE_MAX) {
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

static int dictionary_init(Dictionary *dictionary, size_t capacity)
{
    if (dictionary == NULL) {
        return -1;
    }

    dictionary->entries = NULL;
    dictionary->count = 0U;
    dictionary->capacity = 0U;

    if (capacity == 0U) {
        return 0;
    }

    if (capacity > SIZE_MAX / sizeof(dictionary->entries[0])) {
        return -1;
    }

    dictionary->entries = calloc(capacity, sizeof(dictionary->entries[0]));
    if (dictionary->entries == NULL) {
        return -1;
    }

    dictionary->capacity = capacity;
    return 0;
}

static void dictionary_destroy(Dictionary *dictionary)
{
    size_t index;

    if (dictionary == NULL) {
        return;
    }

    for (index = 0U; index < dictionary->count; ++index) {
        free(dictionary->entries[index].key);
        free(dictionary->entries[index].value);
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->count = 0U;
    dictionary->capacity = 0U;
}

static int dictionary_add(
    Dictionary *dictionary,
    const char *key,
    size_t key_size,
    const char *value,
    size_t value_size)
{
    char *key_copy;
    char *value_copy;
    DictionaryEntry *entry;

    if (dictionary == NULL ||
        dictionary->entries == NULL ||
        key == NULL ||
        value == NULL ||
        key_size == 0U ||
        value_size == 0U ||
        dictionary->count >= dictionary->capacity) {
        return -1;
    }

    key_copy = duplicate_string(key, key_size);
    if (key_copy == NULL) {
        return -1;
    }

    value_copy = duplicate_string(value, value_size);
    if (value_copy == NULL) {
        free(key_copy);
        return -1;
    }

    entry = &dictionary->entries[dictionary->count];
    entry->key = key_copy;
    entry->value = value_copy;
    ++dictionary->count;

    return 0;
}

static const char *dictionary_key_at(
    const Dictionary *dictionary,
    size_t index)
{
    if (dictionary == NULL ||
        dictionary->entries == NULL ||
        index >= dictionary->count) {
        return NULL;
    }

    return dictionary->entries[index].key;
}

int main(void)
{
    static const char name_key[] = "name";
    static const char name_value[] = "Alice";
    static const char age_key[] = "age";
    static const char age_value[] = "30";
    static const char city_key[] = "city";
    static const char city_value[] = "Paris";

    Dictionary dictionary;
    const char *key;
    int status = EXIT_FAILURE;

    if (dictionary_init(&dictionary, 3U) != 0) {
        fputs("Failed to initialize dictionary.\n", stderr);
        return EXIT_FAILURE;
    }

    if (dictionary_add(
            &dictionary,
            name_key,
            sizeof(name_key),
            name_value,
            sizeof(name_value)) != 0 ||
        dictionary_add(
            &dictionary,
            age_key,
            sizeof(age_key),
            age_value,
            sizeof(age_value)) != 0 ||
        dictionary_add(
            &dictionary,
            city_key,
            sizeof(city_key),
            city_value,
            sizeof(city_value)) != 0) {
        fputs("Failed to add dictionary entries.\n", stderr);
        goto cleanup;
    }

    key = dictionary_key_at(&dictionary, 1U);
    if (key == NULL) {
        fputs("Dictionary index is out of range.\n", stderr);
        goto cleanup;
    }

    if (puts(key) == EOF) {
        fputs("Failed to write output.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    dictionary_destroy(&dictionary);
    return status;
}