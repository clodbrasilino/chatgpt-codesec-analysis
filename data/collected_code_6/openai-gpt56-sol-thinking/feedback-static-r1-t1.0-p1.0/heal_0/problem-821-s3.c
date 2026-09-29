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

typedef enum {
    DICTIONARY_OK = 0,
    DICTIONARY_INVALID_ARGUMENT,
    DICTIONARY_OUT_OF_MEMORY
} DictionaryStatus;

void dictionary_init(Dictionary *dictionary)
{
    if (dictionary != NULL) {
        dictionary->entries = NULL;
        dictionary->size = 0;
        dictionary->capacity = 0;
    }
}

void dictionary_destroy(Dictionary *dictionary)
{
    size_t index;

    if (dictionary == NULL) {
        return;
    }

    for (index = 0; index < dictionary->size; ++index) {
        free(dictionary->entries[index].key);
        free(dictionary->entries[index].value);
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->size = 0;
    dictionary->capacity = 0;
}

static char *duplicate_string(const char *source)
{
    char *copy;
    size_t length;

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

static size_t dictionary_find(const Dictionary *dictionary, const char *key)
{
    size_t index;

    for (index = 0; index < dictionary->size; ++index) {
        if (strcmp(dictionary->entries[index].key, key) == 0) {
            return index;
        }
    }

    return dictionary->size;
}

static DictionaryStatus dictionary_reserve(Dictionary *dictionary, size_t required)
{
    DictionaryEntry *new_entries;
    size_t new_capacity;

    if (required <= dictionary->capacity) {
        return DICTIONARY_OK;
    }

    new_capacity = dictionary->capacity == 0 ? 4 : dictionary->capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }
        new_capacity *= 2;
    }

    if (new_capacity > SIZE_MAX / sizeof(*new_entries)) {
        return DICTIONARY_OUT_OF_MEMORY;
    }

    new_entries = realloc(
        dictionary->entries,
        new_capacity * sizeof(*new_entries)
    );

    if (new_entries == NULL) {
        return DICTIONARY_OUT_OF_MEMORY;
    }

    dictionary->entries = new_entries;
    dictionary->capacity = new_capacity;
    return DICTIONARY_OK;
}

DictionaryStatus dictionary_set(
    Dictionary *dictionary,
    const char *key,
    const char *value
)
{
    DictionaryStatus status;
    char *new_key;
    char *new_value;
    size_t index;

    if (dictionary == NULL || key == NULL || value == NULL) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    index = dictionary_find(dictionary, key);

    if (index < dictionary->size) {
        new_value = duplicate_string(value);
        if (new_value == NULL) {
            return DICTIONARY_OUT_OF_MEMORY;
        }

        free(dictionary->entries[index].value);
        dictionary->entries[index].value = new_value;
        return DICTIONARY_OK;
    }

    if (dictionary->size == SIZE_MAX) {
        return DICTIONARY_OUT_OF_MEMORY;
    }

    status = dictionary_reserve(dictionary, dictionary->size + 1);
    if (status != DICTIONARY_OK) {
        return status;
    }

    new_key = duplicate_string(key);
    if (new_key == NULL) {
        return DICTIONARY_OUT_OF_MEMORY;
    }

    new_value = duplicate_string(value);
    if (new_value == NULL) {
        free(new_key);
        return DICTIONARY_OUT_OF_MEMORY;
    }

    dictionary->entries[dictionary->size].key = new_key;
    dictionary->entries[dictionary->size].value = new_value;
    ++dictionary->size;

    return DICTIONARY_OK;
}

DictionaryStatus dictionary_merge(
    const Dictionary *first,
    const Dictionary *second,
    Dictionary **result
)
{
    Dictionary *merged;
    DictionaryStatus status;
    size_t index;

    if (first == NULL || second == NULL || result == NULL) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    *result = NULL;

    merged = malloc(sizeof(*merged));
    if (merged == NULL) {
        return DICTIONARY_OUT_OF_MEMORY;
    }

    dictionary_init(merged);

    for (index = 0; index < first->size; ++index) {
        status = dictionary_set(
            merged,
            first->entries[index].key,
            first->entries[index].value
        );

        if (status != DICTIONARY_OK) {
            dictionary_destroy(merged);
            free(merged);
            return status;
        }
    }

    for (index = 0; index < second->size; ++index) {
        status = dictionary_set(
            merged,
            second->entries[index].key,
            second->entries[index].value
        );

        if (status != DICTIONARY_OK) {
            dictionary_destroy(merged);
            free(merged);
            return status;
        }
    }

    *result = merged;
    return DICTIONARY_OK;
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

    for (current = (const unsigned char *)text; *current != '\0'; ++current) {
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
                if (*current < 0x20U) {
                    if (fprintf(stream, "\\u%04x", (unsigned int)*current) < 0) {
                        return -1;
                    }
                } else if (fputc((int)*current, stream) == EOF) {
                    return -1;
                }
                break;
        }
    }

    return fputc('"', stream) == EOF ? -1 : 0;
}

int dictionary_print(FILE *stream, const Dictionary *dictionary)
{
    size_t index;

    if (stream == NULL || dictionary == NULL) {
        return -1;
    }

    if (fputc('{', stream) == EOF) {
        return -1;
    }

    for (index = 0; index < dictionary->size; ++index) {
        if (index > 0 && fputs(", ", stream) == EOF) {
            return -1;
        }

        if (print_escaped_string(stream, dictionary->entries[index].key) != 0) {
            return -1;
        }

        if (fputs(": ", stream) == EOF) {
            return -1;
        }

        if (print_escaped_string(stream, dictionary->entries[index].value) != 0) {
            return -1;
        }
    }

    return fputc('}', stream) == EOF ? -1 : 0;
}

int main(void)
{
    Dictionary first;
    Dictionary second;
    Dictionary *merged;
    DictionaryStatus status;
    int result;

    dictionary_init(&first);
    dictionary_init(&second);
    merged = NULL;
    result = EXIT_FAILURE;

    status = dictionary_set(&first, "language", "C");
    if (status != DICTIONARY_OK) {
        goto cleanup;
    }

    status = dictionary_set(&first, "standard", "C17");
    if (status != DICTIONARY_OK) {
        goto cleanup;
    }

    status = dictionary_set(&second, "standard", "C23");
    if (status != DICTIONARY_OK) {
        goto cleanup;
    }

    status = dictionary_set(&second, "safety", "enabled");
    if (status != DICTIONARY_OK) {
        goto cleanup;
    }

    status = dictionary_merge(&first, &second, &merged);
    if (status != DICTIONARY_OK) {
        goto cleanup;
    }

    if (dictionary_print(stdout, merged) != 0) {
        goto cleanup;
    }

    if (fputc('\n', stdout) == EOF) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    if (merged != NULL) {
        dictionary_destroy(merged);
        free(merged);
    }

    dictionary_destroy(&second);
    dictionary_destroy(&first);
    return result;
}