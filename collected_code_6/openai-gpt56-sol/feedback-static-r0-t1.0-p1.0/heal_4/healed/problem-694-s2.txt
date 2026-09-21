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

static char *duplicate_string(const char *source, size_t length)
{
    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    char *copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < length; ++i) {
        copy[i] = source[i];
    }

    copy[length] = '\0';
    return copy;
}

static int extract_unique_values(const DictionaryEntry *dictionary,
                                 size_t dictionary_size,
                                 size_t max_value_length,
                                 char ***unique_values,
                                 size_t *unique_count)
{
    char **result = NULL;
    size_t *lengths = NULL;
    size_t count = 0;

    if (unique_values == NULL || unique_count == NULL) {
        return -1;
    }

    *unique_values = NULL;
    *unique_count = 0;

    if (dictionary_size == 0) {
        return 0;
    }

    if (dictionary == NULL || max_value_length == 0 ||
        dictionary_size > SIZE_MAX / sizeof(*result) ||
        dictionary_size > SIZE_MAX / sizeof(*lengths)) {
        return -1;
    }

    result = calloc(dictionary_size, sizeof(*result));
    if (result == NULL) {
        return -1;
    }

    lengths = malloc(dictionary_size * sizeof(*lengths));
    if (lengths == NULL) {
        free(result);
        return -1;
    }

    for (size_t i = 0; i < dictionary_size; ++i) {
        const char *value = dictionary[i].value;
        const char *terminator;
        size_t value_length;
        int found = 0;

        if (value == NULL) {
            free(lengths);
            free_unique_values(result, count);
            return -1;
        }

        terminator = memchr(value, '\0', max_value_length);
        if (terminator == NULL) {
            free(lengths);
            free_unique_values(result, count);
            return -1;
        }

        value_length = (size_t)(terminator - value);

        for (size_t j = 0; j < count; ++j) {
            if (lengths[j] == value_length &&
                (value_length == 0 ||
                 memcmp(result[j], value, value_length) == 0)) {
                found = 1;
                break;
            }
        }

        if (!found) {
            char *copy = duplicate_string(value, value_length);
            if (copy == NULL) {
                free(lengths);
                free_unique_values(result, count);
                return -1;
            }

            result[count] = copy;
            lengths[count] = value_length;
            ++count;
        }
    }

    free(lengths);

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
    const size_t max_value_length = 1024;
    char **unique_values = NULL;
    size_t unique_count = 0;

    if (extract_unique_values(dictionary,
                              dictionary_size,
                              max_value_length,
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