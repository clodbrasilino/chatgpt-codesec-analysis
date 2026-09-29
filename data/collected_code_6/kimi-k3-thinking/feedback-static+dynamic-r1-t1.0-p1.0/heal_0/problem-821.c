#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char *key;
    char *value;
} Entry;

typedef struct {
    Entry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

static void dict_init(Dictionary *dict)
{
    dict->entries = NULL;
    dict->size = 0;
    dict->capacity = 0;
}

static void dict_free(Dictionary *dict)
{
    size_t i;

    if (dict == NULL) {
        return;
    }
    for (i = 0; i < dict->size; i++) {
        free(dict->entries[i].key);
        free(dict->entries[i].value);
    }
    free(dict->entries);
    dict->entries = NULL;
    dict->size = 0;
    dict->capacity = 0;
}

static char *dict_strdup(const char *s)
{
    size_t len;
    char *copy;

    if (s == NULL) {
        return NULL;
    }
    len = strlen(s) + 1;
    copy = malloc(len);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, s, len);
    return copy;
}

static long dict_find(const Dictionary *dict, const char *key)
{
    size_t i;

    for (i = 0; i < dict->size; i++) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            return (long)i;
        }
    }
    return -1;
}

static int dict_set(Dictionary *dict, const char *key, const char *value)
{
    long index;
    char *new_key;
    char *new_value;
    Entry *new_entries;
    size_t new_capacity;

    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }

    index = dict_find(dict, key);
    if (index >= 0) {
        new_value = dict_strdup(value);
        if (new_value == NULL) {
            return -1;
        }
        free(dict->entries[index].value);
        dict->entries[index].value = new_value;
        return 0;
    }

    if (dict->size == dict->capacity) {
        new_capacity = (dict->capacity == 0) ? 8 : dict->capacity * 2;
        if (new_capacity > SIZE_MAX / sizeof(Entry)) {
            return -1;
        }
        new_entries = realloc(dict->entries, new_capacity * sizeof(Entry));
        if (new_entries == NULL) {
            return -1;
        }
        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }

    new_key = dict_strdup(key);
    if (new_key == NULL) {
        return -1;
    }
    new_value = dict_strdup(value);
    if (new_value == NULL) {
        free(new_key);
        return -1;
    }

    dict->entries[dict->size].key = new_key;
    dict->entries[dict->size].value = new_value;
    dict->size++;
    return 0;
}

static const char *dict_get(const Dictionary *dict, const char *key)
{
    long index;

    if (dict == NULL || key == NULL) {
        return NULL;
    }
    index = dict_find(dict, key);
    if (index < 0) {
        return NULL;
    }
    return dict->entries[index].value;
}

int dict_merge(const Dictionary *first, const Dictionary *second, Dictionary *result)
{
    size_t i;

    if (first == NULL || second == NULL || result == NULL) {
        return -1;
    }
    if (result == first || result == second) {
        return -1;
    }

    dict_init(result);

    for (i = 0; i < first->size; i++) {
        if (dict_set(result, first->entries[i].key, first->entries[i].value) != 0) {
            dict_free(result);
            return -1;
        }
    }
    for (i = 0; i < second->size; i++) {
        if (dict_set(result, second->entries[i].key, second->entries[i].value) != 0) {
            dict_free(result);
            return -1;
        }
    }
    return 0;
}

static void dict_print(const Dictionary *dict)
{
    size_t i;

    printf("{");
    for (i = 0; i < dict->size; i++) {
        printf("\"%s\": \"%s\"", dict->entries[i].key, dict->entries[i].value);
        if (i + 1 < dict->size) {
            printf(", ");
        }
    }
    printf("}\n");
}

int main(void)
{
    Dictionary dict_a;
    Dictionary dict_b;
    Dictionary merged;
    int status = EXIT_SUCCESS;

    dict_init(&dict_a);
    dict_init(&dict_b);
    dict_init(&merged);

    if (dict_set(&dict_a, "name", "alice") != 0 ||
        dict_set(&dict_a, "city", "paris") != 0 ||
        dict_set(&dict_a, "lang", "c") != 0 ||
        dict_set(&dict_b, "age", "30") != 0 ||
        dict_set(&dict_b, "city", "lyon") != 0 ||
        dict_set(&dict_b, "os", "linux") != 0) {
        fprintf(stderr, "error: failed to populate dictionaries\n");
        dict_free(&dict_a);
        dict_free(&dict_b);
        return EXIT_FAILURE;
    }

    if (dict_merge(&dict_a, &dict_b, &merged) != 0) {
        fprintf(stderr, "error: failed to merge dictionaries\n");
        dict_free(&dict_a);
        dict_free(&dict_b);
        return EXIT_FAILURE;
    }

    printf("dict a: ");
    dict_print(&dict_a);
    printf("dict b: ");
    dict_print(&dict_b);
    printf("merged: ");
    dict_print(&merged);

    if (dict_get(&merged, "age") == NULL || dict_get(&merged, "lang") == NULL) {
        fprintf(stderr, "error: merge verification failed\n");
        status = EXIT_FAILURE;
    }

    dict_free(&dict_a);
    dict_free(&dict_b);
    dict_free(&merged);

    return status;
}