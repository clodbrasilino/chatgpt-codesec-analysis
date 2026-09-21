#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *value;
    size_t length;
} DictionaryEntry;

static char *duplicate_string(const char *source, size_t length)
{
    char *copy;

    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    if (length > 0U) {
        memcpy(copy, source, length);
    }

    copy[length] = '\0';
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

static int strings_equal(const char *left,
                         size_t left_length,
                         const char *right,
                         size_t right_length)
{
    if (left_length != right_length) {
        return 0;
    }

    if (left_length == 0U) {
        return 1;
    }

    if (left == NULL || right == NULL) {
        return 0;
    }

    return memcmp(left, right, left_length) == 0;
}

static int extract_unique_values(const DictionaryEntry *dictionary,
                                 size_t dictionary_size,
                                 char ***unique_values,
                                 size_t *unique_count)
{
    char **result;
    size_t *lengths;
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

    count = 0U;

    for (i = 0U; i < dictionary_size; ++i) {
        size_t j;
        int found;

        if (dictionary[i].value == NULL ||
            dictionary[i].length == SIZE_MAX) {
            free(lengths);
            free_values(result, count);
            return -1;
        }

        found = 0;

        for (j = 0U; j < count; ++j) {
            if (strings_equal(dictionary[i].value,
                              dictionary[i].length,
                              result[j],
                              lengths[j])) {
                found = 1;
                break;
            }
        }

        if (!found) {
            char *copy;

            copy = duplicate_string(dictionary[i].value,
                                    dictionary[i].length);
            if (copy == NULL) {
                free(lengths);
                free_values(result, count);
                return -1;
            }

            result[count] = copy;
            lengths[count] = dictionary[i].length;
            ++count;
        }
    }

    free(lengths);
    *unique_values = result;
    *unique_count = count;

    return 0;
}

int main(void)
{
    static const DictionaryEntry dictionary[] = {
        {"apple", sizeof("apple") - 1U},
        {"banana", sizeof("banana") - 1U},
        {"apple", sizeof("apple") - 1U},
        {"orange", sizeof("orange") - 1U},
        {"banana", sizeof("banana") - 1U}
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
        if (puts(unique_values[i]) == EOF) {
            free_values(unique_values, unique_count);
            return EXIT_FAILURE;
        }
    }

    free_values(unique_values, unique_count);
    return EXIT_SUCCESS;
}