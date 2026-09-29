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
    size_t count;
} Dictionary;

static void free_dictionary(Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL) {
        return;
    }

    for (i = 0; i < dictionary->count; ++i) {
        free(dictionary->items[i].key);
        free(dictionary->items[i].value);
    }

    free(dictionary->items);
    dictionary->items = NULL;
    dictionary->count = 0;
}

static bool is_empty_item(const DictionaryItem *item)
{
    return item == NULL ||
           item->key == NULL ||
           item->key[0] == '\0' ||
           item->value == NULL ||
           item->value[0] == '\0';
}

static void drop_empty_items(Dictionary *dictionary)
{
    size_t read_index;
    size_t write_index = 0;

    if (dictionary == NULL || dictionary->items == NULL) {
        return;
    }

    for (read_index = 0; read_index < dictionary->count; ++read_index) {
        DictionaryItem *item = &dictionary->items[read_index];

        if (is_empty_item(item)) {
            free(item->key);
            free(item->value);
            item->key = NULL;
            item->value = NULL;
        } else {
            if (write_index != read_index) {
                dictionary->items[write_index] = *item;
                item->key = NULL;
                item->value = NULL;
            }
            ++write_index;
        }
    }

    dictionary->count = write_index;

    if (write_index == 0) {
        free(dictionary->items);
        dictionary->items = NULL;
        return;
    }

    {
        DictionaryItem *resized_items =
            realloc(dictionary->items,
                    write_index * sizeof(*dictionary->items));

        if (resized_items != NULL) {
            dictionary->items = resized_items;
        }
    }
}

static char *copy_string(const char *source, size_t source_size)
{
    const char *terminator;
    size_t length;
    char *copy;

    if (source == NULL || source_size == 0) {
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

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    if (snprintf(copy, length + 1, "%.*s", (int)(length > INT32_MAX ? INT32_MAX : length), source) < 0 ||
        length > INT32_MAX) {
        free(copy);
        return NULL;
    }

    return copy;
}

static bool initialize_dictionary(
    Dictionary *dictionary,
    const char *const keys[],
    const size_t key_sizes[],
    const char *const values[],
    const size_t value_sizes[],
    size_t count)
{
    size_t i;

    if (dictionary == NULL) {
        return false;
    }

    dictionary->items = NULL;
    dictionary->count = 0;

    if (count == 0) {
        return true;
    }

    if (keys == NULL ||
        key_sizes == NULL ||
        values == NULL ||
        value_sizes == NULL) {
        return false;
    }

    if (count > SIZE_MAX / sizeof(*dictionary->items)) {
        return false;
    }

    dictionary->items = calloc(count, sizeof(*dictionary->items));
    if (dictionary->items == NULL) {
        return false;
    }

    dictionary->count = count;

    for (i = 0; i < count; ++i) {
        if (keys[i] != NULL) {
            dictionary->items[i].key =
                copy_string(keys[i], key_sizes[i]);

            if (dictionary->items[i].key == NULL) {
                free_dictionary(dictionary);
                return false;
            }
        }

        if (values[i] != NULL) {
            dictionary->items[i].value =
                copy_string(values[i], value_sizes[i]);

            if (dictionary->items[i].value == NULL) {
                free_dictionary(dictionary);
                return false;
            }
        }
    }

    return true;
}

int main(void)
{
    const char *keys[] = {
        "name",
        "email",
        "",
        "country",
        "phone"
    };
    const size_t key_sizes[] = {
        sizeof("name"),
        sizeof("email"),
        sizeof(""),
        sizeof("country"),
        sizeof("phone")
    };
    const char *values[] = {
        "Ada",
        "",
        "unused",
        "UK",
        NULL
    };
    const size_t value_sizes[] = {
        sizeof("Ada"),
        sizeof(""),
        sizeof("unused"),
        sizeof("UK"),
        0
    };
    Dictionary dictionary = {NULL, 0};
    const size_t count = sizeof(keys) / sizeof(keys[0]);
    size_t i;

    if (count != sizeof(key_sizes) / sizeof(key_sizes[0]) ||
        count != sizeof(values) / sizeof(values[0]) ||
        count != sizeof(value_sizes) / sizeof(value_sizes[0])) {
        fputs("Invalid dictionary input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!initialize_dictionary(
            &dictionary,
            keys,
            key_sizes,
            values,
            value_sizes,
            count)) {
        fputs("Failed to initialize dictionary.\n", stderr);
        return EXIT_FAILURE;
    }

    drop_empty_items(&dictionary);

    for (i = 0; i < dictionary.count; ++i) {
        if (printf("%s: %s\n",
                   dictionary.items[i].key,
                   dictionary.items[i].value) < 0) {
            free_dictionary(&dictionary);
            return EXIT_FAILURE;
        }
    }

    free_dictionary(&dictionary);
    return EXIT_SUCCESS;
}