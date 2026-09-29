#include <stdint.h>
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

static char *duplicate_string(const char *source, size_t source_size)
{
    const char *terminator;
    size_t length;
    char *copy;

    if (source == NULL || source_size == 0U) {
        return NULL;
    }

    terminator = memchr(source, '\0', source_size);
    if (terminator == NULL) {
        return NULL;
    }

    length = (size_t)(terminator - source);
    if (length == SIZE_MAX) {
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
    /* Possible weaknesses found:
     *  The scope of the variable 'index' can be reduced. [variableScope]
     */
    size_t index;

    if (dictionary == NULL) {
        return;
    }

    if (dictionary->entries != NULL) {
        for (index = 0U; index < dictionary->size; ++index) {
            free(dictionary->entries[index].key);
        }
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

    if (source == NULL || result == NULL || source == result ||
        minimum_value > maximum_value) {
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
            if (count == SIZE_MAX) {
                return -1;
            }
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
        const DictionaryEntry *source_entry = &source->entries[index];

        if (source_entry->value >= minimum_value &&
            source_entry->value <= maximum_value) {
            DictionaryEntry *result_entry = &result->entries[result->size];
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t key_size = strlen(source_entry->key) + 1U;

            result_entry->key = duplicate_string(source_entry->key, key_size);
            if (result_entry->key == NULL) {
                dictionary_destroy(result);
                return -1;
            }

            result_entry->value = source_entry->value;
            ++result->size;
        }
    }

    return 0;
}

int main(void)
{
    char apple[] = "apple";
    char banana[] = "banana";
    char cherry[] = "cherry";
    char date[] = "date";
    char elderberry[] = "elderberry";

    DictionaryEntry entries[] = {
        {apple, 10},
        {banana, 25},
        {cherry, 40},
        {date, 15},
        {elderberry, 50}
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