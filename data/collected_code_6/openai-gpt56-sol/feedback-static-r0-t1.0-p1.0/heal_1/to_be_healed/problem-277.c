#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    size_t size;
} Dictionary;

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
    length = strlen(source);
    if (length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, source, length + 1U);
    return copy;
}

static void dictionary_destroy(Dictionary *dictionary)
{
    size_t index;

    if (dictionary == NULL) {
        return;
    }

    for (index = 0U; index < dictionary->size; ++index) {
        free(dictionary->entries[index].key);
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->size = 0U;
}

static int dictionary_filter_by_value(
    const Dictionary *source,
    int minimum_value,
    int maximum_value,
    Dictionary *result)
{
    size_t index;
    size_t count = 0U;

    if (source == NULL || result == NULL || minimum_value > maximum_value) {
        return -1;
    }

    if (source->size > 0U && source->entries == NULL) {
        return -1;
    }

    result->entries = NULL;
    result->size = 0U;

    for (index = 0U; index < source->size; ++index) {
        if (source->entries[index].key == NULL) {
            return -1;
        }

        if (source->entries[index].value >= minimum_value &&
            source->entries[index].value <= maximum_value) {
            ++count;
        }
    }

    if (count == 0U) {
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*result->entries)) {
        return -1;
    }

    result->entries = calloc(count, sizeof(*result->entries));
    if (result->entries == NULL) {
        return -1;
    }

    for (index = 0U; index < source->size; ++index) {
        if (source->entries[index].value >= minimum_value &&
            source->entries[index].value <= maximum_value) {
            DictionaryEntry *entry = &result->entries[result->size];

            entry->key = duplicate_string(source->entries[index].key);
            if (entry->key == NULL) {
                dictionary_destroy(result);
                return -1;
            }

            entry->value = source->entries[index].value;
            ++result->size;
        }
    }

    return 0;
}

int main(void)
{
    DictionaryEntry entries[] = {
        {(char *)"apple", 10},
        {(char *)"banana", 25},
        {(char *)"cherry", 40},
        {(char *)"date", 15},
        {(char *)"elderberry", 50}
    };
    Dictionary source = {
        entries,
        sizeof(entries) / sizeof(entries[0])
    };
    Dictionary filtered = {NULL, 0U};
    size_t index;

    if (dictionary_filter_by_value(&source, 15, 40, &filtered) != 0) {
        fputs("Failed to filter dictionary.\n", stderr);
        return EXIT_FAILURE;
    }

    for (index = 0U; index < filtered.size; ++index) {
        if (printf("%s: %d\n",
                   filtered.entries[index].key,
                   filtered.entries[index].value) < 0) {
            dictionary_destroy(&filtered);
            return EXIT_FAILURE;
        }
    }

    dictionary_destroy(&filtered);
    return EXIT_SUCCESS;
}