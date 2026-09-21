#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *key;
    char *value;
    size_t key_length;
    size_t value_length;
} DictionaryItem;

typedef struct {
    DictionaryItem *items;
    size_t count;
    size_t capacity;
} Dictionary;

static void dictionary_init(Dictionary *dictionary)
{
    if (dictionary == NULL) {
        return;
    }

    dictionary->items = NULL;
    dictionary->count = 0;
    dictionary->capacity = 0;
}

static void dictionary_destroy(Dictionary *dictionary)
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
    dictionary_init(dictionary);
}

static int copy_string(const char *source, size_t length, char **destination)
{
    char *copy;
    size_t i;

    if (source == NULL || destination == NULL || length == SIZE_MAX) {
        return 0;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return 0;
    }

    for (i = 0; i < length; ++i) {
        copy[i] = source[i];
    }

    copy[length] = '\0';
    *destination = copy;
    return 1;
}

static int bytes_equal(const char *left, const char *right, size_t length)
{
    size_t i;

    if (left == NULL || right == NULL) {
        return 0;
    }

    for (i = 0; i < length; ++i) {
        if (left[i] != right[i]) {
            return 0;
        }
    }

    return 1;
}

static int dictionary_reserve(Dictionary *dictionary, size_t required_capacity)
{
    DictionaryItem *new_items;
    size_t new_capacity;

    if (dictionary == NULL) {
        return 0;
    }

    if (required_capacity <= dictionary->capacity) {
        return 1;
    }

    new_capacity = dictionary->capacity == 0 ? 8 : dictionary->capacity;

    while (new_capacity < required_capacity) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required_capacity;
            break;
        }

        new_capacity *= 2;
    }

    if (new_capacity > SIZE_MAX / sizeof(*new_items)) {
        return 0;
    }

    new_items = realloc(dictionary->items,
                        new_capacity * sizeof(*new_items));
    if (new_items == NULL) {
        return 0;
    }

    dictionary->items = new_items;
    dictionary->capacity = new_capacity;
    return 1;
}

static int dictionary_set(Dictionary *dictionary,
                          const char *key,
                          size_t key_length,
                          const char *value,
                          size_t value_length)
{
    size_t i;
    char *new_key = NULL;
    char *new_value = NULL;

    if (dictionary == NULL || key == NULL || value == NULL ||
        key_length == 0) {
        return 0;
    }

    for (i = 0; i < dictionary->count; ++i) {
        DictionaryItem *item = &dictionary->items[i];

        if (item->key_length == key_length &&
            bytes_equal(item->key, key, key_length)) {
            if (!copy_string(value, value_length, &new_value)) {
                return 0;
            }

            free(item->value);
            item->value = new_value;
            item->value_length = value_length;
            return 1;
        }
    }

    if (dictionary->count == SIZE_MAX) {
        return 0;
    }

    if (!dictionary_reserve(dictionary, dictionary->count + 1)) {
        return 0;
    }

    if (!copy_string(key, key_length, &new_key)) {
        return 0;
    }

    if (!copy_string(value, value_length, &new_value)) {
        free(new_key);
        return 0;
    }

    dictionary->items[dictionary->count].key = new_key;
    dictionary->items[dictionary->count].value = new_value;
    dictionary->items[dictionary->count].key_length = key_length;
    dictionary->items[dictionary->count].value_length = value_length;
    ++dictionary->count;

    return 1;
}

static size_t dictionary_drop_empty(Dictionary *dictionary)
{
    size_t read_index;
    size_t write_index = 0;
    size_t original_count;

    if (dictionary == NULL) {
        return 0;
    }

    original_count = dictionary->count;

    for (read_index = 0; read_index < original_count; ++read_index) {
        DictionaryItem *item = &dictionary->items[read_index];
        int is_empty = item->key == NULL ||
                       item->value == NULL ||
                       item->key_length == 0 ||
                       item->value_length == 0 ||
                       item->key[0] == '\0' ||
                       item->value[0] == '\0';

        if (is_empty) {
            free(item->key);
            free(item->value);
            item->key = NULL;
            item->value = NULL;
            item->key_length = 0;
            item->value_length = 0;
            continue;
        }

        if (write_index != read_index) {
            dictionary->items[write_index] = *item;
            item->key = NULL;
            item->value = NULL;
            item->key_length = 0;
            item->value_length = 0;
        }

        ++write_index;
    }

    dictionary->count = write_index;
    return original_count - write_index;
}

static int write_dictionary_item(const DictionaryItem *item)
{
    if (item == NULL || item->key == NULL || item->value == NULL) {
        return 0;
    }

    if (fwrite(item->key, 1, item->key_length, stdout) != item->key_length) {
        return 0;
    }

    if (fputc('=', stdout) == EOF) {
        return 0;
    }

    if (fwrite(item->value, 1, item->value_length, stdout) !=
        item->value_length) {
        return 0;
    }

    if (fputc('\n', stdout) == EOF) {
        return 0;
    }

    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    Dictionary dictionary;
    int argument_index;
    size_t item_index;

    dictionary_init(&dictionary);

    for (argument_index = 1; argument_index < argc; ++argument_index) {
        const char *argument = argv[argument_index];
        size_t argument_length = 0;
        size_t separator_index = SIZE_MAX;
        size_t key_length;
        size_t value_length;

        if (argument == NULL) {
            fprintf(stderr, "Invalid null dictionary item\n");
            dictionary_destroy(&dictionary);
            return EXIT_FAILURE;
        }

        while (argument[argument_length] != '\0') {
            if (argument[argument_length] == '=' &&
                separator_index == SIZE_MAX) {
                separator_index = argument_length;
            }

            if (argument_length == SIZE_MAX - 1) {
                fprintf(stderr, "Dictionary item is too long\n");
                dictionary_destroy(&dictionary);
                return EXIT_FAILURE;
            }

            ++argument_length;
        }

        if (separator_index == SIZE_MAX || separator_index == 0) {
            fprintf(stderr, "Invalid dictionary item: %s\n", argument);
            dictionary_destroy(&dictionary);
            return EXIT_FAILURE;
        }

        key_length = separator_index;
        value_length = argument_length - separator_index - 1;

        if (!dictionary_set(&dictionary,
                            argument,
                            key_length,
                            argument + separator_index + 1,
                            value_length)) {
            fprintf(stderr, "Unable to add dictionary item\n");
            dictionary_destroy(&dictionary);
            return EXIT_FAILURE;
        }
    }

    dictionary_drop_empty(&dictionary);

    for (item_index = 0; item_index < dictionary.count; ++item_index) {
        if (!write_dictionary_item(&dictionary.items[item_index])) {
            fprintf(stderr, "Unable to write output\n");
            dictionary_destroy(&dictionary);
            return EXIT_FAILURE;
        }
    }

    if (fflush(stdout) == EOF) {
        fprintf(stderr, "Unable to flush output\n");
        dictionary_destroy(&dictionary);
        return EXIT_FAILURE;
    }

    dictionary_destroy(&dictionary);
    return EXIT_SUCCESS;
}