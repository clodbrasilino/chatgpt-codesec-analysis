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
    TUPLE_STRING,
    TUPLE_DICTIONARY
} TupleItemType;

typedef struct {
    TupleItemType type;
    union {
        char *string;
        Dictionary dictionary;
    } value;
} TupleItem;

typedef struct {
    TupleItem *items;
    size_t count;
    size_t capacity;
} Tuple;

static char *duplicate_string(const char *source, size_t length)
{
    char *copy;

    if (source == NULL || length == SIZE_MAX) {
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

static int dictionary_copy(Dictionary *destination, const Dictionary *source)
{
    Dictionary copy = { NULL, 0U };

    if (destination == NULL || source == NULL) {
        return -1;
    }

    if (source->count != 0U && source->entries == NULL) {
        return -1;
    }

    if (source->count > SIZE_MAX / sizeof(*copy.entries)) {
        return -1;
    }

    if (source->count != 0U) {
        copy.entries = calloc(source->count, sizeof(*copy.entries));
        if (copy.entries == NULL) {
            return -1;
        }
    }

    copy.count = source->count;

    for (size_t i = 0U; i < source->count; ++i) {
        const char *key = source->entries[i].key;
        const char *value = source->entries[i].value;

        if (key == NULL || value == NULL) {
            dictionary_destroy(&copy);
            return -1;
        }

        copy.entries[i].key = duplicate_string(key, strlen(key));
        if (copy.entries[i].key == NULL) {
            dictionary_destroy(&copy);
            return -1;
        }

        copy.entries[i].value = duplicate_string(value, strlen(value));
        if (copy.entries[i].value == NULL) {
            dictionary_destroy(&copy);
            return -1;
        }
    }

    *destination = copy;
    return 0;
}

static void tuple_destroy(Tuple *tuple)
{
    if (tuple == NULL) {
        return;
    }

    if (tuple->items != NULL) {
        for (size_t i = 0U; i < tuple->count; ++i) {
            switch (tuple->items[i].type) {
                case TUPLE_STRING:
                    free(tuple->items[i].value.string);
                    break;

                case TUPLE_DICTIONARY:
                    dictionary_destroy(&tuple->items[i].value.dictionary);
                    break;

                default:
                    break;
            }
        }
    }

    free(tuple->items);
    tuple->items = NULL;
    tuple->count = 0U;
    tuple->capacity = 0U;
}

static int tuple_reserve(Tuple *tuple, size_t required_capacity)
{
    size_t new_capacity;
    TupleItem *new_items;

    if (tuple == NULL) {
        return -1;
    }

    if (required_capacity <= tuple->capacity) {
        return 0;
    }

    new_capacity = tuple->capacity == 0U ? 4U : tuple->capacity;

    while (new_capacity < required_capacity) {
        if (new_capacity > SIZE_MAX / 2U) {
            new_capacity = required_capacity;
            break;
        }

        new_capacity *= 2U;
    }

    if (new_capacity > SIZE_MAX / sizeof(*new_items)) {
        return -1;
    }

    new_items = realloc(tuple->items, new_capacity * sizeof(*new_items));
    if (new_items == NULL) {
        return -1;
    }

    tuple->items = new_items;
    tuple->capacity = new_capacity;
    return 0;
}

static int tuple_add_dictionary(Tuple *tuple, const Dictionary *dictionary)
{
    Dictionary copy = { NULL, 0U };

    if (tuple == NULL || dictionary == NULL || tuple->count == SIZE_MAX) {
        return -1;
    }

    if (dictionary_copy(&copy, dictionary) != 0) {
        return -1;
    }

    if (tuple_reserve(tuple, tuple->count + 1U) != 0) {
        dictionary_destroy(&copy);
        return -1;
    }

    tuple->items[tuple->count].type = TUPLE_DICTIONARY;
    tuple->items[tuple->count].value.dictionary = copy;
    ++tuple->count;

    return 0;
}

int main(void)
{
    DictionaryEntry entries[] = {
        { "language", "C" },
        { "standard", "C11" }
    };
    Dictionary dictionary = {
        entries,
        sizeof(entries) / sizeof(entries[0])
    };
    Tuple tuple = { NULL, 0U, 0U };

    if (tuple_add_dictionary(&tuple, &dictionary) != 0) {
        fputs("Failed to add dictionary to tuple\n", stderr);
        tuple_destroy(&tuple);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U;
         i < tuple.items[0].value.dictionary.count;
         ++i) {
        const DictionaryEntry *entry =
            &tuple.items[0].value.dictionary.entries[i];

        if (printf("%s: %s\n", entry->key, entry->value) < 0) {
            fputs("Output error\n", stderr);
            tuple_destroy(&tuple);
            return EXIT_FAILURE;
        }
    }

    tuple_destroy(&tuple);
    return EXIT_SUCCESS;
}