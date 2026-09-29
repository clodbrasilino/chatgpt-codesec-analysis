#include <stddef.h>
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

static int copy_string(StringView source, char **destination)
{
    char *copy;
    size_t i;

    if (destination == NULL) {
        return -1;
    }

    *destination = NULL;

    if (source.data == NULL || source.length == SIZE_MAX) {
        return -1;
    }

    copy = malloc(source.length + 1U);
    if (copy == NULL) {
        return -1;
    }

    for (i = 0U; i < source.length; ++i) {
        if (source.data[i] == '\0') {
            free(copy);
            return -1;
        }

        copy[i] = source.data[i];
    }

    copy[source.length] = '\0';
    *destination = copy;
    return 0;
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
        if (copy_string(tuple[i * 2U],
                        &dictionary->pairs[i].key) != 0) {
            free_dictionary(dictionary);
            return -1;
        }

        if (copy_string(tuple[i * 2U + 1U],
                        &dictionary->pairs[i].value) != 0) {
            free_dictionary(dictionary);
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    const StringView tuple[] = {
        { "name", sizeof("name") - 1U },
        { "Alice", sizeof("Alice") - 1U },
        { "age", sizeof("age") - 1U },
        { "30", sizeof("30") - 1U },
        { "city", sizeof("city") - 1U },
        { "London", sizeof("London") - 1U }
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