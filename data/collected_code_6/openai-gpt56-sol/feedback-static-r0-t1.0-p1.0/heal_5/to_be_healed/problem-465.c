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

static char *duplicate_string(const char *source, size_t source_size)
{
    const char *terminator;
    size_t length;
    size_t allocation_size;
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

    allocation_size = length + 1U;
    copy = malloc(allocation_size);
    if (copy == NULL) {
        return NULL;
    }

    if (length > 0U) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
    }
    copy[length] = '\0';

    return copy;
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
    if (dictionary == NULL) {
        return;
    }

    if (dictionary->items != NULL) {
        for (size_t index = 0U; index < dictionary->size; ++index) {
            free(dictionary->items[index].key);
            free(dictionary->items[index].value);
        }
    }

    free(dictionary->items);
    dictionary->items = NULL;
    dictionary->size = 0U;
    dictionary->capacity = 0U;
}

static bool dictionary_add(Dictionary *dictionary,
                           const char *key,
                           size_t key_size,
                           const char *value,
                           size_t value_size)
{
    char *key_copy;
    char *value_copy;

    if (dictionary == NULL ||
        key == NULL ||
        value == NULL ||
        key_size == 0U ||
        value_size == 0U ||
        dictionary->items == NULL ||
        dictionary->size >= dictionary->capacity) {
        return false;
    }

    key_copy = duplicate_string(key, key_size);
    if (key_copy == NULL) {
        return false;
    }

    value_copy = duplicate_string(value, value_size);
    if (value_copy == NULL) {
        free(key_copy);
        return false;
    }

    dictionary->items[dictionary->size].key = key_copy;
    dictionary->items[dictionary->size].value = value_copy;
    ++dictionary->size;

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

static void dictionary_drop_empty(Dictionary *dictionary)
{
    size_t write_index = 0U;
    size_t old_size;

    if (dictionary == NULL ||
        dictionary->items == NULL ||
        dictionary->size > dictionary->capacity) {
        return;
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

        ++write_index;
    }

    for (size_t index = write_index; index < old_size; ++index) {
        dictionary->items[index].key = NULL;
        dictionary->items[index].value = NULL;
    }

    dictionary->size = write_index;
}

static bool dictionary_print(const Dictionary *dictionary)
{
    if (dictionary == NULL ||
        dictionary->size > dictionary->capacity ||
        (dictionary->capacity > 0U && dictionary->items == NULL)) {
        return false;
    }

    for (size_t index = 0U; index < dictionary->size; ++index) {
        const DictionaryItem *item = &dictionary->items[index];

        if (item->key == NULL || item->value == NULL) {
            return false;
        }

        if (printf("%s: %s\n", item->key, item->value) < 0) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    static const char name_key[] = "name";
    static const char name_value[] = "Alice";
    static const char email_key[] = "email";
    static const char email_value[] = "";
    static const char empty_key[] = "";
    static const char unused_value[] = "unused";
    static const char city_key[] = "city";
    static const char city_value[] = "London";
    static const char country_key[] = "country";
    static const char country_value[] = "UK";

    Dictionary dictionary;
    int exit_status = EXIT_FAILURE;

    if (!dictionary_initialize(&dictionary, 5U)) {
        return EXIT_FAILURE;
    }

    if (!dictionary_add(&dictionary,
                        name_key, sizeof(name_key),
                        name_value, sizeof(name_value)) ||
        !dictionary_add(&dictionary,
                        email_key, sizeof(email_key),
                        email_value, sizeof(email_value)) ||
        !dictionary_add(&dictionary,
                        empty_key, sizeof(empty_key),
                        unused_value, sizeof(unused_value)) ||
        !dictionary_add(&dictionary,
                        city_key, sizeof(city_key),
                        city_value, sizeof(city_value)) ||
        !dictionary_add(&dictionary,
                        country_key, sizeof(country_key),
                        country_value, sizeof(country_value))) {
        dictionary_destroy(&dictionary);
        return EXIT_FAILURE;
    }

    dictionary_drop_empty(&dictionary);

    if (dictionary_print(&dictionary)) {
        exit_status = EXIT_SUCCESS;
    }

    dictionary_destroy(&dictionary);
    return exit_status;
}