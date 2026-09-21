#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *data;
    size_t length;
} StringView;

typedef struct {
    StringView key;
    StringView value;
} DictionaryEntryView;

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

static char *duplicate_string(const char *source, size_t length)
{
    char *copy;

    if ((source == NULL && length != 0U) || length == SIZE_MAX) {
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
    size_t i;

    if (dictionary == NULL) {
        return;
    }

    if (dictionary->entries != NULL) {
        for (i = 0U; i < dictionary->count; ++i) {
            free(dictionary->entries[i].key);
            free(dictionary->entries[i].value);
        }
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->count = 0U;
}

static int dictionary_copy(Dictionary *destination,
                           const DictionaryEntryView *source_entries,
                           size_t source_count)
{
    size_t i;

    if (destination == NULL ||
        (source_count != 0U && source_entries == NULL)) {
        return -1;
    }

    destination->entries = NULL;
    destination->count = 0U;

    if (source_count == 0U) {
        return 0;
    }

    if (source_count > SIZE_MAX / sizeof(*destination->entries)) {
        return -1;
    }

    destination->entries = calloc(source_count,
                                  sizeof(*destination->entries));
    if (destination->entries == NULL) {
        return -1;
    }

    for (i = 0U; i < source_count; ++i) {
        const DictionaryEntryView *source = &source_entries[i];
        DictionaryEntry *target = &destination->entries[i];

        if ((source->key.data == NULL && source->key.length != 0U) ||
            (source->value.data == NULL && source->value.length != 0U) ||
            source->key.length == SIZE_MAX ||
            source->value.length == SIZE_MAX) {
            dictionary_destroy(destination);
            return -1;
        }

        target->key = duplicate_string(source->key.data, source->key.length);
        if (target->key == NULL) {
            dictionary_destroy(destination);
            return -1;
        }

        target->value = duplicate_string(source->value.data,
                                         source->value.length);
        if (target->value == NULL) {
            free(target->key);
            target->key = NULL;
            dictionary_destroy(destination);
            return -1;
        }

        destination->count = i + 1U;
    }

    return 0;
}

static int tuple_add_dictionary(Tuple *tuple,
                                const DictionaryEntryView *entries,
                                size_t count)
{
    TupleItem item = {
        .type = TUPLE_DICTIONARY,
        .dictionary = {NULL, 0U}
    };
    size_t new_capacity;
    TupleItem *resized;

    if (tuple == NULL ||
        tuple->count > tuple->capacity ||
        (tuple->capacity == 0U && tuple->items != NULL) ||
        (tuple->capacity != 0U && tuple->items == NULL) ||
        (count != 0U && entries == NULL)) {
        return -1;
    }

    if (dictionary_copy(&item.dictionary, entries, count) != 0) {
        return -1;
    }

    if (tuple->count == tuple->capacity) {
        if (tuple->capacity == 0U) {
            new_capacity = 4U;
        } else {
            if (tuple->capacity > SIZE_MAX / 2U) {
                dictionary_destroy(&item.dictionary);
                return -1;
            }
            new_capacity = tuple->capacity * 2U;
        }

        if (new_capacity > SIZE_MAX / sizeof(*tuple->items)) {
            dictionary_destroy(&item.dictionary);
            return -1;
        }

        resized = realloc(tuple->items,
                          new_capacity * sizeof(*tuple->items));
        if (resized == NULL) {
            dictionary_destroy(&item.dictionary);
            return -1;
        }

        tuple->items = resized;
        tuple->capacity = new_capacity;
    }

    tuple->items[tuple->count] = item;
    ++tuple->count;

    return 0;
}

static void tuple_destroy(Tuple *tuple)
{
    size_t i;

    if (tuple == NULL) {
        return;
    }

    if (tuple->items != NULL) {
        for (i = 0U; i < tuple->count; ++i) {
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
    static const char name_key[] = "name";
    static const char name_value[] = "Alice";
    static const char language_key[] = "language";
    static const char language_value[] = "C";
    static const char role_key[] = "role";
    static const char role_value[] = "developer";

    const DictionaryEntryView entries[] = {
        {
            {name_key, sizeof(name_key) - 1U},
            {name_value, sizeof(name_value) - 1U}
        },
        {
            {language_key, sizeof(language_key) - 1U},
            {language_value, sizeof(language_value) - 1U}
        },
        {
            {role_key, sizeof(role_key) - 1U},
            {role_value, sizeof(role_value) - 1U}
        }
    };

    Tuple tuple = {NULL, 0U, 0U};
    size_t i;

    if (tuple_add_dictionary(&tuple,
                             entries,
                             sizeof(entries) / sizeof(entries[0])) != 0) {
        fputs("Failed to add dictionary to tuple\n", stderr);
        tuple_destroy(&tuple);
        return EXIT_FAILURE;
    }

    if (tuple.count == 0U ||
        tuple.items == NULL ||
        tuple.items[0].type != TUPLE_DICTIONARY) {
        tuple_destroy(&tuple);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < tuple.items[0].dictionary.count; ++i) {
        const DictionaryEntry *entry =
            &tuple.items[0].dictionary.entries[i];

        if (printf("%s: %s\n", entry->key, entry->value) < 0) {
            tuple_destroy(&tuple);
            return EXIT_FAILURE;
        }
    }

    tuple_destroy(&tuple);
    return EXIT_SUCCESS;
}