#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair *pairs;
    size_t count;
} Dictionary;

static char *copy_string(const char *source)
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

static void free_dictionary(Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL) {
        return;
    }

    for (i = 0U; i < dictionary->count; ++i) {
        free(dictionary->pairs[i].key);
        free(dictionary->pairs[i].value);
    }

    free(dictionary->pairs);
    dictionary->pairs = NULL;
    dictionary->count = 0U;
}

static int tuple_to_dictionary(const char *const tuple[],
                               size_t tuple_length,
                               Dictionary *dictionary)
{
    size_t pair_count;
    size_t i;

    if (dictionary == NULL) {
        return -1;
    }

    dictionary->pairs = NULL;
    dictionary->count = 0U;

    if ((tuple_length % 2U) != 0U) {
        return -1;
    }

    if (tuple_length == 0U) {
        return 0;
    }

    if (tuple == NULL) {
        return -1;
    }

    pair_count = tuple_length / 2U;
    if (pair_count > SIZE_MAX / sizeof(*dictionary->pairs)) {
        return -1;
    }

    dictionary->pairs = calloc(pair_count, sizeof(*dictionary->pairs));
    if (dictionary->pairs == NULL) {
        return -1;
    }

    dictionary->count = pair_count;

    for (i = 0U; i < pair_count; ++i) {
        const char *key = tuple[i * 2U];
        const char *value = tuple[i * 2U + 1U];

        if (key == NULL || value == NULL) {
            free_dictionary(dictionary);
            return -1;
        }

        dictionary->pairs[i].key = copy_string(key);
        if (dictionary->pairs[i].key == NULL) {
            free_dictionary(dictionary);
            return -1;
        }

        dictionary->pairs[i].value = copy_string(value);
        if (dictionary->pairs[i].value == NULL) {
            free_dictionary(dictionary);
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    const char *tuple[] = {
        "name", "Alice",
        "age", "30",
        "city", "London"
    };
    const size_t tuple_length = sizeof(tuple) / sizeof(tuple[0]);
    Dictionary dictionary;
    size_t i;

    if (tuple_to_dictionary(tuple, tuple_length, &dictionary) != 0) {
        fputs("Failed to convert tuple to dictionary.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < dictionary.count; ++i) {
        printf("%s: %s\n",
               dictionary.pairs[i].key,
               dictionary.pairs[i].value);
    }

    free_dictionary(&dictionary);
    return EXIT_SUCCESS;
}