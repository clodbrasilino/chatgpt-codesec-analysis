#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} DictionaryItem;

typedef struct {
    DictionaryItem *items;
    size_t size;
    size_t capacity;
} Dictionary;

static bool duplicate_string(const char *source, size_t source_size, char **result)
{
    const char *terminator;
    size_t length;
    char *copy;

    if (source == NULL || result == NULL) {
        return false;
    }

    *result = NULL;

    terminator = memchr(source, '\0', source_size);
    if (terminator == NULL) {
        return false;
    }

    length = (size_t)(terminator - source);

    if (length == SIZE_MAX) {
        return false;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return false;
    }

    if (length > 0U) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
    }

    copy[length] = '\0';
    *result = copy;
    return true;
}

static bool dictionary_initialize(Dictionary *dictionary, size_t capacity)
{
    if (dictionary == NULL) {
        return false;
    }

    dictionary->items = NULL;
    dictionary->size = 0U;
    dictionary->capacity = 0U;

    if (capacity == 0U) {
        return true;
    }

    if (capacity > SIZE_MAX / sizeof(*dictionary->items)) {
        return false;
    }

    dictionary->items = calloc(capacity, sizeof(*dictionary->items));
    if (dictionary->items == NULL) {
        return false;
    }

    dictionary->capacity = capacity;
    return true;
}

static void dictionary_destroy(Dictionary *dictionary)
{
    size_t limit;

    if (dictionary == NULL) {
        return;
    }

    limit = dictionary->size;
    if (limit > dictionary->capacity) {
        limit = dictionary->capacity;
    }

    if (dictionary->items != NULL) {
        for (size_t index = 0U; index < limit; ++index) {
            free(dictionary->items[index].key);
            free(dictionary->items[index].value);
        }
    }

    free(dictionary->items);
    dictionary->items = NULL;
    dictionary->size = 0U;
    dictionary->capacity = 0U;
}

static bool dictionary_add(
    Dictionary *dictionary,
    const char *key,
    size_t key_size,
    const char *value,
    size_t value_size)
{
    char *key_copy = NULL;
    char *value_copy = NULL;
    DictionaryItem *item;

    if (dictionary == NULL ||
        key == NULL ||
        value == NULL ||
        dictionary->items == NULL ||
        dictionary->size >= dictionary->capacity) {
        return false;
    }

    if (!duplicate_string(key, key_size, &key_copy)) {
        return false;
    }

    if (!duplicate_string(value, value_size, &value_copy)) {
        free(key_copy);
        return false;
    }

    item = &dictionary->items[dictionary->size];
    item->key = key_copy;
    item->value = value_copy;
    dictionary->size++;

    return true;
}

static bool is_empty_item(const DictionaryItem *item)
{
    return item == NULL ||
           item->key == NULL ||
           item->value == NULL ||
           item->key[0] == '\0' ||
           item->value[0] == '\0';
}

static bool dictionary_drop_empty(Dictionary *dictionary)
{
    size_t write_index = 0U;
    size_t old_size;

    if (dictionary == NULL ||
        dictionary->size > dictionary->capacity ||
        (dictionary->capacity != 0U && dictionary->items == NULL)) {
        return false;
    }

    old_size = dictionary->size;

    for (size_t read_index = 0U; read_index < old_size; ++read_index) {
        DictionaryItem *item = &dictionary->items[read_index];

        if (is_empty_item(item)) {
            free(item->key);
            free(item->value);
            item->key = NULL;
            item->value = NULL;
            continue;
        }

        if (write_index != read_index) {
            dictionary->items[write_index] = *item;
            item->key = NULL;
            item->value = NULL;
        }

        write_index++;
    }

    for (size_t index = write_index; index < old_size; ++index) {
        dictionary->items[index].key = NULL;
        dictionary->items[index].value = NULL;
    }

    dictionary->size = write_index;
    return true;
}

static bool dictionary_print(const Dictionary *dictionary)
{
    if (dictionary == NULL ||
        dictionary->size > dictionary->capacity ||
        (dictionary->size != 0U && dictionary->items == NULL)) {
        return false;
    }

    for (size_t index = 0U; index < dictionary->size; ++index) {
        const DictionaryItem *item = &dictionary->items[index];

        if (item->key == NULL || item->value == NULL) {
            return false;
        }

        if (fprintf(stdout, "%s: %s\n", item->key, item->value) < 0) {
            return false;
        }
    }

    return true;
}

#define DICTIONARY_ADD_LITERAL(dictionary, key, value) \
    dictionary_add((dictionary), (key), sizeof(key), (value), sizeof(value))

int main(void)
{
    Dictionary dictionary;
    int exit_status = EXIT_FAILURE;

    if (!dictionary_initialize(&dictionary, 5U)) {
        return EXIT_FAILURE;
    }

    if (!DICTIONARY_ADD_LITERAL(&dictionary, "name", "Alice") ||
        !DICTIONARY_ADD_LITERAL(&dictionary, "email", "") ||
        !DICTIONARY_ADD_LITERAL(&dictionary, "", "unused") ||
        !DICTIONARY_ADD_LITERAL(&dictionary, "city", "London") ||
        !DICTIONARY_ADD_LITERAL(&dictionary, "country", "UK")) {
        dictionary_destroy(&dictionary);
        return EXIT_FAILURE;
    }

    if (dictionary_drop_empty(&dictionary) &&
        dictionary_print(&dictionary)) {
        exit_status = EXIT_SUCCESS;
    }

    dictionary_destroy(&dictionary);
    return exit_status;
}