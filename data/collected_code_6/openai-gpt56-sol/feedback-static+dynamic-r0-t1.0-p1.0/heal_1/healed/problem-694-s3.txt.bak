#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *value;
} DictionaryEntry;

static char *duplicate_string(const char *source)
{
    size_t length;
    char *copy;

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

static void free_values(char **values, size_t count)
{
    size_t i;

    if (values == NULL) {
        return;
    }

    for (i = 0U; i < count; ++i) {
        free(values[i]);
    }

    free(values);
}

static int extract_unique_values(const DictionaryEntry *dictionary,
                                 size_t dictionary_size,
                                 char ***unique_values,
                                 size_t *unique_count)
{
    char **result;
    size_t count;
    size_t i;

    if (unique_values == NULL || unique_count == NULL) {
        return -1;
    }

    *unique_values = NULL;
    *unique_count = 0U;

    if (dictionary_size == 0U) {
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

    count = 0U;

    for (i = 0U; i < dictionary_size; ++i) {
        size_t j;
        int found;

        if (dictionary[i].value == NULL) {
            free_values(result, count);
            return -1;
        }

        found = 0;

        for (j = 0U; j < count; ++j) {
            if (strcmp(dictionary[i].value, result[j]) == 0) {
                found = 1;
                break;
            }
        }

        if (!found) {
            result[count] = duplicate_string(dictionary[i].value);
            if (result[count] == NULL) {
                free_values(result, count);
                return -1;
            }

            ++count;
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
    char **unique_values;
    size_t unique_count;
    size_t i;

    unique_values = NULL;
    unique_count = 0U;

    if (extract_unique_values(dictionary,
                              dictionary_size,
                              &unique_values,
                              &unique_count) != 0) {
        fputs("Failed to extract unique values.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < unique_count; ++i) {
        if (printf("%s\n", unique_values[i]) < 0) {
            free_values(unique_values, unique_count);
            return EXIT_FAILURE;
        }
    }

    free_values(unique_values, unique_count);
    return EXIT_SUCCESS;
}