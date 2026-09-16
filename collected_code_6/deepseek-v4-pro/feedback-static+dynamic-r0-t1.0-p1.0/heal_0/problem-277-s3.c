#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    void *value;
    int value_type;
} Entry;

typedef struct {
    Entry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

typedef int (*FilterFunc)(const void *value, int value_type, void *context);

Dictionary *dict_create(void) {
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (!dict) return NULL;
    dict->size = 0;
    dict->capacity = 4;
    dict->entries = malloc(dict->capacity * sizeof(Entry));
    if (!dict->entries) {
        free(dict);
        return NULL;
    }
    return dict;
}

void dict_destroy(Dictionary *dict) {
    if (!dict) return;
    for (size_t i = 0; i < dict->size; i++) {
        free(dict->entries[i].key);
    }
    free(dict->entries);
    free(dict);
}

int dict_add(Dictionary *dict, const char *key, void *value, int value_type) {
    if (!dict || !key) return -1;
    
    if (dict->size == dict->capacity) {
        size_t new_capacity = dict->capacity * 2;
        Entry *new_entries = realloc(dict->entries, new_capacity * sizeof(Entry));
        if (!new_entries) return -1;
        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }
    
    char *key_copy = malloc(strlen(key) + 1);
    if (!key_copy) return -1;
    strcpy(key_copy, key);
    
    dict->entries[dict->size].key = key_copy;
    dict->entries[dict->size].value = value;
    dict->entries[dict->size].value_type = value_type;
    dict->size++;
    return 0;
}

Dictionary *dict_filter(const Dictionary *dict, FilterFunc filter_func, void *context) {
    if (!dict || !filter_func) return NULL;
    
    Dictionary *filtered = dict_create();
    if (!filtered) return NULL;
    
    for (size_t i = 0; i < dict->size; i++) {
        if (filter_func(dict->entries[i].value, dict->entries[i].value_type, context)) {
            if (dict_add(filtered, dict->entries[i].key, dict->entries[i].value, dict->entries[i].value_type) != 0) {
                dict_destroy(filtered);
                return NULL;
            }
        }
    }
    
    return filtered;
}

int filter_positive_numbers(const void *value, int value_type, void *context) {
    (void)context;
    if (value_type == 0) {
        const int *num = value;
        return *num > 0;
    }
    return 0;
}

int main(void) {
    Dictionary *dict = dict_create();
    if (!dict) return 1;
    
    int v1 = 10;
    int v2 = -5;
    int v3 = 0;
    int v4 = 42;
    int v5 = -100;
    
    dict_add(dict, "one", &v1, 0);
    dict_add(dict, "two", &v2, 0);
    dict_add(dict, "three", &v3, 0);
    dict_add(dict, "four", &v4, 0);
    dict_add(dict, "five", &v5, 0);
    
    Dictionary *filtered = dict_filter(dict, filter_positive_numbers, NULL);
    if (!filtered) {
        dict_destroy(dict);
        return 1;
    }
    
    for (size_t i = 0; i < filtered->size; i++) {
        printf("%s: %d\n", filtered->entries[i].key, *(int *)filtered->entries[i].value);
    }
    
    dict_destroy(filtered);
    dict_destroy(dict);
    
    return 0;
}