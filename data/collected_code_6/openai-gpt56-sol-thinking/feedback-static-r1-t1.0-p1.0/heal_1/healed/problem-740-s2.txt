#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *data;
    size_t length;
} StringView;

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair *pairs;
    size_t count;
} Dictionary;

#define STRING_VIEW_LITERAL(value) { (value), sizeof(value) - 1U }

static char *copy_string(const char *source, size_t length)
{
    char *copy;
    size_t i;

    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    for (i = 0U; i < length; ++i) {
        copy[i] = source[i];
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
        free(dictionary->pairs[i].key);
        free(dictionary->pairs[i].value);
    }

    free(dictionary->pairs);
    dictionary->pairs = NULL;
    dictionary->count = 0U;
}

static int tuple_to_dictionary(const StringView tuple[],
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
        const StringView *key = &tuple[i * 2U];
        const StringView *value = &tuple[i * 2U + 1U];

        if (key->data == NULL || value->data == NULL) {
            free_dictionary(dictionary);
            return -1;
        }

        dictionary->pairs[i].key = copy_string(key->data, key->length);
        if (dictionary->pairs[i].key == NULL) {
            free_dictionary(dictionary);
            return -1;
        }

        dictionary->pairs[i].value = copy_string(value->data, value->length);
        if (dictionary->pairs[i].value == NULL) {
            free_dictionary(dictionary);
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    const StringView tuple[] = {
        STRING_VIEW_LITERAL("name"),
        STRING_VIEW_LITERAL("Alice"),
        STRING_VIEW_LITERAL("age"),
        STRING_VIEW_LITERAL("30"),
        STRING_VIEW_LITERAL("city"),
        STRING_VIEW_LITERAL("London")
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