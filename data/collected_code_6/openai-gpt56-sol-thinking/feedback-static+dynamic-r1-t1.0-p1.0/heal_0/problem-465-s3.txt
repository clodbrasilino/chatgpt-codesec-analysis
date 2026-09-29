#include <stdbool.h>
#include <stddef.h>
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
    size_t count;
    size_t capacity;
} Dictionary;

static char *duplicate_string(const char *source)
{
    size_t length;
    char *copy;

    if (source == NULL) {
        return NULL;
    }

    length = strlen(source);
    if (length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, source, length + 1U);
    return copy;
}

static bool dictionary_reserve(Dictionary *dictionary, size_t required_capacity)
{
    size_t new_capacity;
    DictionaryItem *new_items;

    if (dictionary == NULL) {
        return false;
    }

    if (required_capacity <= dictionary->capacity) {
        return true;
    }

    if (required_capacity > SIZE_MAX / sizeof(*dictionary->items)) {
        return false;
    }

    new_capacity = dictionary->capacity == 0U ? 4U : dictionary->capacity;

    while (new_capacity < required_capacity) {
        if (new_capacity > SIZE_MAX / 2U) {
            new_capacity = required_capacity;
            break;
        }
        new_capacity *= 2U;
    }

    new_items = realloc(dictionary->items,
                        new_capacity * sizeof(*dictionary->items));
    if (new_items == NULL) {
        return false;
    }

    dictionary->items = new_items;
    dictionary->capacity = new_capacity;
    return true;
}

static bool dictionary_set(Dictionary *dictionary,
                           const char *key,
                           const char *value)
{
    size_t index;
    char *key_copy;
    char *value_copy;

    if (dictionary == NULL || key == NULL || key[0] == '\0') {
        return false;
    }

    for (index = 0U; index < dictionary->count; ++index) {
        if (strcmp(dictionary->items[index].key, key) == 0) {
            value_copy = value == NULL ? NULL : duplicate_string(value);
            if (value != NULL && value_copy == NULL) {
                return false;
            }

            free(dictionary->items[index].value);
            dictionary->items[index].value = value_copy;
            return true;
        }
    }

    key_copy = duplicate_string(key);
    if (key_copy == NULL) {
        return false;
    }

    value_copy = value == NULL ? NULL : duplicate_string(value);
    if (value != NULL && value_copy == NULL) {
        free(key_copy);
        return false;
    }

    if (dictionary->count == SIZE_MAX ||
        !dictionary_reserve(dictionary, dictionary->count + 1U)) {
        free(value_copy);
        free(key_copy);
        return false;
    }

    dictionary->items[dictionary->count].key = key_copy;
    dictionary->items[dictionary->count].value = value_copy;
    ++dictionary->count;

    return true;
}

size_t dictionary_drop_empty_items(Dictionary *dictionary)
{
    size_t read_index;
    size_t write_index;
    size_t original_count;

    if (dictionary == NULL) {
        return 0U;
    }

    original_count = dictionary->count;
    write_index = 0U;

    for (read_index = 0U; read_index < original_count; ++read_index) {
        DictionaryItem *item = &dictionary->items[read_index];

        if (item->key == NULL || item->value == NULL ||
            item->value[0] == '\0') {
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

        ++write_index;
    }

    dictionary->count = write_index;
    return original_count - write_index;
}

static void dictionary_destroy(Dictionary *dictionary)
{
    size_t index;

    if (dictionary == NULL) {
        return;
    }

    for (index = 0U; index < dictionary->count; ++index) {
        free(dictionary->items[index].key);
        free(dictionary->items[index].value);
    }

    free(dictionary->items);
    dictionary->items = NULL;
    dictionary->count = 0U;
    dictionary->capacity = 0U;
}

int main(void)
{
    Dictionary dictionary = { NULL, 0U, 0U };
    size_t index;
    int result = EXIT_SUCCESS;

    if (!dictionary_set(&dictionary, "name", "Alice") ||
        !dictionary_set(&dictionary, "email", "") ||
        !dictionary_set(&dictionary, "phone", NULL) ||
        !dictionary_set(&dictionary, "city", "Lisbon")) {
        dictionary_destroy(&dictionary);
        return EXIT_FAILURE;
    }

    dictionary_drop_empty_items(&dictionary);

    for (index = 0U; index < dictionary.count; ++index) {
        if (printf("%s=%s\n",
                   dictionary.items[index].key,
                   dictionary.items[index].value) < 0) {
            result = EXIT_FAILURE;
            break;
        }
    }

    dictionary_destroy(&dictionary);
    return result;
}