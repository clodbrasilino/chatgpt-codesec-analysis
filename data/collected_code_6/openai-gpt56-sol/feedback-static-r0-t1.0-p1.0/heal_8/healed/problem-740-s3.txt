#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValue;

typedef struct {
    KeyValue *entries;
    size_t count;
} Dictionary;

static char *duplicate_string(const char *source, size_t maximum_length)
{
    const char *terminator;
    size_t length;
    size_t allocation_size;
    char *copy;

    if (source == NULL || maximum_length == 0U) {
        return NULL;
    }

    terminator = memchr(source, '\0', maximum_length);
    if (terminator == NULL) {
        return NULL;
    }

    length = (size_t)(terminator - source);
    if (length > SIZE_MAX - 1U) {
        return NULL;
    }

    allocation_size = length + 1U;
    copy = malloc(allocation_size);
    if (copy == NULL) {
        return NULL;
    }

    if (length > 0U) {
        memcpy(copy, source, length);
    }
    copy[length] = '\0';

    return copy;
}

static void free_dictionary(Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL) {
        return;
    }

    for (i = 0U; i < dictionary->count; ++i) {
        free(dictionary->entries[i].key);
        free(dictionary->entries[i].value);
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->count = 0U;
}

static int tuple_to_dictionary(const char *const tuple[],
                               size_t tuple_size,
                               size_t maximum_string_length,
                               Dictionary *dictionary)
{
    Dictionary result = {NULL, 0U};
    size_t pair_count;
    size_t i;

    if (dictionary == NULL ||
        (tuple == NULL && tuple_size != 0U) ||
        maximum_string_length == 0U ||
        tuple_size % 2U != 0U) {
        return -1;
    }

    pair_count = tuple_size / 2U;

    if (pair_count == 0U) {
        free_dictionary(dictionary);
        return 0;
    }

    if (pair_count > SIZE_MAX / sizeof(*result.entries)) {
        return -1;
    }

    result.entries = calloc(pair_count, sizeof(*result.entries));
    if (result.entries == NULL) {
        return -1;
    }

    result.count = pair_count;

    for (i = 0U; i < pair_count; ++i) {
        size_t key_index = i * 2U;
        size_t value_index = key_index + 1U;

        if (tuple[key_index] == NULL || tuple[value_index] == NULL) {
            free_dictionary(&result);
            return -1;
        }

        result.entries[i].key =
            duplicate_string(tuple[key_index], maximum_string_length);
        if (result.entries[i].key == NULL) {
            free_dictionary(&result);
            return -1;
        }

        result.entries[i].value =
            duplicate_string(tuple[value_index], maximum_string_length);
        if (result.entries[i].value == NULL) {
            free_dictionary(&result);
            return -1;
        }
    }

    free_dictionary(dictionary);
    *dictionary = result;

    return 0;
}

int main(void)
{
    const char *tuple[] = {
        "name", "Alice",
        "age", "30",
        "city", "London"
    };
    Dictionary dictionary = {NULL, 0U};
    const size_t maximum_string_length = 1024U;
    const size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    size_t i;

    if (tuple_to_dictionary(tuple,
                            tuple_size,
                            maximum_string_length,
                            &dictionary) != 0) {
        fputs("Failed to convert tuple to dictionary.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < dictionary.count; ++i) {
        if (printf("%s: %s\n",
                   dictionary.entries[i].key,
                   dictionary.entries[i].value) < 0) {
            free_dictionary(&dictionary);
            return EXIT_FAILURE;
        }
    }

    free_dictionary(&dictionary);
    return EXIT_SUCCESS;
}