#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NESTING_DEPTH 128U
#define STRING_VIEW_LITERAL(value) \
    { (const unsigned char *)(value), sizeof(value) - 1U }

typedef struct Dictionary Dictionary;

typedef struct {
    const unsigned char *data;
    size_t length;
} StringView;

typedef struct {
    char *data;
    size_t length;
} OwnedString;

typedef enum {
    VALUE_STRING,
    VALUE_DICTIONARY
} ValueType;

typedef struct {
    OwnedString key;
    ValueType type;
    union {
        OwnedString string;
        Dictionary *dictionary;
    } value;
} DictionaryEntry;

struct Dictionary {
    DictionaryEntry *entries;
    size_t size;
    size_t capacity;
};

typedef struct {
    const StringView *items;
    size_t length;
    StringView value;
} StringList;

static bool duplicate_bytes(
    const unsigned char *source,
    size_t length,
    char **copy_out)
{
    char *copy;
    size_t allocation_size;
    size_t index;

    if (copy_out == NULL) {
        return false;
    }

    *copy_out = NULL;

    if ((source == NULL && length != 0U) ||
        length > SIZE_MAX - 1U) {
        return false;
    }

    allocation_size = length + 1U;
    copy = malloc(allocation_size);

    if (copy == NULL) {
        return false;
    }

    for (index = 0U; index < length; ++index) {
        ((unsigned char *)copy)[index] = source[index];
    }

    copy[length] = '\0';
    *copy_out = copy;
    return true;
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

        free(entry->key.data);

        switch (entry->type) {
            case VALUE_STRING:
                free(entry->value.string.data);
                break;

            case VALUE_DICTIONARY:
                dictionary_destroy(entry->value.dictionary);
                break;

            default:
                break;
        }
    }

    free(dictionary->entries);
    free(dictionary);
}

static bool dictionary_reserve(
    Dictionary *dictionary,
    size_t required)
{
    size_t capacity;
    DictionaryEntry *entries;

    if (dictionary == NULL) {
        return false;
    }

    if (required <= dictionary->capacity) {
        return true;
    }

    capacity = dictionary->capacity == 0U
        ? 4U
        : dictionary->capacity;

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

    entries = realloc(
        dictionary->entries,
        capacity * sizeof(*entries));

    if (entries == NULL) {
        return false;
    }

    dictionary->entries = entries;
    dictionary->capacity = capacity;
    return true;
}

static DictionaryEntry *dictionary_find(
    Dictionary *dictionary,
    StringView key)
{
    size_t index;

    if (dictionary == NULL ||
        key.data == NULL ||
        key.length == 0U) {
        return NULL;
    }

    for (index = 0U; index < dictionary->size; ++index) {
        DictionaryEntry *entry = &dictionary->entries[index];

        if (entry->key.length == key.length &&
            memcmp(entry->key.data, key.data, key.length) == 0) {
            return entry;
        }
    }

    return NULL;
}

static bool dictionary_add_dictionary(
    Dictionary *dictionary,
    StringView key,
    Dictionary **child_out)
{
    char *key_copy = NULL;
    Dictionary *child = NULL;
    DictionaryEntry *entry;

    if (child_out == NULL) {
        return false;
    }

    *child_out = NULL;

    if (dictionary == NULL ||
        key.data == NULL ||
        key.length == 0U ||
        dictionary->size == SIZE_MAX ||
        dictionary_find(dictionary, key) != NULL) {
        return false;
    }

    if (!duplicate_bytes(key.data, key.length, &key_copy)) {
        return false;
    }

    child = dictionary_create();

    if (child == NULL) {
        free(key_copy);
        return false;
    }

    if (!dictionary_reserve(
            dictionary,
            dictionary->size + 1U)) {
        dictionary_destroy(child);
        free(key_copy);
        return false;
    }

    entry = &dictionary->entries[dictionary->size];
    entry->key.data = key_copy;
    entry->key.length = key.length;
    entry->type = VALUE_DICTIONARY;
    entry->value.dictionary = child;

    ++dictionary->size;
    *child_out = child;
    return true;
}

static bool dictionary_add_string(
    Dictionary *dictionary,
    StringView key,
    StringView value)
{
    char *key_copy = NULL;
    char *value_copy = NULL;
    DictionaryEntry *entry;

    if (dictionary == NULL ||
        key.data == NULL ||
        key.length == 0U ||
        (value.data == NULL && value.length != 0U) ||
        dictionary->size == SIZE_MAX ||
        dictionary_find(dictionary, key) != NULL) {
        return false;
    }

    if (!duplicate_bytes(key.data, key.length, &key_copy)) {
        return false;
    }

    if (!duplicate_bytes(
            value.data,
            value.length,
            &value_copy)) {
        free(key_copy);
        return false;
    }

    if (!dictionary_reserve(
            dictionary,
            dictionary->size + 1U)) {
        free(value_copy);
        free(key_copy);
        return false;
    }

    entry = &dictionary->entries[dictionary->size];
    entry->key.data = key_copy;
    entry->key.length = key.length;
    entry->type = VALUE_STRING;
    entry->value.string.data = value_copy;
    entry->value.string.length = value.length;

    ++dictionary->size;
    return true;
}

static bool dictionary_insert_list(
    Dictionary *dictionary,
    const StringList *list)
{
    Dictionary *current;
    size_t index;

    if (dictionary == NULL ||
        list == NULL ||
        list->items == NULL ||
        list->length == 0U ||
        list->length > MAX_NESTING_DEPTH ||
        (list->value.data == NULL &&
         list->value.length != 0U)) {
        return false;
    }

    current = dictionary;

    for (index = 0U;
         index + 1U < list->length;
         ++index) {
        StringView key = list->items[index];
        DictionaryEntry *entry;

        if (key.data == NULL || key.length == 0U) {
            return false;
        }

        entry = dictionary_find(current, key);

        if (entry == NULL) {
            Dictionary *child = NULL;

            if (!dictionary_add_dictionary(
                    current,
                    key,
                    &child)) {
                return false;
            }

            current = child;
        } else {
            if (entry->type != VALUE_DICTIONARY ||
                entry->value.dictionary == NULL) {
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

    if (list_count != 0U && lists == NULL) {
        return false;
    }

    dictionary = dictionary_create();

    if (dictionary == NULL) {
        return false;
    }

    for (index = 0U; index < list_count; ++index) {
        if (!dictionary_insert_list(
                dictionary,
                &lists[index])) {
            dictionary_destroy(dictionary);
            return false;
        }
    }

    *result = dictionary;
    return true;
}

static bool print_json_string(
    FILE *stream,
    const char *string,
    size_t length)
{
    size_t index;

    if (stream == NULL ||
        (string == NULL && length != 0U) ||
        fputc('"', stream) == EOF) {
        return false;
    }

    for (index = 0U; index < length; ++index) {
        unsigned char character =
            (unsigned char)string[index];
        int result;

        switch (character) {
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
                if (character < 0x20U) {
                    result = fprintf(
                        stream,
                        "\\u%04x",
                        (unsigned int)character);
                } else {
                    result = fputc(
                        (int)character,
                        stream);
                }
                break;
        }

        if (result < 0) {
            return false;
        }
    }

    return fputc('"', stream) != EOF;
}

static bool dictionary_print_json_internal(
    FILE *stream,
    const Dictionary *dictionary,
    size_t depth)
{
    size_t index;

    if (stream == NULL ||
        dictionary == NULL ||
        depth > MAX_NESTING_DEPTH ||
        fputc('{', stream) == EOF) {
        return false;
    }

    for (index = 0U;
         index < dictionary->size;
         ++index) {
        const DictionaryEntry *entry =
            &dictionary->entries[index];

        if (index != 0U &&
            fputc(',', stream) == EOF) {
            return false;
        }

        if (!print_json_string(
                stream,
                entry->key.data,
                entry->key.length) ||
            fputc(':', stream) == EOF) {
            return false;
        }

        switch (entry->type) {
            case VALUE_STRING:
                if (!print_json_string(
                        stream,
                        entry->value.string.data,
                        entry->value.string.length)) {
                    return false;
                }
                break;

            case VALUE_DICTIONARY:
                if (entry->value.dictionary == NULL ||
                    depth == MAX_NESTING_DEPTH ||
                    !dictionary_print_json_internal(
                        stream,
                        entry->value.dictionary,
                        depth + 1U)) {
                    return false;
                }
                break;

            default:
                return false;
        }
    }

    return fputc('}', stream) != EOF;
}

static bool dictionary_print_json(
    FILE *stream,
    const Dictionary *dictionary)
{
    return dictionary_print_json_internal(
        stream,
        dictionary,
        0U);
}

int main(void)
{
    static const StringView user_alice_email[] = {
        STRING_VIEW_LITERAL("users"),
        STRING_VIEW_LITERAL("alice"),
        STRING_VIEW_LITERAL("email")
    };

    static const StringView user_alice_role[] = {
        STRING_VIEW_LITERAL("users"),
        STRING_VIEW_LITERAL("alice"),
        STRING_VIEW_LITERAL("role")
    };

    static const StringView user_bob_email[] = {
        STRING_VIEW_LITERAL("users"),
        STRING_VIEW_LITERAL("bob"),
        STRING_VIEW_LITERAL("email")
    };

    static const StringView settings_theme[] = {
        STRING_VIEW_LITERAL("settings"),
        STRING_VIEW_LITERAL("theme")
    };

    static const StringList lists[] = {
        {
            user_alice_email,
            sizeof(user_alice_email) /
                sizeof(user_alice_email[0]),
            STRING_VIEW_LITERAL("alice@example.com")
        },
        {
            user_alice_role,
            sizeof(user_alice_role) /
                sizeof(user_alice_role[0]),
            STRING_VIEW_LITERAL("administrator")
        },
        {
            user_bob_email,
            sizeof(user_bob_email) /
                sizeof(user_bob_email[0]),
            STRING_VIEW_LITERAL("bob@example.com")
        },
        {
            settings_theme,
            sizeof(settings_theme) /
                sizeof(settings_theme[0]),
            STRING_VIEW_LITERAL("dark")
        }
    };

    Dictionary *dictionary = NULL;
    int status = EXIT_FAILURE;

    if (!convert_lists_to_nested_dictionary(
            lists,
            sizeof(lists) / sizeof(lists[0]),
            &dictionary)) {
        fputs(
            "Failed to create nested dictionary\n",
            stderr);
        return EXIT_FAILURE;
    }

    if (dictionary_print_json(stdout, dictionary) &&
        fputc('\n', stdout) != EOF &&
        fflush(stdout) == 0) {
        status = EXIT_SUCCESS;
    } else {
        fputs(
            "Failed to print nested dictionary\n",
            stderr);
    }

    dictionary_destroy(dictionary);
    return status;
}