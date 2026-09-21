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
} Dictionary;

static char *duplicate_string(const char *source, size_t source_size)
{
    const char *terminator;
    size_t length;
    char *copy;

    if (source == NULL || source_size == 0U) {
        return NULL;
    }

    terminator = memchr(source, '\0', source_size);
    if (terminator == NULL) {
        return NULL;
    }

    length = (size_t)(terminator - source);
    if (length > SIZE_MAX - 1U) {
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

static void free_dictionary(Dictionary *dictionary)
{
    if (dictionary == NULL) {
        return;
    }

    if (dictionary->items != NULL) {
        for (size_t i = 0U; i < dictionary->size; ++i) {
            free(dictionary->items[i].key);
            free(dictionary->items[i].value);
        }

        free(dictionary->items);
    }

    dictionary->items = NULL;
    dictionary->size = 0U;
}

static int drop_empty_items(Dictionary *dictionary)
{
    size_t write_index = 0U;

    if (dictionary == NULL ||
        (dictionary->size != 0U && dictionary->items == NULL)) {
        return -1;
    }

    for (size_t read_index = 0U;
         read_index < dictionary->size;
         ++read_index) {
        DictionaryItem *item = &dictionary->items[read_index];

        if (item->key == NULL || item->key[0] == '\0' ||
            item->value == NULL || item->value[0] == '\0') {
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

    dictionary->size = write_index;

    if (write_index == 0U) {
        free(dictionary->items);
        dictionary->items = NULL;
        return 0;
    }

    if (write_index > SIZE_MAX / sizeof(*dictionary->items)) {
        return -1;
    }

    {
        DictionaryItem *resized_items =
            realloc(dictionary->items,
                    write_index * sizeof(*dictionary->items));

        if (resized_items != NULL) {
            dictionary->items = resized_items;
        }
    }

    return 0;
}

static int initialize_dictionary(Dictionary *dictionary)
{
    static const char keys[][12] = {
        "name", "empty_value", "", "language"
    };
    static const char values[][8] = {
        "Alice", "", "ignored", "C"
    };
    const size_t count = sizeof(keys) / sizeof(keys[0]);

    if (dictionary == NULL ||
        count != sizeof(values) / sizeof(values[0]) ||
        count > SIZE_MAX / sizeof(*dictionary->items)) {
        return -1;
    }

    dictionary->items = NULL;
    dictionary->size = 0U;

    if (count == 0U) {
        return 0;
    }

    dictionary->items = calloc(count, sizeof(*dictionary->items));
    if (dictionary->items == NULL) {
        return -1;
    }

    for (size_t i = 0U; i < count; ++i) {
        dictionary->items[i].key =
            duplicate_string(keys[i], sizeof(keys[i]));
        dictionary->items[i].value =
            duplicate_string(values[i], sizeof(values[i]));
        dictionary->size = i + 1U;

        if (dictionary->items[i].key == NULL ||
            dictionary->items[i].value == NULL) {
            free_dictionary(dictionary);
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    Dictionary dictionary = {NULL, 0U};

    if (initialize_dictionary(&dictionary) != 0) {
        fputs("Failed to initialize dictionary.\n", stderr);
        return EXIT_FAILURE;
    }

    if (drop_empty_items(&dictionary) != 0) {
        fputs("Failed to process dictionary.\n", stderr);
        free_dictionary(&dictionary);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < dictionary.size; ++i) {
        if (printf("%s: %s\n",
                   dictionary.items[i].key,
                   dictionary.items[i].value) < 0) {
            fputs("Failed to write output.\n", stderr);
            free_dictionary(&dictionary);
            return EXIT_FAILURE;
        }
    }

    free_dictionary(&dictionary);
    return EXIT_SUCCESS;
}