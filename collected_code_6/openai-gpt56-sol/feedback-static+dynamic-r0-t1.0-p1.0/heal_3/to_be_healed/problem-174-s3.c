#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *key;
    const char *value;
} KeyValuePair;

typedef struct {
    char **items;
    size_t count;
    size_t capacity;
} StringList;

typedef struct {
    char *key;
    size_t key_length;
    StringList values;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    size_t count;
    size_t capacity;
} Dictionary;

static int bounded_string_length(const char *text,
                                 size_t max_length,
                                 size_t *length)
{
    const char *terminator;

    if (text == NULL || length == NULL || max_length == 0U) {
        errno = EINVAL;
        return -1;
    }

    terminator = memchr(text, '\0', max_length);
    if (terminator == NULL) {
        errno = EOVERFLOW;
        return -1;
    }

    *length = (size_t)(terminator - text);
    return 0;
}

static char *duplicate_string(const char *source,
                              size_t max_length,
                              size_t *copied_length)
{
    size_t length;
    char *copy;

    if (bounded_string_length(source, max_length, &length) != 0) {
        return NULL;
    }

    if (length > SIZE_MAX - 1U) {
        errno = EOVERFLOW;
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    if (length > 0U) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
    }
    copy[length] = '\0';

    if (copied_length != NULL) {
        *copied_length = length;
    }

    return copy;
}

static void string_list_destroy(StringList *list)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    for (i = 0U; i < list->count; ++i) {
        free(list->items[i]);
    }

    free(list->items);
    list->items = NULL;
    list->count = 0U;
    list->capacity = 0U;
}

static void dictionary_destroy(Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL) {
        return;
    }

    for (i = 0U; i < dictionary->count; ++i) {
        free(dictionary->entries[i].key);
        string_list_destroy(&dictionary->entries[i].values);
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->count = 0U;
    dictionary->capacity = 0U;
}

static int string_list_append(StringList *list,
                              const char *value,
                              size_t value_max_length)
{
    char *copy;

    if (list == NULL || value == NULL || value_max_length == 0U) {
        errno = EINVAL;
        return -1;
    }

    copy = duplicate_string(value, value_max_length, NULL);
    if (copy == NULL) {
        return -1;
    }

    if (list->count == list->capacity) {
        size_t new_capacity;
        char **new_items;

        if (list->capacity == 0U) {
            new_capacity = 4U;
        } else {
            if (list->capacity > SIZE_MAX / 2U) {
                free(copy);
                errno = EOVERFLOW;
                return -1;
            }
            new_capacity = list->capacity * 2U;
        }

        if (new_capacity > SIZE_MAX / sizeof(*new_items)) {
            free(copy);
            errno = EOVERFLOW;
            return -1;
        }

        new_items = realloc(list->items,
                            new_capacity * sizeof(*new_items));
        if (new_items == NULL) {
            free(copy);
            errno = ENOMEM;
            return -1;
        }

        list->items = new_items;
        list->capacity = new_capacity;
    }

    list->items[list->count] = copy;
    ++list->count;

    return 0;
}

static int dictionary_find(Dictionary *dictionary,
                           const char *key,
                           size_t key_max_length,
                           DictionaryEntry **found)
{
    size_t key_length;
    size_t i;

    if (dictionary == NULL || key == NULL || found == NULL ||
        key_max_length == 0U) {
        errno = EINVAL;
        return -1;
    }

    if (bounded_string_length(key, key_max_length, &key_length) != 0) {
        return -1;
    }

    *found = NULL;

    for (i = 0U; i < dictionary->count; ++i) {
        DictionaryEntry *entry = &dictionary->entries[i];

        if (entry->key_length == key_length &&
            (key_length == 0U ||
             memcmp(entry->key, key, key_length) == 0)) {
            *found = entry;
            break;
        }
    }

    return 0;
}

static DictionaryEntry *dictionary_add_entry(Dictionary *dictionary,
                                              const char *key,
                                              size_t key_max_length)
{
    DictionaryEntry *entry;
    char *key_copy;
    size_t key_length;

    if (dictionary == NULL || key == NULL || key_max_length == 0U) {
        errno = EINVAL;
        return NULL;
    }

    key_copy = duplicate_string(key, key_max_length, &key_length);
    if (key_copy == NULL) {
        return NULL;
    }

    if (dictionary->count == dictionary->capacity) {
        size_t new_capacity;
        DictionaryEntry *new_entries;

        if (dictionary->capacity == 0U) {
            new_capacity = 4U;
        } else {
            if (dictionary->capacity > SIZE_MAX / 2U) {
                free(key_copy);
                errno = EOVERFLOW;
                return NULL;
            }
            new_capacity = dictionary->capacity * 2U;
        }

        if (new_capacity > SIZE_MAX / sizeof(*new_entries)) {
            free(key_copy);
            errno = EOVERFLOW;
            return NULL;
        }

        new_entries = realloc(dictionary->entries,
                              new_capacity * sizeof(*new_entries));
        if (new_entries == NULL) {
            free(key_copy);
            errno = ENOMEM;
            return NULL;
        }

        dictionary->entries = new_entries;
        dictionary->capacity = new_capacity;
    }

    entry = &dictionary->entries[dictionary->count];
    entry->key = key_copy;
    entry->key_length = key_length;
    entry->values.items = NULL;
    entry->values.count = 0U;
    entry->values.capacity = 0U;
    ++dictionary->count;

    return entry;
}

static int group_pairs(const KeyValuePair *pairs,
                       size_t pair_count,
                       size_t max_string_length,
                       Dictionary *result)
{
    size_t i;

    if (result == NULL || max_string_length == 0U ||
        (pairs == NULL && pair_count != 0U)) {
        errno = EINVAL;
        return -1;
    }

    result->entries = NULL;
    result->count = 0U;
    result->capacity = 0U;

    for (i = 0U; i < pair_count; ++i) {
        DictionaryEntry *entry;
        int saved_errno;

        if (pairs[i].key == NULL || pairs[i].value == NULL) {
            errno = EINVAL;
            dictionary_destroy(result);
            return -1;
        }

        if (dictionary_find(result,
                            pairs[i].key,
                            max_string_length,
                            &entry) != 0) {
            saved_errno = errno;
            dictionary_destroy(result);
            errno = saved_errno;
            return -1;
        }

        if (entry == NULL) {
            entry = dictionary_add_entry(result,
                                         pairs[i].key,
                                         max_string_length);
            if (entry == NULL) {
                saved_errno = errno;
                dictionary_destroy(result);
                errno = saved_errno;
                return -1;
            }
        }

        if (string_list_append(&entry->values,
                               pairs[i].value,
                               max_string_length) != 0) {
            saved_errno = errno;
            dictionary_destroy(result);
            errno = saved_errno;
            return -1;
        }
    }

    return 0;
}

static int print_quoted(const char *text)
{
    const unsigned char *p;

    if (text == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (fputc('"', stdout) == EOF) {
        return -1;
    }

    for (p = (const unsigned char *)text; *p != '\0'; ++p) {
        switch (*p) {
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
                if (*p < 0x20U) {
                    if (fprintf(stdout,
                                "\\u%04x",
                                (unsigned int)*p) < 0) {
                        return -1;
                    }
                } else if (fputc((int)*p, stdout) == EOF) {
                    return -1;
                }
                break;
        }
    }

    if (fputc('"', stdout) == EOF) {
        return -1;
    }

    return 0;
}

static int dictionary_print(const Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (fputs("{\n", stdout) == EOF) {
        return -1;
    }

    for (i = 0U; i < dictionary->count; ++i) {
        const DictionaryEntry *entry = &dictionary->entries[i];
        size_t j;

        if (fputs("  ", stdout) == EOF ||
            print_quoted(entry->key) != 0 ||
            fputs(": [", stdout) == EOF) {
            return -1;
        }

        for (j = 0U; j < entry->values.count; ++j) {
            if (j != 0U && fputs(", ", stdout) == EOF) {
                return -1;
            }

            if (print_quoted(entry->values.items[j]) != 0) {
                return -1;
            }
        }

        if (fputc(']', stdout) == EOF) {
            return -1;
        }

        if (i + 1U < dictionary->count &&
            fputc(',', stdout) == EOF) {
            return -1;
        }

        if (fputc('\n', stdout) == EOF) {
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
    static const KeyValuePair pairs[] = {
        {"fruit", "apple"},
        {"color", "red"},
        {"fruit", "banana"},
        {"color", "blue"},
        {"fruit", "orange"},
        {"size", "large"}
    };
    const size_t max_string_length = 1024U;
    Dictionary dictionary = {NULL, 0U, 0U};
    int status = EXIT_SUCCESS;

    if (group_pairs(pairs,
                    sizeof(pairs) / sizeof(pairs[0]),
                    max_string_length,
                    &dictionary) != 0) {
        perror("group_pairs");
        return EXIT_FAILURE;
    }

    if (dictionary_print(&dictionary) != 0) {
        perror("dictionary_print");
        status = EXIT_FAILURE;
    }

    dictionary_destroy(&dictionary);

    if (fflush(stdout) == EOF) {
        perror("fflush");
        status = EXIT_FAILURE;
    }

    return status;
}