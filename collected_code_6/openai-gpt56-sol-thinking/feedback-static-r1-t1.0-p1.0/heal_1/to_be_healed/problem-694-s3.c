#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    const char *key;
    const char *value;
} DictionaryEntry;

typedef enum {
    EXTRACT_OK = 0,
    EXTRACT_INVALID_ARGUMENT,
    EXTRACT_NO_MEMORY,
    EXTRACT_SIZE_OVERFLOW
} ExtractStatus;

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

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, source, length + 1);
    return copy;
}

void free_unique_values(char **values, size_t count)
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

ExtractStatus extract_unique_values(
    const DictionaryEntry *dictionary,
    size_t dictionary_count,
    char ***out_values,
    size_t *out_count)
{
    char **unique_values;
    size_t unique_count;
    size_t i;

    if (out_values == NULL || out_count == NULL ||
        (dictionary == NULL && dictionary_count != 0)) {
        return EXTRACT_INVALID_ARGUMENT;
    }

    *out_values = NULL;
    *out_count = 0;

    if (dictionary_count == 0) {
        return EXTRACT_OK;
    }

    if (dictionary_count > SIZE_MAX / sizeof(*unique_values)) {
        return EXTRACT_SIZE_OVERFLOW;
    }

    unique_values = calloc(dictionary_count, sizeof(*unique_values));
    if (unique_values == NULL) {
        return EXTRACT_NO_MEMORY;
    }

    unique_count = 0;

    for (i = 0; i < dictionary_count; ++i) {
        size_t j;
        int is_unique = 1;

        if (dictionary[i].key == NULL || dictionary[i].value == NULL) {
            free_unique_values(unique_values, unique_count);
            return EXTRACT_INVALID_ARGUMENT;
        }

        for (j = 0; j < unique_count; ++j) {
            if (strcmp(dictionary[i].value, unique_values[j]) == 0) {
                is_unique = 0;
                break;
            }
        }

        if (is_unique != 0) {
            unique_values[unique_count] =
                duplicate_string(dictionary[i].value);

            if (unique_values[unique_count] == NULL) {
                free_unique_values(unique_values, unique_count);
                return EXTRACT_NO_MEMORY;
            }

            ++unique_count;
        }
    }

    *out_values = unique_values;
    *out_count = unique_count;
    return EXTRACT_OK;
}

int main(void)
{
    const DictionaryEntry dictionary[] = {
        {"first", "apple"},
        {"second", "banana"},
        {"third", "apple"},
        {"fourth", "orange"},
        {"fifth", "banana"}
    };
    const size_t dictionary_count =
        sizeof(dictionary) / sizeof(dictionary[0]);
    char **unique_values;
    size_t unique_count;
    size_t i;
    ExtractStatus status;

    status = extract_unique_values(
        dictionary,
        dictionary_count,
        &unique_values,
        &unique_count
    );

    if (status != EXTRACT_OK) {
        if (fprintf(stderr, "Failed to extract unique values: %d\n",
                    (int)status) < 0) {
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

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}