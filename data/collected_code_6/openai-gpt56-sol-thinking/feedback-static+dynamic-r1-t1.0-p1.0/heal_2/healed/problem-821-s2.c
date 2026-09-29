#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *key;
    size_t key_length;
    char *value;
    size_t value_length;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    size_t count;
    size_t capacity;
} Dictionary;

static Dictionary *dictionary_create(void)
{
    return calloc(1, sizeof(Dictionary));
}

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

static char *duplicate_bytes(const char *source, size_t length)
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

static bool bytes_equal(
    const char *first,
    size_t first_length,
    const char *second,
    size_t second_length
)
{
    size_t i;

    if (first == NULL || second == NULL || first_length != second_length) {
        return false;
    }

    for (i = 0; i < first_length; ++i) {
        if (first[i] != second[i]) {
            return false;
        }
    }

    return true;
}

static bool dictionary_reserve(
    Dictionary *dictionary,
    size_t minimum_capacity
)
{
    size_t maximum_capacity;
    size_t new_capacity;
    DictionaryEntry *new_entries;

    if (dictionary == NULL) {
        return false;
    }

    if (minimum_capacity <= dictionary->capacity) {
        return true;
    }

    maximum_capacity = SIZE_MAX / sizeof(*dictionary->entries);
    if (minimum_capacity > maximum_capacity) {
        return false;
    }

    if (dictionary->capacity == 0) {
        new_capacity = maximum_capacity >= 4 ? 4 : minimum_capacity;
    } else {
        new_capacity = dictionary->capacity;
    }

    while (new_capacity < minimum_capacity) {
        if (new_capacity > maximum_capacity / 2) {
            new_capacity = minimum_capacity;
            break;
        }

        new_capacity *= 2;
    }

    new_entries = realloc(
        dictionary->entries,
        new_capacity * sizeof(*dictionary->entries)
    );

    if (new_entries == NULL) {
        return false;
    }

    dictionary->entries = new_entries;
    dictionary->capacity = new_capacity;
    return true;
}

static size_t dictionary_find(
    const Dictionary *dictionary,
    const char *key,
    size_t key_length
)
{
    size_t i;

    if (dictionary == NULL || key == NULL) {
        return SIZE_MAX;
    }

    for (i = 0; i < dictionary->count; ++i) {
        if (bytes_equal(
                dictionary->entries[i].key,
                dictionary->entries[i].key_length,
                key,
                key_length)) {
            return i;
        }
    }

    return SIZE_MAX;
}

static bool dictionary_set(
    Dictionary *dictionary,
    const char *key,
    size_t key_length,
    const char *value,
    size_t value_length
)
{
    size_t index;
    char *key_copy;
    char *value_copy;

    if (dictionary == NULL || key == NULL || value == NULL) {
        return false;
    }

    index = dictionary_find(dictionary, key, key_length);

    if (index != SIZE_MAX) {
        value_copy = duplicate_bytes(value, value_length);
        if (value_copy == NULL) {
            return false;
        }

        free(dictionary->entries[index].value);
        dictionary->entries[index].value = value_copy;
        dictionary->entries[index].value_length = value_length;
        return true;
    }

    if (dictionary->count == SIZE_MAX ||
        !dictionary_reserve(dictionary, dictionary->count + 1)) {
        return false;
    }

    key_copy = duplicate_bytes(key, key_length);
    if (key_copy == NULL) {
        return false;
    }

    value_copy = duplicate_bytes(value, value_length);
    if (value_copy == NULL) {
        free(key_copy);
        return false;
    }

    dictionary->entries[dictionary->count].key = key_copy;
    dictionary->entries[dictionary->count].key_length = key_length;
    dictionary->entries[dictionary->count].value = value_copy;
    dictionary->entries[dictionary->count].value_length = value_length;
    ++dictionary->count;

    return true;
}

static Dictionary *merge_dictionaries(
    const Dictionary *first,
    const Dictionary *second
)
{
    Dictionary *merged;
    size_t i;

    if (first == NULL || second == NULL) {
        return NULL;
    }

    merged = dictionary_create();
    if (merged == NULL) {
        return NULL;
    }

    for (i = 0; i < first->count; ++i) {
        if (!dictionary_set(
                merged,
                first->entries[i].key,
                first->entries[i].key_length,
                first->entries[i].value,
                first->entries[i].value_length)) {
            dictionary_destroy(merged);
            return NULL;
        }
    }

    for (i = 0; i < second->count; ++i) {
        if (!dictionary_set(
                merged,
                second->entries[i].key,
                second->entries[i].key_length,
                second->entries[i].value,
                second->entries[i].value_length)) {
            dictionary_destroy(merged);
            return NULL;
        }
    }

    return merged;
}

static bool print_quoted_bytes(
    FILE *stream,
    const char *text,
    size_t length
)
{
    static const char hexadecimal[] = "0123456789ABCDEF";
    size_t i;

    if (stream == NULL || text == NULL || fputc('"', stream) == EOF) {
        return false;
    }

    for (i = 0; i < length; ++i) {
        unsigned char current = (unsigned char)text[i];

        switch (current) {
            case '"':
                if (fputs("\\\"", stream) == EOF) {
                    return false;
                }
                break;

            case '\\':
                if (fputs("\\\\", stream) == EOF) {
                    return false;
                }
                break;

            case '\b':
                if (fputs("\\b", stream) == EOF) {
                    return false;
                }
                break;

            case '\f':
                if (fputs("\\f", stream) == EOF) {
                    return false;
                }
                break;

            case '\n':
                if (fputs("\\n", stream) == EOF) {
                    return false;
                }
                break;

            case '\r':
                if (fputs("\\r", stream) == EOF) {
                    return false;
                }
                break;

            case '\t':
                if (fputs("\\t", stream) == EOF) {
                    return false;
                }
                break;

            default:
                if (current < 0x20) {
                    if (fputs("\\u00", stream) == EOF ||
                        fputc(hexadecimal[current >> 4], stream) == EOF ||
                        fputc(hexadecimal[current & 0x0F], stream) == EOF) {
                        return false;
                    }
                } else if (fputc(current, stream) == EOF) {
                    return false;
                }
                break;
        }
    }

    return fputc('"', stream) != EOF;
}

static bool dictionary_print(
    FILE *stream,
    const Dictionary *dictionary
)
{
    size_t i;

    if (stream == NULL || dictionary == NULL ||
        fputc('{', stream) == EOF) {
        return false;
    }

    for (i = 0; i < dictionary->count; ++i) {
        if (i > 0 && fputs(", ", stream) == EOF) {
            return false;
        }

        if (!print_quoted_bytes(
                stream,
                dictionary->entries[i].key,
                dictionary->entries[i].key_length) ||
            fputs(": ", stream) == EOF ||
            !print_quoted_bytes(
                stream,
                dictionary->entries[i].value,
                dictionary->entries[i].value_length)) {
            return false;
        }
    }

    return fputs("}\n", stream) != EOF;
}

int main(void)
{
    Dictionary *first;
    Dictionary *second;
    Dictionary *merged;
    int result;

    first = dictionary_create();
    second = dictionary_create();
    merged = NULL;
    result = EXIT_FAILURE;

    if (first == NULL || second == NULL) {
        goto cleanup;
    }

    if (!dictionary_set(
            first,
            "name",
            sizeof("name") - 1,
            "Alice",
            sizeof("Alice") - 1) ||
        !dictionary_set(
            first,
            "city",
            sizeof("city") - 1,
            "London",
            sizeof("London") - 1) ||
        !dictionary_set(
            second,
            "city",
            sizeof("city") - 1,
            "Paris",
            sizeof("Paris") - 1) ||
        !dictionary_set(
            second,
            "language",
            sizeof("language") - 1,
            "C",
            sizeof("C") - 1)) {
        goto cleanup;
    }

    merged = merge_dictionaries(first, second);
    if (merged == NULL) {
        goto cleanup;
    }

    if (!dictionary_print(stdout, merged)) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    dictionary_destroy(merged);
    dictionary_destroy(second);
    dictionary_destroy(first);
    return result;
}