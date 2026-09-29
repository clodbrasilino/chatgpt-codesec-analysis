#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Dictionary Dictionary;

typedef enum {
    VALUE_STRING,
    VALUE_DICTIONARY
} ValueType;

typedef struct {
    ValueType type;
    union {
        char *string;
        Dictionary *dictionary;
    } data;
} Value;

typedef struct {
    char *key;
    Value value;
} Entry;

struct Dictionary {
    Entry *entries;
    size_t count;
};

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
        memcpy(copy, source, length);
    }

    copy[length] = '\0';
    return copy;
}

static Dictionary *dictionary_create(size_t count)
{
    Dictionary *dictionary;

    if (count > SIZE_MAX / sizeof(Entry)) {
        return NULL;
    }

    dictionary = calloc(1U, sizeof(*dictionary));
    if (dictionary == NULL) {
        return NULL;
    }

    if (count != 0U) {
        dictionary->entries = calloc(count, sizeof(Entry));
        if (dictionary->entries == NULL) {
            free(dictionary);
            return NULL;
        }
    }

    dictionary->count = count;
    return dictionary;
}

static int dictionary_set_string(Dictionary *dictionary,
                                 size_t index,
                                 const char *key,
                                 size_t key_size,
                                 const char *value,
                                 size_t value_size)
{
    char *key_copy;
    char *value_copy;
    Entry *entry;

    if (dictionary == NULL ||
        key == NULL ||
        value == NULL ||
        index >= dictionary->count ||
        dictionary->entries == NULL) {
        return -1;
    }

    entry = &dictionary->entries[index];
    if (entry->key != NULL) {
        return -1;
    }

    key_copy = duplicate_string(key, key_size);
    if (key_copy == NULL) {
        return -1;
    }

    value_copy = duplicate_string(value, value_size);
    if (value_copy == NULL) {
        free(key_copy);
        return -1;
    }

    entry->key = key_copy;
    entry->value.type = VALUE_STRING;
    entry->value.data.string = value_copy;

    return 0;
}

static int dictionary_set_dictionary(Dictionary *dictionary,
                                     size_t index,
                                     const char *key,
                                     size_t key_size,
                                     Dictionary *child)
{
    char *key_copy;
    Entry *entry;

    if (dictionary == NULL ||
        key == NULL ||
        child == NULL ||
        child == dictionary ||
        index >= dictionary->count ||
        dictionary->entries == NULL) {
        return -1;
    }

    entry = &dictionary->entries[index];
    if (entry->key != NULL) {
        return -1;
    }

    key_copy = duplicate_string(key, key_size);
    if (key_copy == NULL) {
        return -1;
    }

    entry->key = key_copy;
    entry->value.type = VALUE_DICTIONARY;
    entry->value.data.dictionary = child;

    return 0;
}

static size_t dictionary_depth(const Dictionary *dictionary)
{
    size_t maximum_child_depth = 0U;
    size_t index;

    if (dictionary == NULL) {
        return 0U;
    }

    for (index = 0U; index < dictionary->count; ++index) {
        const Entry *entry = &dictionary->entries[index];

        if (entry->key != NULL &&
            entry->value.type == VALUE_DICTIONARY &&
            entry->value.data.dictionary != NULL) {
            size_t child_depth =
                dictionary_depth(entry->value.data.dictionary);

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

    for (index = 0U; index < dictionary->count; ++index) {
        Entry *entry = &dictionary->entries[index];

        if (entry->key == NULL) {
            continue;
        }

        if (entry->value.type == VALUE_STRING) {
            free(entry->value.data.string);
        } else if (entry->value.type == VALUE_DICTIONARY) {
            dictionary_destroy(entry->value.data.dictionary);
        }

        free(entry->key);
    }

    free(dictionary->entries);
    free(dictionary);
}

int main(void)
{
    Dictionary *root = NULL;
    Dictionary *level_one = NULL;
    Dictionary *level_two = NULL;
    int status = EXIT_FAILURE;

    static const char key_name[] = "name";
    static const char value_leaf[] = "leaf";
    static const char key_nested[] = "nested";
    static const char key_child[] = "child";
    static const char key_title[] = "title";
    static const char value_example[] = "example";

    root = dictionary_create(2U);
    level_one = dictionary_create(1U);
    level_two = dictionary_create(1U);

    if (root == NULL || level_one == NULL || level_two == NULL) {
        goto cleanup;
    }

    if (dictionary_set_string(level_two,
                              0U,
                              key_name,
                              sizeof(key_name),
                              value_leaf,
                              sizeof(value_leaf)) != 0) {
        goto cleanup;
    }

    if (dictionary_set_dictionary(level_one,
                                  0U,
                                  key_nested,
                                  sizeof(key_nested),
                                  level_two) != 0) {
        goto cleanup;
    }
    level_two = NULL;

    if (dictionary_set_dictionary(root,
                                  0U,
                                  key_child,
                                  sizeof(key_child),
                                  level_one) != 0) {
        goto cleanup;
    }
    level_one = NULL;

    if (dictionary_set_string(root,
                              1U,
                              key_title,
                              sizeof(key_title),
                              value_example,
                              sizeof(value_example)) != 0) {
        goto cleanup;
    }

    if (printf("%zu\n", dictionary_depth(root)) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    dictionary_destroy(level_two);
    dictionary_destroy(level_one);
    dictionary_destroy(root);

    return status;
}