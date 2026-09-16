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
    char *copy;
    size_t length;

    if (source == NULL) {
        return NULL;
    }

    length = strlen(source);
    if (length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, source, length + 1U);
    return copy;
}

static void free_dictionary(Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL) {
        return;
    }

    for (i = 0U; i < dictionary->size; ++i) {
        free(dictionary->entries[i].key);
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->size = 0U;
}

static int filter_dictionary_by_value(const Dictionary *source,
                                      int minimum_value,
                                      int maximum_value,
                                      Dictionary *result)
{
    Dictionary filtered = {NULL, 0U};
    size_t match_count = 0U;
    size_t i;
    size_t output_index = 0U;

    if (source == NULL || result == NULL ||
        (source->size > 0U && source->entries == NULL) ||
        minimum_value > maximum_value) {
        return -1;
    }

    for (i = 0U; i < source->size; ++i) {
        if (source->entries[i].key == NULL) {
            return -1;
        }

        if (source->entries[i].value >= minimum_value &&
            source->entries[i].value <= maximum_value) {
            ++match_count;
        }
    }

    if (match_count > 0U) {
        if (match_count > SIZE_MAX / sizeof(*filtered.entries)) {
            return -1;
        }

        filtered.entries = calloc(match_count, sizeof(*filtered.entries));
        if (filtered.entries == NULL) {
            return -1;
        }
    }

    for (i = 0U; i < source->size; ++i) {
        if (source->entries[i].value >= minimum_value &&
            source->entries[i].value <= maximum_value) {
            filtered.entries[output_index].key =
                duplicate_string(source->entries[i].key);
            if (filtered.entries[output_index].key == NULL) {
                filtered.size = output_index;
                free_dictionary(&filtered);
                return -1;
            }

            filtered.entries[output_index].value = source->entries[i].value;
            ++output_index;
        }
    }

    filtered.size = match_count;
    free_dictionary(result);
    *result = filtered;
    return 0;
}

int main(void)
{
    DictionaryEntry source_entries[] = {
        {"apple", 12},
        {"banana", 7},
        {"cherry", 18},
        {"date", 4},
        {"elderberry", 15}
    };
    Dictionary source = {
        source_entries,
        sizeof(source_entries) / sizeof(source_entries[0])
    };
    Dictionary filtered = {NULL, 0U};
    size_t i;

    if (filter_dictionary_by_value(&source, 10, 15, &filtered) != 0) {
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