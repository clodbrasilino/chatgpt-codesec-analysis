#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    size_t key_length;
    char *value;
    size_t value_length;
} Entry;

typedef struct {
    Entry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

static char *duplicate_string(const char *source, size_t length)
{
    char *copy;

    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    if (length != 0U) {
        memcpy(copy, source, length);
    }

    copy[length] = '\0';
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

static size_t dictionary_find(const Dictionary *dictionary,
                              const char *key,
                              size_t key_length)
{
    size_t index;

    if (dictionary == NULL || key == NULL) {
        return SIZE_MAX;
    }

    for (index = 0U; index < dictionary->size; ++index) {
        const Entry *entry = &dictionary->entries[index];

        if (entry->key != NULL &&
            entry->key_length == key_length &&
            (key_length == 0U ||
             memcmp(entry->key, key, key_length) == 0)) {
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

static int dictionary_set_n(Dictionary *dictionary,
                            const char *key,
                            size_t key_length,
                            const char *value,
                            size_t value_length)
{
    size_t index;
    char *key_copy;
    char *value_copy;

    if (dictionary == NULL || key == NULL || value == NULL ||
        key_length == SIZE_MAX || value_length == SIZE_MAX) {
        return -1;
    }

    index = dictionary_find(dictionary, key, key_length);
    if (index != SIZE_MAX) {
        value_copy = duplicate_string(value, value_length);
        if (value_copy == NULL) {
            return -1;
        }

        free(dictionary->entries[index].value);
        dictionary->entries[index].value = value_copy;
        dictionary->entries[index].value_length = value_length;
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

    key_copy = duplicate_string(key, key_length);
    if (key_copy == NULL) {
        return -1;
    }

    value_copy = duplicate_string(value, value_length);
    if (value_copy == NULL) {
        free(key_copy);
        return -1;
    }

    dictionary->entries[dictionary->size].key = key_copy;
    dictionary->entries[dictionary->size].key_length = key_length;
    dictionary->entries[dictionary->size].value = value_copy;
    dictionary->entries[dictionary->size].value_length = value_length;
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
        const Entry *entry = &source->entries[index];

        if (entry->key == NULL || entry->value == NULL ||
            entry->key_length == SIZE_MAX ||
            entry->value_length == SIZE_MAX) {
            return -1;
        }

        if (dictionary_set_n(destination,
                             entry->key,
                             entry->key_length,
                             entry->value,
                             entry->value_length) != 0) {
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

    if (first == NULL || second == NULL || third == NULL || result == NULL ||
        result == first || result == second || result == third) {
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

static int write_quoted(FILE *stream, const char *text, size_t length)
{
    size_t index;

    if (stream == NULL || text == NULL || length == SIZE_MAX) {
        return -1;
    }

    if (fputc('"', stream) == EOF) {
        return -1;
    }

    for (index = 0U; index < length; ++index) {
        unsigned char character = (unsigned char)text[index];

        switch (character) {
        case '"':
            if (fputs("\\\"", stream) == EOF) {
                return -1;
            }
            break;
        case '\\':
            if (fputs("\\\\", stream) == EOF) {
                return -1;
            }
            break;
        case '\b':
            if (fputs("\\b", stream) == EOF) {
                return -1;
            }
            break;
        case '\f':
            if (fputs("\\f", stream) == EOF) {
                return -1;
            }
            break;
        case '\n':
            if (fputs("\\n", stream) == EOF) {
                return -1;
            }
            break;
        case '\r':
            if (fputs("\\r", stream) == EOF) {
                return -1;
            }
            break;
        case '\t':
            if (fputs("\\t", stream) == EOF) {
                return -1;
            }
            break;
        default:
            if (character < 0x20U) {
                if (fprintf(stream, "\\u%04x", (unsigned int)character) < 0) {
                    return -1;
                }
            } else if (fputc((int)character, stream) == EOF) {
                return -1;
            }
            break;
        }
    }

    return fputc('"', stream) == EOF ? -1 : 0;
}

static int dictionary_print(const Dictionary *dictionary)
{
    size_t index;

    if (dictionary == NULL) {
        return -1;
    }

    if (fputc('{', stdout) == EOF) {
        return -1;
    }

    for (index = 0U; index < dictionary->size; ++index) {
        const Entry *entry = &dictionary->entries[index];

        if (entry->key == NULL || entry->value == NULL) {
            return -1;
        }

        if (index != 0U && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (write_quoted(stdout, entry->key, entry->key_length) != 0 ||
            fputs(": ", stdout) == EOF ||
            write_quoted(stdout, entry->value, entry->value_length) != 0) {
            return -1;
        }
    }

    return fputs("}\n", stdout) == EOF ? -1 : 0;
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

    if (dictionary_set_n(&first, "name", sizeof("name") - 1U,
                         "Alice", sizeof("Alice") - 1U) != 0 ||
        dictionary_set_n(&first, "city", sizeof("city") - 1U,
                         "Paris", sizeof("Paris") - 1U) != 0 ||
        dictionary_set_n(&second, "age", sizeof("age") - 1U,
                         "30", sizeof("30") - 1U) != 0 ||
        dictionary_set_n(&second, "city", sizeof("city") - 1U,
                         "London", sizeof("London") - 1U) != 0 ||
        dictionary_set_n(&third, "role", sizeof("role") - 1U,
                         "Developer", sizeof("Developer") - 1U) != 0 ||
        dictionary_set_n(&third, "age", sizeof("age") - 1U,
                         "31", sizeof("31") - 1U) != 0) {
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