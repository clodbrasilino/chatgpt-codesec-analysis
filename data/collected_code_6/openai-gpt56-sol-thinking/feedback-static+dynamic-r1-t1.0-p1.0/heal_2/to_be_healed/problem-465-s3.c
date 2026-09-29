#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    size_t key_length;
    char *value;
    size_t value_length;
} DictionaryItem;

typedef struct {
    DictionaryItem *items;
    size_t count;
    size_t capacity;
} Dictionary;

static char *duplicate_string(const char *source, size_t length)
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

static bool dictionary_is_valid(const Dictionary *dictionary)
{
    if (dictionary == NULL || dictionary->count > dictionary->capacity) {
        return false;
    }

    if ((dictionary->capacity == 0U) != (dictionary->items == NULL)) {
        return false;
    }

    return true;
}

static bool dictionary_reserve(Dictionary *dictionary,
                               size_t required_capacity)
{
    size_t maximum_capacity;
    size_t new_capacity;
    DictionaryItem *new_items;

    if (!dictionary_is_valid(dictionary)) {
        return false;
    }

    maximum_capacity = SIZE_MAX / sizeof(*dictionary->items);

    if (dictionary->capacity > maximum_capacity ||
        required_capacity > maximum_capacity) {
        return false;
    }

    if (required_capacity <= dictionary->capacity) {
        return true;
    }

    if (dictionary->capacity == 0U) {
        new_capacity = maximum_capacity >= 4U ? 4U : required_capacity;
    } else {
        new_capacity = dictionary->capacity;
    }

    while (new_capacity < required_capacity) {
        if (new_capacity > maximum_capacity / 2U) {
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
                           size_t key_length,
                           const char *value,
                           size_t value_length)
{
    size_t index;
    char *key_copy;
    char *value_copy;

    if (!dictionary_is_valid(dictionary) ||
        key == NULL ||
        key_length == 0U ||
        key_length == SIZE_MAX) {
        return false;
    }

    if (memchr(key, '\0', key_length) != NULL) {
        return false;
    }

    if (value == NULL) {
        if (value_length != 0U) {
            return false;
        }
    } else {
        if (value_length == SIZE_MAX ||
            memchr(value, '\0', value_length) != NULL) {
            return false;
        }
    }

    for (index = 0U; index < dictionary->count; ++index) {
        DictionaryItem *item = &dictionary->items[index];

        if (item->key_length == key_length &&
            memcmp(item->key, key, key_length) == 0) {
            value_copy = value == NULL
                             ? NULL
                             : duplicate_string(value, value_length);

            if (value != NULL && value_copy == NULL) {
                return false;
            }

            free(item->value);
            item->value = value_copy;
            item->value_length = value == NULL ? 0U : value_length;
            return true;
        }
    }

    key_copy = duplicate_string(key, key_length);
    if (key_copy == NULL) {
        return false;
    }

    value_copy = value == NULL
                     ? NULL
                     : duplicate_string(value, value_length);

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
    dictionary->items[dictionary->count].key_length = key_length;
    dictionary->items[dictionary->count].value = value_copy;
    dictionary->items[dictionary->count].value_length =
        value == NULL ? 0U : value_length;

    ++dictionary->count;
    return true;
}

size_t dictionary_drop_empty_items(Dictionary *dictionary)
{
    size_t read_index;
    size_t write_index;
    size_t original_count;

    if (!dictionary_is_valid(dictionary)) {
        return 0U;
    }

    original_count = dictionary->count;
    write_index = 0U;

    for (read_index = 0U; read_index < original_count; ++read_index) {
        DictionaryItem *item = &dictionary->items[read_index];

        if (item->key == NULL ||
            item->key_length == 0U ||
            item->value == NULL ||
            item->value_length == 0U) {
            free(item->key);
            free(item->value);
            item->key = NULL;
            item->key_length = 0U;
            item->value = NULL;
            item->value_length = 0U;
            continue;
        }

        if (write_index != read_index) {
            dictionary->items[write_index] = *item;
            item->key = NULL;
            item->key_length = 0U;
            item->value = NULL;
            item->value_length = 0U;
        }

        ++write_index;
    }

    dictionary->count = write_index;
    return original_count - write_index;
}

static void dictionary_destroy(Dictionary *dictionary)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'index' can be reduced. [variableScope]
     */
    size_t index;

    if (dictionary == NULL) {
        return;
    }

    if (dictionary->items != NULL) {
        for (index = 0U; index < dictionary->count; ++index) {
            free(dictionary->items[index].key);
            free(dictionary->items[index].value);
        }
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

    if (!dictionary_set(&dictionary,
                        "name", sizeof("name") - 1U,
                        "Alice", sizeof("Alice") - 1U) ||
        !dictionary_set(&dictionary,
                        "email", sizeof("email") - 1U,
                        "", sizeof("") - 1U) ||
        !dictionary_set(&dictionary,
                        "phone", sizeof("phone") - 1U,
                        NULL, 0U) ||
        !dictionary_set(&dictionary,
                        "city", sizeof("city") - 1U,
                        "Lisbon", sizeof("Lisbon") - 1U)) {
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