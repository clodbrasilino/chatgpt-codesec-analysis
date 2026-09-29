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
    size_t size;
    size_t capacity;
} Dictionary;

static void dictionary_init(Dictionary *dictionary)
{
    if (dictionary == NULL) {
        return;
    }

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

static int bytes_equal(
    const char *first,
    size_t first_length,
    const char *second,
    size_t second_length
)
{
    size_t i;

    if (first == NULL || second == NULL || first_length != second_length) {
        return 0;
    }

    for (i = 0; i < first_length; ++i) {
        if (first[i] != second[i]) {
            return 0;
        }
    }

    return 1;
}

static int dictionary_reserve(
    Dictionary *dictionary,
    size_t required_capacity
)
{
    size_t new_capacity;
    DictionaryEntry *new_entries;

    if (dictionary == NULL) {
        return -1;
    }

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
    size_t key_length,
    const char *value,
    size_t value_length
)
{
    size_t i;
    char *new_key;
    char *new_value;

    if (dictionary == NULL || key == NULL || value == NULL) {
        return -1;
    }

    for (i = 0; i < dictionary->size; ++i) {
        if (bytes_equal(
                dictionary->entries[i].key,
                dictionary->entries[i].key_length,
                key,
                key_length
            )) {
            new_value = duplicate_bytes(value, value_length);
            if (new_value == NULL) {
                return -1;
            }

            free(dictionary->entries[i].value);
            dictionary->entries[i].value = new_value;
            dictionary->entries[i].value_length = value_length;
            return 0;
        }
    }

    if (dictionary->size == SIZE_MAX) {
        return -1;
    }

    new_key = duplicate_bytes(key, key_length);
    if (new_key == NULL) {
        return -1;
    }

    new_value = duplicate_bytes(value, value_length);
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
    dictionary->entries[dictionary->size].key_length = key_length;
    dictionary->entries[dictionary->size].value = new_value;
    dictionary->entries[dictionary->size].value_length = value_length;
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
                first->entries[i].key_length,
                first->entries[i].value,
                first->entries[i].value_length
            ) != 0) {
            dictionary_destroy(&merged);
            return -1;
        }
    }

    for (i = 0; i < second->size; ++i) {
        if (dictionary_set(
                &merged,
                second->entries[i].key,
                second->entries[i].key_length,
                second->entries[i].value,
                second->entries[i].value_length
            ) != 0) {
            dictionary_destroy(&merged);
            return -1;
        }
    }

    dictionary_destroy(result);
    *result = merged;
    return 0;
}

static int print_escaped_string(
    FILE *stream,
    const char *text,
    size_t length
)
{
    size_t i;
    unsigned char current;

    if (stream == NULL || text == NULL) {
        return -1;
    }

    if (fputc('"', stream) == EOF) {
        return -1;
    }

    for (i = 0; i < length; ++i) {
        current = (unsigned char)text[i];

        switch (current) {
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
                if (current < 0x20) {
                    if (fprintf(
                            stream,
                            "\\u%04x",
                            (unsigned int)current
                        ) < 0) {
                        return -1;
                    }
                } else if (fputc((int)current, stream) == EOF) {
                    return -1;
                }
                break;
        }
    }

    return fputc('"', stream) == EOF ? -1 : 0;
}

static int dictionary_print(
    FILE *stream,
    const Dictionary *dictionary
)
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

        if (print_escaped_string(
                stream,
                dictionary->entries[i].key,
                dictionary->entries[i].key_length
            ) != 0) {
            return -1;
        }

        if (fputs(": ", stream) == EOF) {
            return -1;
        }

        if (print_escaped_string(
                stream,
                dictionary->entries[i].value,
                dictionary->entries[i].value_length
            ) != 0) {
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

    if (dictionary_set(
            &first,
            "name",
            sizeof("name") - 1,
            "Alice",
            sizeof("Alice") - 1
        ) != 0 ||
        dictionary_set(
            &first,
            "city",
            sizeof("city") - 1,
            "Paris",
            sizeof("Paris") - 1
        ) != 0 ||
        dictionary_set(
            &second,
            "city",
            sizeof("city") - 1,
            "London",
            sizeof("London") - 1
        ) != 0 ||
        dictionary_set(
            &second,
            "role",
            sizeof("role") - 1,
            "Engineer",
            sizeof("Engineer") - 1
        ) != 0) {
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