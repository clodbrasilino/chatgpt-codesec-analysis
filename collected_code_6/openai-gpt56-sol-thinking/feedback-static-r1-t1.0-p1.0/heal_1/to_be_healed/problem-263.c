#include <stdbool.h>
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
    size_t size;
    size_t capacity;
} Dictionary;

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

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, source, length + 1);
    return copy;
}

static Dictionary *dictionary_create(void)
{
    return calloc(1, sizeof(Dictionary));
}

static void dictionary_destroy(Dictionary *dictionary)
{
    size_t index;

    if (dictionary == NULL) {
        return;
    }

    for (index = 0; index < dictionary->size; ++index) {
        free(dictionary->entries[index].key);
        free(dictionary->entries[index].value);
    }

    free(dictionary->entries);
    free(dictionary);
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

    new_capacity = dictionary->capacity == 0 ? 8 : dictionary->capacity;

    while (new_capacity < minimum_capacity) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = minimum_capacity;
            break;
        }
        new_capacity *= 2;
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

static bool dictionary_put(
    Dictionary *dictionary,
    const char *key,
    const char *value
)
{
    size_t index;
    char *new_key;
    char *new_value;

    if (dictionary == NULL || key == NULL || value == NULL) {
        return false;
    }

    for (index = 0; index < dictionary->size; ++index) {
        if (strcmp(dictionary->entries[index].key, key) == 0) {
            new_value = duplicate_string(value);
            if (new_value == NULL) {
                return false;
            }

            free(dictionary->entries[index].value);
            dictionary->entries[index].value = new_value;
            return true;
        }
    }

    if (dictionary->size == SIZE_MAX) {
        return false;
    }

    new_key = duplicate_string(key);
    if (new_key == NULL) {
        return false;
    }

    new_value = duplicate_string(value);
    if (new_value == NULL) {
        free(new_key);
        return false;
    }

    if (!dictionary_reserve(dictionary, dictionary->size + 1)) {
        free(new_key);
        free(new_value);
        return false;
    }

    dictionary->entries[dictionary->size].key = new_key;
    dictionary->entries[dictionary->size].value = new_value;
    ++dictionary->size;

    return true;
}

static Dictionary *dictionary_merge(
    const Dictionary *first,
    const Dictionary *second
)
{
    Dictionary *merged;
    size_t index;

    if (first == NULL || second == NULL) {
        return NULL;
    }

    merged = dictionary_create();
    if (merged == NULL) {
        return NULL;
    }

    for (index = 0; index < first->size; ++index) {
        if (!dictionary_put(
                merged,
                first->entries[index].key,
                first->entries[index].value)) {
            dictionary_destroy(merged);
            return NULL;
        }
    }

    for (index = 0; index < second->size; ++index) {
        if (!dictionary_put(
                merged,
                second->entries[index].key,
                second->entries[index].value)) {
            dictionary_destroy(merged);
            return NULL;
        }
    }

    return merged;
}

static bool dictionary_print(const Dictionary *dictionary)
{
    size_t index;

    if (dictionary == NULL) {
        return false;
    }

    for (index = 0; index < dictionary->size; ++index) {
        if (printf(
                "%s=%s\n",
                dictionary->entries[index].key,
                dictionary->entries[index].value) < 0) {
            return false;
        }
    }

    return fflush(stdout) != EOF;
}

int main(void)
{
    Dictionary *first = NULL;
    Dictionary *second = NULL;
    Dictionary *merged = NULL;
    int result = EXIT_FAILURE;

    first = dictionary_create();
    second = dictionary_create();

    if (first == NULL || second == NULL) {
        goto cleanup;
    }

    if (!dictionary_put(first, "name", "Alice") ||
        !dictionary_put(first, "city", "Paris") ||
        !dictionary_put(second, "city", "Berlin") ||
        !dictionary_put(second, "role", "Engineer")) {
        goto cleanup;
    }

    merged = dictionary_merge(first, second);
    if (merged == NULL) {
        goto cleanup;
    }

    if (!dictionary_print(merged)) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    dictionary_destroy(merged);
    dictionary_destroy(second);
    dictionary_destroy(first);

    return result;
}