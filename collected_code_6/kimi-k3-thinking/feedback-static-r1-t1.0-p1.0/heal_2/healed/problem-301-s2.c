#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH ((size_t)16 * 1024 * 1024)

typedef enum {
    VALUE_STRING,
    VALUE_DICT
} ValueType;

typedef struct Dict Dict;

typedef struct {
    char *key;
    ValueType type;
    union {
        char *str;
        Dict *dict;
    } value;
} DictEntry;

struct Dict {
    DictEntry *entries;
    size_t count;
    size_t capacity;
};

static char *duplicate_string(const char *s)
{
    size_t len;
    char *copy;

    if (s == NULL) {
        return NULL;
    }
    len = strnlen(s, MAX_STRING_LENGTH);
    if (len == MAX_STRING_LENGTH) {
        return NULL;
    }
    copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    if (snprintf(copy, len + 1, "%s", s) < 0) {
        free(copy);
        return NULL;
    }
    return copy;
}

Dict *dict_create(void)
{
    Dict *dict = malloc(sizeof(*dict));

    if (dict == NULL) {
        return NULL;
    }
    dict->entries = NULL;
    dict->count = 0;
    dict->capacity = 0;
    return dict;
}

static int dict_reserve(Dict *dict, size_t capacity)
{
    DictEntry *entries;

    if (capacity <= dict->capacity) {
        return 0;
    }
    if (capacity > SIZE_MAX / sizeof(DictEntry)) {
        return -1;
    }
    entries = realloc(dict->entries, capacity * sizeof(DictEntry));
    if (entries == NULL) {
        return -1;
    }
    dict->entries = entries;
    dict->capacity = capacity;
    return 0;
}

static DictEntry *dict_new_entry(Dict *dict, const char *key)
{
    DictEntry *entry;

    if (dict->count == dict->capacity) {
        size_t capacity = (dict->capacity == 0) ? 4 : dict->capacity * 2;

        if (capacity < dict->capacity) {
            return NULL;
        }
        if (dict_reserve(dict, capacity) != 0) {
            return NULL;
        }
    }
    entry = &dict->entries[dict->count];
    entry->key = duplicate_string(key);
    if (entry->key == NULL) {
        return NULL;
    }
    return entry;
}

int dict_add_string(Dict *dict, const char *key, const char *value)
{
    DictEntry *entry;

    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }
    entry = dict_new_entry(dict, key);
    if (entry == NULL) {
        return -1;
    }
    entry->value.str = duplicate_string(value);
    if (entry->value.str == NULL) {
        free(entry->key);
        entry->key = NULL;
        return -1;
    }
    entry->type = VALUE_STRING;
    dict->count++;
    return 0;
}

int dict_add_dict(Dict *dict, const char *key, Dict *value)
{
    DictEntry *entry;

    if (dict == NULL || key == NULL || value == NULL || dict == value) {
        return -1;
    }
    entry = dict_new_entry(dict, key);
    if (entry == NULL) {
        return -1;
    }
    entry->type = VALUE_DICT;
    entry->value.dict = value;
    dict->count++;
    return 0;
}

size_t dict_depth(const Dict *dict)
{
    size_t i;
    size_t max = 0;
    size_t depth;

    if (dict == NULL) {
        return 0;
    }
    for (i = 0; i < dict->count; i++) {
        if (dict->entries[i].type == VALUE_DICT) {
            depth = dict_depth(dict->entries[i].value.dict);
            if (depth > max) {
                max = depth;
            }
        }
    }
    return max + 1;
}

void dict_free(Dict *dict)
{
    size_t i;

    if (dict == NULL) {
        return;
    }
    for (i = 0; i < dict->count; i++) {
        free(dict->entries[i].key);
        if (dict->entries[i].type == VALUE_STRING) {
            free(dict->entries[i].value.str);
        } else {
            dict_free(dict->entries[i].value.dict);
        }
    }
    free(dict->entries);
    free(dict);
}

int main(void)
{
    Dict *root = dict_create();
    Dict *child = dict_create();
    Dict *grandchild = dict_create();
    Dict *sibling = dict_create();
    int ok = 0;

    if (root != NULL && child != NULL && grandchild != NULL && sibling != NULL) {
        if (dict_add_string(root, "name", "root") == 0 &&
            dict_add_string(root, "type", "example") == 0 &&
            dict_add_string(child, "name", "child") == 0 &&
            dict_add_string(grandchild, "name", "grandchild") == 0 &&
            dict_add_string(sibling, "name", "sibling") == 0 &&
            dict_add_dict(child, "data", grandchild) == 0) {
            grandchild = NULL;
            if (dict_add_dict(root, "child", child) == 0) {
                child = NULL;
                if (dict_add_dict(root, "sibling", sibling) == 0) {
                    sibling = NULL;
                    printf("Depth of dictionary: %zu\n", dict_depth(root));
                    ok = 1;
                }
            }
        }
    }

    if (!ok) {
        fprintf(stderr, "Error: failed to build dictionary\n");
    }

    dict_free(root);
    dict_free(child);
    dict_free(grandchild);
    dict_free(sibling);

    return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}