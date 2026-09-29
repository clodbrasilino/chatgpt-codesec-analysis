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

Dictionary *dict_create(size_t capacity) {
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (!dict) return NULL;
    dict->entries = malloc(capacity * sizeof(DictEntry));
    if (!dict->entries) {
        free(dict);
        return NULL;
    }
    dict->size = 0;
    dict->capacity = capacity;
    return dict;
}

void dict_free(Dictionary *dict) {
    if (!dict) return;
    for (size_t i = 0; i < dict->size; i++) {
        free(dict->entries[i].key);
        free(dict->entries[i].value);
    }
    free(dict->entries);
    free(dict);
}

int dict_insert(Dictionary *dict, const char *key, const char *value) {
    if (!dict || !key || !value) return -1;
    for (size_t i = 0; i < dict->size; i++) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            char *new_value = strdup(value);
            if (!new_value) return -1;
            free(dict->entries[i].value);
            dict->entries[i].value = new_value;
            return 0;
        }
    }
    if (dict->size >= dict->capacity) {
        size_t new_capacity = dict->capacity * 2;
        DictEntry *new_entries = realloc(dict->entries, new_capacity * sizeof(DictEntry));
        if (!new_entries) return -1;
        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }
    char *new_key = strdup(key);
    if (!new_key) return -1;
    char *new_value = strdup(value);
    if (!new_value) {
        free(new_key);
        return -1;
    }
    dict->entries[dict->size].key = new_key;
    dict->entries[dict->size].value = new_value;
    dict->size++;
    return 0;
}

Dictionary *dict_merge(const Dictionary *dict1, const Dictionary *dict2) {
    if (!dict1 || !dict2) return NULL;
    size_t total_capacity = dict1->size + dict2->size;
    if (total_capacity == 0) total_capacity = 1;
    Dictionary *merged = dict_create(total_capacity);
    if (!merged) return NULL;
    for (size_t i = 0; i < dict1->size; i++) {
        if (dict_insert(merged, dict1->entries[i].key, dict1->entries[i].value) != 0) {
            dict_free(merged);
            return NULL;
        }
    }
    for (size_t i = 0; i < dict2->size; i++) {
        if (dict_insert(merged, dict2->entries[i].key, dict2->entries[i].value) != 0) {
            dict_free(merged);
            return NULL;
        }
    }
    return merged;
}

int main(void) {
    Dictionary *d1 = dict_create(4);
    Dictionary *d2 = dict_create(4);
    if (!d1 || !d2) {
        dict_free(d1);
        dict_free(d2);
        return EXIT_FAILURE;
    }
    dict_insert(d1, "a", "1");
    dict_insert(d1, "b", "2");
    dict_insert(d2, "b", "3");
    dict_insert(d2, "c", "4");
    Dictionary *merged = dict_merge(d1, d2);
    if (!merged) {
        dict_free(d1);
        dict_free(d2);
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < merged->size; i++) {
        printf("%s: %s\n", merged->entries[i].key, merged->entries[i].value);
    }
    dict_free(d1);
    dict_free(d2);
    dict_free(merged);
    return EXIT_SUCCESS;
}