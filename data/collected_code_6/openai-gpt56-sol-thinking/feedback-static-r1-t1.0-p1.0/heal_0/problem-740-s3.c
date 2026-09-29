#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    size_t count;
} Dictionary;

static void dictionary_destroy(Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL) {
        return;
    }

    for (i = 0; i < dictionary->count; ++i) {
        free(dictionary->entries[i].key);
        free(dictionary->entries[i].value);
    }

    free(dictionary->entries);
    free(dictionary);
}

static char *copy_string(const char *source)
{
    size_t length;
    char *copy;

    if (source == NULL) {
        errno = EINVAL;
        return NULL;
    }

    length = strlen(source);
    if (length == SIZE_MAX) {
        errno = EOVERFLOW;
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    memcpy(copy, source, length + 1);
    return copy;
}

static DictionaryEntry *dictionary_find(Dictionary *dictionary, const char *key)
{
    size_t i;

    for (i = 0; i < dictionary->count; ++i) {
        if (strcmp(dictionary->entries[i].key, key) == 0) {
            return &dictionary->entries[i];
        }
    }

    return NULL;
}

static Dictionary *tuple_to_dictionary(const char *const tuple[], size_t element_count)
{
    Dictionary *dictionary;
    size_t pair_count;
    size_t i;

    if ((element_count > 0 && tuple == NULL) || element_count % 2 != 0) {
        errno = EINVAL;
        return NULL;
    }

    for (i = 0; i < element_count; ++i) {
        if (tuple[i] == NULL) {
            errno = EINVAL;
            return NULL;
        }
    }

    dictionary = calloc(1, sizeof(*dictionary));
    if (dictionary == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    pair_count = element_count / 2;
    if (pair_count > SIZE_MAX / sizeof(*dictionary->entries)) {
        dictionary_destroy(dictionary);
        errno = EOVERFLOW;
        return NULL;
    }

    if (pair_count > 0) {
        dictionary->entries = calloc(pair_count, sizeof(*dictionary->entries));
        if (dictionary->entries == NULL) {
            dictionary_destroy(dictionary);
            errno = ENOMEM;
            return NULL;
        }
    }

    for (i = 0; i < element_count; i += 2) {
        DictionaryEntry *existing;
        char *key;
        char *value;

        existing = dictionary_find(dictionary, tuple[i]);
        value = copy_string(tuple[i + 1]);
        if (value == NULL) {
            dictionary_destroy(dictionary);
            return NULL;
        }

        if (existing != NULL) {
            free(existing->value);
            existing->value = value;
            continue;
        }

        key = copy_string(tuple[i]);
        if (key == NULL) {
            free(value);
            dictionary_destroy(dictionary);
            return NULL;
        }

        dictionary->entries[dictionary->count].key = key;
        dictionary->entries[dictionary->count].value = value;
        ++dictionary->count;
    }

    return dictionary;
}

int main(void)
{
    const char *const tuple[] = {
        "name", "Alice",
        "age", "30",
        "city", "London"
    };
    const size_t element_count = sizeof(tuple) / sizeof(tuple[0]);
    Dictionary *dictionary;
    size_t i;

    dictionary = tuple_to_dictionary(tuple, element_count);
    if (dictionary == NULL) {
        perror("tuple_to_dictionary");
        return EXIT_FAILURE;
    }

    for (i = 0; i < dictionary->count; ++i) {
        if (printf("%s = %s\n",
                   dictionary->entries[i].key,
                   dictionary->entries[i].value) < 0) {
            dictionary_destroy(dictionary);
            return EXIT_FAILURE;
        }
    }

    dictionary_destroy(dictionary);
    return EXIT_SUCCESS;
}