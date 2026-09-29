#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    size_t key_length;
    char *value;
    size_t value_length;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
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

static void dictionary_init(Dictionary *dictionary)
{
    if (dictionary != NULL) {
        dictionary->entries = NULL;
        dictionary->size = 0U;
        dictionary->capacity = 0U;
    }
}

static void dictionary_destroy(Dictionary *dictionary)
{
    size_t index;

    if (dictionary == NULL) {
        return;
    }

    for (index = 0U; index < dictionary->size; ++index) {
        free(dictionary->entries[index].key);
        free(dictionary->entries[index].value);
    }

    free(dictionary->entries);
    dictionary_init(dictionary);
}

static size_t dictionary_find_n(const Dictionary *dictionary,
                                const char *key,
                                size_t key_length)
{
    size_t index;

    if (dictionary == NULL || key == NULL) {
        return SIZE_MAX;
    }

    for (index = 0U; index < dictionary->size; ++index) {
        const DictionaryEntry *entry = &dictionary->entries[index];

        if (entry->key_length == key_length &&
            (key_length == 0U ||
             memcmp(entry->key, key, key_length) == 0)) {
            return index;
        }
    }

    return SIZE_MAX;
}

static int dictionary_reserve(Dictionary *dictionary, size_t capacity)
{
    DictionaryEntry *new_entries;

    if (dictionary == NULL) {
        return 0;
    }

    if (capacity <= dictionary->capacity) {
        return 1;
    }

    if (capacity > SIZE_MAX / sizeof(*new_entries)) {
        return 0;
    }

    new_entries = realloc(dictionary->entries,
                          capacity * sizeof(*new_entries));
    if (new_entries == NULL) {
        return 0;
    }

    dictionary->entries = new_entries;
    dictionary->capacity = capacity;
    return 1;
}

static int dictionary_set_lengths(Dictionary *dictionary,
                                  const char *key,
                                  size_t key_length,
                                  const char *value,
                                  size_t value_length)
{
    size_t index;
    char *new_key;
    char *new_value;

    if (dictionary == NULL || key == NULL || value == NULL ||
        key_length == SIZE_MAX || value_length == SIZE_MAX) {
        return 0;
    }

    index = dictionary_find_n(dictionary, key, key_length);
    if (index != SIZE_MAX) {
        new_value = duplicate_string_n(value, value_length);
        if (new_value == NULL) {
            return 0;
        }

        free(dictionary->entries[index].value);
        dictionary->entries[index].value = new_value;
        dictionary->entries[index].value_length = value_length;
        return 1;
    }

    if (dictionary->size == dictionary->capacity) {
        size_t new_capacity;

        if (dictionary->capacity == 0U) {
            new_capacity = 4U;
        } else {
            if (dictionary->capacity > SIZE_MAX / 2U) {
                return 0;
            }
            new_capacity = dictionary->capacity * 2U;
        }

        if (!dictionary_reserve(dictionary, new_capacity)) {
            return 0;
        }
    }

    new_key = duplicate_string_n(key, key_length);
    if (new_key == NULL) {
        return 0;
    }

    new_value = duplicate_string_n(value, value_length);
    if (new_value == NULL) {
        free(new_key);
        return 0;
    }

    dictionary->entries[dictionary->size].key = new_key;
    dictionary->entries[dictionary->size].key_length = key_length;
    dictionary->entries[dictionary->size].value = new_value;
    dictionary->entries[dictionary->size].value_length = value_length;
    ++dictionary->size;

    return 1;
}

static int dictionary_set_n(Dictionary *dictionary,
                            const char *key,
                            size_t key_max_length,
                            const char *value,
                            size_t value_max_length)
{
    const char *key_terminator;
    const char *value_terminator;
    size_t key_length;
    size_t value_length;

    if (dictionary == NULL || key == NULL || value == NULL ||
        key_max_length == 0U || value_max_length == 0U) {
        return 0;
    }

    key_terminator = memchr(key, '\0', key_max_length);
    value_terminator = memchr(value, '\0', value_max_length);

    if (key_terminator == NULL || value_terminator == NULL) {
        return 0;
    }

    key_length = (size_t)(key_terminator - key);
    value_length = (size_t)(value_terminator - value);

    return dictionary_set_lengths(dictionary, key, key_length,
                                  value, value_length);
}

static int dictionary_merge(const Dictionary *first,
                            const Dictionary *second,
                            Dictionary *result)
{
    Dictionary temporary;
    size_t index;
    size_t required_capacity;

    if (first == NULL || second == NULL || result == NULL ||
        result == first || result == second) {
        return 0;
    }

    dictionary_init(&temporary);

    if (first->size > SIZE_MAX - second->size) {
        return 0;
    }

    required_capacity = first->size + second->size;

    if (!dictionary_reserve(&temporary, required_capacity)) {
        dictionary_destroy(&temporary);
        return 0;
    }

    for (index = 0U; index < first->size; ++index) {
        const DictionaryEntry *entry = &first->entries[index];

        if (!dictionary_set_lengths(&temporary,
                                    entry->key,
                                    entry->key_length,
                                    entry->value,
                                    entry->value_length)) {
            dictionary_destroy(&temporary);
            return 0;
        }
    }

    for (index = 0U; index < second->size; ++index) {
        const DictionaryEntry *entry = &second->entries[index];

        if (!dictionary_set_lengths(&temporary,
                                    entry->key,
                                    entry->key_length,
                                    entry->value,
                                    entry->value_length)) {
            dictionary_destroy(&temporary);
            return 0;
        }
    }

    dictionary_destroy(result);
    *result = temporary;
    return 1;
}

static int dictionary_print(const Dictionary *dictionary)
{
    size_t index;

    if (dictionary == NULL) {
        return 0;
    }

    for (index = 0U; index < dictionary->size; ++index) {
        const DictionaryEntry *entry = &dictionary->entries[index];

        if (fwrite(entry->key, 1U, entry->key_length, stdout) !=
                entry->key_length ||
            fwrite(": ", 1U, 2U, stdout) != 2U ||
            fwrite(entry->value, 1U, entry->value_length, stdout) !=
                entry->value_length ||
            fputc('\n', stdout) == EOF) {
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    Dictionary first;
    Dictionary second;
    Dictionary merged;
    int exit_status = EXIT_FAILURE;

    dictionary_init(&first);
    dictionary_init(&second);
    dictionary_init(&merged);

    if (!dictionary_set_n(&first, "name", sizeof("name"),
                          "Alice", sizeof("Alice")) ||
        !dictionary_set_n(&first, "city", sizeof("city"),
                          "London", sizeof("London")) ||
        !dictionary_set_n(&second, "city", sizeof("city"),
                          "Paris", sizeof("Paris")) ||
        !dictionary_set_n(&second, "language", sizeof("language"),
                          "C", sizeof("C"))) {
        goto cleanup;
    }

    if (!dictionary_merge(&first, &second, &merged)) {
        goto cleanup;
    }

    if (!dictionary_print(&merged)) {
        goto cleanup;
    }

    exit_status = EXIT_SUCCESS;

cleanup:
    dictionary_destroy(&merged);
    dictionary_destroy(&second);
    dictionary_destroy(&first);

    return exit_status;
}