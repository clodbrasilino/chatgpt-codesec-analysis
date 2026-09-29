#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static char *copy_string(const char *source, size_t length)
{
    char *copy;

    if (source == NULL) {
        errno = EINVAL;
        return NULL;
    }

    if (length == SIZE_MAX) {
        errno = EOVERFLOW;
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    if (length > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
    }

    copy[length] = '\0';
    return copy;
}

static DictionaryEntry *dictionary_find(
    Dictionary *dictionary,
    const char *key,
    size_t key_length)
{
    size_t i;

    if (dictionary == NULL || key == NULL) {
        return NULL;
    }

    for (i = 0; i < dictionary->count; ++i) {
        DictionaryEntry *entry = &dictionary->entries[i];

        if (entry->key_length == key_length &&
            memcmp(entry->key, key, key_length) == 0) {
            return entry;
        }
    }

    return NULL;
}

static Dictionary *tuple_to_dictionary(
    const TupleElement tuple[],
    size_t element_count)
{
    Dictionary *dictionary;
    size_t pair_count;
    size_t i;

    if ((element_count > 0 && tuple == NULL) ||
        element_count % 2 != 0) {
        errno = EINVAL;
        return NULL;
    }

    for (i = 0; i < element_count; ++i) {
        if (tuple[i].data == NULL) {
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
        dictionary->entries =
            calloc(pair_count, sizeof(*dictionary->entries));

        if (dictionary->entries == NULL) {
            dictionary_destroy(dictionary);
            errno = ENOMEM;
            return NULL;
        }
    }

    for (i = 0; i < element_count; i += 2) {
        const TupleElement *key_element = &tuple[i];
        const TupleElement *value_element = &tuple[i + 1];
        DictionaryEntry *existing;
        char *key;
        char *value;
        int saved_errno;

        existing = dictionary_find(
            dictionary,
            key_element->data,
            key_element->length);

        value = copy_string(
            value_element->data,
            value_element->length);

        if (value == NULL) {
            saved_errno = errno;
            dictionary_destroy(dictionary);
            errno = saved_errno;
            return NULL;
        }

        if (existing != NULL) {
            free(existing->value);
            existing->value = value;
            existing->value_length = value_element->length;
            continue;
        }

        key = copy_string(key_element->data, key_element->length);
        if (key == NULL) {
            saved_errno = errno;
            free(value);
            dictionary_destroy(dictionary);
            errno = saved_errno;
            return NULL;
        }

        dictionary->entries[dictionary->count].key = key;
        dictionary->entries[dictionary->count].key_length =
            key_element->length;
        dictionary->entries[dictionary->count].value = value;
        dictionary->entries[dictionary->count].value_length =
            value_element->length;
        ++dictionary->count;
    }

    return dictionary;
}

static int write_data(const char *data, size_t length)
{
    if (length == 0) {
        return 0;
    }

    return fwrite(data, 1, length, stdout) == length ? 0 : -1;
}

int main(void)
{
    static const TupleElement tuple[] = {
        { "name", sizeof("name") - 1 },
        { "Alice", sizeof("Alice") - 1 },
        { "age", sizeof("age") - 1 },
        { "30", sizeof("30") - 1 },
        { "city", sizeof("city") - 1 },
        { "London", sizeof("London") - 1 }
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
        /* Possible weaknesses found:
         *  Variable 'entry' can be declared as pointer to const [constVariablePointer]
         */
        DictionaryEntry *entry = &dictionary->entries[i];

        if (write_data(entry->key, entry->key_length) != 0 ||
            write_data(" = ", sizeof(" = ") - 1) != 0 ||
            write_data(entry->value, entry->value_length) != 0 ||
            fputc('\n', stdout) == EOF) {
            dictionary_destroy(dictionary);
            return EXIT_FAILURE;
        }
    }

    dictionary_destroy(dictionary);
    return EXIT_SUCCESS;
}