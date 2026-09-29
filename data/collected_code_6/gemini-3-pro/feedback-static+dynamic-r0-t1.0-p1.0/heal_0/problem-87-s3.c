#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair *items;
    size_t count;
    size_t capacity;
} Dictionary;

Dictionary* create_dictionary(size_t initial_capacity) {
    if (initial_capacity == 0) return NULL;
    
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (!dict) return NULL;
    
    dict->items = malloc(initial_capacity * sizeof(KeyValuePair));
    if (!dict->items) {
        free(dict);
        return NULL;
    }
    
    dict->count = 0;
    dict->capacity = initial_capacity;
    return dict;
}

void free_dictionary(Dictionary *dict) {
    if (!dict) return;
    
    for (size_t i = 0; i < dict->count; i++) {
        free(dict->items[i].key);
        free(dict->items[i].value);
    }
    free(dict->items);
    free(dict);
}

int add_to_dictionary(Dictionary *dict, const char *key, const char *value) {
    if (!dict || !key || !value) return 0;
    
    if (dict->count >= dict->capacity) {
        size_t new_capacity = dict->capacity * 2;
        KeyValuePair *new_items = realloc(dict->items, new_capacity * sizeof(KeyValuePair));
        if (!new_items) return 0;
        
        dict->items = new_items;
        dict->capacity = new_capacity;
    }
    
    dict->items[dict->count].key = strdup(key);
    if (!dict->items[dict->count].key) return 0;
    
    dict->items[dict->count].value = strdup(value);
    if (!dict->items[dict->count].value) {
        free(dict->items[dict->count].key);
        return 0;
    }
    
    dict->count++;
    return 1;
}

Dictionary* merge_three_dictionaries(Dictionary *dict1, Dictionary *dict2, Dictionary *dict3) {
    if (!dict1 || !dict2 || !dict3) return NULL;
    
    size_t total_capacity = dict1->count + dict2->count + dict3->count;
    Dictionary *merged = create_dictionary(total_capacity > 0 ? total_capacity : 1);
    if (!merged) return NULL;
    
    for (size_t i = 0; i < dict1->count; i++) {
        if (!add_to_dictionary(merged, dict1->items[i].key, dict1->items[i].value)) {
            free_dictionary(merged);
            return NULL;
        }
    }
    
    for (size_t i = 0; i < dict2->count; i++) {
        if (!add_to_dictionary(merged, dict2->items[i].key, dict2->items[i].value)) {
            free_dictionary(merged);
            return NULL;
        }
    }
    
    for (size_t i = 0; i < dict3->count; i++) {
        if (!add_to_dictionary(merged, dict3->items[i].key, dict3->items[i].value)) {
            free_dictionary(merged);
            return NULL;
        }
    }
    
    return merged;
}

int main() {
    Dictionary *dict1 = create_dictionary(10);
    Dictionary *dict2 = create_dictionary(10);
    Dictionary *dict3 = create_dictionary(10);
    
    if (!dict1 || !dict2 || !dict3) {
        free_dictionary(dict1);
        free_dictionary(dict2);
        free_dictionary(dict3);
        return 1;
    }
    
    int success = 1;
    success &= add_to_dictionary(dict1, "key1", "value1");
    success &= add_to_dictionary(dict2, "key2", "value2");
    success &= add_to_dictionary(dict3, "key3", "value3");
    
    if (!success) {
        free_dictionary(dict1);
        free_dictionary(dict2);
        free_dictionary(dict3);
        return 1;
    }
    
    Dictionary *merged_dict = merge_three_dictionaries(dict1, dict2, dict3);
    
    if (merged_dict) {
        for (size_t i = 0; i < merged_dict->count; i++) {
            printf("%s: %s\n", merged_dict->items[i].key, merged_dict->items[i].value);
        }
        free_dictionary(merged_dict);
    }
    
    free_dictionary(dict1);
    free_dictionary(dict2);
    free_dictionary(dict3);
    
    return 0;
}