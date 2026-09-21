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

static char *duplicate_string(const char *source, size_t length)
{
    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    char *copy = malloc(length + 1U);
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

    for (size_t index = 0U; index < dictionary->size; ++index) {
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
    if (source == NULL || result == NULL || source == result ||
        minimum_value > maximum_value) {
        return -1;
    }

    if ((source->size > 0U && source->entries == NULL) ||
        (result->size > 0U && result->entries == NULL)) {
        return -1;
    }

    size_t match_count = 0U;

    for (size_t index = 0U; index < source->size; ++index) {
        const DictionaryEntry *entry = &source->entries[index];

        if (entry->key == NULL) {
            return -1;
        }

        if (entry->value >= minimum_value &&
            entry->value <= maximum_value) {
            if (match_count == SIZE_MAX) {
                return -1;
            }
            ++match_count;
        }
    }

    Dictionary temporary = {NULL, 0U};

    if (match_count > 0U) {
        if (match_count > SIZE_MAX / sizeof(*temporary.entries)) {
            return -1;
        }

        temporary.entries = calloc(match_count, sizeof(*temporary.entries));
        if (temporary.entries == NULL) {
            return -1;
        }

        for (size_t index = 0U; index < source->size; ++index) {
            const DictionaryEntry *source_entry = &source->entries[index];

            if (source_entry->value < minimum_value ||
                source_entry->value > maximum_value) {
                continue;
            }

            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t key_length = strlen(source_entry->key);
            DictionaryEntry *destination_entry =
                &temporary.entries[temporary.size];

            destination_entry->key =
                duplicate_string(source_entry->key, key_length);
            if (destination_entry->key == NULL) {
                dictionary_destroy(&temporary);
                return -1;
            }

            destination_entry->value = source_entry->value;
            ++temporary.size;
        }
    }

    dictionary_destroy(result);
    *result = temporary;

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

    if (dictionary_filter_by_value(&source, 15, 40, &filtered) != 0) {
        fputs("Failed to filter dictionary.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t index = 0U; index < filtered.size; ++index) {
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