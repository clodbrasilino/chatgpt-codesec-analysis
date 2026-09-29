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
    size_t capacity;
} Dictionary;

static void dictionary_init(Dictionary *dictionary)
{
    dictionary->entries = NULL;
    dictionary->size = 0;
    dictionary->capacity = 0;
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
    dictionary_init(dictionary);
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

static int dictionary_reserve(Dictionary *dictionary, size_t required_capacity)
{
    size_t new_capacity;
    DictionaryEntry *new_entries;

    if (required_capacity <= dictionary->capacity) {
        return 0;
    }

    if (required_capacity > SIZE_MAX / sizeof(*new_entries)) {
        return -1;
    }

    new_capacity = dictionary->capacity == 0 ? 4 : dictionary->capacity;

    while (new_capacity < required_capacity) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required_capacity;
            break;
        }
        new_capacity *= 2;
    }

    if (new_capacity > SIZE_MAX / sizeof(*new_entries)) {
        return -1;
    }

    new_entries = realloc(
        dictionary->entries,
        new_capacity * sizeof(*new_entries)
    );

    if (new_entries == NULL) {
        return -1;
    }

    dictionary->entries = new_entries;
    dictionary->capacity = new_capacity;
    return 0;
}

static int dictionary_set(
    Dictionary *dictionary,
    const char *key,
    const char *value
)
{
    size_t i;
    char *new_key;
    char *new_value;

    if (dictionary == NULL || key == NULL || value == NULL) {
        return -1;
    }

    for (i = 0; i < dictionary->size; ++i) {
        if (strcmp(dictionary->entries[i].key, key) == 0) {
            new_value = duplicate_string(value);
            if (new_value == NULL) {
                return -1;
            }

            free(dictionary->entries[i].value);
            dictionary->entries[i].value = new_value;
            return 0;
        }
    }

    if (dictionary->size == SIZE_MAX) {
        return -1;
    }

    new_key = duplicate_string(key);
    if (new_key == NULL) {
        return -1;
    }

    new_value = duplicate_string(value);
    if (new_value == NULL) {
        free(new_key);
        return -1;
    }

    if (dictionary_reserve(dictionary, dictionary->size + 1) != 0) {
        free(new_key);
        free(new_value);
        return -1;
    }

    dictionary->entries[dictionary->size].key = new_key;
    dictionary->entries[dictionary->size].value = new_value;
    ++dictionary->size;

    return 0;
}

int dictionary_merge(
    Dictionary *result,
    const Dictionary *first,
    const Dictionary *second
)
{
    Dictionary merged;
    size_t i;

    if (result == NULL || first == NULL || second == NULL) {
        return -1;
    }

    dictionary_init(&merged);

    for (i = 0; i < first->size; ++i) {
        if (dictionary_set(
                &merged,
                first->entries[i].key,
                first->entries[i].value
            ) != 0) {
            dictionary_destroy(&merged);
            return -1;
        }
    }

    for (i = 0; i < second->size; ++i) {
        if (dictionary_set(
                &merged,
                second->entries[i].key,
                second->entries[i].value
            ) != 0) {
            dictionary_destroy(&merged);
            return -1;
        }
    }

    dictionary_destroy(result);
    *result = merged;
    return 0;
}

static int print_escaped_string(FILE *stream, const char *text)
{
    const unsigned char *current;

    if (stream == NULL || text == NULL) {
        return -1;
    }

    if (fputc('"', stream) == EOF) {
        return -1;
    }

    current = (const unsigned char *)text;

    while (*current != '\0') {
        switch (*current) {
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
                if (*current < 0x20) {
                    if (fprintf(stream, "\\u%04x", (unsigned int)*current) < 0) {
                        return -1;
                    }
                } else if (fputc(*current, stream) == EOF) {
                    return -1;
                }
                break;
        }

        ++current;
    }

    return fputc('"', stream) == EOF ? -1 : 0;
}

static int dictionary_print(FILE *stream, const Dictionary *dictionary)
{
    size_t i;

    if (stream == NULL || dictionary == NULL) {
        return -1;
    }

    if (fputc('{', stream) == EOF) {
        return -1;
    }

    for (i = 0; i < dictionary->size; ++i) {
        if (i != 0 && fputs(", ", stream) == EOF) {
            return -1;
        }

        if (print_escaped_string(stream, dictionary->entries[i].key) != 0) {
            return -1;
        }

        if (fputs(": ", stream) == EOF) {
            return -1;
        }

        if (print_escaped_string(stream, dictionary->entries[i].value) != 0) {
            return -1;
        }
    }

    return fputc('}', stream) == EOF ? -1 : 0;
}

int main(void)
{
    Dictionary first;
    Dictionary second;
    Dictionary merged;
    int status = EXIT_FAILURE;

    dictionary_init(&first);
    dictionary_init(&second);
    dictionary_init(&merged);

    if (dictionary_set(&first, "name", "Alice") != 0 ||
        dictionary_set(&first, "city", "Paris") != 0 ||
        dictionary_set(&second, "city", "London") != 0 ||
        dictionary_set(&second, "role", "Engineer") != 0) {
        goto cleanup;
    }

    if (dictionary_merge(&merged, &first, &second) != 0) {
        goto cleanup;
    }

    if (dictionary_print(stdout, &merged) != 0 ||
        fputc('\n', stdout) == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    dictionary_destroy(&merged);
    dictionary_destroy(&second);
    dictionary_destroy(&first);
    return status;
}