#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *key;
    const char *value;
} ListItem;

typedef struct {
    const char *name;
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

static void *allocate_array(size_t count, size_t element_size)
{
    if (element_size != 0U && count > SIZE_MAX / element_size) {
        return NULL;
    }

    return calloc(count, element_size);
}

static char *copy_string(const char *source)
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
        if (strcmp(lists[i].name, lists[index].name) == 0) {
            return 1;
        }
    }

    return 0;
}

static int has_duplicate_item_key(const ListItem *items, size_t index)
{
    size_t i;

    for (i = 0U; i < index; ++i) {
        if (strcmp(items[i].key, items[index].key) == 0) {
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

        nested->entries[i].key = copy_string(lists[i].name);
        if (nested->entries[i].key == NULL) {
            free_nested_dictionary(nested);
            return ENOMEM;
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
            if (lists[i].items[j].key == NULL ||
                lists[i].items[j].value == NULL) {
                free_nested_dictionary(nested);
                return EINVAL;
            }

            if (has_duplicate_item_key(lists[i].items, j)) {
                free_nested_dictionary(nested);
                return EEXIST;
            }

            dictionary->entries[j].key =
                copy_string(lists[i].items[j].key);
            dictionary->entries[j].value =
                copy_string(lists[i].items[j].value);

            if (dictionary->entries[j].key == NULL ||
                dictionary->entries[j].value == NULL) {
                free_nested_dictionary(nested);
                return ENOMEM;
            }
        }
    }

    *result = nested;
    return 0;
}

static int print_nested_dictionary(const NestedDictionary *nested)
{
    size_t i;
    size_t j;

    if (nested == NULL) {
        return EINVAL;
    }

    if (printf("{\n") < 0) {
        return EIO;
    }

    for (i = 0U; i < nested->count; ++i) {
        const NestedDictionaryEntry *outer = &nested->entries[i];

        if (printf("  \"%s\": {\n", outer->key) < 0) {
            return EIO;
        }

        for (j = 0U; j < outer->dictionary.count; ++j) {
            const DictionaryEntry *inner =
                &outer->dictionary.entries[j];

            if (printf(
                    "    \"%s\": \"%s\"%s\n",
                    inner->key,
                    inner->value,
                    j + 1U < outer->dictionary.count ? "," : "") < 0) {
                return EIO;
            }
        }

        if (printf(
                "  }%s\n",
                i + 1U < nested->count ? "," : "") < 0) {
            return EIO;
        }
    }

    if (printf("}\n") < 0) {
        return EIO;
    }

    return 0;
}

int main(void)
{
    const ListItem personal[] = {
        {"name", "Alice"},
        {"age", "30"},
        {"city", "London"}
    };
    const ListItem employment[] = {
        {"company", "Example Corp"},
        {"position", "Developer"}
    };
    const ListItem contact[] = {
        {"email", "alice@example.com"},
        {"phone", "+1-555-0100"}
    };
    const NamedList lists[] = {
        {"personal", personal, sizeof(personal) / sizeof(personal[0])},
        {"employment", employment, sizeof(employment) / sizeof(employment[0])},
        {"contact", contact, sizeof(contact) / sizeof(contact[0])}
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