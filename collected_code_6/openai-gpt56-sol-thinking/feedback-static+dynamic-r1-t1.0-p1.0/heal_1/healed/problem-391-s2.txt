#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_NESTING_DEPTH 128U
#define STRING_VIEW_LITERAL(value) { (value), sizeof(value) - 1U }

typedef struct Dictionary Dictionary;

typedef struct {
    const char *data;
    size_t length;
} StringView;

typedef enum {
    VALUE_STRING,
    VALUE_DICTIONARY
} ValueType;

typedef struct {
    char *key;
    size_t key_length;
    ValueType type;
    union {
        struct {
            char *data;
            size_t length;
        } string;
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

static char *duplicate_string(const char *source, size_t length)
{
    char *copy;
    size_t index;

    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    for (index = 0U; index < length; ++index) {
        copy[index] = source[index];
    }

    copy[length] = '\0';
    return copy;
}

static bool string_equals(
    const char *left,
    size_t left_length,
    const char *right,
    size_t right_length)
{
    size_t index;

    if (left == NULL || right == NULL || left_length != right_length) {
        return false;
    }

    for (index = 0U; index < left_length; ++index) {
        if (left[index] != right[index]) {
            return false;
        }
    }

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

        free(entry->key);

        if (entry->type == VALUE_STRING) {
            free(entry->value.string.data);
        } else if (entry->type == VALUE_DICTIONARY) {
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
    const StringView *key)
{
    size_t index;

    if (dictionary == NULL || key == NULL || key->data == NULL) {
        return NULL;
    }

    for (index = 0U; index < dictionary->size; ++index) {
        DictionaryEntry *entry = &dictionary->entries[index];

        if (string_equals(
                entry->key,
                entry->key_length,
                key->data,
                key->length)) {
            return entry;
        }
    }

    return NULL;
}

static bool dictionary_add_dictionary(
    Dictionary *dictionary,
    const StringView *key,
    Dictionary **child_out)
{
    char *key_copy;
    Dictionary *child;
    DictionaryEntry *entry;

    if (child_out != NULL) {
        *child_out = NULL;
    }

    if (dictionary == NULL || key == NULL || key->data == NULL ||
        key->length == 0U || child_out == NULL ||
        dictionary_find(dictionary, key) != NULL ||
        dictionary->size == SIZE_MAX) {
        return false;
    }

    key_copy = duplicate_string(key->data, key->length);
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
    entry->key_length = key->length;
    entry->type = VALUE_DICTIONARY;
    entry->value.dictionary = child;

    ++dictionary->size;
    *child_out = child;
    return true;
}

static bool dictionary_add_string(
    Dictionary *dictionary,
    const StringView *key,
    const StringView *value)
{
    char *key_copy;
    char *value_copy;
    DictionaryEntry *entry;

    if (dictionary == NULL || key == NULL || value == NULL ||
        key->data == NULL || value->data == NULL ||
        key->length == 0U ||
        dictionary_find(dictionary, key) != NULL ||
        dictionary->size == SIZE_MAX) {
        return false;
    }

    key_copy = duplicate_string(key->data, key->length);
    if (key_copy == NULL) {
        return false;
    }

    value_copy = duplicate_string(value->data, value->length);
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
    entry->key_length = key->length;
    entry->type = VALUE_STRING;
    entry->value.string.data = value_copy;
    entry->value.string.length = value->length;

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
        list->value.data == NULL || list->length == 0U ||
        list->length > MAX_NESTING_DEPTH) {
        return false;
    }

    current = dictionary;

    for (index = 0U; index + 1U < list->length; ++index) {
        const StringView *key = &list->items[index];
        DictionaryEntry *entry;

        if (key->data == NULL || key->length == 0U) {
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
            if (entry->type != VALUE_DICTIONARY ||
                entry->value.dictionary == NULL) {
                return false;
            }

            current = entry->value.dictionary;
        }
    }

    return dictionary_add_string(
        current,
        &list->items[list->length - 1U],
        &list->value);
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

static bool is_utf8_continuation(unsigned char value)
{
    return value >= 0x80U && value <= 0xBFU;
}

static size_t valid_utf8_sequence_length(
    const unsigned char *data,
    size_t remaining)
{
    unsigned char first;

    if (data == NULL || remaining == 0U) {
        return 0U;
    }

    first = data[0];

    if (first <= 0x7FU) {
        return 1U;
    }

    if (first >= 0xC2U && first <= 0xDFU) {
        if (remaining >= 2U && is_utf8_continuation(data[1])) {
            return 2U;
        }

        return 0U;
    }

    if (first == 0xE0U) {
        if (remaining >= 3U &&
            data[1] >= 0xA0U && data[1] <= 0xBFU &&
            is_utf8_continuation(data[2])) {
            return 3U;
        }

        return 0U;
    }

    if ((first >= 0xE1U && first <= 0xECU) ||
        (first >= 0xEEU && first <= 0xEFU)) {
        if (remaining >= 3U &&
            is_utf8_continuation(data[1]) &&
            is_utf8_continuation(data[2])) {
            return 3U;
        }

        return 0U;
    }

    if (first == 0xEDU) {
        if (remaining >= 3U &&
            data[1] >= 0x80U && data[1] <= 0x9FU &&
            is_utf8_continuation(data[2])) {
            return 3U;
        }

        return 0U;
    }

    if (first == 0xF0U) {
        if (remaining >= 4U &&
            data[1] >= 0x90U && data[1] <= 0xBFU &&
            is_utf8_continuation(data[2]) &&
            is_utf8_continuation(data[3])) {
            return 4U;
        }

        return 0U;
    }

    if (first >= 0xF1U && first <= 0xF3U) {
        if (remaining >= 4U &&
            is_utf8_continuation(data[1]) &&
            is_utf8_continuation(data[2]) &&
            is_utf8_continuation(data[3])) {
            return 4U;
        }

        return 0U;
    }

    if (first == 0xF4U) {
        if (remaining >= 4U &&
            data[1] >= 0x80U && data[1] <= 0x8FU &&
            is_utf8_continuation(data[2]) &&
            is_utf8_continuation(data[3])) {
            return 4U;
        }
    }

    return 0U;
}

static bool print_json_string(
    FILE *stream,
    const char *string,
    size_t length)
{
    const unsigned char *data;
    size_t index;

    if (stream == NULL || string == NULL ||
        fputc('"', stream) == EOF) {
        return false;
    }

    data = (const unsigned char *)string;
    index = 0U;

    while (index < length) {
        unsigned char current = data[index];
        int result;

        switch (current) {
            case '"':
                result = fputs("\\\"", stream);
                ++index;
                break;

            case '\\':
                result = fputs("\\\\", stream);
                ++index;
                break;

            case '\b':
                result = fputs("\\b", stream);
                ++index;
                break;

            case '\f':
                result = fputs("\\f", stream);
                ++index;
                break;

            case '\n':
                result = fputs("\\n", stream);
                ++index;
                break;

            case '\r':
                result = fputs("\\r", stream);
                ++index;
                break;

            case '\t':
                result = fputs("\\t", stream);
                ++index;
                break;

            default:
                if (current < 0x20U) {
                    result = fprintf(
                        stream,
                        "\\u%04x",
                        (unsigned int)current);
                    ++index;
                } else if (current < 0x80U) {
                    result = fputc((int)current, stream);
                    ++index;
                } else {
                    size_t sequence_length;
                    size_t sequence_index;

                    sequence_length = valid_utf8_sequence_length(
                        &data[index],
                        length - index);

                    if (sequence_length == 0U) {
                        return false;
                    }

                    result = 0;

                    for (sequence_index = 0U;
                         sequence_index < sequence_length;
                         ++sequence_index) {
                        if (fputc(
                                (int)data[index + sequence_index],
                                stream) == EOF) {
                            result = EOF;
                            break;
                        }
                    }

                    index += sequence_length;
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

    if (stream == NULL || dictionary == NULL ||
        depth > MAX_NESTING_DEPTH ||
        fputc('{', stream) == EOF) {
        return false;
    }

    for (index = 0U; index < dictionary->size; ++index) {
        const DictionaryEntry *entry = &dictionary->entries[index];

        if (index > 0U && fputc(',', stream) == EOF) {
            return false;
        }

        if (!print_json_string(
                stream,
                entry->key,
                entry->key_length) ||
            fputc(':', stream) == EOF) {
            return false;
        }

        if (entry->type == VALUE_STRING) {
            if (!print_json_string(
                    stream,
                    entry->value.string.data,
                    entry->value.string.length)) {
                return false;
            }
        } else if (entry->type == VALUE_DICTIONARY) {
            if (!dictionary_print_json_internal(
                    stream,
                    entry->value.dictionary,
                    depth + 1U)) {
                return false;
            }
        } else {
            return false;
        }
    }

    return fputc('}', stream) != EOF;
}

static bool dictionary_print_json(
    FILE *stream,
    const Dictionary *dictionary)
{
    return dictionary_print_json_internal(stream, dictionary, 0U);
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
            sizeof(user_alice_email) / sizeof(user_alice_email[0]),
            STRING_VIEW_LITERAL("alice@example.com")
        },
        {
            user_alice_role,
            sizeof(user_alice_role) / sizeof(user_alice_role[0]),
            STRING_VIEW_LITERAL("administrator")
        },
        {
            user_bob_email,
            sizeof(user_bob_email) / sizeof(user_bob_email[0]),
            STRING_VIEW_LITERAL("bob@example.com")
        },
        {
            settings_theme,
            sizeof(settings_theme) / sizeof(settings_theme[0]),
            STRING_VIEW_LITERAL("dark")
        }
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