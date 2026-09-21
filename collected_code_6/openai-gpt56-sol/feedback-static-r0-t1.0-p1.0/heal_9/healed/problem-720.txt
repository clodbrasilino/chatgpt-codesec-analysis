#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    size_t count;
} Dictionary;

typedef enum {
    TUPLE_DICTIONARY
} TupleItemType;

typedef struct {
    TupleItemType type;
    Dictionary dictionary;
} TupleItem;

typedef struct {
    TupleItem *items;
    size_t count;
    size_t capacity;
} Tuple;

static int duplicate_string(const char *source, size_t max_length,
                            char **destination)
{
    const char *terminator;
    size_t length;
    char *copy;

    if (source == NULL || destination == NULL || max_length == 0U) {
        return -1;
    }

    *destination = NULL;

    terminator = memchr(source, '\0', max_length);
    if (terminator == NULL) {
        return -1;
    }

    length = (size_t)(terminator - source);

    if (length == SIZE_MAX) {
        return -1;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return -1;
    }

    if (length != 0U) {
        memcpy(copy, source, length);
    }
    copy[length] = '\0';

    *destination = copy;
    return 0;
}

static void dictionary_destroy(Dictionary *dictionary)
{
    if (dictionary == NULL) {
        return;
    }

    if (dictionary->entries != NULL) {
        for (size_t i = 0U; i < dictionary->count; ++i) {
            free(dictionary->entries[i].key);
            free(dictionary->entries[i].value);
        }
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->count = 0U;
}

static int dictionary_copy(Dictionary *destination,
                           const Dictionary *source,
                           size_t max_string_length)
{
    Dictionary copy = {NULL, 0U};

    if (destination == NULL || source == NULL ||
        max_string_length == 0U ||
        (source->count != 0U && source->entries == NULL)) {
        return -1;
    }

    if (source->count == 0U) {
        *destination = copy;
        return 0;
    }

    if (source->count > SIZE_MAX / sizeof(*copy.entries)) {
        return -1;
    }

    copy.entries = calloc(source->count, sizeof(*copy.entries));
    if (copy.entries == NULL) {
        return -1;
    }

    for (size_t i = 0U; i < source->count; ++i) {
        const DictionaryEntry *entry = &source->entries[i];

        if (entry->key == NULL || entry->value == NULL) {
            dictionary_destroy(&copy);
            return -1;
        }

        copy.count = i + 1U;

        if (duplicate_string(entry->key, max_string_length,
                             &copy.entries[i].key) != 0) {
            dictionary_destroy(&copy);
            return -1;
        }

        if (duplicate_string(entry->value, max_string_length,
                             &copy.entries[i].value) != 0) {
            dictionary_destroy(&copy);
            return -1;
        }
    }

    *destination = copy;
    return 0;
}

static int tuple_add_dictionary(Tuple *tuple,
                                const Dictionary *dictionary,
                                size_t max_string_length)
{
    Dictionary copy = {NULL, 0U};

    if (tuple == NULL || dictionary == NULL ||
        max_string_length == 0U ||
        tuple->count > tuple->capacity ||
        (tuple->capacity != 0U && tuple->items == NULL) ||
        (tuple->capacity == 0U && tuple->items != NULL)) {
        return -1;
    }

    if (dictionary_copy(&copy, dictionary, max_string_length) != 0) {
        return -1;
    }

    if (tuple->count == tuple->capacity) {
        size_t new_capacity;
        TupleItem *new_items;

        if (tuple->capacity == 0U) {
            new_capacity = 4U;
        } else {
            if (tuple->capacity > SIZE_MAX / 2U) {
                dictionary_destroy(&copy);
                return -1;
            }
            new_capacity = tuple->capacity * 2U;
        }

        if (new_capacity > SIZE_MAX / sizeof(*tuple->items)) {
            dictionary_destroy(&copy);
            return -1;
        }

        new_items = realloc(tuple->items,
                            new_capacity * sizeof(*tuple->items));
        if (new_items == NULL) {
            dictionary_destroy(&copy);
            return -1;
        }

        tuple->items = new_items;
        tuple->capacity = new_capacity;
    }

    tuple->items[tuple->count].type = TUPLE_DICTIONARY;
    tuple->items[tuple->count].dictionary = copy;
    ++tuple->count;

    return 0;
}

static void tuple_destroy(Tuple *tuple)
{
    if (tuple == NULL) {
        return;
    }

    if (tuple->items != NULL) {
        size_t valid_count = tuple->count;

        if (valid_count > tuple->capacity) {
            valid_count = tuple->capacity;
        }

        for (size_t i = 0U; i < valid_count; ++i) {
            if (tuple->items[i].type == TUPLE_DICTIONARY) {
                dictionary_destroy(&tuple->items[i].dictionary);
            }
        }
    }

    free(tuple->items);
    tuple->items = NULL;
    tuple->count = 0U;
    tuple->capacity = 0U;
}

int main(void)
{
    enum { MAX_STRING_LENGTH = 4096 };

    DictionaryEntry entries[] = {
        {"name", "Alice"},
        {"language", "C"},
        {"role", "Developer"}
    };
    Dictionary dictionary = {
        entries,
        sizeof(entries) / sizeof(entries[0])
    };
    Tuple tuple = {NULL, 0U, 0U};

    if (tuple_add_dictionary(&tuple, &dictionary,
                             (size_t)MAX_STRING_LENGTH) != 0) {
        fputs("Failed to add dictionary to tuple\n", stderr);
        tuple_destroy(&tuple);
        return EXIT_FAILURE;
    }

    if (tuple.count > 0U &&
        tuple.items[0].type == TUPLE_DICTIONARY) {
        const Dictionary *stored = &tuple.items[0].dictionary;

        for (size_t i = 0U; i < stored->count; ++i) {
            if (printf("%s: %s\n",
                       stored->entries[i].key,
                       stored->entries[i].value) < 0) {
                tuple_destroy(&tuple);
                return EXIT_FAILURE;
            }
        }
    }

    tuple_destroy(&tuple);
    return EXIT_SUCCESS;
}