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
    size_t size;
} Dictionary;

typedef enum {
    DICTIONARY_OK,
    DICTIONARY_INVALID_ARGUMENT,
    DICTIONARY_ALLOCATION_FAILURE
} DictionaryStatus;

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

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, source, length + 1);
    return copy;
}

static void dictionary_destroy(Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL) {
        return;
    }

    for (i = 0; i < dictionary->size; ++i) {
        free(dictionary->entries[i].key);
        free(dictionary->entries[i].value);
    }

    free(dictionary->entries);
    free(dictionary);
}

static Dictionary *tuple_to_dictionary(
    const char *const tuple[],
    size_t element_count,
    DictionaryStatus *status)
{
    Dictionary *dictionary;
    size_t pair_count;
    size_t i;

    if (status != NULL) {
        *status = DICTIONARY_INVALID_ARGUMENT;
    }

    if ((tuple == NULL && element_count != 0) || element_count % 2 != 0) {
        return NULL;
    }

    dictionary = calloc(1, sizeof(*dictionary));
    if (dictionary == NULL) {
        if (status != NULL) {
            *status = DICTIONARY_ALLOCATION_FAILURE;
        }
        return NULL;
    }

    pair_count = element_count / 2;

    if (pair_count > SIZE_MAX / sizeof(*dictionary->entries)) {
        dictionary_destroy(dictionary);
        if (status != NULL) {
            *status = DICTIONARY_ALLOCATION_FAILURE;
        }
        return NULL;
    }

    if (pair_count != 0) {
        dictionary->entries = calloc(pair_count, sizeof(*dictionary->entries));
        if (dictionary->entries == NULL) {
            dictionary_destroy(dictionary);
            if (status != NULL) {
                *status = DICTIONARY_ALLOCATION_FAILURE;
            }
            return NULL;
        }
    }

    for (i = 0; i < pair_count; ++i) {
        const char *key = tuple[i * 2];
        const char *value = tuple[i * 2 + 1];
        size_t j;

        if (key == NULL || value == NULL) {
            dictionary_destroy(dictionary);
            if (status != NULL) {
                *status = DICTIONARY_INVALID_ARGUMENT;
            }
            return NULL;
        }

        for (j = 0; j < dictionary->size; ++j) {
            if (strcmp(dictionary->entries[j].key, key) == 0) {
                char *new_value = copy_string(value);

                if (new_value == NULL) {
                    dictionary_destroy(dictionary);
                    if (status != NULL) {
                        *status = DICTIONARY_ALLOCATION_FAILURE;
                    }
                    return NULL;
                }

                free(dictionary->entries[j].value);
                dictionary->entries[j].value = new_value;
                break;
            }
        }

        if (j == dictionary->size) {
            char *new_key = copy_string(key);
            char *new_value;

            if (new_key == NULL) {
                dictionary_destroy(dictionary);
                if (status != NULL) {
                    *status = DICTIONARY_ALLOCATION_FAILURE;
                }
                return NULL;
            }

            new_value = copy_string(value);
            if (new_value == NULL) {
                free(new_key);
                dictionary_destroy(dictionary);
                if (status != NULL) {
                    *status = DICTIONARY_ALLOCATION_FAILURE;
                }
                return NULL;
            }

            dictionary->entries[dictionary->size].key = new_key;
            dictionary->entries[dictionary->size].value = new_value;
            ++dictionary->size;
        }
    }

    if (status != NULL) {
        *status = DICTIONARY_OK;
    }

    return dictionary;
}

int main(void)
{
    const char *tuple[] = {
        "name", "Alice",
        "age", "30",
        "city", "New York"
    };
    const size_t element_count = sizeof(tuple) / sizeof(tuple[0]);
    DictionaryStatus status;
    Dictionary *dictionary;
    size_t i;

    dictionary = tuple_to_dictionary(tuple, element_count, &status);
    if (dictionary == NULL) {
        if (status == DICTIONARY_INVALID_ARGUMENT) {
            fprintf(stderr, "Invalid tuple\n");
        } else {
            fprintf(stderr, "Unable to allocate dictionary\n");
        }
        return EXIT_FAILURE;
    }

    for (i = 0; i < dictionary->size; ++i) {
        if (printf("%s: %s\n",
                   dictionary->entries[i].key,
                   dictionary->entries[i].value) < 0) {
            dictionary_destroy(dictionary);
            return EXIT_FAILURE;
        }
    }

    if (fflush(stdout) == EOF) {
        dictionary_destroy(dictionary);
        return EXIT_FAILURE;
    }

    dictionary_destroy(dictionary);
    return EXIT_SUCCESS;
}