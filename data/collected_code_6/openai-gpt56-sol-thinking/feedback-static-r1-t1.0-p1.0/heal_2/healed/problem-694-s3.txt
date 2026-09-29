#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *key;
    const char *value;
    size_t value_length;
} DictionaryEntry;

typedef enum {
    EXTRACT_OK = 0,
    EXTRACT_INVALID_ARGUMENT,
    EXTRACT_NO_MEMORY,
    EXTRACT_SIZE_OVERFLOW
} ExtractStatus;

static int contains_null_byte(const char *data, size_t length)
{
    size_t i;

    for (i = 0; i < length; ++i) {
        if (data[i] == '\0') {
            return 1;
        }
    }

    return 0;
}

static int spans_equal(
    const char *left,
    size_t left_length,
    const char *right,
    size_t right_length)
{
    size_t i;

    if (left_length != right_length) {
        return 0;
    }

    for (i = 0; i < left_length; ++i) {
        if (left[i] != right[i]) {
            return 0;
        }
    }

    return 1;
}

static ExtractStatus duplicate_string(
    const char *source,
    size_t source_length,
    char **out_copy)
{
    char *copy;
    size_t i;

    if (out_copy == NULL) {
        return EXTRACT_INVALID_ARGUMENT;
    }

    *out_copy = NULL;

    if (source == NULL) {
        return EXTRACT_INVALID_ARGUMENT;
    }

    if (source_length == SIZE_MAX) {
        return EXTRACT_SIZE_OVERFLOW;
    }

    copy = malloc(source_length + 1);
    if (copy == NULL) {
        return EXTRACT_NO_MEMORY;
    }

    for (i = 0; i < source_length; ++i) {
        copy[i] = source[i];
    }

    copy[source_length] = '\0';
    *out_copy = copy;

    return EXTRACT_OK;
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

    if (out_values == NULL || out_count == NULL) {
        return EXTRACT_INVALID_ARGUMENT;
    }

    *out_values = NULL;
    *out_count = 0;

    if (dictionary == NULL && dictionary_count != 0) {
        return EXTRACT_INVALID_ARGUMENT;
    }

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

        if (dictionary[i].value_length == SIZE_MAX) {
            free_unique_values(unique_values, unique_count);
            return EXTRACT_SIZE_OVERFLOW;
        }

        if (contains_null_byte(
                dictionary[i].value,
                dictionary[i].value_length)) {
            free_unique_values(unique_values, unique_count);
            return EXTRACT_INVALID_ARGUMENT;
        }

        for (j = 0; j < i; ++j) {
            if (spans_equal(
                    dictionary[i].value,
                    dictionary[i].value_length,
                    dictionary[j].value,
                    dictionary[j].value_length)) {
                is_unique = 0;
                break;
            }
        }

        if (is_unique != 0) {
            ExtractStatus status = duplicate_string(
                dictionary[i].value,
                dictionary[i].value_length,
                &unique_values[unique_count]);

            if (status != EXTRACT_OK) {
                free_unique_values(unique_values, unique_count);
                return status;
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
        {"first", "apple", sizeof("apple") - 1},
        {"second", "banana", sizeof("banana") - 1},
        {"third", "apple", sizeof("apple") - 1},
        {"fourth", "orange", sizeof("orange") - 1},
        {"fifth", "banana", sizeof("banana") - 1}
    };
    const size_t dictionary_count =
        sizeof(dictionary) / sizeof(dictionary[0]);
    char **unique_values = NULL;
    size_t unique_count = 0;
    size_t i;
    ExtractStatus status;

    status = extract_unique_values(
        dictionary,
        dictionary_count,
        &unique_values,
        &unique_count);

    if (status != EXTRACT_OK) {
        if (fprintf(
                stderr,
                "Failed to extract unique values: %d\n",
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