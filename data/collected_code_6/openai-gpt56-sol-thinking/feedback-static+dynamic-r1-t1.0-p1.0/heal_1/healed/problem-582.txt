#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DictionaryEntry {
    const char *key;
    const char *value;
    struct DictionaryEntry *next;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *head;
} Dictionary;

typedef enum {
    DICTIONARY_SUCCESS = 0,
    DICTIONARY_INVALID_ARGUMENT,
    DICTIONARY_ALLOCATION_FAILURE,
    DICTIONARY_KEY_NOT_FOUND
} DictionaryStatus;

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

    if (dictionary == NULL || key == NULL || value == NULL) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    for (entry = dictionary->head; entry != NULL; entry = entry->next) {
        if (strcmp(entry->key, key) == 0) {
            entry->value = value;
            return DICTIONARY_SUCCESS;
        }
    }

    entry = malloc(sizeof(*entry));
    if (entry == NULL) {
        return DICTIONARY_ALLOCATION_FAILURE;
    }

    entry->key = key;
    entry->value = value;
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
    return DICTIONARY_KEY_NOT_FOUND;
}

static void dictionary_clear(Dictionary *dictionary)
{
    DictionaryEntry *entry;

    if (dictionary == NULL) {
        return;
    }

    entry = dictionary->head;
    while (entry != NULL) {
        DictionaryEntry *next = entry->next;
        free(entry);
        entry = next;
    }

    dictionary->head = NULL;
}

int main(void)
{
    Dictionary dictionary = { .head = NULL };
    const char *value = NULL;
    bool is_empty = false;

    if (dictionary_is_empty(&dictionary, &is_empty) != DICTIONARY_SUCCESS) {
        fputs("Failed to check dictionary state.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(is_empty ? "Dictionary is empty." : "Dictionary is not empty.");

    if (dictionary_set(&dictionary, "language", "C") != DICTIONARY_SUCCESS) {
        fputs("Failed to add dictionary entry.\n", stderr);
        dictionary_clear(&dictionary);
        return EXIT_FAILURE;
    }

    if (dictionary_get(&dictionary, "language", &value) != DICTIONARY_SUCCESS) {
        fputs("Failed to retrieve dictionary entry.\n", stderr);
        dictionary_clear(&dictionary);
        return EXIT_FAILURE;
    }

    printf("language: %s\n", value);
    dictionary_clear(&dictionary);

    return EXIT_SUCCESS;
}