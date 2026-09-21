#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DictionaryEntry {
    char *key;
    char *value;
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

static char *duplicate_string(const char *source)
{
    size_t length;
    char *copy;

    if (source == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(source) + 1;
    copy = malloc(length);

    if (copy != NULL) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
    }

    return copy;
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
                                       const char *value)
{
    DictionaryEntry *entry;
    char *new_key;
    char *new_value;

    if (dictionary == NULL || key == NULL || value == NULL) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    for (entry = dictionary->head; entry != NULL; entry = entry->next) {
        if (strcmp(entry->key, key) == 0) {
            new_value = duplicate_string(value);
            if (new_value == NULL) {
                return DICTIONARY_ALLOCATION_FAILURE;
            }

            free(entry->value);
            entry->value = new_value;
            return DICTIONARY_SUCCESS;
        }
    }

    new_key = duplicate_string(key);
    if (new_key == NULL) {
        return DICTIONARY_ALLOCATION_FAILURE;
    }

    new_value = duplicate_string(value);
    if (new_value == NULL) {
        free(new_key);
        return DICTIONARY_ALLOCATION_FAILURE;
    }

    entry = malloc(sizeof(*entry));
    if (entry == NULL) {
        free(new_key);
        free(new_value);
        return DICTIONARY_ALLOCATION_FAILURE;
    }

    entry->key = new_key;
    entry->value = new_value;
    entry->next = dictionary->head;
    dictionary->head = entry;

    return DICTIONARY_SUCCESS;
}

static DictionaryStatus dictionary_get(const Dictionary *dictionary,
                                       const char *key,
                                       const char **value)
{
    const DictionaryEntry *entry;

    if (dictionary == NULL || key == NULL || value == NULL) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    for (entry = dictionary->head; entry != NULL; entry = entry->next) {
        if (strcmp(entry->key, key) == 0) {
            *value = entry->value;
            return DICTIONARY_SUCCESS;
        }
    }

    *value = NULL;
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
    Dictionary dictionary;
    DictionaryStatus status;
    const char *value;
    bool is_empty;

    dictionary_init(&dictionary);

    status = dictionary_is_empty(&dictionary, &is_empty);
    if (status != DICTIONARY_SUCCESS) {
        fputs("Failed to check dictionary state.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(is_empty ? "Dictionary is empty." : "Dictionary is not empty.");

    status = dictionary_set(&dictionary, "language", "C");
    if (status != DICTIONARY_SUCCESS) {
        fputs("Failed to add a dictionary entry.\n", stderr);
        dictionary_clear(&dictionary);
        return EXIT_FAILURE;
    }

    status = dictionary_get(&dictionary, "language", &value);
    if (status != DICTIONARY_SUCCESS) {
        fputs("Failed to retrieve a dictionary entry.\n", stderr);
        dictionary_clear(&dictionary);
        return EXIT_FAILURE;
    }

    printf("language: %s\n", value);

    dictionary_clear(&dictionary);
    return EXIT_SUCCESS;
}