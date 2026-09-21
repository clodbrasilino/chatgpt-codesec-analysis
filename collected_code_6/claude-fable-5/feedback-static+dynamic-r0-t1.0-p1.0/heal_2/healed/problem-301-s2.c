#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LEN 4096

typedef enum {
    VALUE_STRING,
    VALUE_DICT
} ValueType;

typedef struct Dict Dict;

typedef struct Entry {
    char *key;
    ValueType type;
    union {
        char *str;
        Dict *dict;
    } value;
} Entry;

struct Dict {
    Entry *entries;
    size_t count;
    size_t capacity;
};

static Dict *dict_create(void)
{
    Dict *d = malloc(sizeof(Dict));
    if (d == NULL) {
        return NULL;
    }
    d->entries = NULL;
    d->count = 0;
    d->capacity = 0;
    return d;
}

static void dict_free(Dict *d)
{
    size_t i;
    if (d == NULL) {
        return;
    }
    for (i = 0; i < d->count; i++) {
        free(d->entries[i].key);
        if (d->entries[i].type == VALUE_STRING) {
            free(d->entries[i].value.str);
        } else {
            dict_free(d->entries[i].value.dict);
        }
    }
    free(d->entries);
    free(d);
}

static int dict_ensure_capacity(Dict *d)
{
    Entry *tmp;
    size_t new_capacity;

    if (d->count < d->capacity) {
        return 0;
    }
    new_capacity = (d->capacity == 0) ? 4 : d->capacity * 2;
    if (new_capacity < d->capacity) {
        return -1;
    }
    if (new_capacity > SIZE_MAX / sizeof(Entry)) {
        return -1;
    }
    tmp = realloc(d->entries, new_capacity * sizeof(Entry));
    if (tmp == NULL) {
        return -1;
    }
    d->entries = tmp;
    d->capacity = new_capacity;
    return 0;
}

static size_t bounded_strlen(const char *s, size_t max_len)
{
    size_t i;
    for (i = 0; i < max_len; i++) {
        if (s[i] == '\0') {
            break;
        }
    }
    return i;
}

static char *dup_string(const char *s)
{
    size_t len;
    size_t i;
    char *copy;

    if (s == NULL) {
        return NULL;
    }
    len = bounded_strlen(s, MAX_STRING_LEN);
    if (len >= MAX_STRING_LEN && s[len] != '\0') {
        return NULL;
    }
    if (len > SIZE_MAX - 1) {
        return NULL;
    }
    copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    for (i = 0; i < len; i++) {
        copy[i] = s[i];
    }
    copy[len] = '\0';
    return copy;
}

static int dict_add_string(Dict *d, const char *key, const char *value)
{
    char *key_copy;
    char *val_copy;

    if (d == NULL || key == NULL || value == NULL) {
        return -1;
    }
    if (dict_ensure_capacity(d) != 0) {
        return -1;
    }
    key_copy = dup_string(key);
    if (key_copy == NULL) {
        return -1;
    }
    val_copy = dup_string(value);
    if (val_copy == NULL) {
        free(key_copy);
        return -1;
    }
    d->entries[d->count].key = key_copy;
    d->entries[d->count].type = VALUE_STRING;
    d->entries[d->count].value.str = val_copy;
    d->count++;
    return 0;
}

static int dict_add_dict(Dict *d, const char *key, Dict *child)
{
    char *key_copy;

    if (d == NULL || key == NULL || child == NULL) {
        return -1;
    }
    if (dict_ensure_capacity(d) != 0) {
        return -1;
    }
    key_copy = dup_string(key);
    if (key_copy == NULL) {
        return -1;
    }
    d->entries[d->count].key = key_copy;
    d->entries[d->count].type = VALUE_DICT;
    d->entries[d->count].value.dict = child;
    d->count++;
    return 0;
}

static size_t dict_depth(const Dict *d)
{
    size_t max_child_depth;
    size_t child_depth;
    size_t i;

    if (d == NULL) {
        return 0;
    }
    max_child_depth = 0;
    for (i = 0; i < d->count; i++) {
        if (d->entries[i].type == VALUE_DICT) {
            child_depth = dict_depth(d->entries[i].value.dict);
            if (child_depth > max_child_depth) {
                max_child_depth = child_depth;
            }
        }
    }
    return 1 + max_child_depth;
}

int main(void)
{
    Dict *root;
    Dict *level2;
    Dict *level3;
    size_t depth;

    root = dict_create();
    if (root == NULL) {
        fprintf(stderr, "Allocation failure\n");
        return EXIT_FAILURE;
    }

    level2 = dict_create();
    if (level2 == NULL) {
        dict_free(root);
        fprintf(stderr, "Allocation failure\n");
        return EXIT_FAILURE;
    }

    level3 = dict_create();
    if (level3 == NULL) {
        dict_free(root);
        dict_free(level2);
        fprintf(stderr, "Allocation failure\n");
        return EXIT_FAILURE;
    }

    if (dict_add_string(level3, "name", "deep_value") != 0) {
        dict_free(root);
        dict_free(level2);
        dict_free(level3);
        fprintf(stderr, "Insertion failure\n");
        return EXIT_FAILURE;
    }

    if (dict_add_dict(level2, "inner", level3) != 0) {
        dict_free(root);
        dict_free(level2);
        dict_free(level3);
        fprintf(stderr, "Insertion failure\n");
        return EXIT_FAILURE;
    }
    level3 = NULL;

    if (dict_add_string(root, "top_key", "top_value") != 0) {
        dict_free(root);
        dict_free(level2);
        fprintf(stderr, "Insertion failure\n");
        return EXIT_FAILURE;
    }

    if (dict_add_dict(root, "nested", level2) != 0) {
        dict_free(root);
        dict_free(level2);
        fprintf(stderr, "Insertion failure\n");
        return EXIT_FAILURE;
    }
    level2 = NULL;

    depth = dict_depth(root);
    printf("Dictionary depth: %zu\n", depth);

    dict_free(root);
    return EXIT_SUCCESS;
}