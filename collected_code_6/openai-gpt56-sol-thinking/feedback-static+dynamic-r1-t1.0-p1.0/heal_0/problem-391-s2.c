#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NESTING_DEPTH 128U

typedef struct Dictionary Dictionary;

typedef enum {
    VALUE_STRING,
    VALUE_DICTIONARY
} ValueType;

typedef struct {
    char *key;
    ValueType type;
    union {
        char *string;
        Dictionary *dictionary;
    } value;
} DictionaryEntry;

struct Dictionary {
    DictionaryEntry *entries;
    size_t size;
    size_t capacity;
};

typedef struct {
    const char *const *items;
    size_t length;
    const char *value;
} StringList;

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

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, source, length + 1U);
    return copy;
}

static Dictionary *dictionary_create(void)
{
    return calloc(1U, sizeof(Dictionary));
}

static void dictionary_destroy(Dictionary *dictionary)
{
    size_t index;

    if (dictionary == NULL) {
        return;
    }

    for (index = 0U; index < dictionary->size; ++index) {
        DictionaryEntry *entry = &dictionary->entries[index];

        free(entry->key);
        if (entry->type == VALUE_STRING) {
            free(entry->value.string);
        } else {
            dictionary_destroy(entry->value.dictionary);
        }
    }

    free(dictionary->entries);
    free(dictionary);
}

static bool dictionary_reserve(Dictionary *dictionary, size_t required)
{
    size_t capacity;
    DictionaryEntry *entries;

    if (dictionary == NULL) {
        return false;
    }

    if (required <= dictionary->capacity) {
        return true;
    }

    capacity = dictionary->capacity == 0U ? 4U : dictionary->capacity;

    while (capacity < required) {
        if (capacity > SIZE_MAX / 2U) {
            capacity = required;
            break;
        }
        capacity *= 2U;
    }

    if (capacity > SIZE_MAX / sizeof(*entries)) {
        return false;
    }

    entries = realloc(dictionary->entries, capacity * sizeof(*entries));
    if (entries == NULL) {
        return false;
    }

    dictionary->entries = entries;
    dictionary->capacity = capacity;
    return true;
}

static DictionaryEntry *dictionary_find(Dictionary *dictionary, const char *key)
{
    size_t index;

    if (dictionary == NULL || key == NULL) {
        return NULL;
    }

    for (index = 0U; index < dictionary->size; ++index) {
        if (strcmp(dictionary->entries[index].key, key) == 0) {
            return &dictionary->entries[index];
        }
    }

    return NULL;
}

static bool dictionary_add_dictionary(
    Dictionary *dictionary,
    const char *key,
    Dictionary **child_out)
{
    char *key_copy;
    Dictionary *child;
    DictionaryEntry *entry;

    if (dictionary == NULL || key == NULL || key[0] == '\0' ||
        child_out == NULL || dictionary_find(dictionary, key) != NULL ||
        dictionary->size == SIZE_MAX) {
        return false;
    }

    *child_out = NULL;

    key_copy = duplicate_string(key);
    if (key_copy == NULL) {
        return false;
    }

    child = dictionary_create();
    if (child == NULL) {
        free(key_copy);
        return false;
    }

    if (!dictionary_reserve(dictionary, dictionary->size + 1U)) {
        dictionary_destroy(child);
        free(key_copy);
        return false;
    }

    entry = &dictionary->entries[dictionary->size];
    entry->key = key_copy;
    entry->type = VALUE_DICTIONARY;
    entry->value.dictionary = child;
    ++dictionary->size;

    *child_out = child;
    return true;
}

static bool dictionary_add_string(
    Dictionary *dictionary,
    const char *key,
    const char *value)
{
    char *key_copy;
    char *value_copy;
    DictionaryEntry *entry;

    if (dictionary == NULL || key == NULL || key[0] == '\0' ||
        value == NULL || dictionary_find(dictionary, key) != NULL ||
        dictionary->size == SIZE_MAX) {
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

    if (!dictionary_reserve(dictionary, dictionary->size + 1U)) {
        free(value_copy);
        free(key_copy);
        return false;
    }

    entry = &dictionary->entries[dictionary->size];
    entry->key = key_copy;
    entry->type = VALUE_STRING;
    entry->value.string = value_copy;
    ++dictionary->size;

    return true;
}

static bool dictionary_insert_list(
    Dictionary *dictionary,
    const StringList *list)
{
    Dictionary *current;
    size_t index;

    if (dictionary == NULL || list == NULL || list->items == NULL ||
        list->value == NULL || list->length == 0U ||
        list->length > MAX_NESTING_DEPTH) {
        return false;
    }

    current = dictionary;

    for (index = 0U; index + 1U < list->length; ++index) {
        const char *key = list->items[index];
        DictionaryEntry *entry;

        if (key == NULL || key[0] == '\0') {
            return false;
        }

        entry = dictionary_find(current, key);
        if (entry == NULL) {
            Dictionary *child;

            if (!dictionary_add_dictionary(current, key, &child)) {
                return false;
            }
            current = child;
        } else {
            if (entry->type != VALUE_DICTIONARY) {
                return false;
            }
            current = entry->value.dictionary;
        }
    }

    return dictionary_add_string(
        current,
        list->items[list->length - 1U],
        list->value);
}

static bool convert_lists_to_nested_dictionary(
    const StringList *lists,
    size_t list_count,
    Dictionary **result)
{
    Dictionary *dictionary;
    size_t index;

    if (result == NULL) {
        return false;
    }

    *result = NULL;

    if (list_count > 0U && lists == NULL) {
        return false;
    }

    dictionary = dictionary_create();
    if (dictionary == NULL) {
        return false;
    }

    for (index = 0U; index < list_count; ++index) {
        if (!dictionary_insert_list(dictionary, &lists[index])) {
            dictionary_destroy(dictionary);
            return false;
        }
    }

    *result = dictionary;
    return true;
}

static bool print_json_string(FILE *stream, const char *string)
{
    const unsigned char *current;

    if (stream == NULL || string == NULL || fputc('"', stream) == EOF) {
        return false;
    }

    current = (const unsigned char *)string;

    while (*current != '\0') {
        int result;

        switch (*current) {
            case '"':
                result = fputs("\\\"", stream);
                break;
            case '\\':
                result = fputs("\\\\", stream);
                break;
            case '\b':
                result = fputs("\\b", stream);
                break;
            case '\f':
                result = fputs("\\f", stream);
                break;
            case '\n':
                result = fputs("\\n", stream);
                break;
            case '\r':
                result = fputs("\\r", stream);
                break;
            case '\t':
                result = fputs("\\t", stream);
                break;
            default:
                if (*current < 0x20U) {
                    result = fprintf(stream, "\\u%04x", (unsigned int)*current);
                } else {
                    result = fputc((int)*current, stream);
                }
                break;
        }

        if (result < 0) {
            return false;
        }

        ++current;
    }

    return fputc('"', stream) != EOF;
}

static bool dictionary_print_json(FILE *stream, const Dictionary *dictionary)
{
    size_t index;

    if (stream == NULL || dictionary == NULL ||
        fputc('{', stream) == EOF) {
        return false;
    }

    for (index = 0U; index < dictionary->size; ++index) {
        const DictionaryEntry *entry = &dictionary->entries[index];

        if (index > 0U && fputc(',', stream) == EOF) {
            return false;
        }

        if (!print_json_string(stream, entry->key) ||
            fputc(':', stream) == EOF) {
            return false;
        }

        if (entry->type == VALUE_STRING) {
            if (!print_json_string(stream, entry->value.string)) {
                return false;
            }
        } else {
            if (!dictionary_print_json(stream, entry->value.dictionary)) {
                return false;
            }
        }
    }

    return fputc('}', stream) != EOF;
}

int main(void)
{
    static const char *const user_alice_email[] = {
        "users", "alice", "email"
    };
    static const char *const user_alice_role[] = {
        "users", "alice", "role"
    };
    static const char *const user_bob_email[] = {
        "users", "bob", "email"
    };
    static const char *const settings_theme[] = {
        "settings", "theme"
    };
    static const StringList lists[] = {
        { user_alice_email, 3U, "alice@example.com" },
        { user_alice_role, 3U, "administrator" },
        { user_bob_email, 3U, "bob@example.com" },
        { settings_theme, 2U, "dark" }
    };

    Dictionary *dictionary = NULL;
    int status = EXIT_FAILURE;

    if (!convert_lists_to_nested_dictionary(
            lists,
            sizeof(lists) / sizeof(lists[0]),
            &dictionary)) {
        fputs("Failed to create nested dictionary\n", stderr);
        return EXIT_FAILURE;
    }

    if (dictionary_print_json(stdout, dictionary) &&
        fputc('\n', stdout) != EOF &&
        fflush(stdout) == 0) {
        status = EXIT_SUCCESS;
    } else {
        fputs("Failed to print nested dictionary\n", stderr);
    }

    dictionary_destroy(dictionary);
    return status;
}