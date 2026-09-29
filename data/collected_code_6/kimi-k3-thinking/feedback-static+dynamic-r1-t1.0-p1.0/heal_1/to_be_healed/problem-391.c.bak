#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    VALUE_STRING,
    VALUE_DICT
} ValueType;

typedef struct Dict Dict;

typedef struct DictEntry {
    char *key;
    ValueType type;
    union {
        char *str_value;
        Dict *dict_value;
    } data;
    struct DictEntry *next;
} DictEntry;

struct Dict {
    DictEntry *head;
    size_t size;
};

Dict *dict_create(void);
void dict_free(Dict *dict);
int dict_set_string(Dict *dict, const char *key, const char *value);
Dict *dict_get_or_create_nested(Dict *dict, const char *key);
Dict *lists_to_nested_dict(const char ***lists, const size_t *lengths, size_t list_count);
void dict_print(const Dict *dict, size_t depth);

static char *duplicate_string(const char *src)
{
    size_t len;
    char *copy;

    if (src == NULL) {
        return NULL;
    }
    len = strlen(src);
    copy = (char *)malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, src, len + 1);
    return copy;
}

Dict *dict_create(void)
{
    Dict *dict = (Dict *)malloc(sizeof(Dict));
    if (dict == NULL) {
        return NULL;
    }
    dict->head = NULL;
    dict->size = 0;
    return dict;
}

static DictEntry *dict_find_entry(const Dict *dict, const char *key)
{
    DictEntry *current;

    if (dict == NULL || key == NULL) {
        return NULL;
    }
    current = dict->head;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void dict_free(Dict *dict)
{
    DictEntry *current;
    DictEntry *next;

    if (dict == NULL) {
        return;
    }
    current = dict->head;
    while (current != NULL) {
        next = current->next;
        free(current->key);
        if (current->type == VALUE_STRING) {
            free(current->data.str_value);
        } else {
            dict_free(current->data.dict_value);
        }
        free(current);
        current = next;
    }
    free(dict);
}

int dict_set_string(Dict *dict, const char *key, const char *value)
{
    DictEntry *entry;
    char *key_copy;
    char *value_copy;

    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }

    entry = dict_find_entry(dict, key);
    if (entry != NULL) {
        if (entry->type != VALUE_STRING) {
            return -1;
        }
        value_copy = duplicate_string(value);
        if (value_copy == NULL) {
            return -1;
        }
        free(entry->data.str_value);
        entry->data.str_value = value_copy;
        return 0;
    }

    entry = (DictEntry *)malloc(sizeof(DictEntry));
    if (entry == NULL) {
        return -1;
    }
    key_copy = duplicate_string(key);
    if (key_copy == NULL) {
        free(entry);
        return -1;
    }
    value_copy = duplicate_string(value);
    if (value_copy == NULL) {
        free(key_copy);
        free(entry);
        return -1;
    }
    entry->key = key_copy;
    entry->type = VALUE_STRING;
    entry->data.str_value = value_copy;
    entry->next = dict->head;
    dict->head = entry;
    dict->size++;
    return 0;
}

Dict *dict_get_or_create_nested(Dict *dict, const char *key)
{
    DictEntry *entry;
    char *key_copy;
    Dict *nested;

    if (dict == NULL || key == NULL) {
        return NULL;
    }

    entry = dict_find_entry(dict, key);
    if (entry != NULL) {
        if (entry->type != VALUE_DICT) {
            return NULL;
        }
        return entry->data.dict_value;
    }

    nested = dict_create();
    if (nested == NULL) {
        return NULL;
    }
    entry = (DictEntry *)malloc(sizeof(DictEntry));
    if (entry == NULL) {
        dict_free(nested);
        return NULL;
    }
    key_copy = duplicate_string(key);
    if (key_copy == NULL) {
        free(entry);
        dict_free(nested);
        return NULL;
    }
    entry->key = key_copy;
    entry->type = VALUE_DICT;
    entry->data.dict_value = nested;
    entry->next = dict->head;
    dict->head = entry;
    dict->size++;
    return nested;
}

Dict *lists_to_nested_dict(const char ***lists, const size_t *lengths, size_t list_count)
{
    Dict *root;
    /* Possible weaknesses found:
     *  The scope of the variable 'current' can be reduced. [variableScope]
     */
    Dict *current;
    Dict *next;
    size_t i;
    size_t row;
    size_t row_count;
    /* Possible weaknesses found:
     *  The scope of the variable 'failed' can be reduced. [variableScope]
     */
    int failed;

    if (lists == NULL || lengths == NULL || list_count < 2) {
        return NULL;
    }

    row_count = lengths[0];
    for (i = 0; i < list_count; i++) {
        if (lists[i] == NULL || lengths[i] != row_count) {
            return NULL;
        }
    }

    root = dict_create();
    if (root == NULL) {
        return NULL;
    }

    for (row = 0; row < row_count; row++) {
        current = root;
        failed = 0;

        for (i = 0; i + 1 < list_count; i++) {
            if (lists[i][row] == NULL) {
                failed = 1;
                break;
            }
            if (i + 2 == list_count) {
                if (lists[list_count - 1][row] == NULL) {
                    failed = 1;
                    break;
                }
                if (dict_set_string(current, lists[i][row],
                                    lists[list_count - 1][row]) != 0) {
                    failed = 1;
                    break;
                }
            } else {
                next = dict_get_or_create_nested(current, lists[i][row]);
                if (next == NULL) {
                    failed = 1;
                    break;
                }
                current = next;
            }
        }

        if (failed) {
            dict_free(root);
            return NULL;
        }
    }

    return root;
}

static void print_indent(size_t depth)
{
    size_t i;

    for (i = 0; i < depth; i++) {
        printf("  ");
    }
}

void dict_print(const Dict *dict, size_t depth)
{
    const DictEntry *current;

    if (dict == NULL) {
        return;
    }
    print_indent(depth);
    printf("{\n");
    current = dict->head;
    while (current != NULL) {
        print_indent(depth + 1);
        printf("\"%s\": ", current->key);
        if (current->type == VALUE_STRING) {
            printf("\"%s\"\n", current->data.str_value);
        } else {
            printf("\n");
            dict_print(current->data.dict_value, depth + 1);
        }
        current = current->next;
    }
    print_indent(depth);
    printf("}\n");
}

int main(void)
{
    const char *countries[] = {"US", "US", "FR", "FR", "JP"};
    const char *cities[] = {"NewYork", "Chicago", "Paris", "Lyon", "Tokyo"};
    const char *populations[] = {"8.3M", "2.7M", "2.1M", "0.5M", "14M"};

    const char **lists[3];
    size_t lengths[3];
    Dict *nested;

    lists[0] = countries;
    lists[1] = cities;
    lists[2] = populations;

    lengths[0] = sizeof(countries) / sizeof(countries[0]);
    lengths[1] = sizeof(cities) / sizeof(cities[0]);
    lengths[2] = sizeof(populations) / sizeof(populations[0]);

    nested = lists_to_nested_dict(lists, lengths, 3);
    if (nested == NULL) {
        fprintf(stderr, "Failed to build nested dictionary\n");
        return EXIT_FAILURE;
    }

    dict_print(nested, 0);
    dict_free(nested);

    return EXIT_SUCCESS;
}