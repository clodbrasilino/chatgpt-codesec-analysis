#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'DictionaryEntry::key' is never used. [unusedStructMember]
     */
    const char *key;
    const char *value;
} DictionaryEntry;

typedef struct {
    const DictionaryEntry *entries;
    size_t count;
} Dictionary;

typedef enum {
    UNIQUE_SUCCESS = 0,
    UNIQUE_INVALID_ARGUMENT,
    UNIQUE_OUT_OF_MEMORY,
    UNIQUE_SIZE_OVERFLOW
} UniqueStatus;

static void free_unique_values(char **values, size_t count)
{
    size_t i;

    if (values == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        free(values[i]);
    }

    free(values);
}

static UniqueStatus duplicate_string(const char *source, char **destination)
{
    size_t length;
    char *copy;

    if (source == NULL || destination == NULL) {
        return UNIQUE_INVALID_ARGUMENT;
    }

    *destination = NULL;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(source);

    if (length == SIZE_MAX) {
        return UNIQUE_SIZE_OVERFLOW;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return UNIQUE_OUT_OF_MEMORY;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, source, length + 1);
    *destination = copy;

    return UNIQUE_SUCCESS;
}

UniqueStatus extract_unique_values(
    const Dictionary *dictionary,
    char ***out_values,
    size_t *out_count)
{
    char **unique_values;
    size_t unique_count;
    size_t i;
    size_t j;
    UniqueStatus status;
    /* Possible weaknesses found:
     *  The scope of the variable 'found' can be reduced. [variableScope]
     */
    int found;

    if (out_values == NULL || out_count == NULL) {
        return UNIQUE_INVALID_ARGUMENT;
    }

    *out_values = NULL;
    *out_count = 0;

    if (dictionary == NULL ||
        (dictionary->count > 0 && dictionary->entries == NULL)) {
        return UNIQUE_INVALID_ARGUMENT;
    }

    if (dictionary->count == 0) {
        return UNIQUE_SUCCESS;
    }

    for (i = 0; i < dictionary->count; ++i) {
        if (dictionary->entries[i].value == NULL) {
            return UNIQUE_INVALID_ARGUMENT;
        }
    }

    if (dictionary->count > SIZE_MAX / sizeof(*unique_values)) {
        return UNIQUE_SIZE_OVERFLOW;
    }

    unique_values = calloc(dictionary->count, sizeof(*unique_values));
    if (unique_values == NULL) {
        return UNIQUE_OUT_OF_MEMORY;
    }

    unique_count = 0;

    for (i = 0; i < dictionary->count; ++i) {
        found = 0;

        for (j = 0; j < unique_count; ++j) {
            if (strcmp(dictionary->entries[i].value, unique_values[j]) == 0) {
                found = 1;
                break;
            }
        }

        if (!found) {
            status = duplicate_string(
                dictionary->entries[i].value,
                &unique_values[unique_count]);

            if (status != UNIQUE_SUCCESS) {
                free_unique_values(unique_values, unique_count);
                return status;
            }

            ++unique_count;
        }
    }

    *out_values = unique_values;
    *out_count = unique_count;

    return UNIQUE_SUCCESS;
}

static const char *unique_status_message(UniqueStatus status)
{
    switch (status) {
        case UNIQUE_SUCCESS:
            return "success";
        case UNIQUE_INVALID_ARGUMENT:
            return "invalid argument";
        case UNIQUE_OUT_OF_MEMORY:
            return "out of memory";
        case UNIQUE_SIZE_OVERFLOW:
            return "size overflow";
        default:
            return "unknown error";
    }
}

int main(void)
{
    const DictionaryEntry entries[] = {
        {"first", "apple"},
        {"second", "banana"},
        {"third", "apple"},
        {"fourth", "orange"},
        {"fifth", "banana"}
    };
    const Dictionary dictionary = {
        entries,
        sizeof(entries) / sizeof(entries[0])
    };
    char **unique_values;
    size_t unique_count;
    size_t i;
    UniqueStatus status;

    status = extract_unique_values(
        &dictionary,
        &unique_values,
        &unique_count);

    if (status != UNIQUE_SUCCESS) {
        if (fprintf(stderr, "Extraction failed: %s\n",
                    unique_status_message(status)) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    for (i = 0; i < unique_count; ++i) {
        if (printf("%s\n", unique_values[i]) < 0) {
            free_unique_values(unique_values, unique_count);
            return EXIT_FAILURE;
        }
    }

    free_unique_values(unique_values, unique_count);
    return EXIT_SUCCESS;
}