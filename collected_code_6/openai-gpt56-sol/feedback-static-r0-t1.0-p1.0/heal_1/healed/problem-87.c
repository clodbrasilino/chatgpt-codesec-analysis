#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} Entry;

typedef struct {
    Entry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

static char *duplicate_string(const char *source)
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

static int dictionary_init(Dictionary *dictionary)
{
    if (dictionary == NULL) {
        return -1;
    }

    dictionary->entries = NULL;
    dictionary->size = 0U;
    dictionary->capacity = 0U;
    return 0;
}

static void dictionary_destroy(Dictionary *dictionary)
{
    size_t index;

    if (dictionary == NULL) {
        return;
    }

    for (index = 0U; index < dictionary->size; ++index) {
        free(dictionary->entries[index].key);
        free(dictionary->entries[index].value);
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->size = 0U;
    dictionary->capacity = 0U;
}

static size_t dictionary_find(const Dictionary *dictionary, const char *key)
{
    size_t index;

    if (dictionary == NULL || key == NULL) {
        return SIZE_MAX;
    }

    for (index = 0U; index < dictionary->size; ++index) {
        if (strcmp(dictionary->entries[index].key, key) == 0) {
            return index;
        }
    }

    return SIZE_MAX;
}

static int dictionary_reserve(Dictionary *dictionary, size_t capacity)
{
    Entry *resized;

    if (dictionary == NULL) {
        return -1;
    }

    if (capacity <= dictionary->capacity) {
        return 0;
    }

    if (capacity > SIZE_MAX / sizeof(*dictionary->entries)) {
        return -1;
    }

    resized = realloc(dictionary->entries,
                      capacity * sizeof(*dictionary->entries));
    if (resized == NULL) {
        return -1;
    }

    dictionary->entries = resized;
    dictionary->capacity = capacity;
    return 0;
}

static int dictionary_set(Dictionary *dictionary,
                          const char *key,
                          const char *value)
{
    size_t index;
    char *key_copy;
    char *value_copy;

    if (dictionary == NULL || key == NULL || value == NULL) {
        return -1;
    }

    index = dictionary_find(dictionary, key);
    if (index != SIZE_MAX) {
        value_copy = duplicate_string(value);
        if (value_copy == NULL) {
            return -1;
        }

        free(dictionary->entries[index].value);
        dictionary->entries[index].value = value_copy;
        return 0;
    }

    if (dictionary->size == dictionary->capacity) {
        size_t new_capacity;

        if (dictionary->capacity == 0U) {
            new_capacity = 4U;
        } else {
            if (dictionary->capacity > SIZE_MAX / 2U) {
                return -1;
            }
            new_capacity = dictionary->capacity * 2U;
        }

        if (dictionary_reserve(dictionary, new_capacity) != 0) {
            return -1;
        }
    }

    key_copy = duplicate_string(key);
    if (key_copy == NULL) {
        return -1;
    }

    value_copy = duplicate_string(value);
    if (value_copy == NULL) {
        free(key_copy);
        return -1;
    }

    dictionary->entries[dictionary->size].key = key_copy;
    dictionary->entries[dictionary->size].value = value_copy;
    ++dictionary->size;
    return 0;
}

static int dictionary_copy_into(Dictionary *destination,
                                const Dictionary *source)
{
    size_t index;

    if (destination == NULL || source == NULL) {
        return -1;
    }

    for (index = 0U; index < source->size; ++index) {
        if (dictionary_set(destination,
                           source->entries[index].key,
                           source->entries[index].value) != 0) {
            return -1;
        }
    }

    return 0;
}

static int merge_three_dictionaries(const Dictionary *first,
                                    const Dictionary *second,
                                    const Dictionary *third,
                                    Dictionary *result)
{
    Dictionary merged;

    if (first == NULL || second == NULL || third == NULL || result == NULL) {
        return -1;
    }

    if (dictionary_init(&merged) != 0) {
        return -1;
    }

    if (dictionary_copy_into(&merged, first) != 0 ||
        dictionary_copy_into(&merged, second) != 0 ||
        dictionary_copy_into(&merged, third) != 0) {
        dictionary_destroy(&merged);
        return -1;
    }

    dictionary_destroy(result);
    *result = merged;
    return 0;
}

static int dictionary_print(const Dictionary *dictionary)
{
    size_t index;

    if (dictionary == NULL) {
        return -1;
    }

    if (putchar('{') == EOF) {
        return -1;
    }

    for (index = 0U; index < dictionary->size; ++index) {
        if (index != 0U && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (printf("\"%s\": \"%s\"",
                   dictionary->entries[index].key,
                   dictionary->entries[index].value) < 0) {
            return -1;
        }
    }

    if (puts("}") == EOF) {
        return -1;
    }

    return 0;
}

int main(void)
{
    Dictionary first;
    Dictionary second;
    Dictionary third;
    Dictionary merged;
    int status = EXIT_FAILURE;

    if (dictionary_init(&first) != 0) {
        return EXIT_FAILURE;
    }

    if (dictionary_init(&second) != 0) {
        dictionary_destroy(&first);
        return EXIT_FAILURE;
    }

    if (dictionary_init(&third) != 0) {
        dictionary_destroy(&second);
        dictionary_destroy(&first);
        return EXIT_FAILURE;
    }

    if (dictionary_init(&merged) != 0) {
        dictionary_destroy(&third);
        dictionary_destroy(&second);
        dictionary_destroy(&first);
        return EXIT_FAILURE;
    }

    if (dictionary_set(&first, "name", "Alice") != 0 ||
        dictionary_set(&first, "city", "Paris") != 0 ||
        dictionary_set(&second, "age", "30") != 0 ||
        dictionary_set(&second, "city", "London") != 0 ||
        dictionary_set(&third, "role", "Developer") != 0 ||
        dictionary_set(&third, "age", "31") != 0) {
        goto cleanup;
    }

    if (merge_three_dictionaries(&first, &second, &third, &merged) != 0) {
        goto cleanup;
    }

    if (dictionary_print(&merged) != 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    dictionary_destroy(&merged);
    dictionary_destroy(&third);
    dictionary_destroy(&second);
    dictionary_destroy(&first);
    return status;
}