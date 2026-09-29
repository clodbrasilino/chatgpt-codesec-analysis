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

    if (length > 0U) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
    }

    copy[length] = '\0';
    return copy;
}

static void dictionary_destroy(Dictionary *dictionary)
{
    if (dictionary == NULL) {
        return;
    }

    if (dictionary->entries != NULL) {
        for (size_t i = 0U; i < dictionary->size; ++i) {
            free(dictionary->entries[i].key);
            free(dictionary->entries[i].value);
        }
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->size = 0U;
    dictionary->capacity = 0U;
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

static size_t dictionary_find(const Dictionary *dictionary,
                              const char *key,
                              size_t key_length)
{
    if (dictionary == NULL || key == NULL ||
        dictionary->size > dictionary->capacity ||
        (dictionary->size != 0U && dictionary->entries == NULL)) {
        return SIZE_MAX;
    }

    for (size_t i = 0U; i < dictionary->size; ++i) {
        const Entry *entry = &dictionary->entries[i];

        if (entry->key != NULL &&
            entry->key_length == key_length &&
            (key_length == 0U ||
             memcmp(entry->key, key, key_length) == 0)) {
            return i;
        }
    }

    return SIZE_MAX;
}

static int dictionary_set_n(Dictionary *dictionary,
                            const char *key,
                            size_t key_length,
                            const char *value,
                            size_t value_length)
{
    size_t index;
    char *new_key;
    char *new_value;

    if (dictionary == NULL || key == NULL || value == NULL ||
        key_length == SIZE_MAX || value_length == SIZE_MAX ||
        dictionary->size > dictionary->capacity ||
        (dictionary->capacity != 0U && dictionary->entries == NULL)) {
        return -1;
    }

    index = dictionary_find(dictionary, key, key_length);

    new_value = duplicate_string(value, value_length);
    if (new_value == NULL) {
        return -1;
    }

    if (index != SIZE_MAX) {
        char *old_value = dictionary->entries[index].value;

        dictionary->entries[index].value = new_value;
        dictionary->entries[index].value_length = value_length;
        free(old_value);
        return 0;
    }

    new_key = duplicate_string(key, key_length);
    if (new_key == NULL) {
        free(new_value);
        return -1;
    }

    if (dictionary->size == dictionary->capacity) {
        size_t new_capacity;

        if (dictionary->capacity == 0U) {
            new_capacity = 4U;
        } else {
            if (dictionary->capacity > SIZE_MAX / 2U) {
                free(new_key);
                free(new_value);
                return -1;
            }

            new_capacity = dictionary->capacity * 2U;
        }

        if (dictionary_reserve(dictionary, new_capacity) != 0) {
            free(new_key);
            free(new_value);
            return -1;
        }
    }

    dictionary->entries[dictionary->size] = (Entry){
        .key = new_key,
        .key_length = key_length,
        .value = new_value,
        .value_length = value_length
    };
    ++dictionary->size;

    return 0;
}

static int dictionary_merge(const Dictionary *first,
                            const Dictionary *second,
                            Dictionary *result)
{
    Dictionary merged = {0};
    size_t maximum_size;

    if (first == NULL || second == NULL || result == NULL ||
        result == first || result == second ||
        first->size > first->capacity ||
        second->size > second->capacity ||
        (first->size != 0U && first->entries == NULL) ||
        (second->size != 0U && second->entries == NULL)) {
        return -1;
    }

    if (first->size > SIZE_MAX - second->size) {
        return -1;
    }

    maximum_size = first->size + second->size;

    if (dictionary_reserve(&merged, maximum_size) != 0) {
        return -1;
    }

    for (size_t i = 0U; i < first->size; ++i) {
        const Entry *entry = &first->entries[i];

        if (entry->key == NULL || entry->value == NULL ||
            entry->key_length == SIZE_MAX ||
            entry->value_length == SIZE_MAX ||
            dictionary_set_n(&merged,
                             entry->key,
                             entry->key_length,
                             entry->value,
                             entry->value_length) != 0) {
            dictionary_destroy(&merged);
            return -1;
        }
    }

    for (size_t i = 0U; i < second->size; ++i) {
        const Entry *entry = &second->entries[i];

        if (entry->key == NULL || entry->value == NULL ||
            entry->key_length == SIZE_MAX ||
            entry->value_length == SIZE_MAX ||
            dictionary_set_n(&merged,
                             entry->key,
                             entry->key_length,
                             entry->value,
                             entry->value_length) != 0) {
            dictionary_destroy(&merged);
            return -1;
        }
    }

    dictionary_destroy(result);
    *result = merged;
    return 0;
}

static int print_quoted(const char *text, size_t length)
{
    if (text == NULL || putchar('"') == EOF) {
        return -1;
    }

    for (size_t i = 0U; i < length; ++i) {
        unsigned char character = (unsigned char)text[i];

        switch (character) {
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
            if (character < 0x20U) {
                if (fprintf(stdout, "\\u%04x",
                            (unsigned int)character) < 0) {
                    return -1;
                }
            } else if (putchar((int)character) == EOF) {
                return -1;
            }
            break;
        }
    }

    return putchar('"') == EOF ? -1 : 0;
}

static int dictionary_print(const Dictionary *dictionary)
{
    if (dictionary == NULL ||
        dictionary->size > dictionary->capacity ||
        (dictionary->size != 0U && dictionary->entries == NULL) ||
        putchar('{') == EOF) {
        return -1;
    }

    for (size_t i = 0U; i < dictionary->size; ++i) {
        const Entry *entry = &dictionary->entries[i];

        if (entry->key == NULL || entry->value == NULL) {
            return -1;
        }

        if (i != 0U && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (print_quoted(entry->key, entry->key_length) != 0 ||
            fputs(": ", stdout) == EOF ||
            print_quoted(entry->value, entry->value_length) != 0) {
            return -1;
        }
    }

    return puts("}") == EOF ? -1 : 0;
}

int main(void)
{
    static const char name_key[] = "name";
    static const char name_value[] = "Alice";
    static const char city_key[] = "city";
    static const char london_value[] = "London";
    static const char paris_value[] = "Paris";
    static const char role_key[] = "role";
    static const char role_value[] = "Developer";

    Dictionary first = {0};
    Dictionary second = {0};
    Dictionary merged = {0};
    int status = EXIT_FAILURE;

    if (dictionary_set_n(&first, name_key, sizeof(name_key) - 1U,
                         name_value, sizeof(name_value) - 1U) != 0 ||
        dictionary_set_n(&first, city_key, sizeof(city_key) - 1U,
                         london_value, sizeof(london_value) - 1U) != 0 ||
        dictionary_set_n(&second, city_key, sizeof(city_key) - 1U,
                         paris_value, sizeof(paris_value) - 1U) != 0 ||
        dictionary_set_n(&second, role_key, sizeof(role_key) - 1U,
                         role_value, sizeof(role_value) - 1U) != 0) {
        fputs("Failed to create dictionaries.\n", stderr);
        goto cleanup;
    }

    if (dictionary_merge(&first, &second, &merged) != 0) {
        fputs("Failed to merge dictionaries.\n", stderr);
        goto cleanup;
    }

    if (dictionary_print(&merged) != 0) {
        fputs("Failed to print dictionary.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    dictionary_destroy(&merged);
    dictionary_destroy(&second);
    dictionary_destroy(&first);
    return status;
}