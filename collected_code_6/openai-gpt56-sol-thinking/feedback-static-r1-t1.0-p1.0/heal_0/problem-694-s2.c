#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *key;
    const char *value;
} DictionaryEntry;

static void free_values(char **values, size_t count)
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

    length = strlen(source);
    copy = malloc(length + 1U);

    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, source, length + 1U);
    return copy;
}

static bool extract_unique_values(
    const DictionaryEntry *dictionary,
    size_t dictionary_size,
    char ***out_values,
    size_t *out_count)
{
    char **values;
    size_t unique_count = 0U;

    if (out_values == NULL || out_count == NULL) {
        return false;
    }

    *out_values = NULL;
    *out_count = 0U;

    if (dictionary_size == 0U) {
        return true;
    }

    if (dictionary == NULL ||
        dictionary_size > SIZE_MAX / sizeof(*values)) {
        return false;
    }

    values = calloc(dictionary_size, sizeof(*values));
    if (values == NULL) {
        return false;
    }

    for (size_t i = 0U; i < dictionary_size; ++i) {
        bool found = false;

        if (dictionary[i].value == NULL) {
            free_values(values, unique_count);
            return false;
        }

        for (size_t j = 0U; j < unique_count; ++j) {
            if (strcmp(dictionary[i].value, values[j]) == 0) {
                found = true;
                break;
            }
        }

        if (!found) {
            values[unique_count] = duplicate_string(dictionary[i].value);
            if (values[unique_count] == NULL) {
                free_values(values, unique_count);
                return false;
            }

            ++unique_count;
        }
    }

    *out_values = values;
    *out_count = unique_count;
    return true;
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
    const size_t dictionary_size =
        sizeof(dictionary) / sizeof(dictionary[0]);
    char **unique_values = NULL;
    size_t unique_count = 0U;
    int result = EXIT_SUCCESS;

    if (!extract_unique_values(
            dictionary,
            dictionary_size,
            &unique_values,
            &unique_count)) {
        fputs("Failed to extract unique values.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < unique_count; ++i) {
        if (printf("%s\n", unique_values[i]) < 0) {
            result = EXIT_FAILURE;
            break;
        }
    }

    if (fflush(stdout) == EOF) {
        result = EXIT_FAILURE;
    }

    free_values(unique_values, unique_count);
    return result;
}