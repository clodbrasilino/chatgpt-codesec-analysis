#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    const char *key;
    const char *value;
    size_t value_length;
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

static int contains_null_byte(const char *value, size_t length)
{
    size_t i;

    for (i = 0; i < length; ++i) {
        if (value[i] == '\0') {
            return 1;
        }
    }

    return 0;
}

static int values_equal(
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

static UniqueStatus duplicate_value(
    const char *source,
    size_t length,
    char **destination)
{
    char *copy;
    size_t i;

    if (source == NULL || destination == NULL) {
        return UNIQUE_INVALID_ARGUMENT;
    }

    *destination = NULL;

    if (length == SIZE_MAX) {
        return UNIQUE_SIZE_OVERFLOW;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return UNIQUE_OUT_OF_MEMORY;
    }

    for (i = 0; i < length; ++i) {
        copy[i] = source[i];
    }

    copy[length] = '\0';
    *destination = copy;

    return UNIQUE_SUCCESS;
}

UniqueStatus extract_unique_values(
    const Dictionary *dictionary,
    char ***out_values,
    size_t *out_count)
{
    char **unique_values;
    size_t *unique_lengths;
    size_t unique_count;
    size_t i;
    size_t j;

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
        const DictionaryEntry *entry = &dictionary->entries[i];

        if (entry->key == NULL || entry->value == NULL) {
            return UNIQUE_INVALID_ARGUMENT;
        }

        if (contains_null_byte(entry->value, entry->value_length)) {
            return UNIQUE_INVALID_ARGUMENT;
        }
    }

    if (dictionary->count > SIZE_MAX / sizeof(*unique_values) ||
        dictionary->count > SIZE_MAX / sizeof(*unique_lengths)) {
        return UNIQUE_SIZE_OVERFLOW;
    }

    unique_values = calloc(dictionary->count, sizeof(*unique_values));
    if (unique_values == NULL) {
        return UNIQUE_OUT_OF_MEMORY;
    }

    unique_lengths = malloc(dictionary->count * sizeof(*unique_lengths));
    if (unique_lengths == NULL) {
        free(unique_values);
        return UNIQUE_OUT_OF_MEMORY;
    }

    unique_count = 0;

    for (i = 0; i < dictionary->count; ++i) {
        const DictionaryEntry *entry = &dictionary->entries[i];
        int found = 0;

        for (j = 0; j < unique_count; ++j) {
            if (values_equal(
                    entry->value,
                    entry->value_length,
                    unique_values[j],
                    unique_lengths[j])) {
                found = 1;
                break;
            }
        }

        if (!found) {
            UniqueStatus status = duplicate_value(
                entry->value,
                entry->value_length,
                &unique_values[unique_count]);

            if (status != UNIQUE_SUCCESS) {
                free(unique_lengths);
                free_unique_values(unique_values, unique_count);
                return status;
            }

            unique_lengths[unique_count] = entry->value_length;
            ++unique_count;
        }
    }

    free(unique_lengths);

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
        {"first", "apple", sizeof("apple") - 1},
        {"second", "banana", sizeof("banana") - 1},
        {"third", "apple", sizeof("apple") - 1},
        {"fourth", "orange", sizeof("orange") - 1},
        {"fifth", "banana", sizeof("banana") - 1}
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
        if (fprintf(
                stderr,
                "Extraction failed: %s\n",
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