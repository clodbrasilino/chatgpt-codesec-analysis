#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NESTING_DEPTH 256U

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

typedef struct Dictionary Dictionary;

typedef struct Entry {
    char *key;
    ValueType type;
    union {
        char *string;
        Dictionary *dictionary;
    } value;
    struct Entry *next;
} Entry;

struct Dictionary {
    Entry *head;
    Entry *tail;
};

typedef struct {
    const char *const *items;
    size_t length;
} StringList;

static char *copy_string(const char *source)
{
    size_t length;
    char *copy;

    if (source == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(source);
    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, source, length + 1U);
    return copy;
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
        free(entry->key);

        if (entry->type == VALUE_STRING) {
            free(entry->value.string);
        } else {
            dictionary_destroy(entry->value.dictionary);
        }

        free(entry);
        entry = next;
    }

    free(dictionary);
}

static Entry *dictionary_find(Dictionary *dictionary, const char *key)
{
    Entry *entry;

    if (dictionary == NULL || key == NULL) {
        return NULL;
    }

    for (entry = dictionary->head; entry != NULL; entry = entry->next) {
        if (strcmp(entry->key, key) == 0) {
            return entry;
        }
    }

    return NULL;
}

static void dictionary_append(Dictionary *dictionary, Entry *entry)
{
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
    const char *key,
    Dictionary **child)
{
    Entry *entry;
    Dictionary *new_dictionary;
    char *key_copy;

    if (dictionary == NULL || key == NULL || child == NULL) {
        return STATUS_INVALID_ARGUMENT;
    }

    *child = NULL;
    key_copy = copy_string(key);
    if (key_copy == NULL) {
        return STATUS_NO_MEMORY;
    }

    new_dictionary = dictionary_create();
    if (new_dictionary == NULL) {
        free(key_copy);
        return STATUS_NO_MEMORY;
    }

    entry = calloc(1U, sizeof(*entry));
    if (entry == NULL) {
        dictionary_destroy(new_dictionary);
        free(key_copy);
        return STATUS_NO_MEMORY;
    }

    entry->key = key_copy;
    entry->type = VALUE_DICTIONARY;
    entry->value.dictionary = new_dictionary;
    dictionary_append(dictionary, entry);
    *child = new_dictionary;

    return STATUS_OK;
}

static Status dictionary_set_string(
    Dictionary *dictionary,
    const char *key,
    const char *value)
{
    Entry *entry;
    char *key_copy;
    char *value_copy;

    if (dictionary == NULL || key == NULL || value == NULL) {
        return STATUS_INVALID_ARGUMENT;
    }

    entry = dictionary_find(dictionary, key);
    if (entry != NULL) {
        if (entry->type != VALUE_STRING) {
            return STATUS_CONFLICT;
        }

        value_copy = copy_string(value);
        if (value_copy == NULL) {
            return STATUS_NO_MEMORY;
        }

        free(entry->value.string);
        entry->value.string = value_copy;
        return STATUS_OK;
    }

    key_copy = copy_string(key);
    if (key_copy == NULL) {
        return STATUS_NO_MEMORY;
    }

    value_copy = copy_string(value);
    if (value_copy == NULL) {
        free(key_copy);
        return STATUS_NO_MEMORY;
    }

    entry = calloc(1U, sizeof(*entry));
    if (entry == NULL) {
        free(value_copy);
        free(key_copy);
        return STATUS_NO_MEMORY;
    }

    entry->key = key_copy;
    entry->type = VALUE_STRING;
    entry->value.string = value_copy;
    dictionary_append(dictionary, entry);

    return STATUS_OK;
}

static Status dictionary_set_path(
    Dictionary *dictionary,
    const StringList *path,
    const char *value)
{
    Dictionary *current;
    Dictionary *child;
    Entry *entry;
    Status status;
    size_t index;

    if (dictionary == NULL || path == NULL || path->items == NULL ||
        path->length == 0U || path->length > MAX_NESTING_DEPTH ||
        value == NULL) {
        return STATUS_INVALID_ARGUMENT;
    }

    current = dictionary;

    for (index = 0U; index + 1U < path->length; ++index) {
        if (path->items[index] == NULL) {
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
            if (entry->type != VALUE_DICTIONARY) {
                return STATUS_CONFLICT;
            }
            current = entry->value.dictionary;
        }
    }

    if (path->items[path->length - 1U] == NULL) {
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
    const char *const *values,
    size_t list_count,
    Dictionary **result)
{
    Dictionary *dictionary;
    /* Possible weaknesses found:
     *  The scope of the variable 'status' can be reduced. [variableScope]
     */
    Status status;
    size_t index;
    size_t item_index;

    if (result == NULL) {
        return STATUS_INVALID_ARGUMENT;
    }

    *result = NULL;

    if (lists == NULL || values == NULL || list_count == 0U) {
        return STATUS_INVALID_ARGUMENT;
    }

    for (index = 0U; index < list_count; ++index) {
        if (lists[index].items == NULL ||
            lists[index].length == 0U ||
            lists[index].length > MAX_NESTING_DEPTH ||
            values[index] == NULL) {
            return STATUS_INVALID_ARGUMENT;
        }

        for (item_index = 0U;
             item_index < lists[index].length;
             ++item_index) {
            if (lists[index].items[item_index] == NULL) {
                return STATUS_INVALID_ARGUMENT;
            }
        }
    }

    dictionary = dictionary_create();
    if (dictionary == NULL) {
        return STATUS_NO_MEMORY;
    }

    for (index = 0U; index < list_count; ++index) {
        status = dictionary_set_path(
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

static Status print_json_string(FILE *stream, const char *string)
{
    const unsigned char *cursor;

    if (stream == NULL || string == NULL) {
        return STATUS_INVALID_ARGUMENT;
    }

    if (fputc('"', stream) == EOF) {
        return STATUS_IO_ERROR;
    }

    for (cursor = (const unsigned char *)string; *cursor != '\0'; ++cursor) {
        switch (*cursor) {
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
                if (*cursor < 0x20U) {
                    if (fprintf(stream, "\\u%04x", (unsigned int)*cursor) < 0) {
                        return STATUS_IO_ERROR;
                    }
                } else if (fputc((int)*cursor, stream) == EOF) {
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
    /* Possible weaknesses found:
     *  The scope of the variable 'status' can be reduced. [variableScope]
     */
    Status status;
    int first;

    if (stream == NULL || dictionary == NULL ||
        depth > MAX_NESTING_DEPTH) {
        return STATUS_INVALID_ARGUMENT;
    }

    if (fputc('{', stream) == EOF) {
        return STATUS_IO_ERROR;
    }

    first = 1;
    for (entry = dictionary->head; entry != NULL; entry = entry->next) {
        if (!first && fputc(',', stream) == EOF) {
            return STATUS_IO_ERROR;
        }
        first = 0;

        status = print_json_string(stream, entry->key);
        if (status != STATUS_OK) {
            return status;
        }

        if (fputc(':', stream) == EOF) {
            return STATUS_IO_ERROR;
        }

        if (entry->type == VALUE_STRING) {
            status = print_json_string(stream, entry->value.string);
        } else {
            status = dictionary_print_json(
                stream,
                entry->value.dictionary,
                depth + 1U
            );
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
    const char *person_name[] = {"person", "name"};
    const char *person_city[] = {"person", "address", "city"};
    const char *person_country[] = {"person", "address", "country"};
    const char *company_name[] = {"company", "name"};
    const char *company_city[] = {"company", "address", "city"};

    const StringList lists[] = {
        {person_name, sizeof(person_name) / sizeof(person_name[0])},
        {person_city, sizeof(person_city) / sizeof(person_city[0])},
        {person_country, sizeof(person_country) / sizeof(person_country[0])},
        {company_name, sizeof(company_name) / sizeof(company_name[0])},
        {company_city, sizeof(company_city) / sizeof(company_city[0])}
    };

    const char *values[] = {
        "Alice",
        "London",
        "United Kingdom",
        "Example Corporation",
        "Manchester"
    };

    Dictionary *dictionary;
    Status status;

    dictionary = NULL;
    status = lists_to_nested_dictionary(
        lists,
        values,
        sizeof(lists) / sizeof(lists[0]),
        &dictionary
    );

    if (status != STATUS_OK) {
        fprintf(stderr, "Conversion failed: %s\n", status_message(status));
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
        fprintf(stderr, "Output failed: %s\n", status_message(status));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}