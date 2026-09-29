#include <stdbool.h>
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

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, source, length + 1);
    return copy;
}

static bool dictionary_reserve(Dictionary *dictionary, size_t minimum_capacity)
{
    size_t new_capacity;
    DictionaryEntry *new_entries;

    if (dictionary == NULL) {
        return false;
    }

    if (minimum_capacity <= dictionary->capacity) {
        return true;
    }

    if (minimum_capacity > SIZE_MAX / sizeof(*dictionary->entries)) {
        return false;
    }

    new_capacity = dictionary->capacity == 0 ? 4 : dictionary->capacity;

    while (new_capacity < minimum_capacity) {
        if (new_capacity > SIZE_MAX / 2) {
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

static size_t dictionary_find(const Dictionary *dictionary, const char *key)
{
    size_t i;

    if (dictionary == NULL || key == NULL) {
        return SIZE_MAX;
    }

    for (i = 0; i < dictionary->count; ++i) {
        if (strcmp(dictionary->entries[i].key, key) == 0) {
            return i;
        }
    }

    return SIZE_MAX;
}

static bool dictionary_set(
    Dictionary *dictionary,
    const char *key,
    const char *value
)
{
    size_t index;
    char *key_copy;
    char *value_copy;

    if (dictionary == NULL || key == NULL || value == NULL) {
        return false;
    }

    index = dictionary_find(dictionary, key);

    if (index != SIZE_MAX) {
        value_copy = duplicate_string(value);
        if (value_copy == NULL) {
            return false;
        }

        free(dictionary->entries[index].value);
        dictionary->entries[index].value = value_copy;
        return true;
    }

    if (dictionary->count == SIZE_MAX ||
        !dictionary_reserve(dictionary, dictionary->count + 1)) {
        return false;
    }

    key_copy = duplicate_string(key);
    if (key_copy == NULL) {
        return false;
    }

    value_copy = duplicate_string(value);
    if (value_copy == NULL) {
        free(key_copy);
        return false;
    }

    dictionary->entries[dictionary->count].key = key_copy;
    dictionary->entries[dictionary->count].value = value_copy;
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
                first->entries[i].value)) {
            dictionary_destroy(merged);
            return NULL;
        }
    }

    for (i = 0; i < second->count; ++i) {
        if (!dictionary_set(
                merged,
                second->entries[i].key,
                second->entries[i].value)) {
            dictionary_destroy(merged);
            return NULL;
        }
    }

    return merged;
}

static bool print_quoted_string(FILE *stream, const char *text)
{
    const unsigned char *current;

    if (stream == NULL || text == NULL || fputc('"', stream) == EOF) {
        return false;
    }

    for (current = (const unsigned char *)text; *current != '\0'; ++current) {
        switch (*current) {
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
                if (*current < 0x20) {
                    if (fprintf(stream, "\\u%04X", *current) < 0) {
                        return false;
                    }
                } else if (fputc(*current, stream) == EOF) {
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

        if (!print_quoted_string(stream, dictionary->entries[i].key) ||
            fputs(": ", stream) == EOF ||
            !print_quoted_string(stream, dictionary->entries[i].value)) {
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

    if (!dictionary_set(first, "name", "Alice") ||
        !dictionary_set(first, "city", "London") ||
        !dictionary_set(second, "city", "Paris") ||
        !dictionary_set(second, "language", "C")) {
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