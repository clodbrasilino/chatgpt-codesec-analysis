#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    DICTIONARY_OK,
    DICTIONARY_INVALID_ARGUMENT,
    DICTIONARY_OUT_OF_RANGE,
    DICTIONARY_OUT_OF_MEMORY
} DictionaryStatus;

typedef struct {
    char *key;
    size_t key_length;
    char *value;
    size_t value_length;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

static DictionaryStatus duplicate_string(
    const char *source,
    size_t length,
    char **destination
)
{
    char *copy;
    size_t index;

    if (source == NULL || destination == NULL) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    *destination = NULL;

    if (length == SIZE_MAX) {
        return DICTIONARY_OUT_OF_MEMORY;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return DICTIONARY_OUT_OF_MEMORY;
    }

    for (index = 0; index < length; ++index) {
        copy[index] = source[index];
    }

    copy[length] = '\0';
    *destination = copy;
    return DICTIONARY_OK;
}

static int strings_equal(
    const char *left,
    size_t left_length,
    const char *right,
    size_t right_length
)
{
    size_t index;

    if (left_length != right_length) {
        return 0;
    }

    for (index = 0; index < left_length; ++index) {
        if (left[index] != right[index]) {
            return 0;
        }
    }

    return 1;
}

static void dictionary_init(Dictionary *dictionary)
{
    if (dictionary == NULL) {
        return;
    }

    dictionary->entries = NULL;
    dictionary->size = 0;
    dictionary->capacity = 0;
}

static void dictionary_destroy(Dictionary *dictionary)
{
    size_t index;

    if (dictionary == NULL) {
        return;
    }

    for (index = 0; index < dictionary->size; ++index) {
        free(dictionary->entries[index].key);
        free(dictionary->entries[index].value);
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->size = 0;
    dictionary->capacity = 0;
}

static DictionaryStatus dictionary_reserve(Dictionary *dictionary)
{
    size_t new_capacity;
    DictionaryEntry *new_entries;

    if (dictionary == NULL) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    if (dictionary->size < dictionary->capacity) {
        return DICTIONARY_OK;
    }

    if (dictionary->capacity == 0) {
        new_capacity = 4;
    } else {
        if (dictionary->capacity > SIZE_MAX / 2) {
            return DICTIONARY_OUT_OF_MEMORY;
        }

        new_capacity = dictionary->capacity * 2;
    }

    if (new_capacity > SIZE_MAX / sizeof(*new_entries)) {
        return DICTIONARY_OUT_OF_MEMORY;
    }

    new_entries = realloc(
        dictionary->entries,
        new_capacity * sizeof(*new_entries)
    );

    if (new_entries == NULL) {
        return DICTIONARY_OUT_OF_MEMORY;
    }

    dictionary->entries = new_entries;
    dictionary->capacity = new_capacity;
    return DICTIONARY_OK;
}

static DictionaryStatus dictionary_set(
    Dictionary *dictionary,
    const char *key,
    size_t key_length,
    const char *value,
    size_t value_length
)
{
    size_t index;
    char *key_copy;
    char *value_copy;
    DictionaryStatus status;

    if (dictionary == NULL || key == NULL || value == NULL) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    for (index = 0; index < dictionary->size; ++index) {
        if (strings_equal(
                dictionary->entries[index].key,
                dictionary->entries[index].key_length,
                key,
                key_length
            )) {
            status = duplicate_string(value, value_length, &value_copy);
            if (status != DICTIONARY_OK) {
                return status;
            }

            free(dictionary->entries[index].value);
            dictionary->entries[index].value = value_copy;
            dictionary->entries[index].value_length = value_length;
            return DICTIONARY_OK;
        }
    }

    status = duplicate_string(key, key_length, &key_copy);
    if (status != DICTIONARY_OK) {
        return status;
    }

    status = duplicate_string(value, value_length, &value_copy);
    if (status != DICTIONARY_OK) {
        free(key_copy);
        return status;
    }

    status = dictionary_reserve(dictionary);
    if (status != DICTIONARY_OK) {
        free(key_copy);
        free(value_copy);
        return status;
    }

    dictionary->entries[dictionary->size].key = key_copy;
    dictionary->entries[dictionary->size].key_length = key_length;
    dictionary->entries[dictionary->size].value = value_copy;
    dictionary->entries[dictionary->size].value_length = value_length;
    ++dictionary->size;

    return DICTIONARY_OK;
}

static DictionaryStatus dictionary_key_at(
    const Dictionary *dictionary,
    size_t index,
    const char **key
)
{
    if (dictionary == NULL || key == NULL) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    *key = NULL;

    if (index >= dictionary->size) {
        return DICTIONARY_OUT_OF_RANGE;
    }

    *key = dictionary->entries[index].key;
    return DICTIONARY_OK;
}

int main(void)
{
    Dictionary dictionary;
    DictionaryStatus status;
    const char *key;
    size_t index;

    dictionary_init(&dictionary);

    status = dictionary_set(
        &dictionary,
        "name",
        sizeof("name") - 1,
        "Alice",
        sizeof("Alice") - 1
    );
    if (status != DICTIONARY_OK) {
        dictionary_destroy(&dictionary);
        return EXIT_FAILURE;
    }

    status = dictionary_set(
        &dictionary,
        "age",
        sizeof("age") - 1,
        "30",
        sizeof("30") - 1
    );
    if (status != DICTIONARY_OK) {
        dictionary_destroy(&dictionary);
        return EXIT_FAILURE;
    }

    status = dictionary_set(
        &dictionary,
        "city",
        sizeof("city") - 1,
        "London",
        sizeof("London") - 1
    );
    if (status != DICTIONARY_OK) {
        dictionary_destroy(&dictionary);
        return EXIT_FAILURE;
    }

    for (index = 0; index < dictionary.size; ++index) {
        status = dictionary_key_at(&dictionary, index, &key);
        if (status != DICTIONARY_OK) {
            dictionary_destroy(&dictionary);
            return EXIT_FAILURE;
        }

        if (printf("%zu: %s\n", index, key) < 0) {
            dictionary_destroy(&dictionary);
            return EXIT_FAILURE;
        }
    }

    dictionary_destroy(&dictionary);
    return EXIT_SUCCESS;
}