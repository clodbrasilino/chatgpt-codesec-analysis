#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

static void dict_init(Dictionary *dict, size_t capacity)
{
    dict->entries = NULL;
    dict->size = 0;
    dict->capacity = 0;

    if (capacity > 0) {
        dict->entries = calloc(capacity, sizeof(*dict->entries));
        if (dict->entries != NULL) {
            dict->capacity = capacity;
        }
    }
}

static int dict_add(Dictionary *dict, const char *key, const char *value)
{
    char *key_copy;
    char *value_copy;

    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }
    if (dict->entries == NULL || dict->size >= dict->capacity) {
        return -1;
    }

    key_copy = malloc(strlen(key) + 1);
    if (key_copy == NULL) {
        return -1;
    }
    strcpy(key_copy, key);

    value_copy = malloc(strlen(value) + 1);
    if (value_copy == NULL) {
        free(key_copy);
        return -1;
    }
    strcpy(value_copy, value);

    dict->entries[dict->size].key = key_copy;
    dict->entries[dict->size].value = value_copy;
    dict->size++;

    return 0;
}

static const char *dict_get_key_by_index(const Dictionary *dict, size_t index)
{
    if (dict == NULL || dict->entries == NULL || index >= dict->size) {
        return NULL;
    }
    return dict->entries[index].key;
}

static const char *dict_get_value_by_index(const Dictionary *dict, size_t index)
{
    if (dict == NULL || dict->entries == NULL || index >= dict->size) {
        return NULL;
    }
    return dict->entries[index].value;
}

static void dict_free(Dictionary *dict)
{
    size_t i;

    if (dict == NULL) {
        return;
    }
    if (dict->entries != NULL) {
        for (i = 0; i < dict->size; i++) {
            free(dict->entries[i].key);
            free(dict->entries[i].value);
        }
        free(dict->entries);
        dict->entries = NULL;
    }
    dict->size = 0;
    dict->capacity = 0;
}

int main(void)
{
    Dictionary dict;
    size_t i;
    const char *key;
    const char *value;

    dict_init(&dict, 4);

    if (dict_add(&dict, "name", "Alice") != 0 ||
        dict_add(&dict, "city", "Paris") != 0 ||
        dict_add(&dict, "lang", "C") != 0) {
        fprintf(stderr, "Error: failed to add dictionary entry\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    for (i = 0; i < dict.size; i++) {
        key = dict_get_key_by_index(&dict, i);
        value = dict_get_value_by_index(&dict, i);
        if (key != NULL && value != NULL) {
            printf("[%zu] %s = %s\n", i, key, value);
        }
    }

    key = dict_get_key_by_index(&dict, 10);
    if (key == NULL) {
        printf("Index 10 is out of range\n");
    }

    dict_free(&dict);

    return EXIT_SUCCESS;
}