#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

typedef struct {
    char *key;
    long value;
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

    if (length > SIZE_MAX - 1) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, source, length);
    copy[length] = '\0';

    return copy;
}

static int dictionary_init(Dictionary *dictionary)
{
    if (dictionary == NULL) {
        return -1;
    }

    dictionary->entries = NULL;
    dictionary->size = 0;
    dictionary->capacity = 0;

    return 0;
}

static void dictionary_destroy(Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL) {
        return;
    }

    for (i = 0; i < dictionary->size; ++i) {
        free(dictionary->entries[i].key);
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->size = 0;
    dictionary->capacity = 0;
}

static size_t dictionary_find(const Dictionary *dictionary, const char *key)
{
    size_t i;

    if (dictionary == NULL || key == NULL) {
        return SIZE_MAX;
    }

    for (i = 0; i < dictionary->size; ++i) {
        if (strcmp(dictionary->entries[i].key, key) == 0) {
            return i;
        }
    }

    return SIZE_MAX;
}

static int dictionary_reserve(Dictionary *dictionary, size_t capacity)
{
    Entry *new_entries;

    if (dictionary == NULL) {
        return -1;
    }

    if (capacity <= dictionary->capacity) {
        return 0;
    }

    if (capacity > SIZE_MAX / sizeof(*dictionary->entries)) {
        return -1;
    }

    new_entries = realloc(dictionary->entries,
                          capacity * sizeof(*dictionary->entries));
    if (new_entries == NULL) {
        return -1;
    }

    dictionary->entries = new_entries;
    dictionary->capacity = capacity;

    return 0;
}

static int dictionary_add(Dictionary *dictionary, const char *key, long value)
{
    size_t index;
    char *key_copy;

    if (dictionary == NULL || key == NULL) {
        return -1;
    }

    index = dictionary_find(dictionary, key);
    if (index != SIZE_MAX) {
        long current = dictionary->entries[index].value;

        if ((value > 0 && current > LONG_MAX - value) ||
            (value < 0 && current < LONG_MIN - value)) {
            return -1;
        }

        dictionary->entries[index].value = current + value;
        return 0;
    }

    if (dictionary->size == dictionary->capacity) {
        size_t new_capacity;

        if (dictionary->capacity == 0) {
            new_capacity = 4;
        } else {
            if (dictionary->capacity > SIZE_MAX / 2) {
                return -1;
            }

            new_capacity = dictionary->capacity * 2;
        }

        if (dictionary_reserve(dictionary, new_capacity) != 0) {
            return -1;
        }
    }

    key_copy = duplicate_string(key);
    if (key_copy == NULL) {
        return -1;
    }

    dictionary->entries[dictionary->size].key = key_copy;
    dictionary->entries[dictionary->size].value = value;
    ++dictionary->size;

    return 0;
}

static int dictionary_combine(const Dictionary *first,
                              const Dictionary *second,
                              Dictionary *result)
{
    Dictionary combined;
    size_t i;

    if (first == NULL || second == NULL || result == NULL ||
        result == first || result == second) {
        return -1;
    }

    if (dictionary_init(&combined) != 0) {
        return -1;
    }

    for (i = 0; i < first->size; ++i) {
        if (dictionary_add(&combined,
                           first->entries[i].key,
                           first->entries[i].value) != 0) {
            dictionary_destroy(&combined);
            return -1;
        }
    }

    for (i = 0; i < second->size; ++i) {
        if (dictionary_add(&combined,
                           second->entries[i].key,
                           second->entries[i].value) != 0) {
            dictionary_destroy(&combined);
            return -1;
        }
    }

    dictionary_destroy(result);
    *result = combined;

    return 0;
}

static int dictionary_print_quoted_key(const char *key)
{
    const unsigned char *cursor;

    if (key == NULL || putchar('"') == EOF) {
        return -1;
    }

    cursor = (const unsigned char *)key;

    while (*cursor != '\0') {
        unsigned char ch = *cursor++;

        switch (ch) {
        case '"':
            if (fputs("\\\"", stdout) == EOF) {
                return -1;
            }
            break;
        case '\\':
            if (fputs("\\\\", stdout) == EOF) {
                return -1;
            }
            break;
        case '\b':
            if (fputs("\\b", stdout) == EOF) {
                return -1;
            }
            break;
        case '\f':
            if (fputs("\\f", stdout) == EOF) {
                return -1;
            }
            break;
        case '\n':
            if (fputs("\\n", stdout) == EOF) {
                return -1;
            }
            break;
        case '\r':
            if (fputs("\\r", stdout) == EOF) {
                return -1;
            }
            break;
        case '\t':
            if (fputs("\\t", stdout) == EOF) {
                return -1;
            }
            break;
        default:
            if (ch < 0x20) {
                if (printf("\\u%04x", (unsigned int)ch) < 0) {
                    return -1;
                }
            } else if (putchar((int)ch) == EOF) {
                return -1;
            }
            break;
        }
    }

    return putchar('"') == EOF ? -1 : 0;
}

static int dictionary_print(const Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL) {
        return -1;
    }

    if (putchar('{') == EOF) {
        return -1;
    }

    for (i = 0; i < dictionary->size; ++i) {
        if (i != 0 && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (dictionary_print_quoted_key(dictionary->entries[i].key) != 0) {
            return -1;
        }

        if (printf(": %ld", dictionary->entries[i].value) < 0) {
            return -1;
        }
    }

    if (fputs("}\n", stdout) == EOF) {
        return -1;
    }

    return 0;
}

int main(void)
{
    Dictionary first;
    Dictionary second;
    Dictionary result;
    int status = EXIT_FAILURE;

    if (dictionary_init(&first) != 0) {
        return EXIT_FAILURE;
    }

    if (dictionary_init(&second) != 0) {
        dictionary_destroy(&first);
        return EXIT_FAILURE;
    }

    if (dictionary_init(&result) != 0) {
        dictionary_destroy(&second);
        dictionary_destroy(&first);
        return EXIT_FAILURE;
    }

    if (dictionary_add(&first, "apple", 3) != 0 ||
        dictionary_add(&first, "banana", 5) != 0 ||
        dictionary_add(&second, "banana", 7) != 0 ||
        dictionary_add(&second, "orange", 4) != 0) {
        goto cleanup;
    }

    if (dictionary_combine(&first, &second, &result) != 0) {
        goto cleanup;
    }

    if (dictionary_print(&result) != 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    dictionary_destroy(&result);
    dictionary_destroy(&second);
    dictionary_destroy(&first);

    return status;
}