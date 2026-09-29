#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Dictionary Dictionary;

typedef enum ValueType {
    VALUE_STRING,
    VALUE_DICT
} ValueType;

typedef struct DictEntry {
    char *key;
    ValueType type;
    union {
        char *string_value;
        Dictionary *dict_value;
    } data;
    struct DictEntry *next;
} DictEntry;

struct Dictionary {
    DictEntry *entries;
};

static char *xstrdup(const char *s)
{
    if (!s) return NULL;
    size_t len = strlen(s);
    char *copy = malloc(len + 1);
    if (!copy) return NULL;
    memcpy(copy, s, len + 1);
    return copy;
}

Dictionary *dict_new(void)
{
    Dictionary *dict = malloc(sizeof(*dict));
    if (!dict) return NULL;
    dict->entries = NULL;
    return dict;
}

static DictEntry *dict_find_entry(const Dictionary *dict, const char *key)
{
    if (!dict || !key) return NULL;
    for (DictEntry *entry = dict->entries; entry; entry = entry->next) {
        if (strcmp(entry->key, key) == 0) return entry;
    }
    return NULL;
}

static void dict_entry_clear_value(DictEntry *entry);

void dict_free(Dictionary *dict)
{
    if (!dict) return;
    DictEntry *entry = dict->entries;
    while (entry) {
        DictEntry *next = entry->next;
        free(entry->key);
        if (entry->type == VALUE_STRING) {
            free(entry->data.string_value);
        } else if (entry->type == VALUE_DICT) {
            dict_free(entry->data.dict_value);
        }
        free(entry);
        entry = next;
    }
    free(dict);
}

static void dict_entry_clear_value(DictEntry *entry)
{
    if (!entry) return;
    if (entry->type == VALUE_STRING) {
        free(entry->data.string_value);
    } else if (entry->type == VALUE_DICT) {
        dict_free(entry->data.dict_value);
    }
}

static int dict_entry_set_string(DictEntry *entry, const char *value)
{
    if (!entry || !value) return 0;
    char *copy = xstrdup(value);
    if (!copy) return 0;
    dict_entry_clear_value(entry);
    entry->type = VALUE_STRING;
    entry->data.string_value = copy;
    return 1;
}

static int dict_entry_set_dict(DictEntry *entry)
{
    if (!entry) return 0;
    Dictionary *sub = dict_new();
    if (!sub) return 0;
    dict_entry_clear_value(entry);
    entry->type = VALUE_DICT;
    entry->data.dict_value = sub;
    return 1;
}

static int dict_add_string(Dictionary *dict, const char *key, const char *value)
{
    if (!dict || !key || !value) return 0;
    DictEntry *entry = malloc(sizeof(*entry));
    if (!entry) return 0;
    entry->key = xstrdup(key);
    if (!entry->key) {
        free(entry);
        return 0;
    }
    entry->data.string_value = xstrdup(value);
    if (!entry->data.string_value) {
        free(entry->key);
        free(entry);
        return 0;
    }
    entry->type = VALUE_STRING;
    entry->next = dict->entries;
    dict->entries = entry;
    return 1;
}

static int dict_add_dict(Dictionary *dict, const char *key, Dictionary *sub_dict)
{
    if (!dict || !key || !sub_dict) return 0;
    DictEntry *entry = malloc(sizeof(*entry));
    if (!entry) return 0;
    entry->key = xstrdup(key);
    if (!entry->key) {
        free(entry);
        return 0;
    }
    entry->type = VALUE_DICT;
    entry->data.dict_value = sub_dict;
    entry->next = dict->entries;
    dict->entries = entry;
    return 1;
}

static int dict_insert_path(Dictionary *root, char **keys, size_t key_count, const char *value)
{
    if (!root || !keys || key_count == 0 || !value) return 0;
    Dictionary *current = root;
    for (size_t i = 0; i < key_count; i++) {
        if (!keys[i]) return 0;
        DictEntry *entry = dict_find_entry(current, keys[i]);
        if (i == key_count - 1) {
            if (entry) {
                return dict_entry_set_string(entry, value);
            }
            return dict_add_string(current, keys[i], value);
        } else {
            if (entry) {
                if (entry->type != VALUE_DICT) {
                    if (!dict_entry_set_dict(entry)) return 0;
                }
                current = entry->data.dict_value;
            } else {
                Dictionary *sub = dict_new();
                if (!sub) return 0;
                if (!dict_add_dict(current, keys[i], sub)) {
                    dict_free(sub);
                    return 0;
                }
                current = sub;
            }
        }
    }
    return 1;
}

Dictionary *lists_to_nested_dictionary(char ***keys, size_t num_levels, size_t num_items, char **values)
{
    if (!keys || num_levels == 0 || !values) return NULL;
    Dictionary *root = dict_new();
    if (!root) return NULL;
    for (size_t i = 0; i < num_items; i++) {
        char **path = malloc(num_levels * sizeof(*path));
        if (!path) {
            dict_free(root);
            return NULL;
        }
        for (size_t level = 0; level < num_levels; level++) {
            if (!keys[level] || !keys[level][i]) {
                free(path);
                dict_free(root);
                return NULL;
            }
            path[level] = keys[level][i];
        }
        if (!values[i]) {
            free(path);
            dict_free(root);
            return NULL;
        }
        if (!dict_insert_path(root, path, num_levels, values[i])) {
            free(path);
            dict_free(root);
            return NULL;
        }
        free(path);
    }
    return root;
}

void dict_print(const Dictionary *dict, int indent)
{
    if (!dict) return;
    for (const DictEntry *entry = dict->entries; entry; entry = entry->next) {
        for (int i = 0; i < indent; i++) {
            printf("  ");
        }
        printf("%s: ", entry->key);
        if (entry->type == VALUE_STRING) {
            printf("%s\n", entry->data.string_value);
        } else if (entry->type == VALUE_DICT) {
            printf("{\n");
            dict_print(entry->data.dict_value, indent + 1);
            for (int i = 0; i < indent; i++) {
                printf("  ");
            }
            printf("}\n");
        }
    }
}

int main(void)
{
    char *level1[] = {"a", "b"};
    char *level2[] = {"c", "d"};
    char *values[] = {"1", "2"};
    char **keys[2];
    keys[0] = level1;
    keys[1] = level2;
    Dictionary *dict = lists_to_nested_dictionary(keys, 2, 2, values);
    if (!dict) {
        fprintf(stderr, "Error: failed to create nested dictionary\n");
        return EXIT_FAILURE;
    }
    dict_print(dict, 0);
    dict_free(dict);
    return EXIT_SUCCESS;
}