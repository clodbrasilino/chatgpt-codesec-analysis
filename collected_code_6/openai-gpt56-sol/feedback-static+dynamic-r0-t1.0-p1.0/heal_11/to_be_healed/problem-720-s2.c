#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    size_t key_length;
    char *value;
    size_t value_length;
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

    if (source == NULL || length > SIZE_MAX - 1U) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    if (length > 0U) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
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

static int dictionary_copy(Dictionary *destination,
                           const Dictionary *source)
{
    Dictionary copy = {NULL, 0U};

    if (destination == NULL || source == NULL) {
        return -1;
    }

    if ((source->count > 0U && source->entries == NULL) ||
        source->count > SIZE_MAX / sizeof(*copy.entries)) {
        return -1;
    }

    if (source->count > 0U) {
        copy.entries = calloc(source->count, sizeof(*copy.entries));
        if (copy.entries == NULL) {
            return -1;
        }

        copy.count = source->count;
    }

    for (size_t i = 0U; i < source->count; ++i) {
        const DictionaryEntry *entry = &source->entries[i];

        if (entry->key == NULL ||
            entry->value == NULL ||
            entry->key_length > SIZE_MAX - 1U ||
            entry->value_length > SIZE_MAX - 1U) {
            dictionary_destroy(&copy);
            return -1;
        }

        copy.entries[i].key =
            duplicate_string(entry->key, entry->key_length);
        if (copy.entries[i].key == NULL) {
            dictionary_destroy(&copy);
            return -1;
        }

        copy.entries[i].key_length = entry->key_length;

        copy.entries[i].value =
            duplicate_string(entry->value, entry->value_length);
        if (copy.entries[i].value == NULL) {
            dictionary_destroy(&copy);
            return -1;
        }

        copy.entries[i].value_length = entry->value_length;
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

static int tuple_is_valid(const Tuple *tuple)
{
    if (tuple == NULL || tuple->count > tuple->capacity) {
        return 0;
    }

    if (tuple->capacity == 0U) {
        return tuple->items == NULL && tuple->count == 0U;
    }

    return tuple->items != NULL;
}

static int tuple_reserve(Tuple *tuple, size_t required_capacity)
{
    size_t new_capacity;
    TupleItem *new_items;

    if (!tuple_is_valid(tuple)) {
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

    new_items = realloc(tuple->items,
                        new_capacity * sizeof(*new_items));
    if (new_items == NULL) {
        return -1;
    }

    tuple->items = new_items;
    tuple->capacity = new_capacity;
    return 0;
}

static int tuple_add_dictionary(Tuple *tuple,
                                const Dictionary *dictionary)
{
    Dictionary copy = {NULL, 0U};

    if (!tuple_is_valid(tuple) ||
        dictionary == NULL ||
        tuple->count == SIZE_MAX) {
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
        {
            "language",
            sizeof("language") - 1U,
            "C",
            sizeof("C") - 1U
        },
        {
            "standard",
            sizeof("standard") - 1U,
            "C11",
            sizeof("C11") - 1U
        }
    };
    Dictionary dictionary = {
        entries,
        sizeof(entries) / sizeof(entries[0])
    };
    Tuple tuple = {NULL, 0U, 0U};
    const Dictionary *stored_dictionary;

    if (tuple_add_dictionary(&tuple, &dictionary) != 0) {
        fputs("Failed to add dictionary to tuple\n", stderr);
        tuple_destroy(&tuple);
        return EXIT_FAILURE;
    }

    if (tuple.count == 0U ||
        tuple.items == NULL ||
        tuple.items[0].type != TUPLE_DICTIONARY) {
        fputs("Invalid tuple state\n", stderr);
        tuple_destroy(&tuple);
        return EXIT_FAILURE;
    }

    stored_dictionary = &tuple.items[0].value.dictionary;

    if (stored_dictionary->count > 0U &&
        stored_dictionary->entries == NULL) {
        fputs("Invalid dictionary state\n", stderr);
        tuple_destroy(&tuple);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < stored_dictionary->count; ++i) {
        const DictionaryEntry *entry = &stored_dictionary->entries[i];

        if (entry->key == NULL ||
            entry->value == NULL ||
            (entry->key_length > 0U &&
             fwrite(entry->key, 1U, entry->key_length, stdout) !=
                 entry->key_length) ||
            fwrite(": ", 1U, 2U, stdout) != 2U ||
            (entry->value_length > 0U &&
             fwrite(entry->value, 1U, entry->value_length, stdout) !=
                 entry->value_length) ||
            fputc('\n', stdout) == EOF) {
            fputs("Output error\n", stderr);
            tuple_destroy(&tuple);
            return EXIT_FAILURE;
        }
    }

    if (fflush(stdout) == EOF) {
        fputs("Output error\n", stderr);
        tuple_destroy(&tuple);
        return EXIT_FAILURE;
    }

    tuple_destroy(&tuple);
    return EXIT_SUCCESS;
}