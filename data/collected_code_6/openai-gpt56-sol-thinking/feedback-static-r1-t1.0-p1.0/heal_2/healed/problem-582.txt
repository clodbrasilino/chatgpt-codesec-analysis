#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct DictionaryEntry {
    char *key;
    size_t key_length;
    char *value;
    size_t value_length;
    struct DictionaryEntry *next;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *head;
} Dictionary;

typedef enum {
    DICTIONARY_SUCCESS = 0,
    DICTIONARY_INVALID_ARGUMENT,
    DICTIONARY_ALLOCATION_FAILURE,
    DICTIONARY_NOT_FOUND
} DictionaryStatus;

static DictionaryStatus duplicate_data(const char *source,
                                       size_t source_length,
                                       char **copy)
{
    char *result;
    size_t index;

    if (source == NULL || copy == NULL) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    if (source_length == SIZE_MAX) {
        return DICTIONARY_ALLOCATION_FAILURE;
    }

    result = malloc(source_length + 1);
    if (result == NULL) {
        return DICTIONARY_ALLOCATION_FAILURE;
    }

    for (index = 0; index < source_length; ++index) {
        result[index] = source[index];
    }

    result[source_length] = '\0';
    *copy = result;

    return DICTIONARY_SUCCESS;
}

static bool data_equal(const char *left,
                       size_t left_length,
                       const char *right,
                       size_t right_length)
{
    size_t index;

    if (left_length != right_length) {
        return false;
    }

    for (index = 0; index < left_length; ++index) {
        if (left[index] != right[index]) {
            return false;
        }
    }

    return true;
}

static void dictionary_init(Dictionary *dictionary)
{
    if (dictionary != NULL) {
        dictionary->head = NULL;
    }
}

static DictionaryStatus dictionary_is_empty(const Dictionary *dictionary,
                                            bool *is_empty)
{
    if (dictionary == NULL || is_empty == NULL) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    *is_empty = dictionary->head == NULL;
    return DICTIONARY_SUCCESS;
}

static DictionaryStatus dictionary_set(Dictionary *dictionary,
                                       const char *key,
                                       size_t key_length,
                                       const char *value,
                                       size_t value_length)
{
    DictionaryEntry *entry;
    DictionaryStatus status;
    char *new_key;
    char *new_value;

    if (dictionary == NULL || key == NULL || value == NULL) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    for (entry = dictionary->head; entry != NULL; entry = entry->next) {
        if (data_equal(entry->key, entry->key_length, key, key_length)) {
            status = duplicate_data(value, value_length, &new_value);
            if (status != DICTIONARY_SUCCESS) {
                return status;
            }

            free(entry->value);
            entry->value = new_value;
            entry->value_length = value_length;
            return DICTIONARY_SUCCESS;
        }
    }

    status = duplicate_data(key, key_length, &new_key);
    if (status != DICTIONARY_SUCCESS) {
        return status;
    }

    status = duplicate_data(value, value_length, &new_value);
    if (status != DICTIONARY_SUCCESS) {
        free(new_key);
        return status;
    }

    entry = malloc(sizeof(*entry));
    if (entry == NULL) {
        free(new_key);
        free(new_value);
        return DICTIONARY_ALLOCATION_FAILURE;
    }

    entry->key = new_key;
    entry->key_length = key_length;
    entry->value = new_value;
    entry->value_length = value_length;
    entry->next = dictionary->head;
    dictionary->head = entry;

    return DICTIONARY_SUCCESS;
}

static DictionaryStatus dictionary_get(const Dictionary *dictionary,
                                       const char *key,
                                       size_t key_length,
                                       const char **value,
                                       size_t *value_length)
{
    const DictionaryEntry *entry;

    if (dictionary == NULL || key == NULL ||
        value == NULL || value_length == NULL) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    for (entry = dictionary->head; entry != NULL; entry = entry->next) {
        if (data_equal(entry->key, entry->key_length, key, key_length)) {
            *value = entry->value;
            *value_length = entry->value_length;
            return DICTIONARY_SUCCESS;
        }
    }

    *value = NULL;
    *value_length = 0;
    return DICTIONARY_NOT_FOUND;
}

static void dictionary_clear(Dictionary *dictionary)
{
    DictionaryEntry *entry;
    DictionaryEntry *next;

    if (dictionary == NULL) {
        return;
    }

    entry = dictionary->head;

    while (entry != NULL) {
        next = entry->next;
        free(entry->key);
        free(entry->value);
        free(entry);
        entry = next;
    }

    dictionary->head = NULL;
}

int main(void)
{
    static const char key[] = "language";
    static const char initial_value[] = "C";

    Dictionary dictionary;
    DictionaryStatus status;
    const char *value;
    size_t value_length;
    bool is_empty;

    dictionary_init(&dictionary);

    status = dictionary_is_empty(&dictionary, &is_empty);
    if (status != DICTIONARY_SUCCESS) {
        fputs("Failed to check dictionary state.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(is_empty ? "Dictionary is empty." : "Dictionary is not empty.");

    status = dictionary_set(&dictionary,
                            key,
                            sizeof(key) - 1,
                            initial_value,
                            sizeof(initial_value) - 1);
    if (status != DICTIONARY_SUCCESS) {
        fputs("Failed to add a dictionary entry.\n", stderr);
        dictionary_clear(&dictionary);
        return EXIT_FAILURE;
    }

    status = dictionary_get(&dictionary,
                            key,
                            sizeof(key) - 1,
                            &value,
                            &value_length);
    if (status != DICTIONARY_SUCCESS) {
        fputs("Failed to retrieve a dictionary entry.\n", stderr);
        dictionary_clear(&dictionary);
        return EXIT_FAILURE;
    }

    if (fputs("language: ", stdout) == EOF ||
        fwrite(value, 1, value_length, stdout) != value_length ||
        fputc('\n', stdout) == EOF) {
        fputs("Failed to write output.\n", stderr);
        dictionary_clear(&dictionary);
        return EXIT_FAILURE;
    }

    dictionary_clear(&dictionary);
    return EXIT_SUCCESS;
}