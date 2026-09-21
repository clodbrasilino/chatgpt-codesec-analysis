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

typedef int (*ValuePredicate)(int value);

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

static void free_dictionary(Dictionary *dictionary)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;

    if (dictionary == NULL) {
        return;
    }

    if (dictionary->entries != NULL) {
        for (i = 0U; i < dictionary->size; ++i) {
            free(dictionary->entries[i].key);
        }

        free(dictionary->entries);
    }

    dictionary->entries = NULL;
    dictionary->size = 0U;
}

static int filter_dictionary(const Dictionary *source,
                             ValuePredicate predicate,
                             Dictionary *result)
{
    size_t i;
    size_t count = 0U;
    size_t output_index = 0U;
    unsigned char *matches = NULL;

    if (source == NULL || predicate == NULL || result == NULL ||
        source == result) {
        return -1;
    }

    result->entries = NULL;
    result->size = 0U;

    if (source->size == 0U) {
        return 0;
    }

    if (source->entries == NULL) {
        return -1;
    }

    matches = calloc(source->size, sizeof(*matches));
    if (matches == NULL) {
        return -1;
    }

    for (i = 0U; i < source->size; ++i) {
        if (source->entries[i].key == NULL) {
            free(matches);
            return -1;
        }

        if (predicate(source->entries[i].value) != 0) {
            matches[i] = 1U;
            ++count;
        }
    }

    if (count == 0U) {
        free(matches);
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*result->entries)) {
        free(matches);
        return -1;
    }

    result->entries = calloc(count, sizeof(*result->entries));
    if (result->entries == NULL) {
        free(matches);
        return -1;
    }

    for (i = 0U; i < source->size; ++i) {
        if (matches[i] != 0U) {
            char *key_copy = duplicate_string(source->entries[i].key);

            if (key_copy == NULL) {
                result->size = output_index;
                free_dictionary(result);
                free(matches);
                return -1;
            }

            result->entries[output_index].key = key_copy;
            result->entries[output_index].value =
                source->entries[i].value;
            ++output_index;
        }
    }

    free(matches);
    result->size = output_index;
    return 0;
}

static int is_positive(int value)
{
    return value > 0;
}

int main(void)
{
    DictionaryEntry source_entries[] = {
        { "apple", 5 },
        { "banana", -2 },
        { "orange", 8 },
        { "pear", 0 }
    };
    Dictionary source = {
        source_entries,
        sizeof(source_entries) / sizeof(source_entries[0])
    };
    Dictionary filtered = { NULL, 0U };
    size_t i;

    if (filter_dictionary(&source, is_positive, &filtered) != 0) {
        fputs("Failed to filter dictionary.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < filtered.size; ++i) {
        if (printf("%s: %d\n",
                   filtered.entries[i].key,
                   filtered.entries[i].value) < 0) {
            free_dictionary(&filtered);
            return EXIT_FAILURE;
        }
    }

    free_dictionary(&filtered);
    return EXIT_SUCCESS;
}