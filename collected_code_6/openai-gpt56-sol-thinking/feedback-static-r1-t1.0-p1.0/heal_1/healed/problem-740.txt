#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *data;
    size_t length;
} TupleElement;

typedef struct {
    char *key;
    size_t key_length;
    char *value;
    size_t value_length;
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

static char *copy_bytes(const char *source, size_t length)
{
    char *copy;
    size_t i;

    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    for (i = 0; i < length; ++i) {
        copy[i] = source[i];
    }

    copy[length] = '\0';
    return copy;
}

static int bytes_equal(
    const char *left,
    const char *right,
    size_t length)
{
    size_t i;

    for (i = 0; i < length; ++i) {
        if (left[i] != right[i]) {
            return 0;
        }
    }

    return 1;
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
    const TupleElement tuple[],
    size_t element_count,
    DictionaryStatus *status)
{
    Dictionary *dictionary;
    size_t pair_count;
    size_t i;

    if (status != NULL) {
        *status = DICTIONARY_INVALID_ARGUMENT;
    }

    if ((tuple == NULL && element_count != 0) ||
        element_count % 2 != 0) {
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
        dictionary->entries =
            calloc(pair_count, sizeof(*dictionary->entries));

        if (dictionary->entries == NULL) {
            dictionary_destroy(dictionary);
            if (status != NULL) {
                *status = DICTIONARY_ALLOCATION_FAILURE;
            }
            return NULL;
        }
    }

    for (i = 0; i < pair_count; ++i) {
        const TupleElement *key = &tuple[i * 2];
        const TupleElement *value = &tuple[i * 2 + 1];
        size_t j;

        if (key->data == NULL || value->data == NULL) {
            dictionary_destroy(dictionary);
            if (status != NULL) {
                *status = DICTIONARY_INVALID_ARGUMENT;
            }
            return NULL;
        }

        for (j = 0; j < dictionary->size; ++j) {
            DictionaryEntry *entry = &dictionary->entries[j];

            if (entry->key_length == key->length &&
                bytes_equal(entry->key, key->data, key->length)) {
                char *new_value = copy_bytes(value->data, value->length);

                if (new_value == NULL) {
                    dictionary_destroy(dictionary);
                    if (status != NULL) {
                        *status = DICTIONARY_ALLOCATION_FAILURE;
                    }
                    return NULL;
                }

                free(entry->value);
                entry->value = new_value;
                entry->value_length = value->length;
                break;
            }
        }

        if (j == dictionary->size) {
            DictionaryEntry *entry;
            char *new_key;
            char *new_value;

            new_key = copy_bytes(key->data, key->length);
            if (new_key == NULL) {
                dictionary_destroy(dictionary);
                if (status != NULL) {
                    *status = DICTIONARY_ALLOCATION_FAILURE;
                }
                return NULL;
            }

            new_value = copy_bytes(value->data, value->length);
            if (new_value == NULL) {
                free(new_key);
                dictionary_destroy(dictionary);
                if (status != NULL) {
                    *status = DICTIONARY_ALLOCATION_FAILURE;
                }
                return NULL;
            }

            entry = &dictionary->entries[dictionary->size];
            entry->key = new_key;
            entry->key_length = key->length;
            entry->value = new_value;
            entry->value_length = value->length;
            ++dictionary->size;
        }
    }

    if (status != NULL) {
        *status = DICTIONARY_OK;
    }

    return dictionary;
}

static int write_bytes(
    FILE *stream,
    const char *data,
    size_t length)
{
    if (length == 0) {
        return 1;
    }

    return fwrite(data, 1, length, stream) == length;
}

int main(void)
{
    const TupleElement tuple[] = {
        {"name", sizeof("name") - 1},
        {"Alice", sizeof("Alice") - 1},
        {"age", sizeof("age") - 1},
        {"30", sizeof("30") - 1},
        {"city", sizeof("city") - 1},
        {"New York", sizeof("New York") - 1}
    };
    const size_t element_count = sizeof(tuple) / sizeof(tuple[0]);
    DictionaryStatus status;
    Dictionary *dictionary;
    size_t i;

    dictionary = tuple_to_dictionary(tuple, element_count, &status);
    if (dictionary == NULL) {
        if (status == DICTIONARY_INVALID_ARGUMENT) {
            fputs("Invalid tuple\n", stderr);
        } else {
            fputs("Unable to allocate dictionary\n", stderr);
        }
        return EXIT_FAILURE;
    }

    for (i = 0; i < dictionary->size; ++i) {
        const DictionaryEntry *entry = &dictionary->entries[i];

        if (!write_bytes(stdout, entry->key, entry->key_length) ||
            fputs(": ", stdout) == EOF ||
            !write_bytes(stdout, entry->value, entry->value_length) ||
            fputc('\n', stdout) == EOF) {
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