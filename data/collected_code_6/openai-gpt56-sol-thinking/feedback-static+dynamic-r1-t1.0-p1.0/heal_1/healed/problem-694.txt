#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *key;
    size_t key_length;
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

static bool is_valid_text(const char *text, size_t length)
{
    size_t i;

    if (text == NULL) {
        return false;
    }

    for (i = 0; i < length; ++i) {
        if (text[i] == '\0') {
            return false;
        }
    }

    return true;
}

static bool values_equal(
    const char *left,
    size_t left_length,
    const char *right,
    size_t right_length)
{
    size_t i;

    if (left_length != right_length) {
        return false;
    }

    for (i = 0; i < left_length; ++i) {
        if (left[i] != right[i]) {
            return false;
        }
    }

    return true;
}

static UniqueStatus duplicate_text(
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
    size_t unique_count = 0;
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

        if (!is_valid_text(entry->key, entry->key_length) ||
            !is_valid_text(entry->value, entry->value_length)) {
            return UNIQUE_INVALID_ARGUMENT;
        }
    }

    if (dictionary->count > SIZE_MAX / sizeof(*unique_values)) {
        return UNIQUE_SIZE_OVERFLOW;
    }

    unique_values = calloc(dictionary->count, sizeof(*unique_values));
    if (unique_values == NULL) {
        return UNIQUE_OUT_OF_MEMORY;
    }

    for (i = 0; i < dictionary->count; ++i) {
        const DictionaryEntry *current = &dictionary->entries[i];
        bool found = false;

        for (j = 0; j < i; ++j) {
            const DictionaryEntry *previous = &dictionary->entries[j];

            if (values_equal(
                    current->value,
                    current->value_length,
                    previous->value,
                    previous->value_length)) {
                found = true;
                break;
            }
        }

        if (!found) {
            UniqueStatus status = duplicate_text(
                current->value,
                current->value_length,
                &unique_values[unique_count]);

            if (status != UNIQUE_SUCCESS) {
                free_unique_values(unique_values, unique_count);
                return status;
            }

            ++unique_count;
        }
    }

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
        {
            "first", sizeof("first") - 1,
            "apple", sizeof("apple") - 1
        },
        {
            "second", sizeof("second") - 1,
            "banana", sizeof("banana") - 1
        },
        {
            "third", sizeof("third") - 1,
            "apple", sizeof("apple") - 1
        },
        {
            "fourth", sizeof("fourth") - 1,
            "orange", sizeof("orange") - 1
        },
        {
            "fifth", sizeof("fifth") - 1,
            "banana", sizeof("banana") - 1
        }
    };
    const Dictionary dictionary = {
        entries,
        sizeof(entries) / sizeof(entries[0])
    };
    char **unique_values = NULL;
    size_t unique_count = 0;
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