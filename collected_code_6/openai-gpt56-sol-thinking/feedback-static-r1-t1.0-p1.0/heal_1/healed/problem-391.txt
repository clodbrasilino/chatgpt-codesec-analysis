#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_NESTING_DEPTH 256U
#define STRING_VIEW_LITERAL(text) { (text), sizeof(text) - 1U }

typedef enum {
    STATUS_OK,
    STATUS_INVALID_ARGUMENT,
    STATUS_NO_MEMORY,
    STATUS_CONFLICT,
    STATUS_IO_ERROR
} Status;

typedef enum {
    VALUE_STRING,
    VALUE_DICTIONARY
} ValueType;

typedef struct {
    const char *data;
    size_t length;
} StringView;

typedef struct {
    char *data;
    size_t length;
} OwnedString;

typedef struct Dictionary Dictionary;

typedef struct Entry {
    OwnedString key;
    ValueType type;
    union {
        OwnedString string;
        Dictionary *dictionary;
    } value;
    struct Entry *next;
} Entry;

struct Dictionary {
    Entry *head;
    Entry *tail;
};

typedef struct {
    const StringView *items;
    size_t length;
} StringList;

static int string_view_is_valid(StringView string)
{
    return string.data != NULL && string.length < SIZE_MAX;
}

static Status copy_string(StringView source, OwnedString *destination)
{
    char *copy;
    size_t index;

    if (destination == NULL) {
        return STATUS_INVALID_ARGUMENT;
    }

    destination->data = NULL;
    destination->length = 0U;

    if (!string_view_is_valid(source)) {
        return STATUS_INVALID_ARGUMENT;
    }

    copy = malloc(source.length + 1U);
    if (copy == NULL) {
        return STATUS_NO_MEMORY;
    }

    for (index = 0U; index < source.length; ++index) {
        copy[index] = source.data[index];
    }
    copy[source.length] = '\0';

    destination->data = copy;
    destination->length = source.length;
    return STATUS_OK;
}

static void owned_string_destroy(OwnedString *string)
{
    if (string == NULL) {
        return;
    }

    free(string->data);
    string->data = NULL;
    string->length = 0U;
}

static StringView owned_string_view(const OwnedString *string)
{
    StringView view = {NULL, 0U};

    if (string != NULL) {
        view.data = string->data;
        view.length = string->length;
    }

    return view;
}

static int strings_equal(const OwnedString *left, StringView right)
{
    size_t index;

    if (left == NULL || left->data == NULL || !string_view_is_valid(right)) {
        return 0;
    }

    if (left->length != right.length) {
        return 0;
    }

    for (index = 0U; index < left->length; ++index) {
        if (left->data[index] != right.data[index]) {
            return 0;
        }
    }

    return 1;
}

static Dictionary *dictionary_create(void)
{
    return calloc(1U, sizeof(Dictionary));
}

static void dictionary_destroy(Dictionary *dictionary)
{
    Entry *entry;
    Entry *next;

    if (dictionary == NULL) {
        return;
    }

    entry = dictionary->head;
    while (entry != NULL) {
        next = entry->next;
        owned_string_destroy(&entry->key);

        if (entry->type == VALUE_STRING) {
            owned_string_destroy(&entry->value.string);
        } else if (entry->type == VALUE_DICTIONARY) {
            dictionary_destroy(entry->value.dictionary);
        }

        free(entry);
        entry = next;
    }

    free(dictionary);
}

static Entry *dictionary_find(Dictionary *dictionary, StringView key)
{
    Entry *entry;

    if (dictionary == NULL || !string_view_is_valid(key)) {
        return NULL;
    }

    for (entry = dictionary->head; entry != NULL; entry = entry->next) {
        if (strings_equal(&entry->key, key)) {
            return entry;
        }
    }

    return NULL;
}

static void dictionary_append(Dictionary *dictionary, Entry *entry)
{
    if (dictionary == NULL || entry == NULL) {
        return;
    }

    entry->next = NULL;

    if (dictionary->tail == NULL) {
        dictionary->head = entry;
        dictionary->tail = entry;
    } else {
        dictionary->tail->next = entry;
        dictionary->tail = entry;
    }
}

static Status dictionary_add_child(
    Dictionary *dictionary,
    StringView key,
    Dictionary **child)
{
    Dictionary *new_dictionary;
    Entry *entry;
    Status status;

    if (dictionary == NULL || child == NULL ||
        !string_view_is_valid(key)) {
        return STATUS_INVALID_ARGUMENT;
    }

    *child = NULL;

    entry = calloc(1U, sizeof(*entry));
    if (entry == NULL) {
        return STATUS_NO_MEMORY;
    }

    status = copy_string(key, &entry->key);
    if (status != STATUS_OK) {
        free(entry);
        return status;
    }

    new_dictionary = dictionary_create();
    if (new_dictionary == NULL) {
        owned_string_destroy(&entry->key);
        free(entry);
        return STATUS_NO_MEMORY;
    }

    entry->type = VALUE_DICTIONARY;
    entry->value.dictionary = new_dictionary;
    dictionary_append(dictionary, entry);

    *child = new_dictionary;
    return STATUS_OK;
}

static Status dictionary_set_string(
    Dictionary *dictionary,
    StringView key,
    StringView value)
{
    Entry *entry;
    OwnedString value_copy = {NULL, 0U};
    Status status;

    if (dictionary == NULL ||
        !string_view_is_valid(key) ||
        !string_view_is_valid(value)) {
        return STATUS_INVALID_ARGUMENT;
    }

    entry = dictionary_find(dictionary, key);
    if (entry != NULL) {
        if (entry->type != VALUE_STRING) {
            return STATUS_CONFLICT;
        }

        status = copy_string(value, &value_copy);
        if (status != STATUS_OK) {
            return status;
        }

        owned_string_destroy(&entry->value.string);
        entry->value.string = value_copy;
        return STATUS_OK;
    }

    entry = calloc(1U, sizeof(*entry));
    if (entry == NULL) {
        return STATUS_NO_MEMORY;
    }

    status = copy_string(key, &entry->key);
    if (status != STATUS_OK) {
        free(entry);
        return status;
    }

    status = copy_string(value, &entry->value.string);
    if (status != STATUS_OK) {
        owned_string_destroy(&entry->key);
        free(entry);
        return status;
    }

    entry->type = VALUE_STRING;
    dictionary_append(dictionary, entry);

    return STATUS_OK;
}

static Status dictionary_set_path(
    Dictionary *dictionary,
    const StringList *path,
    StringView value)
{
    Dictionary *current;
    size_t index;

    if (dictionary == NULL || path == NULL || path->items == NULL ||
        path->length == 0U || path->length > MAX_NESTING_DEPTH ||
        !string_view_is_valid(value)) {
        return STATUS_INVALID_ARGUMENT;
    }

    current = dictionary;

    for (index = 0U; index + 1U < path->length; ++index) {
        Entry *entry;
        Dictionary *child;
        Status status;

        if (!string_view_is_valid(path->items[index])) {
            return STATUS_INVALID_ARGUMENT;
        }

        entry = dictionary_find(current, path->items[index]);
        if (entry == NULL) {
            status = dictionary_add_child(
                current,
                path->items[index],
                &child
            );
            if (status != STATUS_OK) {
                return status;
            }

            current = child;
        } else {
            if (entry->type != VALUE_DICTIONARY ||
                entry->value.dictionary == NULL) {
                return STATUS_CONFLICT;
            }

            current = entry->value.dictionary;
        }
    }

    if (!string_view_is_valid(path->items[path->length - 1U])) {
        return STATUS_INVALID_ARGUMENT;
    }

    return dictionary_set_string(
        current,
        path->items[path->length - 1U],
        value
    );
}

static Status lists_to_nested_dictionary(
    const StringList *lists,
    const StringView *values,
    size_t list_count,
    Dictionary **result)
{
    Dictionary *dictionary;
    size_t index;

    if (result == NULL) {
        return STATUS_INVALID_ARGUMENT;
    }

    *result = NULL;

    if (lists == NULL || values == NULL || list_count == 0U) {
        return STATUS_INVALID_ARGUMENT;
    }

    for (index = 0U; index < list_count; ++index) {
        size_t item_index;

        if (lists[index].items == NULL ||
            lists[index].length == 0U ||
            lists[index].length > MAX_NESTING_DEPTH ||
            !string_view_is_valid(values[index])) {
            return STATUS_INVALID_ARGUMENT;
        }

        for (item_index = 0U;
             item_index < lists[index].length;
             ++item_index) {
            if (!string_view_is_valid(lists[index].items[item_index])) {
                return STATUS_INVALID_ARGUMENT;
            }
        }
    }

    dictionary = dictionary_create();
    if (dictionary == NULL) {
        return STATUS_NO_MEMORY;
    }

    for (index = 0U; index < list_count; ++index) {
        Status status = dictionary_set_path(
            dictionary,
            &lists[index],
            values[index]
        );

        if (status != STATUS_OK) {
            dictionary_destroy(dictionary);
            return status;
        }
    }

    *result = dictionary;
    return STATUS_OK;
}

static Status print_json_string(FILE *stream, StringView string)
{
    size_t index;

    if (stream == NULL || !string_view_is_valid(string)) {
        return STATUS_INVALID_ARGUMENT;
    }

    if (fputc('"', stream) == EOF) {
        return STATUS_IO_ERROR;
    }

    for (index = 0U; index < string.length; ++index) {
        unsigned char character = (unsigned char)string.data[index];

        switch (character) {
            case '"':
                if (fputs("\\\"", stream) == EOF) {
                    return STATUS_IO_ERROR;
                }
                break;

            case '\\':
                if (fputs("\\\\", stream) == EOF) {
                    return STATUS_IO_ERROR;
                }
                break;

            case '\b':
                if (fputs("\\b", stream) == EOF) {
                    return STATUS_IO_ERROR;
                }
                break;

            case '\f':
                if (fputs("\\f", stream) == EOF) {
                    return STATUS_IO_ERROR;
                }
                break;

            case '\n':
                if (fputs("\\n", stream) == EOF) {
                    return STATUS_IO_ERROR;
                }
                break;

            case '\r':
                if (fputs("\\r", stream) == EOF) {
                    return STATUS_IO_ERROR;
                }
                break;

            case '\t':
                if (fputs("\\t", stream) == EOF) {
                    return STATUS_IO_ERROR;
                }
                break;

            default:
                if (character < 0x20U) {
                    if (fprintf(
                            stream,
                            "\\u%04x",
                            (unsigned int)character
                        ) < 0) {
                        return STATUS_IO_ERROR;
                    }
                } else if (fputc((int)character, stream) == EOF) {
                    return STATUS_IO_ERROR;
                }
                break;
        }
    }

    if (fputc('"', stream) == EOF) {
        return STATUS_IO_ERROR;
    }

    return STATUS_OK;
}

static Status dictionary_print_json(
    FILE *stream,
    const Dictionary *dictionary,
    size_t depth)
{
    const Entry *entry;
    int first;

    if (stream == NULL || dictionary == NULL ||
        depth >= MAX_NESTING_DEPTH) {
        return STATUS_INVALID_ARGUMENT;
    }

    if (fputc('{', stream) == EOF) {
        return STATUS_IO_ERROR;
    }

    first = 1;

    for (entry = dictionary->head; entry != NULL; entry = entry->next) {
        Status status;

        if (!first && fputc(',', stream) == EOF) {
            return STATUS_IO_ERROR;
        }
        first = 0;

        status = print_json_string(
            stream,
            owned_string_view(&entry->key)
        );
        if (status != STATUS_OK) {
            return status;
        }

        if (fputc(':', stream) == EOF) {
            return STATUS_IO_ERROR;
        }

        if (entry->type == VALUE_STRING) {
            status = print_json_string(
                stream,
                owned_string_view(&entry->value.string)
            );
        } else if (entry->type == VALUE_DICTIONARY &&
                   entry->value.dictionary != NULL) {
            status = dictionary_print_json(
                stream,
                entry->value.dictionary,
                depth + 1U
            );
        } else {
            return STATUS_INVALID_ARGUMENT;
        }

        if (status != STATUS_OK) {
            return status;
        }
    }

    if (fputc('}', stream) == EOF) {
        return STATUS_IO_ERROR;
    }

    return STATUS_OK;
}

static const char *status_message(Status status)
{
    switch (status) {
        case STATUS_OK:
            return "success";

        case STATUS_INVALID_ARGUMENT:
            return "invalid argument";

        case STATUS_NO_MEMORY:
            return "memory allocation failed";

        case STATUS_CONFLICT:
            return "dictionary path conflict";

        case STATUS_IO_ERROR:
            return "input/output error";

        default:
            return "unknown error";
    }
}

int main(void)
{
    const StringView person_name[] = {
        STRING_VIEW_LITERAL("person"),
        STRING_VIEW_LITERAL("name")
    };
    const StringView person_city[] = {
        STRING_VIEW_LITERAL("person"),
        STRING_VIEW_LITERAL("address"),
        STRING_VIEW_LITERAL("city")
    };
    const StringView person_country[] = {
        STRING_VIEW_LITERAL("person"),
        STRING_VIEW_LITERAL("address"),
        STRING_VIEW_LITERAL("country")
    };
    const StringView company_name[] = {
        STRING_VIEW_LITERAL("company"),
        STRING_VIEW_LITERAL("name")
    };
    const StringView company_city[] = {
        STRING_VIEW_LITERAL("company"),
        STRING_VIEW_LITERAL("address"),
        STRING_VIEW_LITERAL("city")
    };
    const StringList lists[] = {
        {
            person_name,
            sizeof(person_name) / sizeof(person_name[0])
        },
        {
            person_city,
            sizeof(person_city) / sizeof(person_city[0])
        },
        {
            person_country,
            sizeof(person_country) / sizeof(person_country[0])
        },
        {
            company_name,
            sizeof(company_name) / sizeof(company_name[0])
        },
        {
            company_city,
            sizeof(company_city) / sizeof(company_city[0])
        }
    };
    const StringView values[] = {
        STRING_VIEW_LITERAL("Alice"),
        STRING_VIEW_LITERAL("London"),
        STRING_VIEW_LITERAL("United Kingdom"),
        STRING_VIEW_LITERAL("Example Corporation"),
        STRING_VIEW_LITERAL("Manchester")
    };
    Dictionary *dictionary = NULL;
    Status status;

    status = lists_to_nested_dictionary(
        lists,
        values,
        sizeof(lists) / sizeof(lists[0]),
        &dictionary
    );

    if (status != STATUS_OK) {
        fprintf(
            stderr,
            "Conversion failed: %s\n",
            status_message(status)
        );
        return EXIT_FAILURE;
    }

    status = dictionary_print_json(stdout, dictionary, 0U);

    if (status == STATUS_OK && fputc('\n', stdout) == EOF) {
        status = STATUS_IO_ERROR;
    }

    if (status == STATUS_OK && fflush(stdout) == EOF) {
        status = STATUS_IO_ERROR;
    }

    dictionary_destroy(dictionary);

    if (status != STATUS_OK) {
        fprintf(
            stderr,
            "Output failed: %s\n",
            status_message(status)
        );
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}