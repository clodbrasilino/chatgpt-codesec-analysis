#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *key;
    size_t key_length;
} DictionaryEntry;

typedef struct {
    const DictionaryEntry *entries;
    size_t count;
} Dictionary;

typedef struct {
    char **items;
    size_t count;
} KeyList;

static void key_list_destroy(KeyList *list)
{
    size_t index;

    if (list == NULL) {
        return;
    }

    for (index = 0; index < list->count; ++index) {
        free(list->items[index]);
    }

    free(list->items);
    list->items = NULL;
    list->count = 0;
}

static int dictionary_get_keys(const Dictionary *dictionary, KeyList *keys)
{
    KeyList result = {NULL, 0};
    size_t index;

    if (dictionary == NULL || keys == NULL) {
        return 0;
    }

    keys->items = NULL;
    keys->count = 0;

    if (dictionary->count == 0) {
        return 1;
    }

    if (dictionary->entries == NULL ||
        dictionary->count > SIZE_MAX / sizeof(*result.items)) {
        return 0;
    }

    result.items = calloc(dictionary->count, sizeof(*result.items));
    if (result.items == NULL) {
        return 0;
    }

    for (index = 0; index < dictionary->count; ++index) {
        const char *key = dictionary->entries[index].key;
        size_t length = dictionary->entries[index].key_length;
        size_t offset;

        if (key == NULL || length == SIZE_MAX) {
            key_list_destroy(&result);
            return 0;
        }

        result.items[index] = malloc(length + 1);
        if (result.items[index] == NULL) {
            key_list_destroy(&result);
            return 0;
        }

        for (offset = 0; offset < length; ++offset) {
            result.items[index][offset] = key[offset];
        }

        result.items[index][length] = '\0';
        ++result.count;
    }

    *keys = result;
    return 1;
}

int main(void)
{
    static const DictionaryEntry entries[] = {
        {"name", sizeof("name") - 1},
        {"language", sizeof("language") - 1},
        {"level", sizeof("level") - 1}
    };
    const Dictionary dictionary = {
        entries,
        sizeof(entries) / sizeof(entries[0])
    };
    KeyList keys = {NULL, 0};
    size_t index;

    if (!dictionary_get_keys(&dictionary, &keys)) {
        fputs("Failed to get dictionary keys\n", stderr);
        return EXIT_FAILURE;
    }

    for (index = 0; index < keys.count; ++index) {
        if (printf("%s\n", keys.items[index]) < 0) {
            key_list_destroy(&keys);
            return EXIT_FAILURE;
        }
    }

    key_list_destroy(&keys);
    return EXIT_SUCCESS;
}