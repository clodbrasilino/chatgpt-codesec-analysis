#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *key;
    size_t key_length;
    const char *value;
    size_t value_length;
} ListItem;

typedef struct {
    const char *name;
    size_t name_length;
    const ListItem *items;
    size_t count;
} NamedList;

typedef struct {
    char *key;
    size_t key_length;
    char *value;
    size_t value_length;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    size_t count;
} Dictionary;

typedef struct {
    char *key;
    size_t key_length;
    Dictionary dictionary;
} NestedDictionaryEntry;

typedef struct {
    NestedDictionaryEntry *entries;
    size_t count;
} NestedDictionary;

static void *allocate_array(size_t count, size_t element_size)
{
    if (element_size != 0U && count > SIZE_MAX / element_size) {
        return NULL;
    }

    return calloc(count, element_size);
}

static int copy_string(
    const char *source,
    size_t source_length,
    char **result)
{
    char *copy;
    size_t i;

    if (result == NULL) {
        return EINVAL;
    }

    *result = NULL;

    if (source == NULL) {
        return EINVAL;
    }

    if (source_length == SIZE_MAX) {
        return EOVERFLOW;
    }

    copy = malloc(source_length + 1U);
    if (copy == NULL) {
        return ENOMEM;
    }

    for (i = 0U; i < source_length; ++i) {
        copy[i] = source[i];
    }

    copy[source_length] = '\0';
    *result = copy;
    return 0;
}

static int strings_equal(
    const char *left,
    size_t left_length,
    const char *right,
    size_t right_length)
{
    size_t i;

    if (left_length != right_length) {
        return 0;
    }

    for (i = 0U; i < left_length; ++i) {
        if (left[i] != right[i]) {
            return 0;
        }
    }

    return 1;
}

static void free_dictionary(Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL) {
        return;
    }

    for (i = 0U; i < dictionary->count; ++i) {
        free(dictionary->entries[i].key);
        free(dictionary->entries[i].value);
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->count = 0U;
}

static void free_nested_dictionary(NestedDictionary *nested)
{
    size_t i;

    if (nested == NULL) {
        return;
    }

    for (i = 0U; i < nested->count; ++i) {
        free(nested->entries[i].key);
        free_dictionary(&nested->entries[i].dictionary);
    }

    free(nested->entries);
    free(nested);
}

static int has_duplicate_list_name(
    const NamedList *lists,
    size_t index)
{
    size_t i;

    for (i = 0U; i < index; ++i) {
        if (strings_equal(
                lists[i].name,
                lists[i].name_length,
                lists[index].name,
                lists[index].name_length)) {
            return 1;
        }
    }

    return 0;
}

static int has_duplicate_item_key(
    const ListItem *items,
    size_t index)
{
    size_t i;

    for (i = 0U; i < index; ++i) {
        if (strings_equal(
                items[i].key,
                items[i].key_length,
                items[index].key,
                items[index].key_length)) {
            return 1;
        }
    }

    return 0;
}

static int lists_to_nested_dictionary(
    const NamedList *lists,
    size_t list_count,
    NestedDictionary **result)
{
    NestedDictionary *nested;
    size_t i;
    size_t j;
    /* Possible weaknesses found:
     *  The scope of the variable 'status' can be reduced. [variableScope]
     */
    int status;

    if (result == NULL) {
        return EINVAL;
    }

    *result = NULL;

    if (list_count != 0U && lists == NULL) {
        return EINVAL;
    }

    nested = calloc(1U, sizeof(*nested));
    if (nested == NULL) {
        return ENOMEM;
    }

    if (list_count != 0U) {
        nested->entries = allocate_array(
            list_count,
            sizeof(*nested->entries));

        if (nested->entries == NULL) {
            free_nested_dictionary(nested);
            return ENOMEM;
        }
    }

    nested->count = list_count;

    for (i = 0U; i < list_count; ++i) {
        Dictionary *dictionary = &nested->entries[i].dictionary;

        if (lists[i].name == NULL ||
            (lists[i].count != 0U && lists[i].items == NULL)) {
            free_nested_dictionary(nested);
            return EINVAL;
        }

        if (has_duplicate_list_name(lists, i)) {
            free_nested_dictionary(nested);
            return EEXIST;
        }

        status = copy_string(
            lists[i].name,
            lists[i].name_length,
            &nested->entries[i].key);

        if (status != 0) {
            free_nested_dictionary(nested);
            return status;
        }

        nested->entries[i].key_length = lists[i].name_length;

        if (lists[i].count != 0U) {
            dictionary->entries = allocate_array(
                lists[i].count,
                sizeof(*dictionary->entries));

            if (dictionary->entries == NULL) {
                free_nested_dictionary(nested);
                return ENOMEM;
            }
        }

        dictionary->count = lists[i].count;

        for (j = 0U; j < lists[i].count; ++j) {
            DictionaryEntry *entry = &dictionary->entries[j];
            const ListItem *item = &lists[i].items[j];

            if (item->key == NULL || item->value == NULL) {
                free_nested_dictionary(nested);
                return EINVAL;
            }

            if (has_duplicate_item_key(lists[i].items, j)) {
                free_nested_dictionary(nested);
                return EEXIST;
            }

            status = copy_string(
                item->key,
                item->key_length,
                &entry->key);

            if (status != 0) {
                free_nested_dictionary(nested);
                return status;
            }

            entry->key_length = item->key_length;

            status = copy_string(
                item->value,
                item->value_length,
                &entry->value);

            if (status != 0) {
                free_nested_dictionary(nested);
                return status;
            }

            entry->value_length = item->value_length;
        }
    }

    *result = nested;
    return 0;
}

static int write_text(const char *text)
{
    if (fputs(text, stdout) == EOF) {
        return EIO;
    }

    return 0;
}

static int write_json_string(const char *string, size_t length)
{
    size_t i;

    if (string == NULL) {
        return EINVAL;
    }

    if (fputc('"', stdout) == EOF) {
        return EIO;
    }

    for (i = 0U; i < length; ++i) {
        unsigned char character = (unsigned char)string[i];

        switch (character) {
            case '"':
                if (write_text("\\\"") != 0) {
                    return EIO;
                }
                break;

            case '\\':
                if (write_text("\\\\") != 0) {
                    return EIO;
                }
                break;

            case '\b':
                if (write_text("\\b") != 0) {
                    return EIO;
                }
                break;

            case '\f':
                if (write_text("\\f") != 0) {
                    return EIO;
                }
                break;

            case '\n':
                if (write_text("\\n") != 0) {
                    return EIO;
                }
                break;

            case '\r':
                if (write_text("\\r") != 0) {
                    return EIO;
                }
                break;

            case '\t':
                if (write_text("\\t") != 0) {
                    return EIO;
                }
                break;

            default:
                if (character < 0x20U) {
                    if (fprintf(stdout, "\\u%04X", (unsigned int)character) < 0) {
                        return EIO;
                    }
                } else if (fputc((int)character, stdout) == EOF) {
                    return EIO;
                }
                break;
        }
    }

    if (fputc('"', stdout) == EOF) {
        return EIO;
    }

    return 0;
}

static int print_nested_dictionary(const NestedDictionary *nested)
{
    size_t i;
    size_t j;
    int status;

    if (nested == NULL) {
        return EINVAL;
    }

    status = write_text("{\n");
    if (status != 0) {
        return status;
    }

    for (i = 0U; i < nested->count; ++i) {
        const NestedDictionaryEntry *outer = &nested->entries[i];

        status = write_text("  ");
        if (status != 0) {
            return status;
        }

        status = write_json_string(outer->key, outer->key_length);
        if (status != 0) {
            return status;
        }

        status = write_text(": {\n");
        if (status != 0) {
            return status;
        }

        for (j = 0U; j < outer->dictionary.count; ++j) {
            const DictionaryEntry *inner =
                &outer->dictionary.entries[j];

            status = write_text("    ");
            if (status != 0) {
                return status;
            }

            status = write_json_string(
                inner->key,
                inner->key_length);

            if (status != 0) {
                return status;
            }

            status = write_text(": ");
            if (status != 0) {
                return status;
            }

            status = write_json_string(
                inner->value,
                inner->value_length);

            if (status != 0) {
                return status;
            }

            status = write_text(
                j + 1U < outer->dictionary.count ? ",\n" : "\n");

            if (status != 0) {
                return status;
            }
        }

        status = write_text(
            i + 1U < nested->count ? "  },\n" : "  }\n");

        if (status != 0) {
            return status;
        }
    }

    return write_text("}\n");
}

#define LIST_ITEM(key_literal, value_literal) \
    {                                         \
        (key_literal),                        \
        sizeof(key_literal) - 1U,             \
        (value_literal),                      \
        sizeof(value_literal) - 1U            \
    }

#define NAMED_LIST(name_literal, item_array)               \
    {                                                       \
        (name_literal),                                     \
        sizeof(name_literal) - 1U,                          \
        (item_array),                                       \
        sizeof(item_array) / sizeof((item_array)[0])        \
    }

int main(void)
{
    const ListItem personal[] = {
        LIST_ITEM("name", "Alice"),
        LIST_ITEM("age", "30"),
        LIST_ITEM("city", "London")
    };

    const ListItem employment[] = {
        LIST_ITEM("company", "Example Corp"),
        LIST_ITEM("position", "Developer")
    };

    const ListItem contact[] = {
        LIST_ITEM("email", "alice@example.com"),
        LIST_ITEM("phone", "+1-555-0100")
    };

    const NamedList lists[] = {
        NAMED_LIST("personal", personal),
        NAMED_LIST("employment", employment),
        NAMED_LIST("contact", contact)
    };

    NestedDictionary *nested = NULL;
    int status;

    status = lists_to_nested_dictionary(
        lists,
        sizeof(lists) / sizeof(lists[0]),
        &nested);

    if (status != 0) {
        fprintf(stderr, "Conversion failed: %d\n", status);
        return EXIT_FAILURE;
    }

    status = print_nested_dictionary(nested);
    free_nested_dictionary(nested);

    if (status != 0) {
        fprintf(stderr, "Output failed: %d\n", status);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}