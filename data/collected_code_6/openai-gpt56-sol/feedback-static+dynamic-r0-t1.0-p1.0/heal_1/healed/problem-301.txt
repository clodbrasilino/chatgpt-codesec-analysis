#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    VALUE_INTEGER,
    VALUE_DICTIONARY
} ValueType;

typedef struct Dictionary Dictionary;

typedef struct {
    char *key;
    ValueType type;
    union {
        int integer;
        Dictionary *dictionary;
    } value;
} Entry;

struct Dictionary {
    Entry *entries;
    size_t count;
    size_t capacity;
};

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

    memcpy(copy, source, length);
    copy[length] = '\0';

    return copy;
}

static Dictionary *dictionary_create(void)
{
    return calloc(1U, sizeof(Dictionary));
}

static int dictionary_reserve(Dictionary *dictionary)
{
    size_t new_capacity;
    Entry *new_entries;

    if (dictionary == NULL) {
        return 0;
    }

    if (dictionary->count < dictionary->capacity) {
        return 1;
    }

    if (dictionary->capacity == 0U) {
        new_capacity = 4U;
    } else {
        if (dictionary->capacity > SIZE_MAX / 2U) {
            return 0;
        }

        new_capacity = dictionary->capacity * 2U;
    }

    if (new_capacity > SIZE_MAX / sizeof(*new_entries)) {
        return 0;
    }

    new_entries = realloc(dictionary->entries,
                          new_capacity * sizeof(*new_entries));
    if (new_entries == NULL) {
        return 0;
    }

    dictionary->entries = new_entries;
    dictionary->capacity = new_capacity;

    return 1;
}

static int dictionary_add_integer(Dictionary *dictionary,
                                  const char *key,
                                  int value)
{
    Entry *entry;
    char *key_copy;

    if (dictionary == NULL || key == NULL) {
        return 0;
    }

    key_copy = duplicate_string(key);
    if (key_copy == NULL) {
        return 0;
    }

    if (!dictionary_reserve(dictionary)) {
        free(key_copy);
        return 0;
    }

    entry = &dictionary->entries[dictionary->count];
    entry->key = key_copy;
    entry->type = VALUE_INTEGER;
    entry->value.integer = value;
    dictionary->count++;

    return 1;
}

static int dictionary_contains(const Dictionary *dictionary,
                               const Dictionary *target)
{
    size_t index;

    if (dictionary == NULL || target == NULL) {
        return 0;
    }

    if (dictionary == target) {
        return 1;
    }

    for (index = 0U; index < dictionary->count; index++) {
        const Entry *entry = &dictionary->entries[index];

        if (entry->type == VALUE_DICTIONARY &&
            entry->value.dictionary != NULL &&
            dictionary_contains(entry->value.dictionary, target)) {
            return 1;
        }
    }

    return 0;
}

static int dictionary_add_dictionary(Dictionary *dictionary,
                                     const char *key,
                                     Dictionary *child)
{
    Entry *entry;
    char *key_copy;

    if (dictionary == NULL || key == NULL || child == NULL) {
        return 0;
    }

    if (dictionary_contains(child, dictionary)) {
        return 0;
    }

    key_copy = duplicate_string(key);
    if (key_copy == NULL) {
        return 0;
    }

    if (!dictionary_reserve(dictionary)) {
        free(key_copy);
        return 0;
    }

    entry = &dictionary->entries[dictionary->count];
    entry->key = key_copy;
    entry->type = VALUE_DICTIONARY;
    entry->value.dictionary = child;
    dictionary->count++;

    return 1;
}

static size_t dictionary_depth(const Dictionary *dictionary)
{
    size_t maximum_child_depth = 0U;
    size_t index;

    if (dictionary == NULL) {
        return 0U;
    }

    for (index = 0U; index < dictionary->count; index++) {
        const Entry *entry = &dictionary->entries[index];

        if (entry->type == VALUE_DICTIONARY &&
            entry->value.dictionary != NULL) {
            size_t child_depth =
                dictionary_depth(entry->value.dictionary);

            if (child_depth == SIZE_MAX) {
                return SIZE_MAX;
            }

            if (child_depth > maximum_child_depth) {
                maximum_child_depth = child_depth;
            }
        }
    }

    if (maximum_child_depth == SIZE_MAX) {
        return SIZE_MAX;
    }

    return maximum_child_depth + 1U;
}

static void dictionary_destroy(Dictionary *dictionary)
{
    size_t index;

    if (dictionary == NULL) {
        return;
    }

    for (index = 0U; index < dictionary->count; index++) {
        Entry *entry = &dictionary->entries[index];

        free(entry->key);

        if (entry->type == VALUE_DICTIONARY) {
            dictionary_destroy(entry->value.dictionary);
        }
    }

    free(dictionary->entries);
    free(dictionary);
}

int main(void)
{
    Dictionary *root = dictionary_create();
    Dictionary *level_two = dictionary_create();
    Dictionary *level_three = dictionary_create();

    if (root == NULL || level_two == NULL || level_three == NULL) {
        dictionary_destroy(root);
        dictionary_destroy(level_two);
        dictionary_destroy(level_three);
        return EXIT_FAILURE;
    }

    if (!dictionary_add_integer(level_three, "value", 42)) {
        dictionary_destroy(root);
        dictionary_destroy(level_two);
        dictionary_destroy(level_three);
        return EXIT_FAILURE;
    }

    if (!dictionary_add_dictionary(level_two, "level_three", level_three)) {
        dictionary_destroy(root);
        dictionary_destroy(level_two);
        dictionary_destroy(level_three);
        return EXIT_FAILURE;
    }

    level_three = NULL;

    if (!dictionary_add_dictionary(root, "level_two", level_two)) {
        dictionary_destroy(root);
        dictionary_destroy(level_two);
        return EXIT_FAILURE;
    }

    level_two = NULL;

    if (!dictionary_add_integer(root, "number", 7)) {
        dictionary_destroy(root);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", dictionary_depth(root)) < 0) {
        dictionary_destroy(root);
        return EXIT_FAILURE;
    }

    dictionary_destroy(root);

    return EXIT_SUCCESS;
}