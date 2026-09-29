#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

static void dictionary_init(Dictionary *dictionary)
{
    dictionary->entries = NULL;
    dictionary->size = 0U;
    dictionary->capacity = 0U;
}

static void dictionary_destroy(Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL) {
        return;
    }

    for (i = 0U; i < dictionary->size; ++i) {
        free(dictionary->entries[i].key);
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->size = 0U;
    dictionary->capacity = 0U;
}

static char *duplicate_string(const char *source)
{
    size_t length;
    char *copy;

    if (source == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(source);
    if (length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, source, length + 1U);
    return copy;
}

static bool dictionary_reserve(Dictionary *dictionary, size_t minimum_capacity)
{
    size_t new_capacity;
    DictionaryEntry *new_entries;

    if (dictionary == NULL) {
        return false;
    }

    if (minimum_capacity <= dictionary->capacity) {
        return true;
    }

    new_capacity = dictionary->capacity == 0U ? 4U : dictionary->capacity;

    while (new_capacity < minimum_capacity) {
        if (new_capacity > SIZE_MAX / 2U) {
            new_capacity = minimum_capacity;
            break;
        }
        new_capacity *= 2U;
    }

    if (new_capacity > SIZE_MAX / sizeof(*new_entries)) {
        return false;
    }

    new_entries = realloc(
        dictionary->entries,
        new_capacity * sizeof(*new_entries)
    );

    if (new_entries == NULL) {
        return false;
    }

    dictionary->entries = new_entries;
    dictionary->capacity = new_capacity;
    return true;
}

static bool dictionary_set(Dictionary *dictionary, const char *key, int value)
{
    size_t i;
    char *key_copy;

    if (dictionary == NULL || key == NULL) {
        return false;
    }

    for (i = 0U; i < dictionary->size; ++i) {
        if (strcmp(dictionary->entries[i].key, key) == 0) {
            dictionary->entries[i].value = value;
            return true;
        }
    }

    if (dictionary->size == SIZE_MAX) {
        return false;
    }

    key_copy = duplicate_string(key);
    if (key_copy == NULL) {
        return false;
    }

    if (!dictionary_reserve(dictionary, dictionary->size + 1U)) {
        free(key_copy);
        return false;
    }

    dictionary->entries[dictionary->size].key = key_copy;
    dictionary->entries[dictionary->size].value = value;
    ++dictionary->size;

    return true;
}

static bool dictionary_all_values_are_same(
    const Dictionary *dictionary,
    bool *result
)
{
    size_t i;
    int first_value;

    if (dictionary == NULL || result == NULL) {
        return false;
    }

    if (dictionary->size > 0U && dictionary->entries == NULL) {
        return false;
    }

    *result = true;

    if (dictionary->size < 2U) {
        return true;
    }

    first_value = dictionary->entries[0].value;

    for (i = 1U; i < dictionary->size; ++i) {
        if (dictionary->entries[i].value != first_value) {
            *result = false;
            break;
        }
    }

    return true;
}

int main(void)
{
    Dictionary dictionary;
    bool all_same;

    dictionary_init(&dictionary);

    if (!dictionary_set(&dictionary, "first", 42) ||
        !dictionary_set(&dictionary, "second", 42) ||
        !dictionary_set(&dictionary, "third", 42)) {
        fprintf(stderr, "Failed to create dictionary.\n");
        dictionary_destroy(&dictionary);
        return EXIT_FAILURE;
    }

    if (!dictionary_all_values_are_same(&dictionary, &all_same)) {
        fprintf(stderr, "Failed to check dictionary values.\n");
        dictionary_destroy(&dictionary);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", all_same ? "true" : "false") < 0) {
        dictionary_destroy(&dictionary);
        return EXIT_FAILURE;
    }

    dictionary_destroy(&dictionary);
    return EXIT_SUCCESS;
}