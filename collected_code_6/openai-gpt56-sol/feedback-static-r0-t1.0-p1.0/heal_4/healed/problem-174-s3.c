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
    StringList values;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    size_t count;
    size_t capacity;
} Dictionary;

static int duplicate_string(const char *source, size_t length, char **result)
{
    char *copy;

    if (source == NULL || result == NULL) {
        errno = EINVAL;
        return -1;
    }

    *result = NULL;

    if (length == SIZE_MAX) {
        errno = EOVERFLOW;
        return -1;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        errno = ENOMEM;
        return -1;
    }

    if (length > 0U) {
        size_t i;

        for (i = 0U; i < length; ++i) {
            copy[i] = source[i];
        }
    }

    copy[length] = '\0';
    *result = copy;
    return 0;
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
                              size_t value_length)
{
    char *copy = NULL;

    if (list == NULL || value == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (list->count > list->capacity ||
        (list->capacity != 0U && list->items == NULL) ||
        (list->capacity == 0U && list->items != NULL)) {
        errno = EINVAL;
        return -1;
    }

    if (duplicate_string(value, value_length, &copy) != 0) {
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

static DictionaryEntry *dictionary_find(Dictionary *dictionary,
                                        const char *key,
                                        size_t key_length)
{
    size_t i;

    if (dictionary == NULL || key == NULL ||
        dictionary->count > dictionary->capacity ||
        (dictionary->capacity != 0U && dictionary->entries == NULL) ||
        (dictionary->capacity == 0U && dictionary->entries != NULL)) {
        errno = EINVAL;
        return NULL;
    }

    for (i = 0U; i < dictionary->count; ++i) {
        const char *existing_key = dictionary->entries[i].key;

        if (existing_key != NULL &&
            strncmp(existing_key, key, key_length) == 0 &&
            existing_key[key_length] == '\0') {
            return &dictionary->entries[i];
        }
    }

    return NULL;
}

static DictionaryEntry *dictionary_add_entry(Dictionary *dictionary,
                                             const char *key,
                                             size_t key_length)
{
    char *key_copy = NULL;
    DictionaryEntry *entry;

    if (dictionary == NULL || key == NULL) {
        errno = EINVAL;
        return NULL;
    }

    if (dictionary->count > dictionary->capacity ||
        (dictionary->capacity != 0U && dictionary->entries == NULL) ||
        (dictionary->capacity == 0U && dictionary->entries != NULL)) {
        errno = EINVAL;
        return NULL;
    }

    if (duplicate_string(key, key_length, &key_copy) != 0) {
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
    entry->values.items = NULL;
    entry->values.count = 0U;
    entry->values.capacity = 0U;
    ++dictionary->count;

    return entry;
}

static int group_pairs(const KeyValuePair *pairs,
                       const size_t *key_lengths,
                       const size_t *value_lengths,
                       size_t pair_count,
                       Dictionary *result)
{
    Dictionary temporary = { NULL, 0U, 0U };
    size_t i;

    if (result == NULL ||
        (pair_count != 0U &&
         (pairs == NULL || key_lengths == NULL || value_lengths == NULL))) {
        errno = EINVAL;
        return -1;
    }

    if (result->count > result->capacity ||
        (result->capacity != 0U && result->entries == NULL) ||
        (result->capacity == 0U && result->entries != NULL)) {
        errno = EINVAL;
        return -1;
    }

    for (i = 0U; i < pair_count; ++i) {
        DictionaryEntry *entry;

        if (pairs[i].key == NULL || pairs[i].value == NULL) {
            dictionary_destroy(&temporary);
            errno = EINVAL;
            return -1;
        }

        errno = 0;
        entry = dictionary_find(&temporary, pairs[i].key, key_lengths[i]);

        if (entry == NULL) {
            if (errno != 0) {
                int saved_errno = errno;
                dictionary_destroy(&temporary);
                errno = saved_errno;
                return -1;
            }

            entry = dictionary_add_entry(&temporary,
                                         pairs[i].key,
                                         key_lengths[i]);
            if (entry == NULL) {
                int saved_errno = errno;
                dictionary_destroy(&temporary);
                errno = saved_errno;
                return -1;
            }
        }

        if (string_list_append(&entry->values,
                               pairs[i].value,
                               value_lengths[i]) != 0) {
            int saved_errno = errno;
            dictionary_destroy(&temporary);
            errno = saved_errno;
            return -1;
        }
    }

    dictionary_destroy(result);
    *result = temporary;
    return 0;
}

static int print_quoted_string(const char *string)
{
    const unsigned char *current;

    if (string == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (fputc('"', stdout) == EOF) {
        return -1;
    }

    current = (const unsigned char *)string;

    while (*current != '\0') {
        switch (*current) {
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
                if (*current < 0x20U) {
                    if (fprintf(stdout, "\\u%04x",
                                (unsigned int)*current) < 0) {
                        return -1;
                    }
                } else if (fputc((int)*current, stdout) == EOF) {
                    return -1;
                }
                break;
        }

        ++current;
    }

    return fputc('"', stdout) == EOF ? -1 : 0;
}

static int dictionary_print(const Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL ||
        dictionary->count > dictionary->capacity ||
        (dictionary->capacity != 0U && dictionary->entries == NULL) ||
        (dictionary->capacity == 0U && dictionary->entries != NULL)) {
        errno = EINVAL;
        return -1;
    }

    if (fputs("{\n", stdout) == EOF) {
        return -1;
    }

    for (i = 0U; i < dictionary->count; ++i) {
        const DictionaryEntry *entry = &dictionary->entries[i];
        size_t j;

        if (entry->key == NULL ||
            entry->values.count > entry->values.capacity ||
            (entry->values.capacity != 0U &&
             entry->values.items == NULL) ||
            (entry->values.capacity == 0U &&
             entry->values.items != NULL)) {
            errno = EINVAL;
            return -1;
        }

        if (fputs("  ", stdout) == EOF ||
            print_quoted_string(entry->key) != 0 ||
            fputs(": [", stdout) == EOF) {
            return -1;
        }

        for (j = 0U; j < entry->values.count; ++j) {
            if (entry->values.items[j] == NULL) {
                errno = EINVAL;
                return -1;
            }

            if (j != 0U && fputs(", ", stdout) == EOF) {
                return -1;
            }

            if (print_quoted_string(entry->values.items[j]) != 0) {
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

    return fputs("}\n", stdout) == EOF ? -1 : 0;
}

int main(void)
{
    static const KeyValuePair pairs[] = {
        { "fruit", "apple" },
        { "color", "red" },
        { "fruit", "banana" },
        { "color", "blue" },
        { "fruit", "orange" },
        { "size", "large" }
    };
    static const size_t key_lengths[] = {
        sizeof("fruit") - 1U,
        sizeof("color") - 1U,
        sizeof("fruit") - 1U,
        sizeof("color") - 1U,
        sizeof("fruit") - 1U,
        sizeof("size") - 1U
    };
    static const size_t value_lengths[] = {
        sizeof("apple") - 1U,
        sizeof("red") - 1U,
        sizeof("banana") - 1U,
        sizeof("blue") - 1U,
        sizeof("orange") - 1U,
        sizeof("large") - 1U
    };
    Dictionary dictionary = { NULL, 0U, 0U };
    int status = EXIT_SUCCESS;

    if (group_pairs(pairs,
                    key_lengths,
                    value_lengths,
                    sizeof(pairs) / sizeof(pairs[0]),
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