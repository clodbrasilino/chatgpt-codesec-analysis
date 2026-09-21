#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *key;
    size_t key_length;
    int value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

static void dictionary_init(Dictionary *dictionary)
{
    if (dictionary == NULL) {
        return;
    }

    dictionary->entries = NULL;
    dictionary->size = 0U;
    dictionary->capacity = 0U;
}

static void dictionary_destroy(Dictionary *dictionary)
{
    if (dictionary == NULL) {
        return;
    }

    if (dictionary->entries != NULL) {
        for (size_t i = 0U; i < dictionary->size; ++i) {
            free(dictionary->entries[i].key);
        }
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->size = 0U;
    dictionary->capacity = 0U;
}

static char *duplicate_string(const char *source, size_t length)
{
    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    char *copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    for (size_t i = 0U; i < length; ++i) {
        copy[i] = source[i];
    }

    copy[length] = '\0';
    return copy;
}

static bool strings_are_equal(
    const char *left,
    size_t left_length,
    const char *right,
    size_t right_length
)
{
    if (left == NULL || right == NULL || left_length != right_length) {
        return false;
    }

    for (size_t i = 0U; i < left_length; ++i) {
        if (left[i] != right[i]) {
            return false;
        }
    }

    return true;
}

static bool dictionary_reserve(
    Dictionary *dictionary,
    size_t minimum_capacity
)
{
    if (dictionary == NULL) {
        return false;
    }

    if (minimum_capacity <= dictionary->capacity) {
        return true;
    }

    size_t new_capacity =
        dictionary->capacity == 0U ? 4U : dictionary->capacity;

    while (new_capacity < minimum_capacity) {
        if (new_capacity > SIZE_MAX / 2U) {
            new_capacity = minimum_capacity;
            break;
        }

        new_capacity *= 2U;
    }

    if (new_capacity > SIZE_MAX / sizeof(DictionaryEntry)) {
        return false;
    }

    DictionaryEntry *new_entries = realloc(
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

static bool dictionary_set(
    Dictionary *dictionary,
    const char *key,
    size_t key_length,
    int value
)
{
    if (dictionary == NULL || key == NULL) {
        return false;
    }

    for (size_t i = 0U; i < dictionary->size; ++i) {
        if (strings_are_equal(
                dictionary->entries[i].key,
                dictionary->entries[i].key_length,
                key,
                key_length
            )) {
            dictionary->entries[i].value = value;
            return true;
        }
    }

    if (dictionary->size == SIZE_MAX) {
        return false;
    }

    char *key_copy = duplicate_string(key, key_length);
    if (key_copy == NULL) {
        return false;
    }

    if (!dictionary_reserve(dictionary, dictionary->size + 1U)) {
        free(key_copy);
        return false;
    }

    DictionaryEntry *entry = &dictionary->entries[dictionary->size];
    entry->key = key_copy;
    entry->key_length = key_length;
    entry->value = value;
    ++dictionary->size;

    return true;
}

static bool dictionary_all_values_are_same(
    const Dictionary *dictionary,
    bool *result
)
{
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

    const int first_value = dictionary->entries[0].value;

    for (size_t i = 1U; i < dictionary->size; ++i) {
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

    if (!dictionary_set(
            &dictionary,
            "first",
            sizeof("first") - 1U,
            42
        ) ||
        !dictionary_set(
            &dictionary,
            "second",
            sizeof("second") - 1U,
            42
        ) ||
        !dictionary_set(
            &dictionary,
            "third",
            sizeof("third") - 1U,
            42
        )) {
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