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

static Dictionary *dict_create(size_t capacity)
{
    Dictionary *dict;

    if (capacity == 0) {
        return NULL;
    }

    dict = malloc(sizeof(*dict));
    if (dict == NULL) {
        return NULL;
    }

    dict->entries = malloc(capacity * sizeof(*dict->entries));
    if (dict->entries == NULL) {
        free(dict);
        return NULL;
    }

    dict->size = 0;
    dict->capacity = capacity;
    return dict;
}

static int dict_set(Dictionary *dict, const char *key, const char *value)
{
    char *key_copy;
    char *value_copy;
    size_t i;

    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }

    for (i = 0; i < dict->size; i++) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            value_copy = strdup(value);
            if (value_copy == NULL) {
                return -1;
            }
            free(dict->entries[i].value);
            dict->entries[i].value = value_copy;
            return 0;
        }
    }

    if (dict->size >= dict->capacity) {
        return -1;
    }

    key_copy = strdup(key);
    if (key_copy == NULL) {
        return -1;
    }

    value_copy = strdup(value);
    if (value_copy == NULL) {
        free(key_copy);
        return -1;
    }

    dict->entries[dict->size].key = key_copy;
    dict->entries[dict->size].value = value_copy;
    dict->size++;
    return 0;
}

static char **dict_get_keys(const Dictionary *dict, size_t *count)
{
    char **keys;
    size_t i;
    size_t j;

    if (dict == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;

    if (dict->size == 0) {
        return NULL;
    }

    keys = malloc(dict->size * sizeof(*keys));
    if (keys == NULL) {
        return NULL;
    }

    for (i = 0; i < dict->size; i++) {
        keys[i] = strdup(dict->entries[i].key);
        if (keys[i] == NULL) {
            for (j = 0; j < i; j++) {
                free(keys[j]);
            }
            free(keys);
            return NULL;
        }
    }

    *count = dict->size;
    return keys;
}

static void free_keys(char **keys, size_t count)
{
    size_t i;

    if (keys == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        free(keys[i]);
    }
    free(keys);
}

static void dict_destroy(Dictionary *dict)
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
    free(dict);
}

int main(void)
{
    Dictionary *dict;
    char **keys;
    size_t count;
    size_t i;

    dict = dict_create(10);
    if (dict == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        return EXIT_FAILURE;
    }

    if (dict_set(dict, "name", "Alice") != 0 ||
        dict_set(dict, "city", "Paris") != 0 ||
        dict_set(dict, "language", "C") != 0) {
        fprintf(stderr, "Failed to insert entries\n");
        dict_destroy(dict);
        return EXIT_FAILURE;
    }

    keys = dict_get_keys(dict, &count);
    if (keys == NULL) {
        fprintf(stderr, "Failed to get keys\n");
        dict_destroy(dict);
        return EXIT_FAILURE;
    }

    printf("Dictionary keys:\n");
    for (i = 0; i < count; i++) {
        printf("  %s\n", keys[i]);
    }

    free_keys(keys, count);
    dict_destroy(dict);

    return EXIT_SUCCESS;
}