#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *value;
    size_t value_length;
} DictionaryEntry;

static void free_values(char **values, size_t count)
{
    if (values == NULL) {
        return;
    }

    for (size_t i = 0U; i < count; ++i) {
        free(values[i]);
    }

    free(values);
}

static bool strings_equal(
    const char *left,
    size_t left_length,
    const char *right,
    size_t right_length)
{
    if (left == NULL || right == NULL || left_length != right_length) {
        return false;
    }

    for (size_t i = 0U; i < left_length; ++i) {
        if (left[i] != right[i]) {
            return false;
        }
    }

    return true;
}

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

    for (size_t i = 0U; i < length; ++i) {
        copy[i] = source[i];
    }

    copy[length] = '\0';
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

        if (dictionary[i].value == NULL ||
            dictionary[i].value_length == SIZE_MAX) {
            free_values(values, unique_count);
            return false;
        }

        for (size_t j = 0U; j < i; ++j) {
            if (strings_equal(
                    dictionary[i].value,
                    dictionary[i].value_length,
                    dictionary[j].value,
                    dictionary[j].value_length)) {
                found = true;
                break;
            }
        }

        if (!found) {
            values[unique_count] = duplicate_string(
                dictionary[i].value,
                dictionary[i].value_length);

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
        {"apple", sizeof("apple") - 1U},
        {"banana", sizeof("banana") - 1U},
        {"apple", sizeof("apple") - 1U},
        {"orange", sizeof("orange") - 1U},
        {"banana", sizeof("banana") - 1U}
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