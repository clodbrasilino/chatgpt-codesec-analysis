#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    const char *key;
    const char *value;
    size_t value_buffer_size;
} DictionaryEntry;

typedef enum {
    EXTRACT_OK = 0,
    EXTRACT_INVALID_ARGUMENT,
    EXTRACT_NO_MEMORY,
    EXTRACT_SIZE_OVERFLOW
} ExtractStatus;

static ExtractStatus bounded_string_length(
    const char *source,
    size_t source_size,
    size_t *out_length)
{
    size_t i;

    if (source == NULL || source_size == 0 || out_length == NULL) {
        return EXTRACT_INVALID_ARGUMENT;
    }

    for (i = 0; i < source_size; ++i) {
        if (source[i] == '\0') {
            *out_length = i;
            return EXTRACT_OK;
        }
    }

    return EXTRACT_INVALID_ARGUMENT;
}

static ExtractStatus duplicate_string(
    const char *source,
    size_t length,
    char **out_copy)
{
    char *copy;
    size_t i;

    if (source == NULL || out_copy == NULL) {
        return EXTRACT_INVALID_ARGUMENT;
    }

    *out_copy = NULL;

    if (length == SIZE_MAX) {
        return EXTRACT_SIZE_OVERFLOW;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return EXTRACT_NO_MEMORY;
    }

    for (i = 0; i < length; ++i) {
        copy[i] = source[i];
    }

    copy[length] = '\0';
    *out_copy = copy;

    return EXTRACT_OK;
}

static int strings_equal(
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
    size_t *unique_lengths;
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

    if (dictionary_count > SIZE_MAX / sizeof(*unique_values) ||
        dictionary_count > SIZE_MAX / sizeof(*unique_lengths)) {
        return EXTRACT_SIZE_OVERFLOW;
    }

    unique_values = calloc(dictionary_count, sizeof(*unique_values));
    if (unique_values == NULL) {
        return EXTRACT_NO_MEMORY;
    }

    unique_lengths = calloc(dictionary_count, sizeof(*unique_lengths));
    if (unique_lengths == NULL) {
        free(unique_values);
        return EXTRACT_NO_MEMORY;
    }

    unique_count = 0;

    for (i = 0; i < dictionary_count; ++i) {
        ExtractStatus status;
        size_t value_length;
        size_t j;
        int is_unique;

        if (dictionary[i].key == NULL || dictionary[i].value == NULL) {
            free(unique_lengths);
            free_unique_values(unique_values, unique_count);
            return EXTRACT_INVALID_ARGUMENT;
        }

        status = bounded_string_length(
            dictionary[i].value,
            dictionary[i].value_buffer_size,
            &value_length
        );

        if (status != EXTRACT_OK) {
            free(unique_lengths);
            free_unique_values(unique_values, unique_count);
            return status;
        }

        is_unique = 1;

        for (j = 0; j < unique_count; ++j) {
            if (strings_equal(
                    dictionary[i].value,
                    value_length,
                    unique_values[j],
                    unique_lengths[j])) {
                is_unique = 0;
                break;
            }
        }

        if (is_unique) {
            status = duplicate_string(
                dictionary[i].value,
                value_length,
                &unique_values[unique_count]
            );

            if (status != EXTRACT_OK) {
                free(unique_lengths);
                free_unique_values(unique_values, unique_count);
                return status;
            }

            unique_lengths[unique_count] = value_length;
            ++unique_count;
        }
    }

    free(unique_lengths);
    *out_values = unique_values;
    *out_count = unique_count;

    return EXTRACT_OK;
}

int main(void)
{
    const DictionaryEntry dictionary[] = {
        {"first", "apple", sizeof("apple")},
        {"second", "banana", sizeof("banana")},
        {"third", "apple", sizeof("apple")},
        {"fourth", "orange", sizeof("orange")},
        {"fifth", "banana", sizeof("banana")}
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