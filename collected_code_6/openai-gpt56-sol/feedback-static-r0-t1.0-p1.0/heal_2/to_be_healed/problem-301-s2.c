#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Dictionary Dictionary;

typedef enum {
    VALUE_INTEGER,
    VALUE_STRING,
    VALUE_DICTIONARY
} ValueType;

typedef struct {
    char *key;
    ValueType type;
    union {
        long integer;
        char *string;
        Dictionary *dictionary;
    } value;
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
    if (length == SIZE_MAX) {
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
        dictionary->entries = calloc(count, sizeof(*dictionary->entries));
        if (dictionary->entries == NULL) {
            free(dictionary);
            return NULL;
        }
    }

    dictionary->count = count;
    return dictionary;
}

static void entry_clear(Entry *entry)
{
    if (entry == NULL) {
        return;
    }

    free(entry->key);

    if (entry->type == VALUE_STRING) {
        free(entry->value.string);
    } else if (entry->type == VALUE_DICTIONARY) {
        Dictionary *child = entry->value.dictionary;
        entry->value.dictionary = NULL;

        if (child != NULL) {
            size_t index;

            for (index = 0U; index < child->count; ++index) {
                entry_clear(&child->entries[index]);
            }

            free(child->entries);
            free(child);
        }
    }

    entry->key = NULL;
    entry->type = VALUE_INTEGER;
    entry->value.integer = 0L;
}

static void dictionary_destroy(Dictionary *dictionary)
{
    size_t index;

    if (dictionary == NULL) {
        return;
    }

    for (index = 0U; index < dictionary->count; ++index) {
        entry_clear(&dictionary->entries[index]);
    }

    free(dictionary->entries);
    free(dictionary);
}

static int dictionary_set_integer(Dictionary *dictionary, size_t index,
                                  const char *key, size_t key_size, long value)
{
    char *key_copy;

    if (dictionary == NULL || index >= dictionary->count || key == NULL) {
        return 0;
    }

    key_copy = duplicate_string(key, key_size);
    if (key_copy == NULL) {
        return 0;
    }

    entry_clear(&dictionary->entries[index]);
    dictionary->entries[index].key = key_copy;
    dictionary->entries[index].type = VALUE_INTEGER;
    dictionary->entries[index].value.integer = value;

    return 1;
}

static int dictionary_set_dictionary(Dictionary *dictionary, size_t index,
                                     const char *key, size_t key_size,
                                     Dictionary *child)
{
    char *key_copy;

    if (dictionary == NULL || index >= dictionary->count ||
        key == NULL || child == NULL || child == dictionary) {
        return 0;
    }

    key_copy = duplicate_string(key, key_size);
    if (key_copy == NULL) {
        return 0;
    }

    entry_clear(&dictionary->entries[index]);
    dictionary->entries[index].key = key_copy;
    dictionary->entries[index].type = VALUE_DICTIONARY;
    dictionary->entries[index].value.dictionary = child;

    return 1;
}

static size_t dictionary_depth(const Dictionary *dictionary)
{
    size_t index;
    size_t maximum_child_depth = 0U;

    if (dictionary == NULL) {
        return 0U;
    }

    for (index = 0U; index < dictionary->count; ++index) {
        if (dictionary->entries[index].type == VALUE_DICTIONARY) {
            size_t child_depth =
                dictionary_depth(dictionary->entries[index].value.dictionary);

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

int main(void)
{
    static const char value_key[] = "value";
    static const char grandchild_key[] = "grandchild";
    static const char child_key[] = "child";
    static const char number_key[] = "number";

    Dictionary *root = NULL;
    Dictionary *child = NULL;
    Dictionary *grandchild = NULL;
    size_t depth;
    int status = EXIT_FAILURE;

    root = dictionary_create(2U);
    child = dictionary_create(1U);
    grandchild = dictionary_create(1U);

    if (root == NULL || child == NULL || grandchild == NULL) {
        goto cleanup;
    }

    if (!dictionary_set_integer(grandchild, 0U, value_key,
                                sizeof(value_key), 42L)) {
        goto cleanup;
    }

    if (!dictionary_set_dictionary(child, 0U, grandchild_key,
                                   sizeof(grandchild_key), grandchild)) {
        goto cleanup;
    }
    grandchild = NULL;

    if (!dictionary_set_dictionary(root, 0U, child_key,
                                   sizeof(child_key), child)) {
        goto cleanup;
    }
    child = NULL;

    if (!dictionary_set_integer(root, 1U, number_key,
                                sizeof(number_key), 7L)) {
        goto cleanup;
    }

    depth = dictionary_depth(root);
    if (printf("%zu\n", depth) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    dictionary_destroy(grandchild);
    dictionary_destroy(child);
    dictionary_destroy(root);

    return status;
}