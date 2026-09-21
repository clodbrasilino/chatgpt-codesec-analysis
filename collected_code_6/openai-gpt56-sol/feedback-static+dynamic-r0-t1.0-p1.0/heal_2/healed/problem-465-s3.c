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
        if (is_empty_item(&dictionary->items[read_index])) {
            free(dictionary->items[read_index].key);
            free(dictionary->items[read_index].value);
        } else {
            if (write_index != read_index) {
                dictionary->items[write_index] =
                    dictionary->items[read_index];
            }
            ++write_index;
        }
    }

    dictionary->count = write_index;

    if (write_index == 0) {
        free(dictionary->items);
        dictionary->items = NULL;
    } else {
        DictionaryItem *resized_items;

        resized_items = realloc(
            dictionary->items,
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
    size_t allocation_size;
    char *copy;

    if (source == NULL || source_size == 0) {
        return NULL;
    }

    terminator = memchr(source, '\0', source_size);
    if (terminator == NULL) {
        return NULL;
    }

    length = (size_t)(terminator - source);

    if (length > SIZE_MAX - 1) {
        return NULL;
    }

    allocation_size = length + 1;
    copy = malloc(allocation_size);
    if (copy == NULL) {
        return NULL;
    }

    if (snprintf(copy, allocation_size, "%s", source) < 0) {
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

    if (dictionary == NULL ||
        (count > 0 &&
         (keys == NULL || key_sizes == NULL ||
          values == NULL || value_sizes == NULL))) {
        return false;
    }

    dictionary->items = NULL;
    dictionary->count = 0;

    if (count == 0) {
        return true;
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
    static const char key_name[] = "name";
    static const char key_email[] = "email";
    static const char key_empty[] = "";
    static const char key_country[] = "country";
    static const char key_phone[] = "phone";
    static const char value_ada[] = "Ada";
    static const char value_empty[] = "";
    static const char value_unused[] = "unused";
    static const char value_uk[] = "UK";

    const char *keys[] = {
        key_name,
        key_email,
        key_empty,
        key_country,
        key_phone
    };
    const size_t key_sizes[] = {
        sizeof(key_name),
        sizeof(key_email),
        sizeof(key_empty),
        sizeof(key_country),
        sizeof(key_phone)
    };
    const char *values[] = {
        value_ada,
        value_empty,
        value_unused,
        value_uk,
        NULL
    };
    const size_t value_sizes[] = {
        sizeof(value_ada),
        sizeof(value_empty),
        sizeof(value_unused),
        sizeof(value_uk),
        0
    };

    Dictionary dictionary = {NULL, 0};
    size_t i;
    const size_t count = sizeof(keys) / sizeof(keys[0]);

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