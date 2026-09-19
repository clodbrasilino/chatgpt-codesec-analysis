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

    memcpy(copy, source, length + 1U);
    return copy;
}

static void dictionary_destroy(Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL) {
        return;
    }

    for (i = 0U; i < dictionary->count; ++i) {
        free(dictionary->entries[i].key);
        free(dictionary->entries[i].value);
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->count = 0U;
}

static int dictionary_copy(Dictionary *destination, const Dictionary *source)
{
    size_t i;

    if (destination == NULL || source == NULL ||
        (source->count > 0U && source->entries == NULL)) {
        return -1;
    }

    destination->entries = NULL;
    destination->count = 0U;

    if (source->count == 0U) {
        return 0;
    }

    if (source->count > SIZE_MAX / sizeof(*destination->entries)) {
        return -1;
    }

    destination->entries = calloc(source->count,
                                  sizeof(*destination->entries));
    if (destination->entries == NULL) {
        return -1;
    }

    for (i = 0U; i < source->count; ++i) {
        if (source->entries[i].key == NULL ||
            source->entries[i].value == NULL) {
            dictionary_destroy(destination);
            return -1;
        }

        destination->entries[i].key =
            duplicate_string(source->entries[i].key);
        if (destination->entries[i].key == NULL) {
            dictionary_destroy(destination);
            return -1;
        }

        destination->count = i + 1U;
        destination->entries[i].value =
            duplicate_string(source->entries[i].value);
        if (destination->entries[i].value == NULL) {
            dictionary_destroy(destination);
            return -1;
        }
    }

    return 0;
}

static int tuple_add_dictionary(Tuple *tuple, const Dictionary *dictionary)
{
    Dictionary copy;
    TupleItem *resized_items;

    if (tuple == NULL || dictionary == NULL ||
        tuple->count > tuple->capacity ||
        (tuple->capacity > 0U && tuple->items == NULL)) {
        return -1;
    }

    if (dictionary_copy(&copy, dictionary) != 0) {
        return -1;
    }

    if (tuple->count == tuple->capacity) {
        size_t new_capacity;

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

        resized_items = realloc(
            tuple->items, new_capacity * sizeof(*tuple->items));
        if (resized_items == NULL) {
            dictionary_destroy(&copy);
            return -1;
        }

        tuple->items = resized_items;
        tuple->capacity = new_capacity;
    }

    tuple->items[tuple->count].type = TUPLE_DICTIONARY;
    tuple->items[tuple->count].dictionary = copy;
    ++tuple->count;

    return 0;
}

static void tuple_destroy(Tuple *tuple)
{
    size_t i;

    if (tuple == NULL) {
        return;
    }

    for (i = 0U; i < tuple->count; ++i) {
        if (tuple->items[i].type == TUPLE_DICTIONARY) {
            dictionary_destroy(&tuple->items[i].dictionary);
        }
    }

    free(tuple->items);
    tuple->items = NULL;
    tuple->count = 0U;
    tuple->capacity = 0U;
}

int main(void)
{
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
    size_t i;

    if (tuple_add_dictionary(&tuple, &dictionary) != 0) {
        fputs("Failed to add dictionary to tuple\n", stderr);
        tuple_destroy(&tuple);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < tuple.items[0].dictionary.count; ++i) {
        printf("%s: %s\n",
               tuple.items[0].dictionary.entries[i].key,
               tuple.items[0].dictionary.entries[i].value);
    }

    tuple_destroy(&tuple);
    return EXIT_SUCCESS;
}