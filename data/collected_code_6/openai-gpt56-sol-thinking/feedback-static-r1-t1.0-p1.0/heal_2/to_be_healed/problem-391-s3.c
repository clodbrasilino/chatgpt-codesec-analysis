#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *data;
    size_t length;
} Text;

typedef struct {
    Text key;
    Text value;
} ListItem;

typedef struct {
    Text name;
    const ListItem *items;
    size_t count;
} NamedList;

typedef struct {
    char *key;
    char *value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    size_t count;
} Dictionary;

typedef struct {
    char *key;
    Dictionary dictionary;
} NestedDictionaryEntry;

typedef struct {
    NestedDictionaryEntry *entries;
    size_t count;
} NestedDictionary;

#define TEXT_LITERAL(value) { (value), sizeof(value) - 1U }

static void *allocate_array(size_t count, size_t element_size)
{
    if (element_size != 0U && count > SIZE_MAX / element_size) {
        return NULL;
    }

    return calloc(count, element_size);
}

static int text_is_valid(Text text)
{
    size_t i;

    if (text.data == NULL || text.length == SIZE_MAX) {
        return 0;
    }

    for (i = 0U; i < text.length; ++i) {
        if (text.data[i] == '\0') {
            return 0;
        }
    }

    return 1;
}

static int text_equal(Text left, Text right)
{
    size_t i;

    if (left.length != right.length) {
        return 0;
    }

    for (i = 0U; i < left.length; ++i) {
        if (left.data[i] != right.data[i]) {
            return 0;
        }
    }

    return 1;
}

static int copy_text(Text source, char **result)
{
    char *copy;
    size_t i;

    if (result == NULL) {
        return EINVAL;
    }

    *result = NULL;

    if (!text_is_valid(source)) {
        return EINVAL;
    }

    copy = malloc(source.length + 1U);
    if (copy == NULL) {
        return ENOMEM;
    }

    for (i = 0U; i < source.length; ++i) {
        copy[i] = source.data[i];
    }

    copy[source.length] = '\0';
    *result = copy;

    return 0;
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

static int has_duplicate_list_name(const NamedList *lists, size_t index)
{
    size_t i;

    for (i = 0U; i < index; ++i) {
        if (text_equal(lists[i].name, lists[index].name)) {
            return 1;
        }
    }

    return 0;
}

static int has_duplicate_item_key(const ListItem *items, size_t index)
{
    size_t i;

    for (i = 0U; i < index; ++i) {
        if (text_equal(items[i].key, items[index].key)) {
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

        if (!text_is_valid(lists[i].name) ||
            (lists[i].count != 0U && lists[i].items == NULL)) {
            free_nested_dictionary(nested);
            return EINVAL;
        }

        if (has_duplicate_list_name(lists, i)) {
            free_nested_dictionary(nested);
            return EEXIST;
        }

        status = copy_text(lists[i].name, &nested->entries[i].key);
        if (status != 0) {
            free_nested_dictionary(nested);
            return status;
        }

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
            if (!text_is_valid(lists[i].items[j].key) ||
                !text_is_valid(lists[i].items[j].value)) {
                free_nested_dictionary(nested);
                return EINVAL;
            }

            if (has_duplicate_item_key(lists[i].items, j)) {
                free_nested_dictionary(nested);
                return EEXIST;
            }

            status = copy_text(
                lists[i].items[j].key,
                &dictionary->entries[j].key);

            if (status != 0) {
                free_nested_dictionary(nested);
                return status;
            }

            status = copy_text(
                lists[i].items[j].value,
                &dictionary->entries[j].value);

            if (status != 0) {
                free_nested_dictionary(nested);
                return status;
            }
        }
    }

    *result = nested;
    return 0;
}

static int print_json_string(const char *text)
{
    const unsigned char *current;

    if (text == NULL) {
        return EINVAL;
    }

    if (putchar('"') == EOF) {
        return EIO;
    }

    current = (const unsigned char *)text;

    while (*current != '\0') {
        switch (*current) {
            case '"':
                if (fputs("\\\"", stdout) < 0) {
                    return EIO;
                }
                break;

            case '\\':
                if (fputs("\\\\", stdout) < 0) {
                    return EIO;
                }
                break;

            case '\b':
                if (fputs("\\b", stdout) < 0) {
                    return EIO;
                }
                break;

            case '\f':
                if (fputs("\\f", stdout) < 0) {
                    return EIO;
                }
                break;

            case '\n':
                if (fputs("\\n", stdout) < 0) {
                    return EIO;
                }
                break;

            case '\r':
                if (fputs("\\r", stdout) < 0) {
                    return EIO;
                }
                break;

            case '\t':
                if (fputs("\\t", stdout) < 0) {
                    return EIO;
                }
                break;

            default:
                if (*current < 0x20U) {
                    if (printf("\\u%04X", (unsigned int)*current) < 0) {
                        return EIO;
                    }
                } else if (putchar((int)*current) == EOF) {
                    return EIO;
                }
                break;
        }

        ++current;
    }

    if (putchar('"') == EOF) {
        return EIO;
    }

    return 0;
}

static int print_nested_dictionary(const NestedDictionary *nested)
{
    size_t i;
    size_t j;
    /* Possible weaknesses found:
     *  The scope of the variable 'status' can be reduced. [variableScope]
     */
    int status;

    if (nested == NULL) {
        return EINVAL;
    }

    if (fputs("{\n", stdout) < 0) {
        return EIO;
    }

    for (i = 0U; i < nested->count; ++i) {
        const NestedDictionaryEntry *outer = &nested->entries[i];

        if (fputs("  ", stdout) < 0) {
            return EIO;
        }

        status = print_json_string(outer->key);
        if (status != 0) {
            return status;
        }

        if (fputs(": {\n", stdout) < 0) {
            return EIO;
        }

        for (j = 0U; j < outer->dictionary.count; ++j) {
            const DictionaryEntry *inner =
                &outer->dictionary.entries[j];

            if (fputs("    ", stdout) < 0) {
                return EIO;
            }

            status = print_json_string(inner->key);
            if (status != 0) {
                return status;
            }

            if (fputs(": ", stdout) < 0) {
                return EIO;
            }

            status = print_json_string(inner->value);
            if (status != 0) {
                return status;
            }

            if (j + 1U < outer->dictionary.count &&
                putchar(',') == EOF) {
                return EIO;
            }

            if (putchar('\n') == EOF) {
                return EIO;
            }
        }

        if (fputs("  }", stdout) < 0) {
            return EIO;
        }

        if (i + 1U < nested->count && putchar(',') == EOF) {
            return EIO;
        }

        if (putchar('\n') == EOF) {
            return EIO;
        }
    }

    if (fputs("}\n", stdout) < 0) {
        return EIO;
    }

    return 0;
}

int main(void)
{
    const ListItem personal[] = {
        {TEXT_LITERAL("name"), TEXT_LITERAL("Alice")},
        {TEXT_LITERAL("age"), TEXT_LITERAL("30")},
        {TEXT_LITERAL("city"), TEXT_LITERAL("London")}
    };
    const ListItem employment[] = {
        {TEXT_LITERAL("company"), TEXT_LITERAL("Example Corp")},
        {TEXT_LITERAL("position"), TEXT_LITERAL("Developer")}
    };
    const ListItem contact[] = {
        {TEXT_LITERAL("email"), TEXT_LITERAL("alice@example.com")},
        {TEXT_LITERAL("phone"), TEXT_LITERAL("+1-555-0100")}
    };
    const NamedList lists[] = {
        {
            TEXT_LITERAL("personal"),
            personal,
            sizeof(personal) / sizeof(personal[0])
        },
        {
            TEXT_LITERAL("employment"),
            employment,
            sizeof(employment) / sizeof(employment[0])
        },
        {
            TEXT_LITERAL("contact"),
            contact,
            sizeof(contact) / sizeof(contact[0])
        }
    };
    NestedDictionary *nested = NULL;
    int status;

    status = lists_to_nested_dictionary(
        lists,
        sizeof(lists) / sizeof(lists[0]),
        &nested);

    if (status != 0) {
        fprintf(stderr, "Conversion failed: %s\n", strerror(status));
        return EXIT_FAILURE;
    }

    status = print_nested_dictionary(nested);
    free_nested_dictionary(nested);

    if (status != 0) {
        fprintf(stderr, "Output failed: %s\n", strerror(status));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}