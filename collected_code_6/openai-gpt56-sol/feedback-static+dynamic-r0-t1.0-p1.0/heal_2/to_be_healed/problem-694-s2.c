#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *value;
} DictionaryEntry;

static void free_unique_values(char **values, size_t count)
{
    if (values == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(values[i]);
    }

    free(values);
}

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
    memcpy(copy, source, length);
    copy[length] = '\0';

    return copy;
}

static int extract_unique_values(const DictionaryEntry *dictionary,
                                 size_t dictionary_size,
                                 char ***unique_values,
                                 size_t *unique_count)
{
    char **result;
    size_t count = 0;

    if (unique_values == NULL || unique_count == NULL) {
        return -1;
    }

    *unique_values = NULL;
    *unique_count = 0;

    if (dictionary_size == 0) {
        return 0;
    }

    if (dictionary == NULL ||
        dictionary_size > SIZE_MAX / sizeof(*result)) {
        return -1;
    }

    result = calloc(dictionary_size, sizeof(*result));
    if (result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < dictionary_size; ++i) {
        const char *value = dictionary[i].value;
        int found = 0;

        if (value == NULL) {
            free_unique_values(result, count);
            return -1;
        }

        for (size_t j = 0; j < count; ++j) {
            if (strcmp(result[j], value) == 0) {
                found = 1;
                break;
            }
        }

        if (!found) {
            result[count] = duplicate_string(value);
            if (result[count] == NULL) {
                free_unique_values(result, count);
                return -1;
            }

            ++count;
        }
    }

    if (count < dictionary_size) {
        char **resized = realloc(result, count * sizeof(*result));

        if (resized != NULL) {
            result = resized;
        }
    }

    *unique_values = result;
    *unique_count = count;
    return 0;
}

int main(void)
{
    const DictionaryEntry dictionary[] = {
        {"apple"},
        {"banana"},
        {"apple"},
        {"orange"},
        {"banana"}
    };
    const size_t dictionary_size =
        sizeof(dictionary) / sizeof(dictionary[0]);
    char **unique_values = NULL;
    size_t unique_count = 0;

    if (extract_unique_values(dictionary,
                              dictionary_size,
                              &unique_values,
                              &unique_count) != 0) {
        fputs("Failed to extract unique values.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < unique_count; ++i) {
        if (puts(unique_values[i]) == EOF) {
            free_unique_values(unique_values, unique_count);
            return EXIT_FAILURE;
        }
    }

    free_unique_values(unique_values, unique_count);
    return EXIT_SUCCESS;
}